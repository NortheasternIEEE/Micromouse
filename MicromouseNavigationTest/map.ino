//
//  map.c
//  MicroMouse
//
//  Created by Matthew Murphy on 2/10/16.
//  Copyright © 2016 Northeastern-IEEE. All rights reserved.
//

#include "map.h"
#include "Arduino.h"


void map(location *position, node param[mazeSize][mazeSize]) {
    int x = position->x;
    int y = position->y;
    // If you have already been to this node return
    if (param[x][y].mapped) {return;}
    //printf("X = %d, Y = %d\n",x, y);
    direction options[4];
    // Visit the node to get all the relevant information you need
    visit(&param[x][y]);
    // Get all the possible ways the mouse can move from this cell
    getSuccessors(param[x][y], options);
    getSuccessors1(param, param[x][y], options, x, y);
    Serial.println("Made it past get successors");
    for (int i = 0; i < 4; i++) {
         // Move the mouse that direction and update its location
         if (canMove(position, options[i], param)) {
                Serial.println("We can move here");
             moveRobot(position, options[i]);
    //         printf("Moved to: ");
    //         printf("X = %d, Y = %d\n",position->x, position->y);
    //         // Map the maze starting from that new location
    //         map(position, param); // COME OUT HERE
    //         // GO BACK - Not implemented yet
    //         moveRobot(position, reverse(options[i]));
         }
    //     printf("Go back to: ");
    //     printf("X = %d, Y = %d\n",position->x, position->y);
     }
}


bool canMove(location *p, direction d, node param[mazeSize][mazeSize]) {
    location temp;
    temp.x = p->x;
    temp.y = p->y;
    switch (d) {
        case RIGHT:
            temp.x = temp.x + 1;
            if (param[temp.x][temp.y].mapped) {
                return false;
            }
            return true;
            break;
        case LEFT:
            temp.x = temp.x - 1;
            if (param[temp.x][temp.y].mapped) {
                return false;
            }
            return true;
            break;
        case UP:
            temp.y = temp.y + 1;
            if (param[temp.x][temp.y].mapped) {
                return false;
            }
            return true;
            break;
        case DOWN:
            temp.y = temp.y - 1;
            if (param[temp.x][temp.y].mapped) {
                return false;
            }
            return true;
            break;
        case STOP:
            return false;
        default:
            return false;
            break;
    }
    
}

void visit(node *n) {
    n->mapped = true;
    sensors_event_t event;
    bno.getEvent(&event);
    
    // FIGURE OUT ALL THE SENOR SHIT
    float left = getLeftDistance();
    if(left < 100 && left > 10) {
        if (x > 80 || < 100) {
          n->up = false;
        }
        else if (x > 170 || x < 190) {
          x->right = false;
        }
        else if (x > 260 || x < 280) {
          x->down = false;
        }
        else if (x > 350 || x < 10) {
          x->left = false;
        }
    }
    float right = getRightDistance();
    if(right < 100 && right > 10) {
        if (x > 80 || < 100) {
          n->up = false;
        }
        else if (x > 170 || x < 190) {
          x->right = false;
        }
        else if (x > 260 || x < 280) {
          x->down = false;
        }
        else if (x > 350 || x < 10) {
          x->left = false;
        }
    }
    float front = 0;
    for(int i=0; i<5; i++) {
        front += getFrontDistance();
        delay(100);
    }
    front /= 5;
    if(front <= TURN_BEGIN_THRESHOLD) {
        if (x > 80 || < 100) {
          n->up = false;
        }
        else if (x > 170 || x < 190) {
          x->right = false;
        }
        else if (x > 260 || x < 280) {
          x->down = false;
        }
        else if (x > 350 || x < 10) {
          x->left = false;
        }
    }
}

void getSuccessors(node v, direction array[4]) {
    array[0] = goRight(v);
    array[1] = goLeft(v);
    array[2] = goUp(v);
    array[3] = goDown(v);
    // SOME FANCY SHIT THAT CHANGES STUFF AROUND
}

void getSuccessors1(node param[mazeSize][mazeSize], node v, direction array[4], int x, int y) {
    getSuccessors(v, array);
    for (int i = 0; i < 4; i++) {
        switch (array[i]) {
            case RIGHT:
                x = x + 1;
                if (param[x][y].mapped) {
                    array[i] = STOP;
                }
                x = x - 1;
                break;
            case LEFT:
                x = x - 1;
                if (param[x][y].mapped) {
                    array[i] = STOP;
                }
                x = x + 1;
                break;
            case UP:
                y = y + 1;
                if (param[x][y].mapped) {
                    array[i] = STOP;
                }
                y = y - 1;
                break;
            case DOWN:
                y = y - 1;
                if (param[x][y].mapped) {
                    array[i] = STOP;
                }
                y = y + 1;
                break;
            default:
                break;
        }
    }
}
