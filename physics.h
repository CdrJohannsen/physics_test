#include <iostream>
using namespace std;

struct Ball {
    float vel_x = 1;
    float vel_y = 1;
    float x;
    float y;
};

Ball updatePhysics(Ball ball){
    float rel_x = ball.x-540;
    float rel_y = ball.y-960;
    ball.vel_x += (rel_y/rel_x)*ball.vel_x*0.01;
    ball.vel_y += (rel_x/rel_y)*ball.vel_y*0.01;

    cout << ball.vel_x;
    cout << " ";
    cout << ball.vel_x+ball.x;
    cout << " ";
    cout << ball.x;
    cout << " ";

    ball.x = ball.x+ball.vel_x;
    ball.y = ball.y+ball.vel_y;
    return ball;
}
