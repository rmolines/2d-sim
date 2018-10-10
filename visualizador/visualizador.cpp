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
#include <future>
#include <chrono>
#include <unistd.h>
#include "math.h"
#include <omp.h>
#include <signal.h> 
#include <time.h> 
#include <iostream>
#include <fstream>
#include <ctime>
#include <ratio>
#include <string>

typedef std::chrono::high_resolution_clock Time;

int NUM_SAMPLES = 100;

Visualizador::Visualizador(std::vector<ball> &bodies, int field_width, int field_height, double delta_t, simul &sim) :
    delta_t(delta_t),
    field_width(field_width),
    field_height(field_height),
    bodies(bodies),
    sim(sim) {
    
    if(sim.gui == 1) {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
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
    }


    std::vector<ball> collided(bodies.size());


    iter = 0;
}

Visualizador::~Visualizador() {
    if (sim.gui == 1){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(win);
        SDL_Quit();

    }
}


void Visualizador::draw() {
    SDL_SetRenderDrawColor(renderer, 117, 117, 117, 255);
    SDL_RenderClear(renderer);
    for (auto i = bodies.begin(); i != bodies.end(); i++) {
        filledCircleRGBA(renderer, i->x / field_width * win_width,
                         i->y / field_height* win_height,
                         i->radius / field_width * win_width,
                         57, 73, 171, 255);
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

void handler(int sig)
{
    printf("singal %d\n", sig);
    exit(1);
}



void Visualizador::gui_run() {
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, 0);
    
    
    std::chrono::duration<double> timer;
    double sec = 0;
    Time::time_point t2 = Time::now();    
    Time::time_point t1 = t2;

    while (1) {
        Time::time_point t2 = Time::now();
        timer = std::chrono::duration_cast<std::chrono::duration<double>> (t2-t1);

        if (timer.count() > 1){
            sec+=1;
            t1 = t2;
            for (int id=0; id<(int) bodies.size(); id++){
                printf("id=%d raio=%f massa=%f x=%d y=%d vx=%f vy=%f sec=%fs \n", bodies[id].id, bodies[id].radius, bodies[id].mass, \
                                                             int(bodies[id].x), int(bodies[id].y), bodies[id].vx, \
                                                             bodies[id].vy, sec);
            }
        }
        do_iteration();
    }
}


void Visualizador::results(){
    std::chrono::duration<double> sum;
    int counter = 0;
    std::string filename = "./results/-s=" +  sim.s + " -gui=" + std::to_string(sim.gui) + " -model=" + std::to_string(sim.model) + \ 
                            + " -n_balls=" + std::to_string(bodies.size()) +  ".csv";
    std::ofstream myfile;
    myfile.open (filename);


    for (int i=0; i<NUM_SAMPLES; i++){
        auto start = Time::now();
        do_iteration();
        auto finish = Time::now();
        counter++;
        sum = (finish-start);
        myfile << sum.count() << "\n";
        printf("%fs - iteration=%d\n", sum.count(), i);
    }
    myfile.close();
}



void Visualizador::update_pos(std::vector<ball> &balls){
    #pragma omp parallel for
    for (int i=0; i<int(bodies.size()); i++){
        balls[i].x+=balls[i].vx*delta_t;
        balls[i].y+=balls[i].vy*delta_t;
    }
}

void Visualizador::update_v(std::vector<ball> &balls){
    #pragma omp parallel for

    for (int i=0; i<int(bodies.size()); i++){
        double mod = calc_mod(balls[i].vx, balls[i].vy);
        double theta = calc_theta(balls[i].vx, balls[i].vy, mod);

        double ax = (sim.mu*10*delta_t) * cos(theta);
        double ay = -(sim.mu*10*delta_t) * sin(theta);        
       
        double vx = (mod) * cos(theta);
        double vy = (mod) * sin(theta);   


        if (abs(balls[i].vx - ax) < 0) {
            balls[i].vx = 0;
        } else {
            balls[i].vx -= ax;
        }

        if (abs(balls[i].vy - ay) < 0) {
            balls[i].vy = 0;
        } else {
            balls[i].vy -= ay;
        }
    }
}

void Visualizador::check_boundaries(){
    #pragma omp parallel for

    for (int i=0; i<int(bodies.size()); i++){
        if((bodies[i].x-bodies[i].radius)<0 || (bodies[i].x+bodies[i].radius)>field_width){
            if ((bodies[i].x-bodies[i].radius)<0){
                bodies[i].x=bodies[i].radius;    
            } else {
                bodies[i].x=field_width-bodies[i].radius;
            }
            
            bodies[i].vx*=-1;
        }
        if((bodies[i].y-bodies[i].radius)<0 || (bodies[i].y+bodies[i].radius)>field_height){            
            if ((bodies[i].y-bodies[i].radius)<0){
                bodies[i].y=bodies[i].radius;    
            } else {
                bodies[i].y=field_height-bodies[i].radius;
            }
            bodies[i].vy*=-1;
        }
    }
}

double Visualizador::calc_dist(ball ball1, ball ball2){
    
    double x1 = ball1.x+ball1.vx*delta_t;
    double y1 = ball1.y+ball1.vy*delta_t;
    double x2 = ball2.x+ball2.vx*delta_t;
    double y2 = ball2.y+ball2.vy*delta_t;


    double dist = sqrt((pow((x2-x1),2) + pow((y2-y1), 2)));
    
    return dist;
}

void Visualizador::check_collision(){
    #pragma omp parallel for

    for (int i=0; i<int(bodies.size()); i++){
        ball *ball1 = &bodies[i];
        ball1->ball_col = NULL;
        for (int j=0; j<int(bodies.size()); j++){
            if (j != i) {
                ball ball2 = bodies[j];

                double dist = calc_dist(*ball1, ball2);
                double min_dist = ball1->radius + ball2.radius;
                if (abs(dist) < abs(min_dist)){
                    if (!ball1->ball_col){
                        ball *ball_col = &ball2;
                        ball1->ball_col = &bodies[j];
                        ball1->dist = dist;
                    } else {
                        if (ball1->dist > dist){
                            ball *ball_col = &ball2;
                            ball1->ball_col = &bodies[j];
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

double Visualizador::calc_theta(double vx, double vy, double mod){
    double theta;
    double x = vx/mod;
    if (x<=-1){
        x = -1;
    } else if (x>=1){
        x = 1;
    }
    if (vy < 0){
        theta = acos (x);
    } else {
        theta = 2*M_PI - acos (x);
    }
    return theta;
}

double Visualizador::calc_delta_theta(ball &ball1, ball &ball2){
    double delta_x = (ball2.x) - (ball1.x);
    double delta_y = (ball2.y) - (ball1.y);

    double mod1 = calc_mod(ball1.vx, ball1.vy);
    double mod2 = calc_mod(delta_x, delta_y);
    double theta1 = calc_theta(ball1.vx, ball1.vy, mod1);
    double theta2 = calc_theta(delta_x, delta_y, mod2);

    double delta_theta = (theta2-theta1);

    return delta_theta;
}


void Visualizador::death_func(ball *ballp1, ball *ballp2){
    ball *ball1 = ballp1;
    ball *ball2 = ballp1->ball_col;

    double delta_x = (ball2->x) - (ball1->x);
    double delta_y = (ball2->y) - (ball1->y);

    double mod1 = calc_mod(ball1->vx, ball1->vy);
    double mod2 = calc_mod(delta_x, delta_y);
    double theta2 = calc_theta(delta_x, delta_y, mod2);

    double delta_theta = calc_delta_theta(*ball1, *ball2);


    double new_vx, new_vy, new_theta;

    if (delta_theta >= 0) {
        double new_theta = theta2 + (M_PI - delta_theta);
        new_vx = mod1 * cos (new_theta);
        new_vy = -mod1 * sin (new_theta);
    } else {
        new_theta = theta2 + (M_PI + delta_theta);
        new_vx = mod1 * cos (new_theta);
        new_vy = -mod1 * sin (new_theta);
    }


    ballp1->vx = new_vx;
    ballp1->vy = new_vy;
}


void Visualizador::modelo2(ball *ballp1, ball *ballp2){
    ball *ball1 = ballp1;
    ball *ball2 = ballp1->ball_col;

    double delta_x = ((ball2->x) - (ball1->x));
    double delta_y = ((ball2->y) - (ball1->y));
    double phi =  atan2(delta_y, delta_x);
    double m1 = ball1->mass;
    double m2 = ball2->mass;
    double v1 = calc_mod(ball1->vx, ball1->vy);
    double v2 = calc_mod(ball2->vx, ball2->vy);
    double theta1 = calc_theta(ball1->vx, ball1->vy, v1);
    double theta2 = calc_theta(ball2->vx, ball2->vy, v2);

    double vx_linha1 = ((v1*cos(theta1-phi)*(m1-m2)+(2*m2*v2*cos(theta2-phi)))/(m1+m2))*cos(phi)+v1*-sin(theta1-phi)*-sin(phi); 
    double vy_linha1 = ((v1*cos(theta1-phi)*(m1-m2)+2*m2*v2*cos(theta2-phi))/(m1+m2))*-sin(phi)+v1*-sin(theta1-phi)*cos(phi);


    ballp1->vx = vx_linha1;
    ballp1->vy = vy_linha1;

}

void Visualizador::elastic_collision(ball *ballp1, ball *ballp2){
    ball *ball1 = ballp1;
    ball *ball2 = ballp1->ball_col;

    double delta_x = ((ball1->x) - (ball2->x));
    double delta_y = ((ball1->y) - (ball2->y));

    double delta_vx = ball1->vx - ball2->vx;
    double delta_vy = ball1->vy - ball2->vy;

    double modx = calc_mod(delta_x, delta_y);

    double m1 = ball1->mass;
    double m2 = ball2->mass;

    double new_vx = ball1->vx - (2*m2/(m1+m2)) * \
                    ((delta_vx*delta_x + delta_y*delta_vy) \
                    / modx*modx) * delta_x;

    double new_vy = ball1->vy - (2*m2/(m1+m2)) * \
                    ((delta_vx*delta_x + delta_y*delta_vy) \
                    / modx*modx) * delta_y;

    ballp1->vx = new_vx;
    ballp1->vy = new_vy;
}

void Visualizador::do_collision(){
    #pragma omp parallel for

    for (int i=0; i<int(bodies.size()); i++){
        if (bodies[i].ball_col != NULL){
            if (sim.gui == 0){
                printf("CHOQUE ID%d > ID%d");
            }
            if(sim.model == 0){
                death_func(&bodies[i], bodies[i].ball_col);
            } else if (sim.model == 1){
                modelo2(&bodies[i], bodies[i].ball_col);
            }
        }
    }
}

void Visualizador::print_ball(int id){
    printf("id=%d raio=%f massa=%f x=%d y=%d vx=%f vy=%f\n", bodies[id].id, bodies[id].radius, bodies[id].mass, \
                                                             int(bodies[id].x), int(bodies[id].y), bodies[id].vx, \
                                                             bodies[id].vy);
}

void Visualizador::do_iteration() {
    /* TODO: me implemente! */
    update_v(bodies);
    check_collision();
    do_collision();
    check_boundaries();
    update_pos(bodies);
    iter++;
}
