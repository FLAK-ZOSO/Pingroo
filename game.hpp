#include <iostream>
#include <cstdlib>
#include "time.h"


struct Ball {
    int x;
    int y;
    char skin;
    unsigned direction; // 1=NE, 2=SE, 3=SO, 4=NO
};
struct Game {
    char matrix[20][50]; // Il campo di gioco
    int points; // Punteggio del giocatore
    char skin; // Pedina
    int x; // Posizione in orizzontale della pedina
    Ball ball; // Palla in questione
};


void wallTouched(Game &game_, unsigned wall) {
    // 0=paddle, 1=top, 2=left, 3=bottom, 4=right
    // case 1:  The ball touched the upper wall, the user lost
    if (wall == 0) {
        if (game_.ball.direction == 1)
            game_.ball.direction = 2;
        else if (game_.ball.direction == 4)
            game_.ball.direction = 3;
    } else if (wall == 2) {
        if (game_.ball.direction == 3)
            game_.ball.direction = 2;
        else if (game_.ball.direction == 4)
            game_.ball.direction = 1;
    } else if (wall == 3) {
        if (game_.ball.direction == 3)
            game_.ball.direction = 4;
        else if (game_.ball.direction == 2)
            game_.ball.direction = 1;
    } else if (wall == 4) {
        if (game_.ball.direction == 1)
            game_.ball.direction = 4;
        else if (game_.ball.direction == 2)
            game_.ball.direction = 3;
    }
}


void moveBall(Game &game_) {
    if (game_.ball.direction == 1) {
        game_.ball.x++;
        game_.ball.y--;
        if (game_.ball.y == 0) {
            wallTouched(game_, 1);
        } else if (game_.ball.x == 48) {
            wallTouched(game_, 4);
            return;
        }
        if (game_.ball.y == 3) {
            if (game_.ball.x == game_.x || game_.matrix[3][game_.ball.x] == game_.skin)
                wallTouched(game_, 0);
        }
    } else if (game_.ball.direction == 2) {
        game_.ball.x++;
        game_.ball.y++;
        if (game_.ball.y == 19) {
            wallTouched(game_, 3);
            return;
        } else if (game_.ball.x == 48) {
            wallTouched(game_, 4);
            return;
        }
    } else if (game_.ball.direction == 3) {
        game_.ball.x--;
        game_.ball.y++;
        if (game_.ball.y == 19) {
            wallTouched(game_, 3);
            return;
        } else if (game_.ball.x == 1) {
            wallTouched(game_, 2);
            return;
        }
    } else if (game_.ball.direction == 4) {
        game_.ball.x--;
        game_.ball.y--;
        if (game_.ball.y == 0) {
            wallTouched(game_, 1);
        } else if (game_.ball.x == 1) {
            wallTouched(game_, 2);
            return;
        }
        if (game_.ball.y == 3) {
            if (game_.ball.x == game_.x || game_.matrix[3][game_.ball.x] == game_.skin)
                wallTouched(game_, 0);
        }
    }
}


bool check(Game &game_) {
    return game_.ball.y == 0;
}


void processMove(Game &game_, std::string move) {
	size_t n = std::count(move.begin(), move.end(), 'd');
    int right = static_cast<int>(n);
    n = std::count(move.begin(), move.end(), 'D');
    right += static_cast<int>(n);
    n = std::count(move.begin(), move.end(), 's');
    int left = static_cast<int>(n);
    n = std::count(move.begin(), move.end(), 'S');
    left += static_cast<int>(n);

    for (int i = 0; i < right; i++)
        game_.x++;
    for (int i = 0; i < left; i++)
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
    for (int i = -2; i < 3; i++)
        game_.matrix[3][game_.x-i] = game_.skin;
    for (int i = 0; i < 20; i++) {
        game_.matrix[i][0] = '#';
        game_.matrix[i][49] = '#';
    }
    game_.matrix[game_.ball.y][game_.ball.x] = game_.ball.skin;
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