#pragma once

// C std library
#include <cstdio>
#include <cstdlib>
#include <cstring>
// C++ std library
#include <iostream>
#include <algorithm>
// STL library
#include <queue>

// Windows Library
#ifdef _WIN32
#include <Windows.h>
#endif

// Custom Library
#include "GraphADT.h"

// Macro for better showing effects
#define _PAUSE system("PAUSE");
#ifdef _WIN32
#define _SCREEN_WHITE	system("color 70");
#define _SCREEN_RED		system("color 4f");
#define _SCREEN_GREEN	system("color 2f");
#define _CLEAR			system("cls");
#else
#define _SCREEN_WHITE
#define _SCREEN_RED
#define _SCREEN_GREEN
#define _CLEAR			system("clear");
#endif
#define _PW _PAUSE _SCREEN_WHITE

// Custom Functions
ALGraph Second_menu(ALGraph& G);

// Custom Variables
const int MaxV = 20;
const int MaxVR = 100;
