/*
 * Copyright (c) 2018 Igor Montagner igordsm@gmail.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "visualizador.h"

#include <vector>
#include <random>
#include <iostream>

#define XB 6
#define YB 6
#define FW 10000
#define FH 10000
#define RADIUS 140


void read_global(simul *sim){
  double w, h, n, mu, alpha_w, alpha_b;
  if (!(std::cin >> w >> h >> n)) { throw 1; } // error
  if (!(std::cin >> mu >> alpha_w >> alpha_b)) { throw 1; } // error
  *sim = { w, h, mu, n, alpha_w, alpha_b };
}

void read_balls(double n, std::vector<ball> &balls){    

  for (int i=0; i<int(n); i++){
    double id, raio, massa, x0, y0, vx0, vy0;
    std::cin >> id >> raio >> massa >> x0 >> y0 >> vx0 >> vy0;
    ball ball = { id, raio, massa, x0, y0, vx0, vy0};
    balls[int(i)] = ball;
  }  
}

int main(int argc, char ** argv) {

    std::default_random_engine gen;
    std::uniform_real_distribution<double> dist(-1.0,1.0);
    std::uniform_real_distribution<double> mass(1, 10);       
    

    simul sim;
    read_global(&sim);
    std::vector<ball> balls(sim.n);

    // int counter = 0;
    // for (int i = 0; i < XB; i++) {
    //     for (int j = 0; j < YB; j++) {
    //         balls[i*YB + j].id = counter++;
    //         balls[i*YB + j].x = i*(FW/XB)+RADIUS;
    //         balls[i*YB + j].y = j*(FH/YB)+RADIUS;
    //         balls[i*YB + j].radius = RADIUS;
    //         balls[i*YB + j].vx = dist(gen);
    //         balls[i*YB + j].vy = dist(gen);
    //         balls[i*YB + j].mass = mass(gen);
    //         balls[i*YB + j].ball_col = NULL;
    //     }
    // }

    // balls[0].x = FW/3;
    // balls[0].y = FH/2;
    // balls[0].vx = 1;
    // balls[0].vy = 0;
    // balls[0].mass = 1;

    // balls[1].x = FW/3*2;
    // balls[1].y = FH/2;
    // balls[1].vx = -1;
    // balls[1].vy = 0;
    // balls[1].mass = 1;
    read_balls(sim.n, balls);
    
    // printf("id=%f, raio=%f, x=%f, y=%f, n=%f\n", balls[1].id, balls[1].radius, balls[1].x, balls[1].y, sim.n);

    Visualizador v(balls, sim.w, sim.h, 0.01, sim);
        
    v.run();

    return 0; 
}
