//
// Created by jacel on 4/25/2019.
//

#ifndef INC_3D_GRAPHICS_DISK_H
#define INC_3D_GRAPHICS_DISK_H

#include "quad.h"

class Disk {
public:
    point center;
    color myColor;
    int ID;
    int size;
    bool selected = false;
    bool selectable = false;

    Disk();

    Disk(int size, int id, double x, double y);

    bool isOverlapping(double x, double y);

    void draw();
};


#endif //INC_3D_GRAPHICS_DISK_H
