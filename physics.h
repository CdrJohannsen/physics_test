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
    int r;
};

float friction=0.99;
//float friction=0.25;

float calcSpeedAxis(float v1,float v2,int m1,int m2) {
    return ((m1*v1+m2*(2*v2-v1))/(m1+m2))*friction;
}

Vect calcSpeed(Ball &ball1,Ball &ball2, Vect axis) {
    ball1.velocity*=Vect(0,0)-axis;
    ball2.velocity*=Vect(0,0)+axis;
    cout << "___________\n";
    cout << ball1.velocity;
    cout << ball2.velocity;
    //ball1.velocity.y=calcSpeedAxis(ball1.velocity.x,ball2.velocity.x,ball1.r,ball2.r);
    //ball1.velocity.x=calcSpeedAxis(ball1.velocity.y,ball2.velocity.y,ball1.r,ball2.r);
    //ball2.velocity.y=calcSpeedAxis(ball2.velocity.x,ball1.velocity.x,ball2.r,ball1.r);
    //ball2.velocity.x=calcSpeedAxis(ball2.velocity.y,ball1.velocity.y,ball2.r,ball1.r);
    ball1.velocity=axis*-calcSpeedAxis(ball1.velocity.length(),ball2.velocity.length(),ball1.r,ball2.r);
    ball2.velocity=axis*calcSpeedAxis(ball2.velocity.length(),ball1.velocity.length(),ball2.r,ball1.r);
    cout << ball1.velocity;
    cout << ball2.velocity;
    cout << "------------\n";
}

Vect center = {960,540};

void updatePhysics(Ball &ball, Ball* balls,int index,int ball_count){
    //ball.velocity += (center - ball.position)*0.0001f;
    ball.velocity.y += 0.5000f;

    ball.position+=ball.velocity;
    ball.velocity*=0.9998;

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
            axis.reverse();
            Vect diff=(ball.velocity-balls[i].velocity);
            //ball.velocity-=diff*friction*0.65;
            //balls[i].velocity+=diff*friction*0.65;
            calcSpeed(ball,balls[i],axis);
        }
    if (ball.position.x<=ball.r){ball.velocity.x=-ball.velocity.x*friction;ball.position.x=ball.r;}
    if (ball.position.x>=1920-ball.r){ball.velocity.x=-ball.velocity.x*friction;ball.position.x=1920-ball.r;}
    if (ball.position.y<=ball.r){ball.velocity.y=-ball.velocity.y*friction;ball.position.y=ball.r;}
    if (ball.position.y>=1080-ball.r){ball.velocity.y=-ball.velocity.y*friction;ball.position.y=1080-ball.r;}
    }
    return;
}
