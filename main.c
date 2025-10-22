#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define BOARD_SIZE 8
#define TILE_SIZE 42
#define TILE_TYPES 5
#define SCORE_FONT_SIZE 32
const char tile_chars[TILE_TYPES] = {'#' , '@' , '$' , '%', '&'};

char board[BOARD_SIZE][BOARD_SIZE];

Vector2 grid_origin;

Texture2D background;
Font score_font;

int score = 200;

Vector2 selected_tile = {-1,-1};

char random_tile() {
    return tile_chars[rand() % TILE_TYPES];
}



void init_board() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = random_tile();
        }
    }
    int grid_width = BOARD_SIZE * TILE_SIZE;
    int grid_height = BOARD_SIZE * TILE_SIZE;
    grid_origin = (Vector2){
        (GetScreenWidth() - grid_width) / 2,
        (GetScreenHeight() - grid_height) / 2
    };
}




int main(void) {
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 450;
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tile 3 By 004X");
    SetTargetFPS(60);
    srand(time(NULL));
    background = LoadTexture("Resources/bg.png");
    score_font = LoadFontEx("Resources/font.ttf", SCORE_FONT_SIZE, NULL, 0);
    init_board();
    Vector2 mouse = {0,0 };

    while (!WindowShouldClose()) {

        mouse = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            int x = (mouse.x - grid_origin.x) / TILE_SIZE;
            int y = (mouse.y - grid_origin.y) / TILE_SIZE;
            if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
                selected_tile = (Vector2){x,y};
            }

        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTexturePro(
            background,
            (Rectangle){
                0,0, background.width, background.height
            },
            (Rectangle){
                0,0, GetScreenWidth(), GetScreenHeight()
            },
            (Vector2){
                0,0
            },
            0,
            YELLOW
        );

        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                Rectangle rect = {
                    grid_origin.x + i * TILE_SIZE,
                    grid_origin.y + j * TILE_SIZE,
                    TILE_SIZE,
                    TILE_SIZE,
                };
                DrawRectangleLinesEx(rect, 1,DARKGRAY);
                DrawTextEx(
                    GetFontDefault(),
                    TextFormat("%c", board[i][j]),
                    (Vector2){ rect.x+12, rect.y+8 },
                    20,
                    1,
                    WHITE
                );

            }
        }
        // Draw Selected Tile
        if (selected_tile.x >= 0 && selected_tile.y >= 0) {
            DrawRectangleLinesEx(
                (Rectangle){
                grid_origin.x + (selected_tile.x * TILE_SIZE),
                grid_origin.y + (selected_tile.y * TILE_SIZE),
                TILE_SIZE,
                TILE_SIZE
                },
                2,
                YELLOW
            );
        }

        // DrawText(TextFormat("Score %d", score), 20, 20 , 24, DARKBLUE);
        DrawTextEx(
            score_font,
            TextFormat("Score: %d" , score),
            (Vector2){20,20},
            SCORE_FONT_SIZE,
            1.0f,
            DARKBLUE
        );

        EndDrawing();
    }
    UnloadTexture(background);
    CloseWindow();
    return 0;
}