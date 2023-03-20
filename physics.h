#include <math.h>
#include <stdio.h> 
#include <iostream>
using namespace std;

class Vect {
    public:
        float x;
        float y;
        Vect operator + (Vect a){return Vect {x+a.x,y+a.y};}
        Vect operator - (Vect a){return Vect {x-a.x,y-a.y};}
        Vect operator * (Vect a){return Vect {x*a.x,y*a.y};}
        Vect operator * (float a){return Vect {x*a,y*a};}
        Vect operator / (Vect a){return Vect {x/a.x,y/a.y};}
        Vect operator / (float a){return Vect {x/a,y/a};}
        void operator += (Vect a) { x += a.x;y+=a.y; }
        void operator -= (Vect a) { x -= a.x;y-=a.y; }
        void operator *= (Vect a) { x *= a.x;y*=a.y; }
        void operator *= (float a) { x *= a;y*=a; }
        void operator /= (Vect a) { x /= a.x;y/=a.y; }
        Vect(float a,float b) {x=a;y=b;}
        void reverse() {
            float a=x;
            x=y;
            y=a;
        }
        float length() {
            return sqrt(pow(x,2)+pow(y,2));
        }
};

std::ostream& operator << (std::ostream& out,Vect const& a) {
    out << "x: "<<a.x<<" y: "<<a.y<<"\n";
    return out;
}
struct Ball {
    Vect velocity = {0,0};
    Vect position = {0,0};
    Vect old_position = position;
    int r;
    int w;
};

float friction=0.95f;
//float friction=0.25;
float gravity=1.0f;

float calcSpeedAxis(float v1,float v2,int m1,int m2) {
    return ((m1*v1+m2*(2*v2-v1))/(m1+m2))*friction;
}

Vect calcSpeed(Ball &ball1,Ball &ball2, Vect axis) {
    ball1.velocity=axis*calcSpeedAxis(ball1.velocity.length(),ball2.velocity.length(),ball1.w,ball2.w)*friction;
    ball2.velocity=axis*-calcSpeedAxis(ball2.velocity.length(),ball1.velocity.length(),ball2.w,ball1.w)*friction;
}

Vect center = {960,540};

void updatePhysics(Ball &ball, Ball * balls,int index,int ball_count){
    Vect vect_to_center = center-ball.position;
    float dist_to_center = sqrt(pow(vect_to_center.x,2)+pow(vect_to_center.y,2));
    Vect axis_to_center = vect_to_center/dist_to_center;
    //ball.velocity += axis_to_center*gravity;
    ball.velocity.y = ball.velocity.y+gravity;

    ball.position+=ball.velocity;
    //ball.velocity*=0.9998;

    if (ball.position.x<=ball.r){
        ball.velocity.x=ball.velocity.x*friction;
        ball.position.x=ball.r;}
    if (ball.position.x>=1920-ball.r){
        ball.velocity.x=ball.velocity.x*friction;
        ball.position.x=1920-ball.r;}
    if (ball.position.y<=ball.r){
        ball.velocity.y=ball.velocity.y*friction;
        ball.position.y=ball.r;}
    if (ball.position.y>=1080-ball.r){
        ball.velocity.y=ball.velocity.y*friction;
        ball.position.y=1080-ball.r;}


    for (int i=0;i<ball_count;i++) {
        if (i==index){
            continue;
        }
        Vect col = ball.position-balls[i].position;
        float d = sqrt(pow(col.x,2)+pow(col.y,2));
        float min_dist=(ball.r+balls[i].r);
        if (d <= min_dist-1){
            Vect axis = col/d;
            ball.position+=axis*0.5f*(min_dist-d);
            balls[i].position-=axis*0.5f*(min_dist-d);
            Vect diff=(ball.velocity-balls[i].velocity);
            //ball.velocity-=diff*friction*0.65;
            //balls[i].velocity+=diff*friction*0.65;
            ball.velocity=(ball.position-ball.old_position);
            //calcSpeed(ball,balls[i],axis);

            cout << "-----------\n";
            cout << ball.position;
            cout << ball.velocity;
            cout << balls[i].old_position;
            cout << balls[i].position;
            cout << balls[i].velocity;
        }
    }
    ball.old_position=ball.position;
    return;
}
