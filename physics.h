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
    Vect velocity = {.x=200,.y=200};
    Vect position;
    int w = 1;
    int r=49/2;
};

Vect center = {.x=960,.y=540};
float friction=0.99;

Ball updatePhysics(Ball ball, Ball* balls,int index,int ball_count){
    ball.velocity.x += 0.0001f*(center.x - ball.position.x);
    ball.velocity.y += 0.0001f*(center.y - ball.position.y);

    bool touching = false;
    for (int i=0;i<ball_count;i++) {
        if (i==index){
            continue;
        }
        Vect col = {.x=ball.position.x-balls[i].position.x,.y=ball.position.y-balls[i].position.y};
        float d = sqrt(pow(col.x,2)+pow(col.y,2));
        int min_dist=(ball.r+balls[i].r);
        if (d < min_dist){
            touching = true;
            Vect axe = {.x=col.x/d,.y=col.y/d};
            ball.position={.x=ball.position.x+0.5*(min_dist-d)*axe.x,.y=ball.position.y+0.5*(min_dist-d)*axe.y};
            balls[i].position={.x=balls[i].position.x-0.5*(min_dist-d)*axe.x,.y=balls[i].position.y-0.5*(min_dist-d)*axe.y};
            Vect diff={.x=(ball.velocity.x-balls[i].velocity.x),.y=(ball.velocity.y-balls[i].velocity.y)};
            ball.velocity={.x=ball.velocity.x-diff.x*friction,.y=ball.velocity.y-diff.y*friction};
            balls[i].velocity={.x=balls[i].velocity.x+diff.x*friction,.y=balls[i].velocity.y+diff.y*friction};
        }
    }
    ball.position={.x=ball.position.x+ball.velocity.x,.y=ball.position.y+ball.velocity.y};
    ball.velocity={.x=ball.velocity.x*0.9999,.y=ball.velocity.y*0.9999};
    return ball;
}
