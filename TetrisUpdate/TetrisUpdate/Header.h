#pragma once
#include <iostream>
#include <Windows.h>
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <string>
#include <vector>
#include <cstdlib>
#include <random>
#include <ctime>
#include <SDL_ttf.h>
#include <fstream>
#include <SDL_mixer.h>

using namespace std;

//Quan ly man hinh
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 667;

const int block[7][4] = {
	1, 3, 5, 7, //I
	2, 4, 5, 7, //Z nguoc nam doc
	3, 5, 4, 6, //Z nam doc
	3, 5, 4, 7, //T nam doc
	2, 3, 5, 7, //L bi nguoc
	3, 5, 7, 6, // j
	2, 3, 4, 5, //o vuong
};

//quan ly vung choi
const int height = 20;
const int width = 10;
const int SQUARE_SIZE = 32;

