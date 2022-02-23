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

    // Colore
    std::string color;
    std::cout << "Color: ";
    std::cin >> color;
    if (color == "matrix")
        system("color 0A");
    if (color == "red")
        system("color 0C");
    if (color == "fucsia")
        system("color DE");

    // Riempio la matrice, che in partenza è vuota
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 50; j++)
            myGame.matrix[i][j] = ' ';
        myGame.matrix[i][0] = '#';
        myGame.matrix[i][49] = '#';
    }

    // Start
    myGame.skin = '-';
    myGame.x = 24;
    myGame.matrix[3][24] = myGame.skin;
    myGame.matrix[myGame.ball.y][myGame.ball.x] = 'O';

    bool end = false;
    while (true) {
        // Enable standard literals as 2s and ""s.
        using namespace std::literals;
    	// Eseguo la funzione inputMove in modo asincrono
	    auto input = std::async(std::launch::async, inputMove);
	    
        // Continue execution in main thread.
        while (input.wait_for(0.2s) != std::future_status::ready) {
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
    return 0;
}