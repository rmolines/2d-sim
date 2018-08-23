#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <string>
#include <iostream>


using namespace std;

struct Ball {
  double id, raio, massa, x0, y0, vx0, vy0;
}


void read_file(){
  double w, h, n, mu, alpha_w, alpha_b;
  if (!(cin >> w >> h >> n)) { throw 1; } // error
  if (!(cin >> mu >> alpha_w >> alpha_b)) { throw 1; } // error

  Ball *balls = new Ball[n];
  
  for (int i=0; i<n; i++){
    double id, raio, massa, x0, y0, vx0, vy0;
    cin >> id >> raio >> massa >> x0 >> y0 >> vx0 >> vy0;
    Ball ball = Ball(id, raio, massa, x0, y0, vx0, vy0);
  }
  

}

int main(int argc, char const *argv[]) {
  read_file();
  return 0;
}
