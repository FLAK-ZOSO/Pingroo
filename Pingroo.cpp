#include <future>
#include <thread>
#include <limits>
#include "game.hpp"


std::string inputMove() {
	std::string move;
	if (std::cin >> move) return move;
}


Game game() { // Ritorna l'oggetto Game
    Game myGame;
    myGame.ball.direction = 2;
    myGame.ball.x = 24;
    myGame.ball.y = 15;
    myGame.points = 0;
    srand(time(0));

    // Durata del frame
    long double frame_duration_;
    std::cout << "Frame duration [double]: ";
    std::cin >> frame_duration_;
    if (frame_duration_ < 0.02)
        frame_duration_ = 0.02;
    auto frame_duration = std::chrono::duration<long double> (frame_duration_);

    // Colore
    std::string color;
    std::cout << "Color [string]: ";
    std::cin >> color;
    if (color == "matrix")
        system("color 0A");
    else if (color == "red")
        system("color 0C");
    else if (color == "fucsia")
        system("color DE");
    
    // Skin
    std::cout << "Paddle skin [char]: ";
    std::cin >> myGame.skin;
    std::cout << "Ball skin [char]: ";
    std::cin >> myGame.ball.skin;

    // Riempio la matrice, che in partenza è vuota
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 50; j++)
            myGame.matrix[i][j] = ' ';
        myGame.matrix[i][0] = '#';
        myGame.matrix[i][49] = '#';
    }

    // Start
    myGame.x = 24;
    myGame.matrix[3][24] = myGame.skin;
    myGame.matrix[myGame.ball.y][myGame.ball.x] = myGame.ball.skin;

    bool end = false;
    while (true) {
        using namespace std::literals;
	    auto input = std::async(std::launch::async, inputMove);
        while (input.wait_for(frame_duration) != std::future_status::ready) {
            // Controlliamo se ha perso
            if (check(myGame)) { // The user lost
                end = true;
                break;
            }
            // Muoviamo la pallina
            moveBall(myGame);
            // Aggiorniamo la matrice
            updateMatrix(myGame);
            // Aggiorniamo l'immagine
            printMatrix(myGame.matrix);
            myGame.points++;
        }
        processMove(myGame, input.get());
        if (end) break;
    }
    updateMatrix(myGame);
    printMatrix(myGame.matrix);
	return myGame;
}


int main() {
    do {
        Game game_ = game();
        system("cls");
        std::cout << "Points: " << game_.points << std::endl;
        std::cout << std::endl << std::endl;
    } while (newGame());
}