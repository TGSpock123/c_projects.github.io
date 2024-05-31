#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>

#define COUNT 4
#define X_UP 124
#define Y_UP 200
#define TIME 30
#define DS_PER_SEC 60 
#define CLOCK_PER_DS ((CLOCKS_PER_SEC) / 60)

void init_window (void);
void put_white (int j, int p);
void put_black (int j, int p);
void draw_map (void);
void init_black (void);
void draw_black (void);
void init_word (void);
void put_word (int j, int p);
void play (void);
