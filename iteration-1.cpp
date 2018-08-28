#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <string>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

struct Ball {
  double id, raio, massa, x, y, vx, vy;
};

struct Sim {
  double w, hu, n, alpha_w, alpha_b;
};

void print_pos(Ball ball){
  printf("id=%d, x_pos=%f, y_pos=%f, vx=%f, vy=%f\n", int(ball.id), ball.x, ball.y, ball.vx, ball.vy);
}


void read_global(Sim *sim){
  double w, h, n, mu, alpha_w, alpha_b;
  if (!(cin >> w >> h >> n)) { throw 1; } // error
  if (!(cin >> mu >> alpha_w >> alpha_b)) { throw 1; } // error
  *sim = { w, h, n, alpha_w, alpha_b };
}

void read_balls(double n, Ball *&balls){    

  for (int i=0; i<int(n); i++){
    double id, raio, massa, x0, y0, vx0, vy0;
    cin >> id >> raio >> massa >> x0 >> y0 >> vx0 >> vy0;
    Ball ball = { id, raio, massa, x0, y0, vx0, vy0 };
    balls[int(i)] = ball;
  }  
}

void update_pos(Ball *balls, double n){
  for (int i=0; i<n; i++){
    balls[i].x+=balls[i].vx;
    balls[i].y+=balls[i].vy;
  }
}

int main(int argc, char const *argv[]) {
  Sim sim;
  read_global(&sim);

  Ball *balls = new Ball[int(sim.n)];
  read_balls(sim.n, balls);

  print_pos(balls[0]);

  update_pos(balls, sim.n);

  print_pos(balls[0]);


  return 0;
}
