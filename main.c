#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <SDL_mixer.h>
#include <stdlib.h>
#include <SDL_ttf.h>
#include <ctype.h>
const int width = 1100; // ความกว้าง
const int height = 800; // ความสูง
/*********************************************************/
int x[1000];
int y[1000];
int temp_x[1000], temp_y[1000];
int size = 3;
/*********************************************************/
int main(int argc, char* args[]){
     // init sdl
    TTF_Init();
    SDL_Init(SDL_INIT_EVERYTHING);
    // สร้างหน้าต่างโปรแกรม
    SDL_Window* window = SDL_CreateWindow("Snake Game @@", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    // สร้าง ตัวแปร renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // สร้างตัวแปร event
    SDL_Event event;
    // สร้างตัวเช็คว่าโปรแกรมรันอยู่หรือเปล่า
    int running = 1;
    // โหลดภาพพื้นหลัง
    SDL_Surface* bg_surface = NULL;
    SDL_Texture* bg_texture = NULL;
    bg_surface = IMG_Load("bg.png");
    bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);
    SDL_Rect bg = {0, 0, 1200, 800};

    SDL_Surface* forest_surface = NULL;
    SDL_Texture* forest_texture = NULL;
    forest_surface = IMG_Load("forest.jpg");
    forest_texture = SDL_CreateTextureFromSurface(renderer, forest_surface);
    SDL_Rect forest = {20, 20, 760, 760};

    SDL_Surface* menu_surface = NULL;
    SDL_Texture* menu_texture = NULL;
    menu_surface = IMG_Load("menu.png");
    menu_texture = SDL_CreateTextureFromSurface(renderer, menu_surface);
    SDL_Rect menu = {0, 0, 1200, 800};

    SDL_Surface* game_option_surface = NULL;
    SDL_Texture* game_option_texture = NULL;
    game_option_surface = IMG_Load("game_option.png");
    game_option_texture = SDL_CreateTextureFromSurface(renderer, game_option_surface);
    SDL_Rect game_option = {0, 0, 1200, 800};
    // โหลดตัวงู
    SDL_Surface* snake_surface = NULL;
    SDL_Texture* snake_texture = NULL;
    snake_surface = IMG_Load("snake.png");
    snake_texture = SDL_CreateTextureFromSurface(renderer, snake_surface);
    //
    SDL_Surface* snake2_surface = NULL;
    SDL_Texture* snake2_texture = NULL;
    snake2_surface = IMG_Load("snake2.png");
    snake2_texture = SDL_CreateTextureFromSurface(renderer, snake2_surface);
    //
    SDL_Surface* game_over_surface = NULL;
    SDL_Texture* game_over_texture = NULL;
    game_over_surface = IMG_Load("game_over.jpg");
    game_over_texture = SDL_CreateTextureFromSurface(renderer, game_over_surface);
    SDL_Rect game_over = {0, 0, 1100, 800};
    //
    SDL_Surface* food_surface = NULL;
    SDL_Texture* food_texture = NULL;
    food_surface = IMG_Load("plus.png");
    //
    // ตั้งพิกัด
    x[0] = 400;
    y[0] = 400;
    x[1] = 380;
    y[1] = 400;
    x[2] = 360;
    y[2] = 400;
    //
    TTF_Font* sans = TTF_OpenFont("OpenSans-Regular.ttf", 100);
    SDL_Color black = {0, 0, 0};
    SDL_Surface* surfacemessage = TTF_RenderText_Solid(sans, "xxxxxx", black);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfacemessage);
    SDL_Rect message_rect = {810, 665, 260, 100};
    //
    SDL_Surface* menu_message_surface = TTF_RenderText_Solid(sans, "Snake Game with C language", black);
    SDL_Texture* menu_message = SDL_CreateTextureFromSurface(renderer, menu_message_surface);
    SDL_Rect menu_message_rect = {210, 50, 700, 100};
    //
    SDL_Surface* menu_message2_surface = TTF_RenderText_Solid(sans, "Press ENTER to start", black);
    SDL_Texture* menu_message2 = SDL_CreateTextureFromSurface(renderer, menu_message2_surface);
    SDL_Rect menu_message2_rect = {250, 600, 600, 100};
    //
    SDL_Surface* gameoption_message_surface = TTF_RenderText_Solid(sans, "Game option", black);
    SDL_Texture* gameoption_message = SDL_CreateTextureFromSurface(renderer, gameoption_message_surface);
    SDL_Rect gameoption_message_rect = {300, 50, 500, 100};
    //
    SDL_Surface* diff_message_surface = TTF_RenderText_Solid(sans, "Easy", black);
    SDL_Texture* diff_message = SDL_CreateTextureFromSurface(renderer, diff_message_surface);
    SDL_Rect diff_message_rect = {450, 200, 150, 100};
    //
    SDL_Surface* diff2_message_surface = TTF_RenderText_Solid(sans, "Medium", black);
    SDL_Texture* diff2_message = SDL_CreateTextureFromSurface(renderer, diff2_message_surface);
    SDL_Rect diff2_message_rect = {450, 400, 250, 100};
    //
    SDL_Surface* diff3_message_surface = TTF_RenderText_Solid(sans, "Hard", black);
    SDL_Texture* diff3_message = SDL_CreateTextureFromSurface(renderer, diff3_message_surface);
    SDL_Rect diff3_message_rect = {450, 600, 150, 100};
    //
    SDL_Surface* select_message_surface = TTF_RenderText_Solid(sans, ">", black);
    SDL_Texture* select_message = SDL_CreateTextureFromSurface(renderer, select_message_surface);
    //
    int select_diff = 1;
    int food_x = 0;
    int food_y = 0;
    char going = 'R';
    int food_status = 1;
    int keyboard_bug_fix = 1;
    int score = 0;
    char score_str[10000];
    int menu_check = 1;
    int diff_t = 200;
    // โปรแกรมรัน
    while (running){
        // เช็ค event
        while (SDL_PollEvent(&event)) {
            // ถ้ากดปิดหน้าต่าง
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_RIGHT && going != 'L' && keyboard_bug_fix && menu_check == 3){
                    going = 'R';
                    keyboard_bug_fix = 0;
                }
                else if (event.key.keysym.sym == SDLK_LEFT && going != 'R' && keyboard_bug_fix && menu_check == 3){
                    going = 'L';
                    keyboard_bug_fix = 0;
                }
                else if (event.key.keysym.sym == SDLK_UP && going != 'D' && keyboard_bug_fix && menu_check == 3){
                    going = 'U';
                    keyboard_bug_fix = 0;
                }
                else if (event.key.keysym.sym == SDLK_DOWN && going != 'U' && keyboard_bug_fix && menu_check == 3){
                    going = 'D';
                    keyboard_bug_fix = 0;
                }
                else if (menu_check == 1 && event.key.keysym.sym == SDLK_RETURN){
                    menu_check = 2;
                }
                else if (menu_check == 2 && event.key.keysym.sym == SDLK_UP){
                    select_diff --;
                }
                else if (menu_check == 2 && event.key.keysym.sym == SDLK_DOWN){
                    select_diff ++;
                }
                else if (menu_check == 2 && event.key.keysym.sym == SDLK_RETURN){
                    menu_check++;
                }
                else if (menu_check == 4 && event.key.keysym.sym == SDLK_RETURN){
                    running = 0;
                }
            }
        }
        if (menu_check == 1){
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, menu_texture, NULL, &menu);
            SDL_RenderCopy(renderer, menu_message, NULL, &menu_message_rect);
            SDL_RenderCopy(renderer, menu_message2, NULL, &menu_message2_rect);
            SDL_RenderPresent(renderer);
        }
        else if (menu_check == 2){
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, game_option_texture, NULL, &game_option);
            SDL_RenderCopy(renderer, gameoption_message, NULL, &gameoption_message_rect);
            SDL_RenderCopy(renderer, diff_message, NULL, &diff_message_rect);
            SDL_RenderCopy(renderer, diff2_message, NULL, &diff2_message_rect);
            SDL_RenderCopy(renderer, diff3_message, NULL, &diff3_message_rect);
            if (select_diff < 1){
                select_diff = 3;
            }
            if (select_diff > 3){
                select_diff = 1;
            }

            if (select_diff == 1){
                diff_t = 200;
            }
            else if (select_diff == 2){
                diff_t = 400;
            }
            else if (select_diff == 3){
                diff_t = 600;
            }
            SDL_Rect select_message_rect = {350, diff_t, 50, 100};
            SDL_RenderCopy(renderer, select_message, NULL, &select_message_rect);
            SDL_RenderPresent(renderer);
        }
        else if (menu_check == 3){
            sprintf(score_str, "%06d", score);
            SDL_Surface* surfacemessage = TTF_RenderText_Solid(sans, score_str, black);
            SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfacemessage);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, bg_texture, NULL, &bg);
            SDL_RenderCopy(renderer, forest_texture, NULL, &forest);
            while (food_status){
                food_texture = SDL_CreateTextureFromSurface(renderer, food_surface);
                food_x = 20 * (rand() % 35);
                food_y = 20 * (rand() % 35);
                if (food_x == 0) food_x = 20;
                if (food_y == 0) food_y = 20;
                food_status = 0;
                for (int i = 0; i < size; i++){
                    if (food_x == x[i] && food_y == y[i]){
                        food_status++;
                        break;
                    }
                }
            }
            SDL_Rect food = {food_x, food_y, 20, 20};
            SDL_RenderCopy(renderer, food_texture, NULL, &food);
            for (int i = 0; i < size; i++){
                SDL_Rect snake = {x[i], y[i], 20, 20};
                if (i != 0) SDL_RenderCopy(renderer, snake2_texture, NULL, &snake);
                else SDL_RenderCopy(renderer, snake_texture, NULL, &snake);
            }
            if (going == 'R'){
                x[0] += 20;
            }
            else if (going == 'L'){
                x[0] -= 20;
            }
            else if (going == 'U'){
                y[0] -= 20;
            }
            else if (going == 'D'){
                y[0] += 20;
            }
            if (x[0] > 760){
                x[0] = 20;
            }
            if (x[0] < 20){
                x[0] = 760;
            }
            if (y[0] > 760){
                y[0] = 20;
            }
            if (y[0] < 20){
                y[0] = 760;
            }
            if (x[0] == food_x && y[0] == food_y){
                x[size] = x[size - 1] - 20;
                size++;
                food_status++;
                score += 100;
                SDL_DestroyTexture(food_texture);
            }
            for (int i = 1; i < size; i++){
                if (x[0] == x[i] && y[0] == y[i]){
                    menu_check = 4;
                    break;
                }
                x[i] = temp_x[i - 1];
                y[i] = temp_y[i - 1];
            }
            for (int i = 0; i < size; i++){
                temp_x[i] = x[i];
                temp_y[i] = y[i];
            }
            SDL_RenderCopy(renderer, message, NULL, &message_rect);
            SDL_RenderPresent(renderer);
            // ตั้งค่า delay time;
            int delay_diff;
            if (diff_t == 200){
                delay_diff = 4000;
            }
            else if (diff_t == 400){
                delay_diff = 3000;
            }
            else{
                delay_diff = 2000;
            }
            int delay= delay_diff / 60 - SDL_GetTicks() + SDL_GetTicks();
            if(delay > 0){
                SDL_Delay(delay);
            }
            keyboard_bug_fix = 1;
        }
        else if (menu_check == 4){
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, game_over_texture, NULL, &game_over);
            SDL_RenderPresent(renderer);
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}