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
int main(int argc, char* args[]){
     // init sdl
    TTF_Init();
    SDL_Init(SDL_INIT_EVERYTHING);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    // สร้างหน้าต่างโปรแกรม
    SDL_Window* window = SDL_CreateWindow("Snake Game with C language", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    // สร้าง ตัวแปร renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // สร้างตัวแปร event
    SDL_Event event;
    // สร้างตัวเช็คว่าโปรแกรมรันอยู่หรือเปล่า
    int running = 1;
    // โหลดกรอบ
    SDL_Surface* bg_surface = NULL;
    SDL_Texture* bg_texture = NULL;
    bg_surface = IMG_Load("image/bg.png");
    bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);
    SDL_Rect bg = {0, 0, 1200, 800};
    // โหลดภาพพื้นหลังในเกม
    SDL_Surface* ingame_bg_surface = NULL;
    SDL_Texture* ingame_bg_texture = NULL;
    ingame_bg_surface = IMG_Load("image/ingame_bg.png");
    ingame_bg_texture = SDL_CreateTextureFromSurface(renderer, ingame_bg_surface);
    SDL_Rect ingame_bg = {20, 20, 760, 760};
    // โหลดภาพ title ใน start menu
    SDL_Surface* menu_title_surface = NULL;
    SDL_Texture* menu_title_texture = NULL;
    menu_title_surface = IMG_Load("image/menu_title.png");
    menu_title_texture = SDL_CreateTextureFromSurface(renderer, menu_title_surface);
    SDL_Rect menu_title = {300, 60, 520, 138};
    // โหลดภาพ title ใน เมนูเลือกระดับความยาก
    SDL_Surface* diff_title_surface = NULL;
    SDL_Texture* diff_title_texture = NULL;
    diff_title_surface = IMG_Load("image/select_diff.png");
    diff_title_texture = SDL_CreateTextureFromSurface(renderer, diff_title_surface);
    SDL_Rect diff_title = {225, 60, 664, 151};
    // โหลดภาพ "Press ENTER to start" ใน start menu
    SDL_Surface* press_title_surface = NULL;
    SDL_Texture* press_title_texture = NULL;
    press_title_surface = IMG_Load("image/press_title.png");
    press_title_texture = SDL_CreateTextureFromSurface(renderer, press_title_surface);
    SDL_Rect press_title = {320, 660, 443, 53};
    // โหลดภาพคําว่า "Easy"
    SDL_Surface* easy_surface = NULL;
    SDL_Texture* easy_texture = NULL;
    easy_surface = IMG_Load("image/easy.png");
    easy_texture = SDL_CreateTextureFromSurface(renderer, easy_surface);
    SDL_Rect easy = {480, 250, 143, 76};
    // โหลดภาพ "Medium"
    SDL_Surface* medium_surface = NULL;
    SDL_Texture* medium_texture = NULL;
    medium_surface = IMG_Load("image/medium.png");
    medium_texture = SDL_CreateTextureFromSurface(renderer, medium_surface);
    SDL_Rect medium = {430, 450, 269, 66};
    // โหลดภาพ "Hard"
    SDL_Surface* hard_surface = NULL;
    SDL_Texture* hard_texture = NULL;
    hard_surface = IMG_Load("image/hard.png");
    hard_texture = SDL_CreateTextureFromSurface(renderer, hard_surface);
    SDL_Rect hard = {480, 650, 162, 66};
    // โหลดภาพ ">"
    SDL_Surface* select_surface = NULL;
    SDL_Texture* select_texture = NULL;
    select_surface = IMG_Load("image/select.png");
    select_texture = SDL_CreateTextureFromSurface(renderer, select_surface);
    SDL_Rect select = {440, 250, 43, 57};
    // โหลดภาพ "Game over!!"
    SDL_Surface* gameover_surface = NULL;
    SDL_Texture* gameover_texture = NULL;
    gameover_surface = IMG_Load("image/gameover.png");
    gameover_texture = SDL_CreateTextureFromSurface(renderer, gameover_surface);
    SDL_Rect gameover = {310, 60, 521, 82};
    // โหลดภาพ "play again"
    SDL_Surface* playagain_surface = NULL;
    SDL_Texture* playagain_texture = NULL;
    playagain_surface = IMG_Load("image/playagain.png");
    playagain_texture = SDL_CreateTextureFromSurface(renderer, playagain_surface);
    SDL_Rect playagain = {400, 300, 339, 80};
    // โหลดภาพ "exit"
    SDL_Surface* exit_surface = NULL;
    SDL_Texture* exit_texture = NULL;
    exit_surface = IMG_Load("image/exit.png");
    exit_texture = SDL_CreateTextureFromSurface(renderer, exit_surface);
    SDL_Rect exit = {490, 500, 134, 66};
    // โหลดภาพที่จะขึ้นมาเวลา pause
    SDL_Surface* pausepic_surface = NULL;
    SDL_Texture* pausepic_texture = NULL;
    pausepic_surface = IMG_Load("image/pause.png");
    pausepic_texture = SDL_CreateTextureFromSurface(renderer, pausepic_surface);
    SDL_Rect pausepic = {260, 320, 290, 127};
    // โหลด you score
    SDL_Surface* youscore_surface = NULL;
    SDL_Texture* youscore_texture = NULL;
    youscore_surface = IMG_Load("image/youscore.png");
    youscore_texture = SDL_CreateTextureFromSurface(renderer, youscore_surface);
    SDL_Rect youscore = {300, 700, 480, 70};
    // โหลดภาพเมนู
    SDL_Surface* menu_surface = NULL;
    SDL_Texture* menu_texture = NULL;
    menu_surface = IMG_Load("image/menu.png");
    menu_texture = SDL_CreateTextureFromSurface(renderer, menu_surface);
    // โหลดตัวงู
    SDL_Surface* snake_surface = NULL;
    SDL_Texture* snake_texture = NULL;
    snake_surface = IMG_Load("image/snake.png");
    snake_texture = SDL_CreateTextureFromSurface(renderer, snake_surface);
    // โหลดภาพในเกมด้านขวา
    SDL_Surface* ingame_right_surface = NULL;
    SDL_Texture* ingame_right_texture = NULL;
    ingame_right_surface = IMG_Load("image/right_img.png");
    ingame_right_texture = SDL_CreateTextureFromSurface(renderer, ingame_right_surface);
    SDL_Rect ingame_right = {800, 20, 280, 620};
    // โหลดภาพในเกมด้านขวาล่าง
    SDL_Surface* right_bot_surface = NULL;
    SDL_Texture* right_bot_texture = NULL;
    right_bot_surface = IMG_Load("image/right_bot.png");
    right_bot_texture = SDL_CreateTextureFromSurface(renderer, right_bot_surface);
    SDL_Rect right_bot = {800, 660, 280, 120};
    // โหลดอาหาร
    SDL_Surface* food_surface = NULL;
    SDL_Texture* food_texture = NULL;
    food_surface = IMG_Load("image/plus.png");
    // โหลด music
    Mix_Music *music = NULL;
    music = Mix_LoadMUS("audio/bg_music.mp3");
    // โหลด sound effect ตอนงูกินอาหาร
    Mix_Chunk *eat = NULL;
    eat = Mix_LoadWAV("audio/eat.wav");
    // โหลด sound effect ตอนเลื่อน
    Mix_Chunk *selection = NULL;
    selection = Mix_LoadWAV("audio/selection.wav");
    // โหลด sound effect ตอนกด enter
    Mix_Chunk *enter = NULL;
    enter = Mix_LoadWAV("audio/enter.wav");
    // โหลด sound effect game over
    Mix_Chunk* game_over_sound = NULL;
    game_over_sound = Mix_LoadWAV("audio/gameover.wav");
    // โหลด fonts
    TTF_Font* sans = TTF_OpenFont("OpenSans-Regular.ttf", 100);
    // ตั้งตัวแปร สี
    SDL_Color black = {0, 0, 0};
    // กําหนดข้อความ xxxxxx
    SDL_Surface* surfacemessage = TTF_RenderText_Solid(sans, "xxxxxx", black);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfacemessage);
    SDL_Rect message_rect = {810, 665, 260, 100};
    // กําหนดข้อความ ------
    SDL_Surface* score_die = TTF_RenderText_Solid(sans, "------", black);
    SDL_Texture* score_die_texture = SDL_CreateTextureFromSurface(renderer, score_die);
    SDL_Rect score_die_rect = {530, 675, 250, 90};
    // ตั้งตัวแปรต่างๆ
    int x[1000]; // arrays ของ งู ในแกน x
    int y[1000]; // arrays ของ งู ในแกน y
    int temp_x[1000], temp_y[1000]; // array ไว้พักค่างู
    int size = 3; // ตัวแปรไว้เก็บขนาดของงู (ความยาว) เริ่มต้นที่ 3
    x[0] = 400; // พิกัดของงูตําแหน่งที่ 0 ในแกน x
    y[0] = 400; // พิกัดของงูตําแหน่งที่ 0 ในแกน y
    x[1] = 380; // พิกัดของงูตําแหน่งที่ 1 ในแกน x
    y[1] = 400; // พิกัดของงูตําแหน่งที่ 1 ในแกน y
    x[2] = 360; // พิกัดของงูตําแหน่งที่ 2 ในแกน x
    y[2] = 400; // พิกัดของงูตําแหน่งที่ 2 ในแกน y
    int select_diff = 1; // ตัวแปรเก็บค่าระดับความยาก ตั้งแต่ 1 - 3
    int food_x = 0; // ตําแหน่งของอาหาร ในแกน x
    int food_y = 0; // ตําแหน่งของอาหาร ในแกน y
    char going = 'R'; // ตัวแปรไว้บอกทิศทางของงู (R L U D) ขวา ซ้าย บน ล่าง
    int food_status = 1; // ตัวแปรไว้เช็คว่า อาหารโดนเก็บหรือยัง (0 & 1)
    int keyboard_bug_fix = 1; // ตัวแปรแก้บัค keyboard
    int score = 0; // ตัวแปรเก็บค่า score
    char score_str[10000]; // score ที่เป็น str
    int menu_check = 1; // ตัวแปรไว้บอกว่าตอนนี้อยู่หน้าเมนูอันไหน
    int diff_y = 250; // ตัวแปรไว้เก็บตําแหน่งของรูป ">" ในหน้าเมนูเลือกระดับความยาก แกน y
    int diff_x = 440; // ตัวแปรไว้เก็บตําแหน่งของรูป ">" ในหน้าเมนูเลือกระดับความยาก แกน x
    float menu_x = -820; // ตัวแปรไว้เก็บแกน x ของภาพเมนู
    int menu_pos = 1; // ตัวแปรไว้เก็บว่าขณะนี้ ภาพเมนูเลื่อนจาก ขวา > ซ้าย หรือ ซ้าย > ขวา
    int pause = 0; // กําหนกตัวแปร pause ไว้ใช้เวลา user กดหยุดเกม
    // เล่นเพลง (ไม่มีวันจบ)
    Mix_PlayMusic(music, -1);
    // ตั้งรูปของหน้าต่าง window
    SDL_SetWindowIcon(window, snake_surface);
    // โปรแกรมรัน
    while (running){
        // เช็ค event
        while (SDL_PollEvent(&event)) {
            // ถ้ากดปิดหน้าต่าง
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_RIGHT && going != 'L' && keyboard_bug_fix && menu_check == 3 && !pause){
                    going = 'R';
                    keyboard_bug_fix = 0;
                }
                else if (event.key.keysym.sym == SDLK_LEFT && going != 'R' && keyboard_bug_fix && menu_check == 3 && !pause){
                    going = 'L';
                    keyboard_bug_fix = 0;
                }
                else if (event.key.keysym.sym == SDLK_UP && going != 'D' && keyboard_bug_fix && menu_check == 3 && !pause){
                    going = 'U';
                    keyboard_bug_fix = 0;
                }
                else if (event.key.keysym.sym == SDLK_DOWN && going != 'U' && keyboard_bug_fix && menu_check == 3 && !pause){
                    going = 'D';
                    keyboard_bug_fix = 0;
                }
                else if (menu_check == 1 && event.key.keysym.sym == SDLK_RETURN){
                    menu_check = 2;
                    Mix_PlayChannel( -1, enter, 0 );
                }
                else if (menu_check == 2 && event.key.keysym.sym == SDLK_UP){
                    select_diff --;
                    Mix_PlayChannel( -1, selection, 0 );
                }
                else if (menu_check == 2 && event.key.keysym.sym == SDLK_DOWN){
                    select_diff ++;
                    Mix_PlayChannel( -1, selection, 0 );
                }
                else if (menu_check == 2 && event.key.keysym.sym == SDLK_RETURN){
                    menu_check++;
                    Mix_PlayChannel( -1, enter, 0 );
                }
                else if (menu_check == 4 && event.key.keysym.sym == SDLK_UP){
                    select_diff--;
                    Mix_PlayChannel( -1, selection, 0 );
                }
                else if (menu_check == 4 && event.key.keysym.sym == SDLK_DOWN){
                    select_diff++;
                    Mix_PlayChannel( -1, selection, 0 );
                }
                else if (menu_check == 4 && event.key.keysym.sym == SDLK_RETURN){
                    Mix_PlayChannel( -1, enter, 0 );
                    if (select_diff == 1){
                        score = 0;
                        memset(x, 0, sizeof(x));
                        memset(y, 0, sizeof(y));
                        memset(temp_x, 0, sizeof(temp_x));
                        memset(temp_y, 0, sizeof(temp_y));
                        size = 3;
                        x[0] = 400;
                        y[0] = 400;
                        x[1] = 380;
                        y[1] = 400;
                        x[2] = 360;
                        y[2] = 400;
                        going = 'R';
                        food_status = 1;
                        keyboard_bug_fix = 1;
                        menu_check = 2;
                    }
                    else{
                        running = 0;
                    }
                }
                else if (menu_check == 3 && event.key.keysym.sym == SDLK_p){
                    if (pause == 1){
                        pause = 0;
                    }
                    else{
                        pause = 1;
                    }
                }
            }
        }
        if (menu_check == 1){
            SDL_RenderClear(renderer);
            SDL_Rect menu = {menu_x, 0, 1920, 800};
            if (menu_pos == 1){
                menu_x += 0.01;
            }
            if (menu_pos == 2){
                menu_x -= 0.01;
            }
            if (menu_x >= 0){
                menu_pos = 2;
            }
            if (menu_x <= -820){
                menu_pos = 1;
            }
            SDL_RenderCopy(renderer, menu_texture, NULL, &menu);
            SDL_RenderCopy(renderer, press_title_texture, NULL, &press_title);
            SDL_RenderCopy(renderer, menu_title_texture, NULL, &menu_title);
            SDL_RenderPresent(renderer);
        }
        else if (menu_check == 2){
            SDL_RenderClear(renderer);
            SDL_Rect menu = {menu_x, 0, 1920, 800};
            if (menu_pos == 1){
                menu_x += 0.01;
            }
            if (menu_pos == 2){
                menu_x -= 0.01;
            }
            if (menu_x >= 0){
                menu_pos = 2;
            }
            if (menu_x <= -820){
                menu_pos = 1;
            }
            SDL_RenderCopy(renderer, menu_texture, NULL, &menu);
            SDL_RenderCopy(renderer, diff_title_texture, NULL, &diff_title);
            SDL_RenderCopy(renderer, easy_texture, NULL, &easy);
            SDL_RenderCopy(renderer, medium_texture, NULL, &medium);
            SDL_RenderCopy(renderer, hard_texture, NULL, &hard);
            if (select_diff < 1){
                select_diff = 3;
            }
            if (select_diff > 3){
                select_diff = 1;
            }
            if (select_diff == 1){
                diff_y = 250;
                diff_x = 440;
            }
            if (select_diff == 2){
                diff_y = 450;
                diff_x = 390;
            }
            if (select_diff == 3){
                diff_y = 650;
                diff_x = 440;
            }
            SDL_Rect select = {diff_x, diff_y, 43, 57};
            SDL_RenderCopy(renderer, select_texture, NULL, &select);
            SDL_RenderPresent(renderer);
        }
        else if (menu_check == 3){
            if (pause){
                SDL_RenderCopy(renderer, pausepic_texture, NULL, &pausepic);
                SDL_RenderPresent(renderer);
                continue;
            }
            sprintf(score_str, "%06d", score);
            SDL_Surface* surfacemessage = TTF_RenderText_Solid(sans, score_str, black);
            SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfacemessage);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, bg_texture, NULL, &bg);
            SDL_RenderCopy(renderer, ingame_bg_texture, NULL, &ingame_bg);
            SDL_RenderCopy(renderer, ingame_right_texture, NULL, &ingame_right);
            SDL_RenderCopy(renderer, right_bot_texture, NULL, &right_bot);
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
                SDL_RenderCopy(renderer, snake_texture, NULL, &snake);
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
                Mix_PlayChannel( -1, eat, 0 );
                x[size] = x[size - 1] - 20;
                size++;
                food_status++;
                score += 100;
                SDL_DestroyTexture(food_texture);
            }
            for (int i = 1; i < size; i++){
                if (x[0] == x[i] && y[0] == y[i]){
                    menu_check = 4;
                    Mix_PlayChannel( -1, game_over_sound, 0 );
                    score_die = TTF_RenderText_Solid(sans, score_str, black);
                    score_die_texture = SDL_CreateTextureFromSurface(renderer, score_die);
                    select_diff = 1;
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
            if (select_diff == 1){
                delay_diff = 4000;
            }
            else if (select_diff == 2){
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
            SDL_Rect test_rect = {530, 675, 250, 90};
            SDL_RenderClear(renderer);
            SDL_Rect menu = {menu_x, 0, 1920, 800};
            if (menu_pos == 1){
                menu_x += 0.01;
            }
            if (menu_pos == 2){
                menu_x -= 0.01;
            }
            if (menu_x >= 0){
                menu_pos = 2;
            }
            if (menu_x <= -820){
                menu_pos = 1;
            }
            if (select_diff > 2){
                select_diff = 1;
            }
            if (select_diff < 1){
                select_diff = 2;
            }
            if (select_diff == 1){
                diff_x = 360;
                diff_y = 305;
            }
            if (select_diff == 2){
                diff_x = 450;
                diff_y = 505;
            }
            SDL_RenderCopy(renderer, menu_texture, NULL, &menu);
            SDL_RenderCopy(renderer, gameover_texture, NULL, &gameover);
            SDL_RenderCopy(renderer, playagain_texture, NULL, &playagain);
            SDL_RenderCopy(renderer, exit_texture, NULL, &exit);
            SDL_RenderCopy(renderer, youscore_texture, NULL, &youscore);
            SDL_RenderCopy(renderer, score_die_texture, NULL, &score_die_rect);
            SDL_Rect select = {diff_x, diff_y, 43, 57};
            SDL_RenderCopy(renderer, select_texture, NULL, &select);
            SDL_RenderPresent(renderer);
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();
}