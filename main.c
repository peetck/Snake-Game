#include <SDL.h> // โหลด library SDL
#include <SDL_image.h> // โหลด library SDL_image
#include <stdio.h>  // โหลด library stdio
#include <string.h>  // โหลด library string.h
#include <SDL_mixer.h>  // โหลด library SDL_mixer
#include <stdlib.h>  // โหลด library stdlib.h
#include <SDL_ttf.h>  // โหลด library SDL_ttf
#include <ctype.h>  // โหลด library ctype

/*-----------------------------------------------ตั้งตัวแปรต่างๆให้เป็น Global variable---------------------------------------------------------*/
SDL_Window* window; // หน้าต่างโปรแกรม
SDL_Renderer* renderer; // ตัวแปร render
SDL_Event event; // ตัวแปร event

/* ตัวแปรไว้เก็บภาพงู (icon) */
SDL_Surface* snake_title_surface = NULL;
SDL_Texture* snake_title_texture = NULL;

/* ตัวแปรเก็บรูปกรอบในเกม */
SDL_Surface* bg_surface = NULL;
SDL_Texture* bg_texture = NULL;

/* ตัวแปรภาพพื้นหลังในเกม */
SDL_Surface* ingame_bg_surface = NULL;
SDL_Texture* ingame_bg_texture = NULL;

/* ตัวแปรภาพใน start menu */
SDL_Surface* menu_title_surface = NULL;
SDL_Texture* menu_title_texture = NULL;

/* ตัวแปรภาพใน select difficulty */
SDL_Surface* diff_title_surface = NULL;
SDL_Texture* diff_title_texture = NULL;

/* ตัวแปรภาพ "Press Enter to start" */
SDL_Surface* press_title_surface = NULL;
SDL_Texture* press_title_texture = NULL;

/* ตัวแปรเก็บค่าคําว่า "easy" */
SDL_Surface* easy_surface = NULL;
SDL_Texture* easy_texture = NULL;

/* ตัวแปรเก็บค่าคําว่า "medium" */
SDL_Surface* medium_surface = NULL;
SDL_Texture* medium_texture = NULL;

/* ตัวแปรเก็บค่าคําว่า "hard" */
SDL_Surface* hard_surface = NULL;
SDL_Texture* hard_texture = NULL;

/* ตัวแปรเก็บภาพสัญลักษณ์ ">" */
SDL_Surface* select_surface = NULL;
SDL_Texture* select_texture = NULL;

/* ตัวแปรเก็บภาพอักษร gameover */
SDL_Surface* gameover_surface = NULL;
SDL_Texture* gameover_texture = NULL;

/* ตัวแปรเก็บภาพอักษร play again */
SDL_Surface* playagain_surface = NULL;
SDL_Texture* playagain_texture = NULL;

/* ตัวแปรเก็บภาพอักษร exit */
SDL_Surface* exit_surface = NULL;
SDL_Texture* exit_texture = NULL;

/* ตัวแปรเก็บภาพที่จะขึ้นมาตอนกด pause เกม */
SDL_Surface* pausepic_surface = NULL;
SDL_Texture* pausepic_texture = NULL;

/* ตัวแปรเก็บภาพ score ตอน game over */
SDL_Surface* youscore_surface = NULL;
SDL_Texture* youscore_texture = NULL;

/* ตัวแปรเก็บภาพ menu */
SDL_Surface* menu_surface = NULL;
SDL_Texture* menu_texture = NULL;

/* ตัวแปรเก็บค่าภาพงู */
SDL_Surface* snake_surface = NULL;
SDL_Texture* snake_texture = NULL;

/* ตัวแปรเก็บภาพตอนเล่นเกมในมุมขวา */
SDL_Surface* ingame_right_surface = NULL;
SDL_Texture* ingame_right_texture = NULL;

/* ตัวแปรเก็บภาพตอนเล่นเกมในมุมขวาล่าง */
SDL_Surface* right_bot_surface = NULL;
SDL_Texture* right_bot_texture = NULL;

/* ตัวแปรเก็บภาพอาหาร */
SDL_Surface* food_surface = NULL;
SDL_Texture* food_texture = NULL;

/* ตัวแปรเก็บเพลงหลัก */
Mix_Music *music = NULL;

/* ตัวแปรเก็บ sound effect ตอนงูกินอาหาร */
Mix_Chunk *eat = NULL;

/* ตัวแปรเก็บ sound effect ตอนเลือกต่างๆ */
Mix_Chunk *selection = NULL;

/* ตัวแปรเก็บ sound effect ตอนกด enter เลือก */
Mix_Chunk *enter = NULL;

/* ตัวแปรเก็บ sound effect ตอนกด pause */
Mix_Chunk *beep = NULL;

/* ตัวแปรเก็บ sound effect ตอนตาย */
Mix_Chunk* game_over_sound = NULL;

/* ตั้งตัวแปรต่างๆ */
const int width = 1100; // ความกว้างของหน้าต่างโปรแกรม
const int height = 800; // ความสูงของหน้าต่างโปรแกรม
int x[1000]; // arrays ของ งู ในแกน x
int y[1000]; // arrays ของ งู ในแกน y
int temp_x[1000], temp_y[1000]; // array ไว้พักค่างู
int size = 3; // ตัวแปรไว้เก็บขนาดของงู (ความยาว) เริ่มต้นที่ 3
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
int running; // ตัวแปรไว้ใช้เช็คว่าโปรแกรมรันอยู่หรือไม่

/*--------------------------------------------------------------------------------------------------------*/
int main(int argc, char* args[]){
    TTF_Init(); // init font
    SDL_Init(SDL_INIT_EVERYTHING); // init SDL
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048); // Mix_openaudio
    window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN); // สร้างหน้าต่างโปรแกรม
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // สร้างตัว renderer
    running = 1; // ตั้งค่าตัวแปร running เป็น 1
    /* โหลดภาพงู (icon) */
    snake_title_surface = IMG_Load("image/snake_title.png");
    snake_title_texture = SDL_CreateTextureFromSurface(renderer, snake_title_surface);
    SDL_Rect snake_title = {400, 250, 324, 324};
    /* โหลดกรอบ */
    bg_surface = IMG_Load("image/bg.png");
    bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);
    SDL_Rect bg = {0, 0, 1200, 800};
    /* โหลดภาพพื้นหลังในเกม */
    ingame_bg_surface = IMG_Load("image/ingame_bg.png");
    ingame_bg_texture = SDL_CreateTextureFromSurface(renderer, ingame_bg_surface);
    SDL_Rect ingame_bg = {20, 20, 760, 760};
    /* โหลดภาพ title ใน start menu */
    menu_title_surface = IMG_Load("image/menu_title.png");
    menu_title_texture = SDL_CreateTextureFromSurface(renderer, menu_title_surface);
    SDL_Rect menu_title = {300, 60, 520, 138};
    /* โหลดภาพ title ใน เมนูเลือกระดับความยาก */
    diff_title_surface = IMG_Load("image/select_diff.png");
    diff_title_texture = SDL_CreateTextureFromSurface(renderer, diff_title_surface);
    SDL_Rect diff_title = {225, 60, 664, 151};
    /* โหลดภาพ "Press ENTER to start" ใน start menu */
    press_title_surface = IMG_Load("image/press_title.png");
    press_title_texture = SDL_CreateTextureFromSurface(renderer, press_title_surface);
    SDL_Rect press_title = {320, 660, 443, 53};
    /* โหลดภาพคําว่า "Easy" */
    easy_surface = IMG_Load("image/easy.png");
    easy_texture = SDL_CreateTextureFromSurface(renderer, easy_surface);
    SDL_Rect easy = {480, 250, 143, 76};
    /* โหลดภาพ "Medium" */
    medium_surface = IMG_Load("image/medium.png");
    medium_texture = SDL_CreateTextureFromSurface(renderer, medium_surface);
    SDL_Rect medium = {430, 450, 269, 66};
    /* โหลดภาพ "Hard" */
    hard_surface = IMG_Load("image/hard.png");
    hard_texture = SDL_CreateTextureFromSurface(renderer, hard_surface);
    SDL_Rect hard = {480, 650, 162, 66};
    /* โหลดภาพ ">" */
    select_surface = IMG_Load("image/select.png");
    select_texture = SDL_CreateTextureFromSurface(renderer, select_surface);
    SDL_Rect select = {440, 250, 43, 57};
    /* โหลดภาพ "Game over!!" */
    gameover_surface = IMG_Load("image/gameover.png");
    gameover_texture = SDL_CreateTextureFromSurface(renderer, gameover_surface);
    SDL_Rect gameover = {310, 60, 521, 82};
    /* โหลดภาพ "play again" */
    playagain_surface = IMG_Load("image/playagain.png");
    playagain_texture = SDL_CreateTextureFromSurface(renderer, playagain_surface);
    SDL_Rect playagain = {400, 300, 339, 80};
    /* โหลดภาพ "exit" */
    exit_surface = IMG_Load("image/exit.png");
    exit_texture = SDL_CreateTextureFromSurface(renderer, exit_surface);
    SDL_Rect exit = {490, 500, 134, 66};
    /* โหลดภาพที่จะขึ้นมาเวลา pause */
    pausepic_surface = IMG_Load("image/pause.png");
    pausepic_texture = SDL_CreateTextureFromSurface(renderer, pausepic_surface);
    SDL_Rect pausepic = {260, 320, 290, 127};
    /* โหลด you score */
    youscore_surface = IMG_Load("image/youscore.png");
    youscore_texture = SDL_CreateTextureFromSurface(renderer, youscore_surface);
    SDL_Rect youscore = {300, 700, 480, 70};
    /* โหลดภาพเมนู */
    menu_surface = IMG_Load("image/menu.png");
    menu_texture = SDL_CreateTextureFromSurface(renderer, menu_surface);
    /* โหลดตัวงู */
    snake_surface = IMG_Load("image/snake.png");
    snake_texture = SDL_CreateTextureFromSurface(renderer, snake_surface);
    /* โหลดภาพในเกมด้านขวา */
    ingame_right_surface = IMG_Load("image/right_img.png");
    ingame_right_texture = SDL_CreateTextureFromSurface(renderer, ingame_right_surface);
    SDL_Rect ingame_right = {800, 20, 280, 620};
    /* โหลดภาพในเกมด้านขวาล่าง */
    right_bot_surface = IMG_Load("image/right_bot.png");
    right_bot_texture = SDL_CreateTextureFromSurface(renderer, right_bot_surface);
    SDL_Rect right_bot = {800, 660, 280, 120};
    /* โหลดอาหาร */
    food_surface = IMG_Load("image/plus.png");
    /* โหลด music */
    music = Mix_LoadMUS("audio/bg_music.mp3");
    /* โหลด sound effect ตอนงูกินอาหาร */
    eat = Mix_LoadWAV("audio/eat.wav");
    /* โหลด sound effect ตอนเลื่อน */
    selection = Mix_LoadWAV("audio/selection.wav");
    /* โหลด sound effect ตอนกด enter */
    enter = Mix_LoadWAV("audio/enter.wav");
    /* โหลด sound effect ตอนกด pause */
    beep = Mix_LoadWAV("audio/beep.ogg");
    /* โหลด sound effect game over */
    game_over_sound = Mix_LoadWAV("audio/gameover.wav");
    /* โหลด fonts */
    TTF_Font* sans = TTF_OpenFont("OpenSans-Regular.ttf", 100);
    /* ตั้งตัวแปร สี */
    SDL_Color black = {0, 0, 0};
    /* กําหนดข้อความ xxxxxx */
    SDL_Surface* surfacemessage = TTF_RenderText_Solid(sans, "xxxxxx", black);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfacemessage);
    SDL_Rect message_rect = {810, 665, 260, 100};
    /* กําหนดข้อความ ------ */
    SDL_Surface* score_die = TTF_RenderText_Solid(sans, "------", black);
    SDL_Texture* score_die_texture = SDL_CreateTextureFromSurface(renderer, score_die);
    SDL_Rect score_die_rect = {530, 675, 250, 90};
    /* เล่นเพลง (ไม่มีวันจบ) */
    Mix_PlayMusic(music, -1);
    /* ตั้งรูปของหน้าต่าง window */
    SDL_SetWindowIcon(window, snake_title_surface);
    /* ตั้งพิกัดเริ่มต้นของงู */
    x[0] = 400; // พิกัดของงูตําแหน่งที่ 0 ในแกน x
    y[0] = 400; // พิกัดของงูตําแหน่งที่ 0 ในแกน y
    x[1] = 380; // พิกัดของงูตําแหน่งที่ 1 ในแกน x
    y[1] = 400; // พิกัดของงูตําแหน่งที่ 1 ในแกน y
    x[2] = 360; // พิกัดของงูตําแหน่งที่ 2 ในแกน x
    y[2] = 400; // พิกัดของงูตําแหน่งที่ 2 ในแกน y
    while (running){ // โปรแกรมรัน
        while (SDL_PollEvent(&event)) { // เช็ค event
            if (event.type == SDL_QUIT) { // ถ้ากดปิดหน้าต่าง
                running = 0; // ให้ running เป็น 0
            }
            else if (event.type == SDL_KEYDOWN){ // ถ้า user กด keyboard
                if (event.key.keysym.sym == SDLK_RIGHT && going != 'L' && keyboard_bug_fix && menu_check == 3 && !pause){ // ถ้ากดลูกศรขวาและทิศทางของงูไม่ใช่ ซ้าย และอยู่หน้าเล่นเกมและไม่ได้ pause อยู่
                    going = 'R'; // ให้ทิศทางของงูเป็น R (ขวา)
                    keyboard_bug_fix = 0; // ตัวแก้บัคการกด keyboard
                }
                else if (event.key.keysym.sym == SDLK_LEFT && going != 'R' && keyboard_bug_fix && menu_check == 3 && !pause){ // ถ้ากดลูกศรซ้ายและทิศทางของงูไม่ใช่ ขวา และอยู่หน้าเล่นเกมและไม่ได้ pause อยู่
                    going = 'L'; // ให้ทิศทางของงูเป็น L (ซ้าย)
                    keyboard_bug_fix = 0; // ตัวแก้บัคการกด keyboard
                }
                else if (event.key.keysym.sym == SDLK_UP && going != 'D' && keyboard_bug_fix && menu_check == 3 && !pause){ // ถ้ากดลูกศรขึ้นและทิศทางของงูไม่ใช่ ลง และอยู่หน้าเล่นเกมและไม่ได้ pause อยู่
                    going = 'U'; // ให้ทิศทางของงูเป็น U (บน)
                    keyboard_bug_fix = 0; // ตัวแก้บัคการกด keyboard
                }
                else if (event.key.keysym.sym == SDLK_DOWN && going != 'U' && keyboard_bug_fix && menu_check == 3 && !pause){ // ถ้ากดลูกศรลงและทิศทางของงูไม่ใช่ ขึ้น และอยู่หน้าเล่นเกมและไม่ได้ pause อยู่
                    going = 'D'; // ให้ทิศทางของงูเป็น D (ล่าง)
                    keyboard_bug_fix = 0; // ตัวแก้บัคการกด keyboard
                }
                else if (menu_check == 1 && event.key.keysym.sym == SDLK_RETURN){ // ถ้าอยู่เมนูหน้าแรก และ กด ENTER
                    menu_check = 2; // ให้ไปเมนูหน้าถัดไป
                    Mix_PlayChannel( -1, enter, 0 ); // เล่น soundeffect enter
                }
                else if (menu_check == 2 && event.key.keysym.sym == SDLK_UP){ // ถ้าอยู่เมนูหน้าที่สอง และ กด ลูกศรขึ้น
                    select_diff --; // ให้ตัวแปร select_diff (เลือกตําแหน่ง) ลดลงหนึ่ง
                    Mix_PlayChannel( -1, selection, 0 ); // เล่น sound effect selection
                }
                else if (menu_check == 2 && event.key.keysym.sym == SDLK_DOWN){ // ถ้าอยู่เมนูหน้าที่สอง และ กด ลูกศรลง
                    select_diff ++; // ให้ตัวแปร select_diff (เลือกตําแหน่ง) เพิ่มขึ้นหนึ่ง
                    Mix_PlayChannel( -1, selection, 0 ); // เล่น sound effect selection
                }
                else if (menu_check == 2 && event.key.keysym.sym == SDLK_RETURN){ // ถ้าอยู่เมนูหน้าที่สอง และ กด ENTER
                    menu_check++;
                    Mix_PlayChannel( -1, enter, 0 ); // เล่น soundeffect enter
                }
                else if (menu_check == 4 && event.key.keysym.sym == SDLK_UP){ // ถ้าอยู่เมนูหน้าที่สี่ และ กด ลูกศรขึ้น
                    select_diff--;
                    Mix_PlayChannel( -1, selection, 0 ); // เล่น sound effect selection
                }
                else if (menu_check == 4 && event.key.keysym.sym == SDLK_DOWN){ // ถ้าอยู่เมนูหน้าที่สี่ และ กด ลูกศรลง
                    select_diff++;
                    Mix_PlayChannel( -1, selection, 0 ); // เล่น sound effect selection
                }
                else if (menu_check == 4 && event.key.keysym.sym == SDLK_RETURN){  // ถ้าอยู่เมนูหน้าที่สี่ และ กด ENTER
                    Mix_PlayChannel( -1, enter, 0 ); // เล่น soundeffect enter
                    if (select_diff == 1){ // ถ้าเลือก play again ในหน้าเมนู gameover
                        score = 0; // reset score
                        memset(x, 0, sizeof(x)); // clear array ของงูในแกน x
                        memset(y, 0, sizeof(y)); // clear array ของงูในแกน y
                        memset(temp_x, 0, sizeof(temp_x)); // clear array ของตัวพักค่างูในแกน x
                        memset(temp_y, 0, sizeof(temp_y)); // clear array ของตัวพักค่างูในแกน y
                        size = 3; // ขนาดเริ่มต้นกลับไปเป็นเท่าเดิมคือ 3
                        x[0] = 400; // พิกัดของงูตําแหน่งที่ 0 ในแกน x
                        y[0] = 400; // พิกัดของงูตําแหน่งที่ 0 ในแกน y
                        x[1] = 380; // พิกัดของงูตําแหน่งที่ 1 ในแกน x
                        y[1] = 400; // พิกัดของงูตําแหน่งที่ 1 ในแกน y
                        x[2] = 360; // พิกัดของงูตําแหน่งที่ 2 ในแกน x
                        y[2] = 400; // พิกัดของงูตําแหน่งที่ 2 ในแกน y
                        going = 'R'; // ทิศทางไปทางขวา
                        food_status = 1; // ตั้งตัวแปร food_status เป็น 1
                        keyboard_bug_fix = 1; // ตัวแก้บัคการกด keyboard
                        menu_check = 2; // ให้หน้าเมนูเริ่มต้นที่ หน้าที่สอง (หน้าเลือกระดับความยาก)
                    }
                    else{ // ถ้าเลือก Exit
                        running = 0; // ให้หยุดการทํางานโปรแกรมด้วยการเซ็ท running เป็น 0
                    }
                }
                else if (menu_check == 3 && event.key.keysym.sym == SDLK_p){ // ถ้าอยู่หน้าเล่นเกมและกดตัวอักษร p บน keyboard
                    if (pause == 1){ // เช็คว่าขณะนี้ pause อยู่หรือไม่
                        pause = 0; // ให้ pause เป็น 0
                        Mix_PlayChannel( -1, enter, 0 ); // เล่น sound effect ENTER
                    }
                    else{ // ถ้าไม่ได้ pause อยู่
                        pause = 1; // ให้ pause เป็น 1
                        Mix_PlayChannel( -1, beep, 0 ); // เล่น sound effect beep
                    }
                }
            }
        }
        if (menu_check == 1){ // ถ้าอยู่หน้าเมนูแรก
            SDL_RenderClear(renderer); // clear ตัว renderer
            SDL_Rect menu = {menu_x, 0, 1920, 800}; // ตั้งค่าพิกัดของภาพ menu
            if (menu_pos == 1){ // ถ้าเลื่อนไปทางขวา
                menu_x += 0.01; // แกน x ของภาพ menu + 0.01
            }
            if (menu_pos == 2){ // ถ้าเลื่อนไปทางซ้าย
                menu_x -= 0.01;  // แกน x ของภาพ menu - 0.01
            }
            if (menu_x >= 0){ // ถ้าแกน x ของภาพ menu มากกว่าเท่ากับ 0 ให้เลือกไปทางซ้าย
                menu_pos = 2; // menu_pos = 2
            }
            if (menu_x <= -820){  // ถ้าแกน x ของภาพ menu น้อยกว่าเท่ากับ -820 ให้เลือกไปทางขวา
                menu_pos = 1; // menu_pos = 1
            }
            SDL_RenderCopy(renderer, menu_texture, NULL, &menu); // ทําการ render ภาพ menu
            SDL_RenderCopy(renderer, press_title_texture, NULL, &press_title); // ทําการ render ภาพ Press ENTER to Start
            SDL_RenderCopy(renderer, menu_title_texture, NULL, &menu_title); // ทําการ render ภาพ Snake Game
            SDL_RenderPresent(renderer); // Present ออกทางหน้าจอ
        }
        else if (menu_check == 2){ // ถ้าอยู่หน้าเมนูที่สอง
            SDL_RenderClear(renderer); // clear ตัว renderer
            SDL_Rect menu = {menu_x, 0, 1920, 800}; // ตั้งค่าพิกัดของภาพ menu
            if (menu_pos == 1){ // ถ้าเลื่อนไปทางขวา
                menu_x += 0.01; // แกน x ของภาพ menu + 0.01
            }
            if (menu_pos == 2){ // ถ้าเลื่อนไปทางซ้าย
                menu_x -= 0.01;  // แกน x ของภาพ menu - 0.01
            }
            if (menu_x >= 0){ // ถ้าแกน x ของภาพ menu มากกว่าเท่ากับ 0 ให้เลือกไปทางซ้าย
                menu_pos = 2; // menu_pos = 2
            }
            if (menu_x <= -820){  // ถ้าแกน x ของภาพ menu น้อยกว่าเท่ากับ -820 ให้เลือกไปทางขวา
                menu_pos = 1; // menu_pos = 1
            }
            SDL_RenderCopy(renderer, menu_texture, NULL, &menu); // ทําการ render ภาพ menu
            SDL_RenderCopy(renderer, diff_title_texture, NULL, &diff_title); // ทําการ render ภาพ Select difficulty
            SDL_RenderCopy(renderer, easy_texture, NULL, &easy);  // ทําการ render ภาพ Easy
            SDL_RenderCopy(renderer, medium_texture, NULL, &medium);  // ทําการ render ภาพ Medium
            SDL_RenderCopy(renderer, hard_texture, NULL, &hard);  // ทําการ render ภาพ Hard
            if (select_diff < 1){ // ถ้าตัวชี้ตําแหน่งการเลือก น้อยกว่า 1 ให้กลายเป็น 3
                select_diff = 3;
            }
            if (select_diff > 3){ // ถ้าตัวชี้ตําแหน่งการเลือก มากกว่า 3 ให้กลายเป็น 1
                select_diff = 1;
            }
            if (select_diff == 1){ // ถ้าตัวชี้ตําแหน่งการเลือก เท่ากับ 1 ให้ตั้งค่าแกน x และ y ของภาพ ">"
                diff_y = 250;
                diff_x = 440;
            }
            if (select_diff == 2){ // ถ้าตัวชี้ตําแหน่งการเลือก เท่ากับ 2 ให้ตั้งค่าแกน x และ y ของภาพ ">"
                diff_y = 450;
                diff_x = 390;
            }
            if (select_diff == 3){ // ถ้าตัวชี้ตําแหน่งการเลือก เท่ากับ 3 ให้ตั้งค่าแกน x และ y ของภาพ ">"
                diff_y = 650;
                diff_x = 440;
            }
            SDL_Rect select = {diff_x, diff_y, 43, 57}; // ตั้งพิกัดของภาพ ">"
            SDL_RenderCopy(renderer, select_texture, NULL, &select); // ทําการ render ภาพ ">"
            SDL_RenderPresent(renderer); // Present ออกทางหน้าจอ
        }
        else if (menu_check == 3){ // ถ้าอยู่หน้าเมนูที่สาม (ในเกม)
            if (pause){ // เช็คว่าตัวแปร pause มีค่า เป็น จริงหรือไม่ (user กด pause เกมหรือเปล่า)
                SDL_RenderCopy(renderer, pausepic_texture, NULL, &pausepic); // ให้แสดงข้อความ pause
                SDL_RenderPresent(renderer); // Present ภาพเดิมออกทางหน้าจอ
                continue; // continue
            }
            sprintf(score_str, "%06d", score); // แปลง score ที่เป็น int เป็น string ที่มีความยาว 6 ตัวอักษรและเก็บไว้ในตัวแปร score_str
            SDL_Surface* surfacemessage = TTF_RenderText_Solid(sans, score_str, black); // ตั้งค่า font และ ข้อความ และ สี
            SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfacemessage); // ตั้งค่า texture ของ message
            SDL_RenderClear(renderer); // clear ตัว renderer
            SDL_RenderCopy(renderer, bg_texture, NULL, &bg); // ทําการ render ภาพกรอบ
            SDL_RenderCopy(renderer, ingame_bg_texture, NULL, &ingame_bg); // ทําการ render ภาพพื้นหลัง
            SDL_RenderCopy(renderer, ingame_right_texture, NULL, &ingame_right);  // ทําการ render ภาพทางขวา
            SDL_RenderCopy(renderer, right_bot_texture, NULL, &right_bot);  // ทําการ render ภาพทางขวาล่าง
            while (food_status){ // เช็คว่างูกินอาหารหรือยัง
                food_texture = SDL_CreateTextureFromSurface(renderer, food_surface); // ตั้ง texture
                food_x = 20 * (rand() % 35); // random แกน x ของอาหาร
                food_y = 20 * (rand() % 35); // random แกน y ของอาหาร
                if (food_x == 0) food_x = 20; // ถ้า random ได้ 0 ให้เป็น 20
                if (food_y == 0) food_y = 20; // ถ้า random ได้ 0 ให้เป็น 20
                food_status = 0; // ตั้งค่า food_status เป็น 0

                /* เช็คว่าพิกัดของอาหารซํ้ากับตัวงูหรือไม่ */
                for (int i = 0; i < size; i++){
                    if (food_x == x[i] && food_y == y[i]){
                        food_status++;
                        break;
                    }
                }
                /*------------------------------*/
            }
            SDL_Rect food = {food_x, food_y, 20, 20}; // ตั้งพิกัดของอาหาร
            SDL_RenderCopy(renderer, food_texture, NULL, &food); // ทําการ render อาหาร

            /* ทําการ render ตัวงู */
            for (int i = 0; i < size; i++){
                SDL_Rect snake = {x[i], y[i], 20, 20};
                SDL_RenderCopy(renderer, snake_texture, NULL, &snake);
            }
            /* -----------------*/

            if (going == 'R'){ // ถ้าทิศทางไปทางขวาให้แกน x บวก
                x[0] += 20;
            }
            else if (going == 'L'){ // ถ้าทิศทางไปทางซ้ายให้แกน x ลบ
                x[0] -= 20;
            }
            else if (going == 'U'){ // ถ้าทิศทางขึ้นด้านบนให้แกน y ลบ
                y[0] -= 20;
            }
            else if (going == 'D'){ // ถ้าทิศทางลงด้านล่างให้แกน y บวก
                y[0] += 20;
            }

            /* เงื่อนไขเวลาทะลุกรอบแล้วไปโผล่อีกด้านนึง */
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
            /* ---------------------------------*/

            if (x[0] == food_x && y[0] == food_y){ // ถ้าเก็บอาหารได้
                Mix_PlayChannel( -1, eat, 0 ); // เล่น sound effect eat
                x[size] = x[size - 1] - 20; // เพิ่มขนาดของงู
                size++; // ตัวแปรขนาด บวก 1
                food_status++; // ตั้ง food_status = 1 เพื่อให้ไป render อาหารใหม่
                score += 100; // ได้คะแนน 100
                SDL_DestroyTexture(food_texture); // ทําลาย texture อาหารเก่าทิ้ง
            }

            for (int i = 1; i < size; i++){
                if (x[0] == x[i] && y[0] == y[i]){ // ถ้างูชนตัวเอง
                    menu_check = 4; // ให้หน้าเมนู = 4
                    Mix_PlayChannel( -1, game_over_sound, 0 ); // เล่น sound effect gameover
                    score_die = TTF_RenderText_Solid(sans, score_str, black); // ตั้งค่า font ข้อความและ สี
                    score_die_texture = SDL_CreateTextureFromSurface(renderer, score_die); // ทําการสร้าง texture score ที่จะนําไว้แสดงในหน้าเมนูที่ 4
                    select_diff = 1; // รีเซ็ทตัวชี้ เป็น 1
                    break; //หยุด loop นี้
                }
                x[i] = temp_x[i - 1]; // นําค่างูที่พักไว้มาใส่ใน array แกน x
                y[i] = temp_y[i - 1]; // นําค่างูที่พักไว้มาใส่ใน array แกน y
            }

            /* เก็บค่างูในปัจจุบันไว้ใน ตัวแปรพักค่า */
            for (int i = 0; i < size; i++){
                temp_x[i] = x[i];
                temp_y[i] = y[i];
            }

            SDL_RenderCopy(renderer, message, NULL, &message_rect); // ทําการ render score
            SDL_RenderPresent(renderer); // Present ออกทางหน้าจอ

            /* ตั้งค่า delay time ตามระดับความยากที่เลือกไว้ */
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
            /*--------------------------------------*/

            keyboard_bug_fix = 1; // ตัวแปรแก้ bug keyboard
        }
        else if (menu_check == 4){ // ถ้าหน้าเมนูเป็น 4
            SDL_RenderClear(renderer); // clear ตัว renderer
            SDL_Rect menu = {menu_x, 0, 1920, 800}; // ตั้งค่าพิกัดของภาพ menu

            if (menu_pos == 1){ // ถ้าเลื่อนไปทางขวา
                menu_x += 0.01; // แกน x ของภาพ menu + 0.01
            }
            if (menu_pos == 2){ // ถ้าเลื่อนไปทางซ้าย
                menu_x -= 0.01;  // แกน x ของภาพ menu - 0.01
            }
            if (menu_x >= 0){ // ถ้าแกน x ของภาพ menu มากกว่าเท่ากับ 0 ให้เลือกไปทางซ้าย
                menu_pos = 2; // menu_pos = 2
            }
            if (menu_x <= -820){  // ถ้าแกน x ของภาพ menu น้อยกว่าเท่ากับ -820 ให้เลือกไปทางขวา
                menu_pos = 1; // menu_pos = 1
            }

            if (select_diff > 2){ // ถ้าตัวชี้ มากกว่า 2 ให้ เท่ากับ 1
                select_diff = 1;
            }
            if (select_diff < 1){ // ถ้าตัวชี้ตําแหน่งน้อยกว่า 1 ให้เท่ากับ 2
                select_diff = 2;
            }
            if (select_diff == 1){ // ตั้งค่าแกน x และ y ของภาพ ">" ตามตัวชี้ตําแหน่ง
                diff_x = 360;
                diff_y = 305;
            }
            if (select_diff == 2){ // ตั้งค่าแกน x และ y ของภาพ ">" ตามตัวชี้ตําแหน่ง
                diff_x = 450;
                diff_y = 505;
            }
            SDL_RenderCopy(renderer, menu_texture, NULL, &menu); // ทําการ render ภาพ menu
            SDL_RenderCopy(renderer, gameover_texture, NULL, &gameover); // ทําการ render ภาพ Game over
            SDL_RenderCopy(renderer, playagain_texture, NULL, &playagain); // ทําการ render ภาพ Play again
            SDL_RenderCopy(renderer, exit_texture, NULL, &exit); // ทําการ render ภาพ Exit
            SDL_RenderCopy(renderer, youscore_texture, NULL, &youscore); // ทําการ render ภาพ Score:
            SDL_RenderCopy(renderer, score_die_texture, NULL, &score_die_rect); // ทําการแสดง score ที่ได้
            SDL_Rect select = {diff_x, diff_y, 43, 57}; // ตั้งพิกัดของภาพ ">"
            SDL_RenderCopy(renderer, select_texture, NULL, &select); // ทําการ render ภาพ ">"
            SDL_RenderPresent(renderer); // Present ออกทางจอภาพ
        }
    }
    // ถ้าออกจากโปรแกรม
    SDL_DestroyRenderer(renderer); // ทําลายตัว renderer
    SDL_DestroyWindow(window); // ทําลายหน้าต่างโปรแกรม
    Mix_FreeMusic(music);
    Mix_CloseAudio(); // ปิดเสียงเพลง
    SDL_Quit(); // ออกจากโปรแกรม
}
