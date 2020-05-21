/* C program to solve Maze problem using backtracking */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "boolean.h"

int baris,kolom;
int curDir = 0;
int xp,yp;

void solveMazeUtil(int maze[baris][kolom], int* x, int* y, int vis[baris][kolom]);
bool isPath(int maze[baris][kolom], int x, int y);

void msleep(int ms)
{
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

/* A utility function to print the maze movement */
void printSolution(int maze[baris][kolom], int x, int y) 
{ 
    msleep(50 * 10);
    system("@cls||clear");
    for (int i = 0; i < baris; i++) { 
        for (int j = 0; j < kolom; j++) {
            if (maze[i][j] == 0) 
            {
                if (i == x && j == y) printf(" O ");
                else printf("   ");
            }
            if (maze[i][j] == 1) printf(" X ");
        }
        printf("\n");
    }
} 

/* A utility function to check if x, y is valid index for M*N maze */
bool isSafe(int maze[baris][kolom], int x, int y) 
{ 
    // if (x, y outside maze) return false 
    if (x >= 0 && x < baris && y >= 0 && y < kolom && maze[x][y] == 0) 
        return true; 
    return false; 
}

/* A utility function to search the initialized position */
void initPos(int maze[baris][kolom], int* x, int* y)
{
    int i = 0;
    int j = 0;
    while (i < baris && maze[i][j] != 2)
    {
        j = 0;
        while (j < kolom && maze[i][j] != 2) j++;
        if (maze[i][j] != 2) i++;
    }
    *x = i; *y = j;
}
  
/* This function solves the Maze problem using Backtracking.  It mainly 
   uses solveMazeUtil() to solve the problem. It returns false if no  
   path is possible (asumption: goal is always at the bottom section)*/
bool solveMaze(int maze[baris][kolom]) 
{ 
    int vis[baris][kolom]; 
    for (int i = 0; i < baris; i++)
    {
        for (int j = 0; j < kolom; j++)
        {
            vis[i][j] = 1;   
        }
    }
    int x,y;
    xp = -1; yp = -1;
    initPos(maze,&x,&y);
    maze[x][y] = 0;
    while (true){
        if ((x == baris - 1 ||  y == kolom - 1) && maze[x][y] == 0) break;
        solveMazeUtil(maze,&x,&y,vis);
    }
    return true; 
}
  
/* Backtracking with movement hierarchy (Down->Left->Right->Up) */
void solveMazeUtil(int maze[baris][kolom], int* x, int* y, int vis[baris][kolom]) 
{ 
    if (isSafe(maze,*x+1,*y) && (*x+1 != xp || *y != yp) && vis[*x+1][*y]){
        xp = *x; yp = *y;
        *x += 1;
        curDir = 0;
    } 
    else if (isSafe(maze,*x,*y-1) && (*x != xp || *y-1 != yp) && vis[*x][*y-1]){
        xp = *x; yp = *y;
        *y -= 1;
        curDir = 1;
    } 
    else if (isSafe(maze,*x,*y+1) && (*x != xp || *y+1 != yp) && vis[*x][*y+1]){
        xp = *x; yp = *y;
        *y += 1;
        curDir = 2;
    } 
    else if (isSafe(maze,*x-1,*y) && (*x-1 != xp || *y != yp) && vis[*x-1][*y]){
        xp = *x; yp = *y;
        *x -= 1;
        curDir = 3;
    } 
    else {
        if (isSafe(maze,*x+1,*y) && (*x+1 != xp || *y != yp)){
            xp = *x; yp = *y;
            *x += 1;
            curDir = 0;
        }
        else if (isSafe(maze,*x,*y-1) && (*x != xp || *y-1 != yp)){
            xp = *x; yp = *y;
            *y -= 1;
            curDir = 1;
        } 
        else if (isSafe(maze,*x,*y+1) && (*x != xp || *y+1 != yp)){
            xp = *x; yp = *y;
            *y += 1;
            curDir = 2;
        } 
        else if (isSafe(maze,*x-1,*y) && (*x-1 != xp || *y != yp)){
            xp = *x; yp = *y;
            *x -= 1;
            curDir = 3;
        } 
        else {
            int xt, yt;
            xt = *x; yt = *y;
            *x = xp; *y = yp;
            xp = xt; yp = yt;
        }
    }
    vis[*x][*y] = 0;
    printSolution(maze,*x,*y); 
} 

// Main program
int main() 
{
    printf("Masukkan jumlah baris: "); scanf("%d", &baris);
    printf("Masukkan jumlah kolom: "); scanf("%d", &kolom);
    int maze[baris][kolom];
    printf("Masukkan kode peta: \n");
    for (int i = 0; i < baris; i++)
    {
        for (int j = 0; j < kolom; j++)
        {
            int el;
            scanf("%d", &el);
            maze[i][j] = el;   
        }
    }
    clock_t begin = clock();
    solveMaze(maze);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Selesai\n");
    printf("--------------------------------------------");
    printf("\nOperation took %f milliseconds\n", time_spent);
    return 0; 
} 