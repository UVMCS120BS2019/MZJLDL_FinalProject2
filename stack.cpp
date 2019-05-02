//
// Created by jacel on 4/25/2019.
//

#include "stack.h"
#include "disk.h"
#include "graphics.h"

Stack::Stack(int id){
    this->ID = id;
    this->base.x = this->ID * 200;
    this->base.y = 400;
}

bool Stack::addDisk(Disk *toAdd) {
    topDiskIndex = myDisks.size() - 1;
    toAdd-> selected = false;
    if (myDisks.size() == 0){
        toAdd->center.x = this->base.x;
        toAdd->center.y = this->base.y - 15;
        myDisks.push_back(toAdd);
        this->topDisk = toAdd;
        topDiskIndex += 1;
        return true;
    } else if (toAdd->size < myDisks[topDiskIndex]->size){
        toAdd->center.x = this->base.x;
        toAdd->center.y = this->myDisks[topDiskIndex]->center.y - 20;
        myDisks.push_back(toAdd);
        this->topDisk = toAdd;
        topDiskIndex += 1;
        return true;
    }
    return false;
}

void Stack::removeDisk() {
    try {
        myDisks.pop_back();
        topDiskIndex = (int)myDisks.size() - 1;
        if (myDisks.size() != 0){
            topDisk = myDisks[topDiskIndex];
        } else {
            topDisk = nullptr;
        }
    } catch (...){
        return;
    }
}

void Stack::draw(){
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex2d(this->base.x + 5, this->base.y + 5);
    glVertex2d(this->base.x - 50, this->base.y + 5);
    glVertex2d(this->base.x - 50, this->base.y - 5);
    glVertex2d(this->base.x - 5, this->base.y - 5);
    glVertex2d(this->base.x - 5, this->base.y - 200);
    glVertex2d(this->base.x + 5, this->base.y - 200);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2d(this->base.x + 5, this->base.y + 5);
    glVertex2d(this->base.x + 50, this->base.y + 5);
    glVertex2d(this->base.x + 50, this->base.y - 5);
    glVertex2d(this->base.x + 5, this->base.y - 5);
    glEnd();


    for (int i = 0; i < myDisks.size(); ++i) {
        myDisks[i]->draw();
    }
}

bool Stack::isOverlapping(double x, double y){
    try {
        if (topDisk->isOverlapping(x,y)){
            topDisk->selected = true;
            return true;
        }
    } catch (...) {
        return false;
    }
    return false;
}

bool Stack::isOverlapping(double x) {
    if (x < this->base.x + 50 && x > this->base.x - 50){
        return true;
    }
    return false;
}

bool Stack::placeDisk(Disk *toPlace){
    if (this->topDisk == NULL){
        this->addDisk(toPlace);
        return true;
    } else if (toPlace->size < this->topDisk->size){
        this->addDisk(toPlace);
        return true;
    }
    return false;
}

bool Stack::isGameOver(int numDisks){
    if (this->myDisks.size() == numDisks){
        return true;
    }
    return false;
}

void Stack::clear(){
    this->myDisks.clear();
    this->topDisk = NULL;

}