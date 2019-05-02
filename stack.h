//
// Created by jacel on 4/25/2019.
//

#ifndef INC_3D_GRAPHICS_STACK_H
#define INC_3D_GRAPHICS_STACK_H

#include "disk.h"
#include "vector"


class Stack {
public:
    std::vector<Disk*> myDisks;
    Disk *topDisk;

    int topDiskIndex;

    point base;

    int ID;

    Stack(int id);

    bool addDisk(Disk *toAdd);

    bool isOverlapping(double x, double y);
    bool isOverlapping(double x);

    bool placeDisk(Disk *toPlace);

    void removeDisk();

    void draw();

    bool isGameOver(int numDisks);

};


#endif //INC_3D_GRAPHICS_STACK_H
