#include <iostream>
#include <cstdlib>
#include "time.h"


struct Ball {
    int x;
    int y;
    unsigned direction; // 1=NE, 2=SE, 3=SO, 4=NO
};
struct Game {
    char matrix[20][50]; // Il campo di gioco
    int points; // Punteggio del giocatore
    std::string name; // Nome del giocatore
    char skin; // Iniziale del giocatore, da usare come pedina
    int x; // Posizione in orizzontale della pedina
    Ball ball; // Palla in questione
};


void wallTouched(Game &game_, unsigned wall) {
    // 0=paddle, 1=top, 2=left, 3=bottom, 4=right
    switch (wall) {
        case 0:
            if (game_.ball.direction == 1)
                game_.ball.direction = 2;
            else
                game_.ball.direction = 3;
        // case 1:  The ball touched the upper wall, the user lost
        case 2:
            if (game_.ball.direction == 3)
                game_.ball.direction = 2;
            else
                game_.ball.direction = 3;
        case 3:
            if (game_.ball.direction == 3)
                game_.ball.direction = 1;
            else
                game_.ball.direction = 4;
        case 4:
            if (game_.ball.direction == 1)
                game_.ball.direction = 4;
            else
                game_.ball.direction = 1;
    }
}


void moveBall(Game &game_) {
    switch (game_.ball.direction) {
        case 1:
            if (game_.ball.y == 0) {
                wallTouched(game_, 1);
                return;
            } else if (game_.ball.x == 48) {
                wallTouched(game_, 4);
                return;
            } else if (game_.ball.y == 4) {
                if (game_.ball.x == game_.x)
                    wallTouched(game_, 0);
                    return;
            } else {
                game_.ball.x++;
                game_.ball.y--;
            }
        case 2:
            if (game_.ball.y == 19) {
                wallTouched(game_, 3);
                return;
            } else if (game_.ball.x == 48) {
                wallTouched(game_, 4);
                return;
            } else {
                game_.ball.x++;
                game_.ball.y++;
            }
        case 3:
            if (game_.ball.y == 19) {
                wallTouched(game_, 3);
                return;
            } else if (game_.ball.x == 1) {
                wallTouched(game_, 2);
                return;
            } else {
                game_.ball.x--;
                game_.ball.y++;
            }
        case 4:
            if (game_.ball.y == 0) {
                wallTouched(game_, 1);
                return;
            } else if (game_.ball.x == 1) {
                wallTouched(game_, 2);
                return;
            } else if (game_.ball.y == 4) {
                if (game_.ball.x == game_.x)
                    wallTouched(game_, 0);
                    return;
            } else {
                game_.ball.x--;
                game_.ball.y--;
            }
    }
}


bool check(Game &game_) {
    if (game_.ball.y == 0)
        return true;
    return false;
}


void processMove(Game &game_, std::string move) {
	if (move == "d" or move == "D")
        game_.x++;
    if (move == "s" or move == "S")
        game_.x--;
    
    // Effetto pacman
    if (game_.x == 49)
        game_.x = 1;
    if (game_.x == 0)
        game_.x = 48;
}


void updateMatrix(Game &game_) {
    for (int j = 0; j < 50; j++)
        game_.matrix[3][j] == ' ';
    for (int j = 0; j < 50; j++) {
        for (int i = 0; i < 20; i++)
            game_.matrix[i][j] = ' ';
    }
    for (int i = 0; i < 20; i++) {
        game_.matrix[i][0] = '#';
        game_.matrix[i][49] = '#';
    }
    game_.matrix[3][game_.x] = game_.skin;
    game_.matrix[game_.ball.y][game_.ball.x] = 'O';
}


void printMatrix(char m[20][50]) {
	system("cls");
	for (int i = 0; i < 50; i++)
		std::cout << '#';
	std::cout << std::endl;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 50; j++)
			std::cout << m[i][j];
		std::cout << std::endl;
	}
	for (int i = 0; i < 50; i++)
		std::cout << '#';
    std::cout << std::endl;
    // std::cout << std::endl << "Points: " << game_.points << std::endl;
}


bool newGame() {
    char answer;
    std::cout << "Play again? (y/n)" << std::endl << ">";
    std::cin >> answer;

    switch (answer) {
        case 'y': case 'Y':
            return true;
        case 'n': case 'N':
            return false;
        default:
            std::cout << "Invalid input" << std::endl;
            return false;
    }
}