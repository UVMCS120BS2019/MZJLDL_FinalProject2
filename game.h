//
// Created by jacel on 4/25/2019.
//

#ifndef INC_3D_GRAPHICS_GAME_H
#define INC_3D_GRAPHICS_GAME_H

using namespace std;
#include <string>
#include "graphics.h"

class Game {
public:
    void drawStart();
    void drawGame();
    void drawEnd();

    void drawString(string label, int x, int y);
};


#endif //INC_3D_GRAPHICS_GAME_H
