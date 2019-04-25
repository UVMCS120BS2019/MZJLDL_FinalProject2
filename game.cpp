//
// Created by jacel on 4/25/2019.
//

#include "game.h"

void Game::drawStart() {

}

void Game::drawGame() {

}

void Game::drawEnd() {

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