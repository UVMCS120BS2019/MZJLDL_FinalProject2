//
// Created by jacel on 4/25/2019.
//

#include "game.h"
#include "confetti.h"
Game::Game() : box({1, 0, 0}, {350, 220}, 200, 50),
                playAgainButton(box, "Play Again?") {

}
void Game::drawStart() {
    drawString("Welcome to Hanoi!", 280, 70);
    drawString("Please hit 'Enter' to Begin", 250, 100);
}

void Game::drawGame() {

}

void Game::drawEnd() {
    drawString("Congratulations! You Won!", 260, 150);
}

void Game::displayMoves(int counter) {
    string moves = to_string(counter);
    drawMoves("Moves: ", moves);
}

void Game::drawMoves(string message, string moves){
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(150, 30);
    // draw each part of message
    for (char &letter : message) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
    }
    for (char &letter : moves) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
    }
}

// Function to draw strings
void Game::drawString(string label, int x, int y) {
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(x, y);
    for (char &letter : label)  {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
    }
    glEnd();
}