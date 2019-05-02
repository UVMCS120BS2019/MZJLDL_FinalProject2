//
// Created by jacel on 4/25/2019.
//

#ifndef MZJLDL_FINALPROJECT2_CIRCLE_H
#define MZJLDL_FINALPROJECT2_CIRCLE_H

#include "shape.h"
#include <iostream>
#include "graphics.h"
#define _USE_MATH_DEFINES
#include <math.h>

class Circle : public Shape {

private:
    int radius;

public:
    // constructors
    Circle();
    Circle(int radius);
    Circle(int x, int y, int radius);

    // getters
    int getRadius() const;

    int getLeftX() const;
    int getRightX() const;
    int getTopY() const;
    int getBottomY() const;
    int getCenterY() const;


    // must be >= 0
    void setRadius(int radius);

    virtual void draw() const override;

    // for overriding << operator
    std::ostream& doprint(std::ostream& out) const override;
};

#endif //MZJLDL_FINALPROJECT2_CIRCLE_H
