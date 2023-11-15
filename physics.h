#include <math.h>
#include <stdio.h>
#include <cmath>
#include <iostream>
using namespace std;

class Vect {
 public:
  float x;
  float y;
  Vect operator+(Vect a) { return Vect{x + a.x, y + a.y}; }
  Vect operator-(Vect a) { return Vect{x - a.x, y - a.y}; }
  Vect operator*(Vect a) { return Vect{x * a.x, y * a.y}; }
  Vect operator*(float a) { return Vect{x * a, y * a}; }
  Vect operator/(Vect a) { return Vect{x / a.x, y / a.y}; }
  Vect operator/(float a) { return Vect{x / a, y / a}; }
  void operator+=(Vect a) {
    x += a.x;
    y += a.y;
  }
  void operator-=(Vect a) {
    x -= a.x;
    y -= a.y;
  }
  void operator*=(Vect a) {
    x *= a.x;
    y *= a.y;
  }
  void operator*=(float a) {
    x *= a;
    y *= a;
  }
  void operator/=(Vect a) {
    x /= a.x;
    y /= a.y;
  }
  Vect(float a, float b) {
    x = a;
    y = b;
  }
  void reverse() {
    float a = x;
    x = y;
    y = a;
  }
  float length() { return sqrt(pow(x, 2) + pow(y, 2)); }
};

std::ostream& operator<<(std::ostream& out, Vect const& a) {
  out << "x: " << a.x << " y: " << a.y << "\n";
  return out;
}

Vect operator*(float a, Vect b) {
  return b * a;
}

struct Ball {
  Vect velocity = {0, 0};
  Vect position = {0, 0};
  Vect old_position = position;
  int r;
  int w;
};

float dot(Vect v1, Vect v2) { return v1.x * v2.x + v1.y * v2.y; }

const float friction = 0.90f;
// float friction=0.25;
const float gravity = 1.0f;

float calcSpeedAxis(float v1, float v2, int m1, int m2) {
  return ((m1 * v1 + m2 * (2 * v2 - v1)) / (m1 + m2)) * friction;
}

void calcSpeed(Ball& ball1, Ball& ball2, Vect axis) {
  ball1.velocity = axis * calcSpeedAxis(ball1.velocity.length(), ball2.velocity.length(), ball1.w, ball2.w) * friction;
  ball2.velocity = axis * -calcSpeedAxis(ball2.velocity.length(), ball1.velocity.length(), ball2.w, ball1.w) * friction;
}

Vect center = {960, 540};

void updatePhysics(Ball& ball, Ball* balls, int index, int ball_count) {
  ball.old_position = ball.position;
  Vect vect_to_center = center - ball.position;
  float dist_to_center = sqrt(pow(vect_to_center.x, 2) + pow(vect_to_center.y, 2));
  Vect axis_to_center = vect_to_center / dist_to_center;
  // ball.velocity += axis_to_center*gravity;
  ball.velocity.y = ball.velocity.y + gravity;

  ball.position += ball.velocity;
  // ball.velocity*=0.9998;

  for (int i = 0; i < ball_count; i++) {
    if (i == index) {
      continue;
    }
    Ball ball2 = balls[i];
    Vect col = ball.position - balls[i].position;
    float d = sqrt(pow(col.x, 2) + pow(col.y, 2));
    float min_dist = (ball.r + balls[i].r);
    if (d < min_dist - 1) {
      Vect axis = col / d;
      ball.position += axis * 0.5f * (min_dist - d);
      balls[i].position -= axis * 0.5f * (min_dist - d);
      // ball.velocity.x = (ball.velocity.x * (ball.r - balls[i].r) + (2 * balls[i].r * balls[i].velocity.x)) / (ball.r
      // + balls[i].r); ball.velocity.y = (ball.velocity.y * (ball.r - balls[i].r) + (2 * balls[i].r *
      // balls[i].velocity.y)) / (ball.r + balls[i].r); balls[i].velocity.x = (balls[i].velocity.x * (balls[i].r -
      // ball.r) + (2 * ball.r * ball.velocity.x)) / (balls[i].r + ball.r); balls[i].velocity.y = (balls[i].velocity.y *
      // (balls[i].r - ball.r) + (2 * ball.r * ball.velocity.y)) / (balls[i].r + ball.r);
      ball.velocity = ball.velocity - ((2.0 * ball2.r) / (ball.r + ball2.r)) *
                                          (dot(ball.velocity - ball2.velocity, ball.position - ball2.position) /
                                           pow((ball.position - ball2.position).length(), 2)) *
                                          (ball.position - ball2.position) * friction;
      ball2.velocity = ball2.velocity - ((2.0 * ball.r) / (ball2.r + ball.r)) *
                                          (dot(ball2.velocity - ball.velocity, ball2.position - ball.position) /
                                           pow((ball2.position - ball.position).length(), 2)) *
                                          (ball2.position - ball.position) * friction;
      // ball.position += ball.velocity;
      // balls[i].position += balls[i].velocity;
      /*
      Vect diff = (ball.velocity - balls[i].velocity);
      // ball.velocity-=diff*friction*0.65;
      // balls[i].velocity+=diff*friction*0.65;
      ball.velocity = (ball.position - ball.old_position);
      // calcSpeed(ball,balls[i],axis);
      */
      cout << "-----------\n";
      // cout << ball.position;
      cout << ball.velocity;
      cout << ball2.velocity;
      // cout << balls[i].old_position;
      // cout << balls[i].position;
      // cout << balls[i].velocity;
    }
  }
  if (ball.position.x <= ball.r) {
    ball.velocity.x = -ball.velocity.x * friction;
    ball.position.x = ball.r;
  }
  if (ball.position.x >= 1920 - ball.r) {
    ball.velocity.x = -ball.velocity.x * friction;
    ball.position.x = 1920 - ball.r;
  }
  if (ball.position.y <= ball.r) {
    ball.velocity.y = -ball.velocity.y * friction;
    ball.position.y = ball.r;
  }
  if (ball.position.y >= 1080 - ball.r) {
    ball.velocity.y = -ball.velocity.y * friction;
    ball.position.y = 1080 - ball.r;
  }
  return;
}
