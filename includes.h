#pragma once
#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <conio.h>
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <thread>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <cmath>
#include "tinyxml2.h"
#define eps 1e-8
using namespace tinyxml2;
using namespace std;
const int dx[] = {0, -1, 0, 1};
const int dy[] = {-1, 0, 1, 0};
string to_string(int x) {ostringstream os; os << x; return os.str();}
#include "Point.h"
#include "PointF.h"
#include "Rectangle.h"

#include "Window.h"

#include "Shape.h"
#include "Object.h"

#include "Dialog.h"
#include "KeyboardHandler.h"
#include "MenuHandler.h"

#include "Player.h"

#include "TrafficLight.h"
#include "Lane.h"

#include "Obstacle.h"

#include "Road.h"
#include "Map.h"
#include "Game.h"