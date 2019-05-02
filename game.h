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
private:
    Button playAgainButton;
    //Confetti confetti;
    Quad box;
public:
    static int width;
    static int height;
    void drawStart();
    void drawGame();
    void drawEnd();

    void drawString(string label, int x, int y);

    // play again button
    const Button &getPlayAgainButton() const;
    void setPlayAgainButton(const Button &button);
    void playAgainButtonHover();
    void playAgainButtonRelease();
    void playAgainButtonPressDown();
    void playAgainButtonClick();
};


#endif //INC_3D_GRAPHICS_GAME_H
