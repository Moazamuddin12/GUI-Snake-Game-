#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define GRID_SIZE 15       
#define CELL_SIZE 50       
#define MAX_LENGTH 256      

typedef enum {
    PLAYING_MODE,
    GAME_OVER
} GameState;


typedef struct {
    int x[MAX_LENGTH];      
    int y[MAX_LENGTH];      
    int length;            
    int dx;                
    int dy;                
} Snake;

typedef struct {
    int x;                
    int y;                 
} Food;

void InitGame(Snake* snake, Food* food, int* score);
void DrawGame(Snake* snake, Food* food, int score);
void MoveSnake(Snake* snake);
bool DetectFood(Snake* snake, Food* food, int* score, Sound eatSound);
bool DetectCollision(Snake* snake);
void ResetGame(Snake* snake);
void GenerateFood(Food* food, Snake* snake);

int main(void)
{
    srand(time(NULL));

    const int screenWidth = GRID_SIZE * CELL_SIZE;
    const int screenHeight = GRID_SIZE * CELL_SIZE;

    InitWindow(screenWidth, screenHeight, "Snake Game - State Machine");
    SetTargetFPS(10);

    InitAudioDevice();
    Sound eatSound = LoadSound("Sounds/eat.mp3");
    Sound wallSound = LoadSound("Sounds/wall.mp3");

    Snake snake;
    Food food;
    int score = 0;
    
    GameState state = PLAYING_MODE; 
    
    InitGame(&snake, &food, &score);

    while (!WindowShouldClose())
    {    
        if (state == PLAYING_MODE)
        {
            
            if (IsKeyPressed(KEY_UP) && snake.dy == 0)    { snake.dx = 0; snake.dy = -1; }
            if (IsKeyPressed(KEY_DOWN) && snake.dy == 0)  { snake.dx = 0; snake.dy = 1; }
            if (IsKeyPressed(KEY_LEFT) && snake.dx == 0)  { snake.dx = -1; snake.dy = 0; }
            if (IsKeyPressed(KEY_RIGHT) && snake.dx == 0) { snake.dx = 1; snake.dy = 0; }

            MoveSnake(&snake);

            if (DetectFood(&snake, &food, &score, eatSound)) {
                GenerateFood(&food, &snake);
            }

            if (DetectCollision(&snake)) {
                PlaySound(wallSound);
                state = GAME_OVER;
            }
        }
        else if (state == GAME_OVER)
        {
            if (IsKeyPressed(KEY_ENTER)) {
                ResetGame(&snake);
                score = 0;
                GenerateFood(&food, &snake);
                state = PLAYING_MODE;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawGame(&snake, &food, score);

        if (state == GAME_OVER) {
            DrawText("GAME OVER", screenWidth/2 - 100, screenHeight/2 - 50, 40, DARKGRAY);
            DrawText("Press ENTER to Restart", screenWidth/2 - 120, screenHeight/2 + 10, 20, DARKGRAY);
        }

        EndDrawing();
    }

    UnloadSound(eatSound);
    UnloadSound(wallSound);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

void InitGame(Snake* snake, Food* food, int* score)
{
    snake->length = 3;
    snake->x[0] = GRID_SIZE / 2;
    snake->y[0] = GRID_SIZE / 2;
    snake->x[1] = snake->x[0]-1;
    snake->y[1] = snake->y[0];
    snake->x[2] = snake->x[1]-1;
    snake->y[2] = snake->y[0];
    snake->dx = 1;
    snake->dy = 0;

    *score = 0;

    GenerateFood(food, snake);
}

void DrawGame(Snake* snake, Food* food, int score)
{

    for (int i=0; i<snake->length; i++)
    {
        DrawRectangle(snake->x[i]*CELL_SIZE, snake->y[i]*CELL_SIZE, CELL_SIZE, CELL_SIZE, GREEN);
    }

    DrawRectangle(food->x*CELL_SIZE, food->y*CELL_SIZE, CELL_SIZE, CELL_SIZE, RED);

    DrawText(TextFormat("Score: %d", score), 10, 10, 20, BLACK);
}

void MoveSnake(Snake* snake)
{
    for (int i = snake->length-1; i > 0; i--)
    {
        snake->x[i] = snake->x[i-1];
        snake->y[i] = snake->y[i-1];
    }
    snake->x[0] += snake->dx;
    snake->y[0] += snake->dy;
}

bool DetectFood(Snake* snake, Food* food, int* score, Sound eatSound)
{
    if (snake->x[0] == food->x && snake->y[0] == food->y)
    {
        if (snake->length < MAX_LENGTH)
        {
            snake->length++;
            snake->x[snake->length-1] = snake->x[snake->length-2];
            snake->y[snake->length-1] = snake->y[snake->length-2];
        }
        (*score)++;
        PlaySound(eatSound);
        return true;
    }
    return false;
}


bool DetectCollision(Snake* snake)
{
    if (snake->x[0] < 0 || snake->x[0] >= GRID_SIZE ||
        snake->y[0] < 0 || snake->y[0] >= GRID_SIZE)
    {
        return true;
    }
    for (int i=1; i<snake->length; i++)
    {
        if (snake->x[0] == snake->x[i] && snake->y[0] == snake->y[i])
            return true;
    }
    return false;
}

void ResetGame(Snake* snake)
{
    snake->length = 3;
    snake->x[0] = GRID_SIZE / 2;
    snake->y[0] = GRID_SIZE / 2;
    snake->x[1] = snake->x[0]-1;
    snake->y[1] = snake->y[0];
    snake->x[2] = snake->x[1]-1;
    snake->y[2] = snake->y[0];
    snake->dx = 1;
    snake->dy = 0;
}

void GenerateFood(Food* food, Snake* snake)
{
    bool valid = false;
    while (!valid)
    {
        food->x = rand() % GRID_SIZE;
        food->y = rand() % GRID_SIZE;
        valid = true;
        for (int i=0; i<snake->length; i++)
        {
            if (snake->x[i] == food->x && snake->y[i] == food->y)
            {
                valid = false;
                break;
            }
        }
    }
}
