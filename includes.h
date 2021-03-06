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
#include <mutex>
#include "tinyxml2.h"
#define eps 1e-8
using namespace tinyxml2;
using namespace std;
const int RUNNING = 1;
const int PLAYING = 2;
const int LOADING_DATA = 500;
const int LEVEL_UP = 1500;
const int WAIT_FOR_THREAD_TO_TERMINATE = 100;
const int DEFAULT_WINDOW_WIDTH = 80;
const int DEFAULT_WINDOW_HEIGHT = 28;
const int dx[] = {0, -1, 0, 1};
const int dy[] = {-1, 0, 1, 0};
string to_string(int x) {ostringstream os; os << x; return os.str();}
int to_num(string x) {int res = 0;for (int i = 0; i < x.length(); i++)res = res * 10 + x[i] - '0';return res;}
#include "Geo/Point.h"
#include "Geo/PointF.h"
#include "Geo/Rectangle.h"

#include "Utils/Window.h"

#include "Object/Shape.h"
#include "Object/Object.h"
#include "GameInstances/Obstacle.h"

#include "Handlers/Dialog.h"
#include "Handlers/KeyboardHandler.h"
#include "Handlers/MenuHandler.h"
#include "Handlers/Prompt.h"
#include "GameInstances/Player.h"

#include "Traffic/TrafficLight.h"
#include "Traffic/Lane.h"

#include "Traffic/Road.h"
#include "GameInstances/Map.h"
#include "GameInstances/Game.h"