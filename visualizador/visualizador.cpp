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
#include "SDL2/SDL.h"
#include "SDL2/SDL2_gfxPrimitives.h"

#include <stdio.h>

#include <chrono>

#include "math.h"

typedef std::chrono::high_resolution_clock Time;


Visualizador::Visualizador(std::vector<ball> &bodies, int field_width, int field_height, double delta_t) :
    delta_t(delta_t),
    field_width(field_width),
    field_height(field_height),
    bodies(bodies) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);


    std::vector<ball> collided(bodies.size());

    double ratio = (double) field_width / field_height;
    if (ratio > 1) {
        win_width = max_dimension;
        win_height = max_dimension / ratio;
    } else {
        win_width = max_dimension * ratio;
        win_height = max_dimension;
    }
    win = SDL_CreateWindow("Visualizador SUPERCOMP", SDL_WINDOWPOS_CENTERED,
                           SDL_WINDOWPOS_CENTERED, win_width, win_height, 0);
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    iter = 0;
}

Visualizador::~Visualizador() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
}


void Visualizador::draw() {
    SDL_SetRenderDrawColor(renderer, 160, 160, 185, 255);
    SDL_RenderClear(renderer);
    for (auto i = bodies.begin(); i != bodies.end(); i++) {
        filledCircleRGBA(renderer, i->x / field_width * win_width,
                         i->y / field_height* win_height,
                         i->radius / field_width * win_width,
                         255, 0 ,0, 255);
    }
    SDL_RenderPresent(renderer);
}


void Visualizador::run() {
    SDL_ShowWindow(win);
    draw();
    while (!SDL_QuitRequested()) {
        do_iteration();       
        draw();
    }
}

void Visualizador::update_pos(std::vector<ball> &balls){
  for (int i=0; i<int(bodies.size()); i++){
    balls[i].x+=balls[i].vx;
    balls[i].y+=balls[i].vy;
  }
}

void Visualizador::check_boundaries(){
    for (int i=0; i<int(bodies.size()); i++){
        if((bodies[i].x-bodies[i].radius)<0 || (bodies[i].x+bodies[i].radius)>field_width){
            bodies[i].vx*=-1;
        }
        if((bodies[i].y-bodies[i].radius)<0 || (bodies[i].y+bodies[i].radius)>field_height){
            bodies[i].vy*=-1;
        }
    }
}

double Visualizador::calc_dist(ball ball1, ball ball2){
    double x1 = ball1.x+ball1.vx;
    double y1 = ball1.y+ball1.vy;
    double x2 = ball2.x+ball2.vx;
    double y2 = ball2.y+ball2.vy;

    double dist = sqrt((pow((x2-x1),2) + pow((y2-y1), 2)));
    
    return dist;
}

void Visualizador::check_collision(){
    for (int i=0; i<int(bodies.size()); i++){
        ball *ball1 = &bodies[i];
        ball1->ball_col = NULL;
        for (int j=0; j<int(bodies.size()); j++){
            if (j != i) {
                ball ball2 = bodies[j];
                double dist = calc_dist(*ball1, ball2);
                double min_dist = ball1->radius + ball2.radius;
                if (dist < min_dist){
                    printf("CHECK_COLLISION\nball1 id: %d, x=%f, y=%f.\n", ball1->id, ball1->x, ball1->y);
                    printf("ball2 id: %d, x2=%f, y2=%f.\n\n", ball2.id, ball2.x, ball2.y);
                    if (!ball1->ball_col){
                        ball ball_col = ball2;
                        ball1->ball_col = &ball_col;
                        ball1->dist = dist;
                    } else {
                        if (ball1->dist > dist){
                            ball ball_col = ball2;
                            ball1->ball_col = &ball_col;
                            ball1->dist = dist;
                        }
                    }
                }
            }
        }
    }
}

double Visualizador::calc_mod(double vx, double vy){
    double mod = sqrt(pow(vx,2) + pow(vy, 2));
    return mod;
}

double Visualizador::calc_theta(double vx, double mod){
    double theta = acos (vx/mod);
    return theta;
}

void Visualizador::death_func(ball *ballp1, ball *ballp2){
    ball *ball1 = ballp1;
    ball *ball2 = ballp2;
    printf("DEATH_FUNC\nball1 id: %d, x=%f, y=%f.\n", ball1->id, ball1->x, ball1->y);
    printf("ball2 id: %d, x2=%f, y2=%f.\n\n", ball2->id, ball2->x, ball2->y);
    // printf("x=%f, y=%f.\n", ball1->x, ball1->y);
    // printf("x2=%f, y2=%f.\n", ball2->x, ball2->y);

    double delta_x = (ball2->x) - (ball1->x);
    double delta_y = (ball2->y) - (ball1->y);
    // printf("dist=%f\n", calc_dist(*ballp1, *ballp1->ball_col)); 

    double mod1 = calc_mod(ball1->vx, ball1->vy);
    double mod2 = calc_mod(delta_x, delta_y);
    double theta1 = calc_theta(delta_x, mod1);
    double theta2 = calc_theta(delta_x, mod2);

    double delta_theta = abs (theta2-theta1);

    double vx = mod1 * cos (delta_theta);
    double vy = mod1 * sin (delta_theta);

    vx = -vx; // LINHA DO A+

    double resulting_v = calc_mod(vx, vy);
    double resulting_theta = calc_theta(vx, resulting_v);

    double new_vx = resulting_v * cos(resulting_theta);
    double new_vy = resulting_v * sin(resulting_v);

    ballp1->vx = new_vx;
    ballp1->vy = new_vy;
}

void Visualizador::do_collision(){
    for (int i=0; i<int(bodies.size()); i++){
        if (bodies[i].ball_col != NULL){
            // print_ball(bodies[i], i);
            death_func(&bodies[i], *&bodies[i].ball_col);
            // print_ball(bodies[i], i);
        }
    }
}

void Visualizador::print_ball(ball ball, int i){
    printf("Ball %d, x=%d, y=%d, vx=%f, vy=%f.\n", i, int(ball.x), int(ball.y), ball.vx, ball.vy);
}

void Visualizador::do_iteration() {
    /* TODO: me implemente! */
    update_pos(bodies);
    check_boundaries();
    check_collision();
    do_collision();
    iter++;
}




