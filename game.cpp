//
// Created by jacel on 4/25/2019.
//

#include "game.h"
#include "confetti.h"
Game::Game() : box({1, 0, 0}, {350, 220}, 200, 50),
                playAgainButton(box, "Play Again?") {

}
void Game::drawStart() {
    drawString("This is the Start Screen", 200, 150);
}

void Game::drawGame() {
    drawString("This is the Game Screen", 200, 150);
}

void Game::drawEnd() {
    drawString("This is the End Screen", 200, 150);
}

void Game::displayMoves(int counter) {
    string moves = to_string(counter);
    drawMoves("Moves: ", moves);
}

void Game::drawMoves(string message, string moves){
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2i(225, 30);
    // draw each part of message
    for (char &letter : message) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, letter);
    }
    for (char &letter : moves) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, letter);
    }
}

void Game::restartGame() {
    
}

// Function to draw strings
void Game::drawString(string label, int x, int y) {
    glColor3f(1.0f, 0.0f, 0.0f);
    glRasterPos2i(x, y);
    for (char &letter : label)  {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, letter);
    }
    glEnd();
}