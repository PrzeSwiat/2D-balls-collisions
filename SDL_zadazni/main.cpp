#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "Ball.cpp"

using namespace std;

const int WIDTH = 1200, HEIGHT = 700;

void draw_circle(SDL_Renderer*, float,float,float, SDL_Color);
float get_distance_btw_points(float , float,float,float);
void ball_generator(vector<Ball>*, int);
void move_balls(vector<Ball>);
void colision(vector<Ball>*);
VectorsLib vectors;
bool separation_flag = true;
bool reflect_flag = true;

int main(int argc, char* argv[])
{
    SDL_Event event;
    const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);
    SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);

    if (NULL == window)
    {
        std::cout << "Could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }
    // call SDL_CreateRenderer in order for draw calls to affect this window
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Color color_circle = { 3, 236, 252 ,100 };
    vector<Ball> ball_container;
    ball_generator(&ball_container, 30);
    cout << "Press A to switch Separation" << endl;
    cout << "Press S to switch Reflection" << endl;

    while (window)
    {
        SDL_SetRenderDrawColor(renderer, 93, 128, 115, 255);
        SDL_RenderClear(renderer);
      
        for (int i = 0; i < ball_container.size(); i++)
        {
            
            draw_circle(renderer, ball_container.at(i).get_x(), ball_container.at(i).get_y(), ball_container.at(i).get_radius(), color_circle);
            ball_container.at(i).move();
            ball_container.at(i).chceckwallcolision(WIDTH,HEIGHT);
        }
        colision(&ball_container);
        SDL_RenderPresent(renderer);
       
        
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_KEYDOWN:
                if ((keyboard_state_array[SDL_SCANCODE_A])) {
                    bool helper = false;
                    if (separation_flag==false) {
                        separation_flag = true;
                        helper = true;
                        cout << "Separation: ON" << endl;
                    }
                    
                    if(separation_flag==true&&helper!=true){
                        separation_flag = false;
                        cout << "Separation: OFF" << endl;
                    }
                    
                    
                }
                if ((keyboard_state_array[SDL_SCANCODE_S])) {
                    bool helper2 = false;
                    if(reflect_flag==false){
                        reflect_flag = true;
                        helper2 = true;
                        cout << "Reflection: ON" << endl;
                    }
                    
                    if (reflect_flag==true&&helper2!=true)
                    {
                        reflect_flag = false;
                        cout << "Reflection: OFF" << endl;
                    }
                    
                    
                }
                break;
            }
            }
        
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}

void draw_circle(SDL_Renderer* renderer, float x, float y, float radius, SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    for (int w = 0; w < radius * 2; w++)
    {
        for (int h = 0; h < radius * 2; h++)
        {
            float dx = radius - w; // horizontal offset
            float dy = radius - h; // vertical offset
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}
float get_distance_btw_points(float x1, float y1, float x2, float y2)
{
    return float(sqrt(pow(double(x2-x1),2)+ pow(double(y2-y1), 2)));
}

void ball_generator(vector<Ball>* ball_container, int amount)
{
    srand(time(NULL));
    for (int i = 0; i < amount; i++)
    {
        float randX = rand() % (WIDTH - 0 + 1) + 0;
        float randY = rand() % (HEIGHT - 0 + 1) + 0;
        Ball new_ball = Ball(randX,randY,20);
        new_ball.direction_set();
        ball_container->push_back(new_ball);
    }
}

void colision(vector<Ball>* ball_container)
{
    vector<float> vec;
    for (int i = 0; i < ball_container->size(); i++)
    {
        for (int j = 0; j < ball_container->size(); j++)
        {
            if (i!=j)
            {
                if (get_distance_btw_points(ball_container->at(i).get_x(), ball_container->at(i).get_y(),
                    ball_container->at(j).get_x(), ball_container->at(j).get_y()) < (ball_container->at(i).get_radius() + ball_container->at(j).get_radius()))
                {
                    float distance = get_distance_btw_points(ball_container->at(i).get_x(), ball_container->at(i).get_y(),
                        ball_container->at(j).get_x(), ball_container->at(j).get_y());

                    if (separation_flag)
                    {
                        ball_container->at(i).separete(&ball_container->at(j), distance, WIDTH, HEIGHT);
                        ball_container->at(j).separete(&ball_container->at(i), distance, WIDTH, HEIGHT);
                    }
                    if (reflect_flag)
                    {
                        ball_container->at(i).reflect(&ball_container->at(j), distance);
                        //ball_container->at(j).reflect(&ball_container->at(i), distance);
                    }



                    
                }
            }
        }
        
    }   

}

