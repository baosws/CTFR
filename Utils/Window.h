#pragma once
#include "../includes.h"
typedef pair<char, int> ci;
typedef vector<vector<ci> > Screen;

class Window: public Rectangle {
protected:
	HANDLE handle; // save
	HWND consoleWindow; // save
	Screen screen, lastScreen; // save
	vector<Point> toBeRendered, lastRendered; // save
	void _putCharXY(int, int, char);
	friend class Prompt;
	void gotoXY(int, int);
public:
	Window(HANDLE, HWND, int, int, int, int);
	~Window();
	void fixConsoleWindow();
	void putCharXY(int, int, char, int);
	void putStringXY(int, int, string, int);
	void render();
	void buildFrame(char);
	void hideCursor();
	void showCursor();
	void clearScreen(bool);
	void setTitle(const char*);
};

Window::Window(HANDLE _handle = STD_OUTPUT_HANDLE, HWND _consoleWindow = GetConsoleWindow(), int _x = 1, int _y = 1, int _width = DEFAULT_WINDOW_WIDTH, int _height = DEFAULT_WINDOW_HEIGHT) {
	handle = _handle;
	consoleWindow = _consoleWindow;
	coord = Point(_x, _y);
	width = _width;
	height = _height;
	screen.resize(height, vector<ci>(width, ci(' ', 0)));
	lastScreen = screen;
	fixConsoleWindow();
	hideCursor();
}
Window::~Window() {
	clearScreen(false);
}
void Window::fixConsoleWindow() {
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void Window::gotoXY(int y, int x) {
	COORD _coord;
	_coord.X = x + getX();
	_coord.Y = y + getY();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _coord);
}
void Window::_putCharXY(int x, int y, char c) {
	gotoXY(x, y);
	cout << c;
}
void Window::putCharXY(int x, int y, char c, int priority = 0) {
	if (x * (height - 1 - x) >= 0 && y * (width - y - 1) >= 0)
	if (screen[x][y].second <= priority) {
		screen[x][y] = ci(c, priority);
		toBeRendered.push_back(Point(x, y));
	}
}
void Window::putStringXY(int x, int y, string s, int priority = 0) {
	for (int i = 0; i < s.length(); i++)
		putCharXY(x, y + i, s[i], priority);
}
void Window::render() {
	for (auto& p: lastRendered) {
		int i = p.getX(), j = p.getY();
		if (screen[i][j].first != lastScreen[i][j].first) {
			_putCharXY(i, j, ' ');
			lastScreen[i][j].first = ' ';
		}
	}
	lastRendered.clear();
	for (auto& p: toBeRendered) {
		int i = p.getX(), j = p.getY();
		if (screen[i][j].first != lastScreen[i][j].first) {
			_putCharXY(i, j, screen[i][j].first);
			lastScreen[i][j].first = screen[i][j].first;
		}
	}
	for (auto& p: toBeRendered) {
		int i = p.getX(), j = p.getY();
		screen[i][j] = ci(' ', 0);
	}
	lastRendered = toBeRendered;
	toBeRendered.clear();
}
void Window::buildFrame(char brick = '#') {
	for (int i = -1; i <= height; i++) {
		_putCharXY(i, -1, brick);
		_putCharXY(i, width, brick);
	}
	for (int i = -1; i <= width; i++) {
		_putCharXY(-1, i, brick);
		_putCharXY(height, i, brick);
	}
}
void Window::hideCursor() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(handle, &cci);
	cci.bVisible = false;
	SetConsoleCursorInfo(handle, &cci);
}
void Window::showCursor() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(handle, &cci);
	cci.bVisible = true;
	SetConsoleCursorInfo(handle, &cci);
}
void Window::clearScreen(bool rebuildFrame = false) {
	system("cls");
	lastRendered.clear();
	toBeRendered.clear();
	for (int i = 0; i < screen.size(); i++)
		for (int j = 0; j < screen[0].size(); j++)
			screen[i][j] = lastScreen[i][j] = ci(' ', 0);
	if (rebuildFrame)
		buildFrame();
}
void Window::setTitle(const char* title) {
	SetConsoleTitle(title);
}