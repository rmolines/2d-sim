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
#include <string>

#define XB 2
#define YB 1
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

  std::string arg0 = argv[1];
  std::string arg1 = argv[2];
  std::string arg2 = argv[3];
  std::string arg3 = argv[4];

  int gui = std::stoi(arg1);
  std::string s = arg2;
  double delta_t = std::stod(arg0);
  int model = std::stoi(arg3);

  std::default_random_engine gen;
  std::uniform_real_distribution<double> dist(-1.0,1.0);
  std::uniform_real_distribution<double> mass(1, 10);       
  

  simul sim;
  read_global(&sim);
  sim.s = s;
  sim.gui = gui;
  sim.model = model;
  std::vector<ball> balls(sim.n);

  read_balls(sim.n, balls);


  Visualizador v(balls, sim.w, sim.h, delta_t, sim);
    
  if (gui == 0){
    v.gui_run();
    
  } else if (gui == 1) {
      v.run();
  } else {
      v.results();
  }

  return 0; 
}
