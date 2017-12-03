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

#include "GameInstances/Player.h"

#include "Traffic/TrafficLight.h"
#include "Traffic/Lane.h"


#include "Traffic/Road.h"
#include "GameInstances/Map.h"
#include "GameInstances/Game.h"