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

Button replay(Quad({1,.5,.5},{400,250},100,100),"Replay");
Button restart(Quad({1,.3,.3},{400,30},75,50),"Restart");


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

void init() {
    width = Game::width;
    height = Game::height;
    srand(time(0));

    stacks.push_back(&stack1);
    stacks.push_back(&stack2);
    stacks.push_back(&stack3);


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
            game.drawStart();

            break;
        }
        case state::play: {
            game.drawGame();
            for (int j = 0; j < allDisks.size(); ++j) {
                allDisks[j]->selectable = true;
            }
            for (int i = 0; i < stacks.size(); ++i) {
                stacks[i]->draw();
            }
            game.displayMoves(counter);
            restart.draw();
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


            //if (game.userWon()) {
            //    confetti.draw();
            //}
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
     // uses 'a' to manually switch between screens
     else if (key == 97) {
     	if (programState == state::start) {
     		programState = state::play;
     	} else if (programState == state::play) {
     		programState = state::end;
     	} else {
     		programState = state::start;
     	}
     }
     // Hit Enter at the start screen to begin the game
    if (programState == state::start) {
        if (key == 13) {
            programState = state::play;
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
    Disk debug1, debug2, debug3;
    debug1 = disk1;
    debug2 = disk2;
    debug3 = disk3;
    for (int i = 0; i < allDisks.size(); ++i) {
        if (allDisks[i]->selected){
            allDisks[i]->center = {dX,dY};
            allDisks[i]->draw();
            break;
        }
    }
    if (replay.isOverlapping(x, y)) {
        replay.hover();
    } else {
        replay.release();
    }
    if (restart.isOverlapping(x, y)) {
        restart.hover();
    } else {
        restart.release();
    }
    
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if(programState == state::end){
        if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON && replay.isOverlapping(x, y)) {
            replay.pressDown();
        } else if(replay.isOverlapping(x, y)) {
            replay.hover();
        } else{
            replay.release();
        }

        if (state == GLUT_UP && button == GLUT_LEFT_BUTTON && replay.isOverlapping(x, y)) {
            replay.click(setProgramStateStart);
        }
    }

    if(programState == state::play){
        if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON && restart.isOverlapping(x, y)) {
            restart.pressDown();
        } else if(replay.isOverlapping(x, y)) {
            restart.hover();
        } else{
            restart.release();
        }

        if (state == GLUT_UP && button == GLUT_LEFT_BUTTON && restart.isOverlapping(x, y)) {
            restart.click(setProgramStateGame);
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
            Disk *debug1, *debug2, *debug3;
            debug1 = &disk1;
            debug2 = &disk2;
            debug3 = &disk3;
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
