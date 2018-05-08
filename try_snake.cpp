#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;

struct snake_inf{
    int speed;
    int len;
    int x[20];
    int y[40];
}snake;

struct food_inf{
    int x;
    int y;
}food;

int flag = 0;
int frame_x = 20;
int frame_y = 40;
char ch = 'w';

void gotoxy(int x,int y)
{
    COORD c;
    HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(h,c);
}

void init_map()
{
    int i,j;
    srand(time(NULL));
    for(i = 0;i < frame_y;i++){
        printf("#");
    }
    printf("\n");
    for(i = 0;i < frame_x-1;i++){
        printf("#\n");
    }
    gotoxy(1,frame_x-1);
    for(i = 0;i < frame_y-1;i++){
        printf("#");
    }
    for(i = 0;i < frame_x;i++){
       gotoxy(frame_y-1,i);
       printf("#\n");
   }
   food.x = rand()%18+1;
   food.y = rand()%38+1;
   gotoxy(food.y,food.x);
   printf("$");
   snake.x[0] = rand()%16+1;
   snake.y[0] = rand()%38+1;
   snake.x[1] = snake.x[0]+1; snake.x[2] = snake.x[0]+2;
   snake.y[1] = snake.y[0]; snake.y[2] = snake.y[0];
   for(i = 0;i < 3;i++){
        gotoxy(snake.y[i],snake.x[i]);
        printf("@");
   }
   snake.len = 3;
   snake.speed = 200;
}

void update_food()
{
    if(snake.x[0] == food.x && snake.y[0] == food.y){
        food.x = rand()%18+1;
        food.y = rand()%38+1;
        gotoxy(food.y,food.x);
        printf("$");
        snake.len++;
        flag = 1;
    }
}

void move_snake()
{
    if(kbhit())
        ch = getch();
    if(!flag){
        gotoxy(snake.y[snake.len-1],snake.x[snake.len-1]);
        printf(" ");
    }
    for(int i = snake.len-1;i > 0;i--){
        snake.x[i] = snake.x[i-1];
        snake.y[i] = snake.y[i-1];
    }
    switch(ch){
        case 'w': snake.x[0]--; break;
        case 's': snake.x[0]++; break;
        case 'a': snake.y[0]--; break;
        case 'd': snake.y[0]++; break;
        default:
            break;
    }
    gotoxy(snake.y[0],snake.x[0]);
    printf("@");
    flag = 0;
    gotoxy(0,frame_x);
}

void update_speed()
{
    if(snake.len <= 6){
        snake.speed = 500;
    }else if(snake.len <= 10){
        snake.speed = 100;
    }else if(snake.len <= 13){
        snake.speed = 80;
    }else{
        snake.speed = 60;
    }
}

bool alive()
{
    int i;
    for(i = 1;i < snake.len ;i++)
        if(snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i])
            return 0;
    if(snake.x[0] == 0 || snake.y[0] == 0 || snake.x[0] == frame_x-1 || snake.y[0] == frame_y-1)
        return 0;
    return 1;
}

int main()
{
    init_map();
    while(1)
    {
       update_food();
       move_snake();
       update_speed();
       Sleep(snake.speed);
       if(!alive()){
          gotoxy(0,frame_x);
          printf("Game Over!");
          break;
       }
    }
    system("pause");
    return 0;
}
