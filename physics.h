#include <math.h>
#include <vector>
#include <stdio.h> 
#include <iostream>
using namespace std;

struct Vect {
    float x;
    float y;
};

struct Ball {
    Vect velocity;
    Vect position;
    int w = 1;
    int r=49/2;
};

Vect center = {.x=960,.y=540};

Ball updatePhysics(Ball ball, Ball* balls,int index){
    ball.velocity.x += 0.0001f*(center.x - ball.position.x);
    ball.velocity.y += 0.0001f*(center.y - ball.position.y);

    printf("velx: %f\n",ball.velocity.x);
    
    bool touching = false;
    for (int i=0;i<5;i++) {
        if (i==index){
            continue;
        }
        Vect col = {.x=ball.position.x-balls[i].position.x,.y=ball.position.y-balls[i].position.y};
        float d = sqrt(pow(col.x,2)+pow(col.y,2));
        printf("D: %f\n",d);
        if (d < 49){
            touching = true;
            Vect axe = {.x=col.x/d,.y=col.y/d};
            ball.position={.x=ball.position.x+0.5*(49-d)*axe.x,.y=ball.position.y+0.5*(49-d)*axe.y};
            balls[i].position={.x=balls[i].position.x+0.5*(49-d)*axe.x,.y=balls[i].position.y+0.5*(49-d)*axe.y};
        }
        else {
        }
    }
    if (!touching) {
        ball.position={.x=ball.position.x+ball.velocity.x,.y=ball.position.y+ball.velocity.y};
    }
    return ball;
}
