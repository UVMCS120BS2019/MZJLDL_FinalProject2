//
// Created by jacel on 4/25/2019.
//

#ifndef MZJLDL_FINALPROJECT2_CONFETTI_H
#define MZJLDL_FINALPROJECT2_CONFETTI_H


#include "quad.h"
#include "shape.h"
#include "circle.h"
#include "game.h"
#include <time.h>
#include <vector>
#include <memory>

class Confetti {
private:
    // size of the two shape types
    const static int QUAD_SIZE = 6;
    const static int RADIUS = 10;
    std::vector<std::unique_ptr<Shape>> confetti;

public:
    // constructor
    Confetti();

    // draw the confetti on the screen
    void draw();

    // populate the vector of shapes
    void spawnConfetti();

    // move the confetti down and jitter to the side
    void timestep();
};

#endif //MZJLDL_FINALPROJECT2_CONFETTI_H
