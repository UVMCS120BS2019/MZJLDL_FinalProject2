#include "graphics.h"
#include "button.h"
#include <iostream>
#include "confetti.h"
#include "game.h"
#include <vector>
#include <time.h>
#include "shape.h"
#include "disk.h"
#include "stack.h"

using namespace std;

GLdouble width, height;
int wd;
int lastTick;
Game game;
int counter = 0;
int numDisks = 3;
Confetti confetti;
vector<Stack*> stacks;
static Stack stack1(1);
static Stack stack2(2);
static Stack stack3(3);

static Stack stack1a(1);
static Stack stack2a(2);
static Stack stack3a(3);

vector<Disk*> allDisks;
static Disk disk1(80, 0, 0,0);
static Disk disk2(70, 1, 0,0);
static Disk disk3(60, 2, 0,0);
static Disk disk4(50, 3, 0,0);
static Disk disk5(40, 4, 0,0);
static Disk disk6(30, 5, 0,0);
static Disk disk7(20, 6, 0,0);
static Disk disk8(10, 7, 0,0);

bool ringSelected = false;
Stack* previousStack = nullptr;
point returnPos;

vector<Button*> allButtons;
vector<Button*> numberButtons;

Button replay(Quad({1,.5,.5},{400,250},100,100),"Replay");
Button restart(Quad({1,.3,.3},{400,30},75,50),"Restart");
Button three(Quad({0,1,1},{150,150},75,50),"3",3);
Button four(Quad({0,1,1},{250,150},75,50),"4",4);
Button five(Quad({0,1,1},{350,150},75,50),"5",5);
Button six(Quad({0,1,1},{450,150},75,50),"6",6);
Button seven(Quad({0,1,1},{550,150},75,50),"7",7);
Button eight(Quad({0,1,1},{650,150},75,50),"8",8);

enum state {start, play, end};
state programState;

// go to start screen
void setProgramStateStart() {
    programState = state::start;
    counter = 0;
}

void setProgramStateGame() {
    init();
    counter = 0;
}

void startAllDisksFresh(){
    allDisks.clear();
    stack1.clear();
    stack2.clear();
    stack3.clear();
    if (numDisks > 8){
        numDisks = 8;
    }
    switch (numDisks){
        case 8:
            stack1.addDisk(&disk1);
            allDisks.push_back(&disk1);
        case 7:
            stack1.addDisk(&disk2);
            allDisks.push_back(&disk2);
        case 6:
            stack1.addDisk(&disk3);
            allDisks.push_back(&disk3);
        case 5:
            stack1.addDisk(&disk4);
            allDisks.push_back(&disk4);
        case 4:
            stack1.addDisk(&disk5);
            allDisks.push_back(&disk5);
        case 3:
            stack1.addDisk(&disk6);
            allDisks.push_back(&disk6);
            stack1.addDisk(&disk7);
            allDisks.push_back(&disk7);
            stack1.addDisk(&disk8);
            allDisks.push_back(&disk8);
    }
}

void init() {
    width = Game::width;
    height = Game::height;
    srand(time(0));

    stacks.push_back(&stack1);
    stacks.push_back(&stack2);
    stacks.push_back(&stack3);

    allButtons.push_back(&replay);
    allButtons.push_back(&restart);
    allButtons.push_back(&three);
    allButtons.push_back(&four);
    allButtons.push_back(&five);
    allButtons.push_back(&six);
    allButtons.push_back(&seven);
    allButtons.push_back(&eight);

    numberButtons.push_back(&three);
    numberButtons.push_back(&four);
    numberButtons.push_back(&five);
    numberButtons.push_back(&six);
    numberButtons.push_back(&seven);
    numberButtons.push_back(&eight);

}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);
    
    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);
    
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    /*
     * Draw here
     */
    switch(programState) {
        case state::start: {
            init();
            stack1a.draw();
            stack2a.draw();
            stack3a.draw();

            three.draw();
            four.draw();
            five.draw();
            six.draw();
            seven.draw();
            eight.draw();

            game.drawStart();

            break;
        }
        case state::play: {
            for (int j = 0; j < allDisks.size(); ++j) {
                allDisks[j]->selectable = true;
            }
            for (int i = 0; i < stacks.size(); ++i) {
                stacks[i]->draw();
            }
            game.displayMoves(counter);
            restart.draw();

            // Draw minimum moves
            switch(numDisks) {
                case 3:
                    game.drawString("Minimum Moves: 7", 470, 40);
                    break;
                case 4:
                    game.drawString("Minimum Moves: 15", 470, 40);
                    break;
                case 5:
                    game.drawString("Minimum Moves: 31", 470, 40);
                    break;
                case 6:
                    game.drawString("Minimum Moves: 63", 470, 40);
                    break;
                case 7:
                    game.drawString("Minimum Moves: 127", 470, 40);
                    break;
                case 8:
                    game.drawString("Minimum Moves: 255", 470, 40);
                    break;
            }
            break;
        }
        case state::end: {
            game.drawEnd();
            for (int j = 0; j < allDisks.size(); ++j) {
                allDisks[j]->selectable = false;
            }
            confetti.draw();
            replay.draw();
            glFlush();
            break;
        }
    }
    glFlush();  // Render now
    timer(0); // start timer to redraw
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    // Hit Enter at the start screen to begin the game
    if (programState == state::start) {
        if (key == 13) {
            programState = state::play;
            startAllDisksFresh();
        }
    }
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            break;
        case GLUT_KEY_LEFT:
            break;
        case GLUT_KEY_RIGHT:
            break;
        case GLUT_KEY_UP:
            break;
    }
    glutPostRedisplay();
}

void cursor(int x, int y) {
    int dX, dY;
    dX = x;
    dY = y;
    for (int i = 0; i < allDisks.size(); ++i) {
        if (allDisks[i]->selected){
            allDisks[i]->center = {dX,dY};
            allDisks[i]->draw();
            break;
        }
    }

    for(int i = 0; i < allButtons.size(); i++){
        if (allButtons[i]->isOverlapping(x, y)) {
            allButtons[i]->hover();
        } else {
            allButtons[i]->release();
        }
    }
    
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if(programState == state::start) {
        for (int i = 0; i < numberButtons.size(); i++) {
            if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON && numberButtons[i]->isOverlapping(x, y)) {
                numberButtons[i]->pressDown();
                numDisks = numberButtons[i]->numDisks;
                for (int j = i+1; j < numberButtons.size(); ++j) {
                    numberButtons[j]->clickStatus = false;
                    numberButtons[j]->release();
                }
            }
        }
    }

    if(programState == state::play){
        if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON && restart.isOverlapping(x, y)) {
            restart.pressDown();
            startAllDisksFresh();
        }else {
            restart.release();
        }
        if (state == GLUT_UP && button == GLUT_LEFT_BUTTON && restart.isOverlapping(x, y)) {
            restart.click(setProgramStateGame);
        }
    }

    if(programState == state::end){
        if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON && replay.isOverlapping(x, y)) {
            replay.pressDown();
        }else{
            replay.release();
        }

        if (state == GLUT_UP && button == GLUT_LEFT_BUTTON && replay.isOverlapping(x, y)) {
            replay.click(setProgramStateStart);
            for (int k = 1; k < numberButtons.size(); ++k) {
                numberButtons[k]->clickStatus = false;
                numberButtons[k]->release();
            }
        }
    }

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if (ringSelected){
            ++counter;
            for (int i = 0; i < allDisks.size(); ++i) {
                if (allDisks[i]->selected){
                    for (int j = 0; j < stacks.size(); ++j) {
                        if (stacks[j]->isOverlapping(x)){
                            if (stacks[j]->placeDisk(allDisks[i])) {
                                ringSelected = false;
                                previousStack->removeDisk();
                                previousStack = nullptr;
                                if (stack3.isGameOver(numDisks)){
                                    programState = state::end;
                                }
                                break;
                            } else {
                                allDisks[i]->center = returnPos;
                                allDisks[i]->selected = false;
                                previousStack = nullptr;
                                ringSelected = false;
                                break;
                            }
                        }
                    }
                }
            }
        } else {
            for (int i = 0; i < stacks.size(); ++i) {
                if (stacks[i]->isOverlapping(x, y)) {
                    returnPos = stacks[i]->topDisk->center;
                    ringSelected = true;
                    previousStack = stacks[i];
                    break;
                }
            }
        }
    }
    glutPostRedisplay();
}

void timer(int dummy) {
    int tick = glutGet(GLUT_ELAPSED_TIME);

    // if it's not time to move everything, then don't do anything
    if (tick < lastTick) {
        return;
    }
    // while we're "behind" tick until we're ahead again
    while (tick > lastTick) {
        if (programState == state::end) {
            confetti.timestep();
        }
        // target 45 fps, and wait for us to get there
        lastTick += 1000 / 45;
    }
    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    
    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Tower of Hanoi!" /* title */ );
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();
    
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    
    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);
    
    // handles mouse movement
    glutPassiveMotionFunc(cursor);
    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer
    glutTimerFunc(0, timer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
