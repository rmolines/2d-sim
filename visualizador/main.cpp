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

#define XB 3
#define YB 3
#define FW 10000
#define FH 10000
#define RADIUS 200

int main(int argc, char ** argv) {

    std::default_random_engine gen;
    std::uniform_real_distribution<double> dist(-1.0,1.0);    
    
    std::vector<ball> balls(XB * YB);
    int counter = 0;
    for (int i = 0; i < XB; i++) {
        for (int j = 0; j < YB; j++) {
            balls[i*YB + j].id = counter++;
            balls[i*YB + j].x = i*(FW/XB)+RADIUS;
            balls[i*YB + j].y = j*(FH/YB)+RADIUS;
            balls[i*YB + j].radius = RADIUS;
            balls[i*YB + j].vx = dist(gen);
            balls[i*YB + j].vy = dist(gen);
            balls[i*YB + j].ball_col = NULL;
        }
    }
    Visualizador v(balls, FW, FH, 0.01);
    
    v.run();

    return 0; 
}
