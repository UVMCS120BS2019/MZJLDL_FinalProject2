//
// Created by jacel on 4/25/2019.
//

#ifndef INC_3D_GRAPHICS_GAME_H
#define INC_3D_GRAPHICS_GAME_H

using namespace std;
#include <string>
#include "graphics.h"
#include "button.h"
#include "circle.h"
#include "quad.h"
#include "button.h"
#include "confetti.h"
#include "shape.h"

class Game {

public:
    const static int width = 800;
    const static int height = 500;

    void drawStart();
    void drawEnd();

    void displayMoves(int counter);
    void drawMoves(string message, string moves);

    void drawString(string label, int x, int y);

};

#endif //INC_3D_GRAPHICS_GAME_H