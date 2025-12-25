#include <iostream>
#include <conio.h>
#include <chrono>
#include <vector>
#include <windows.h>
#include <fstream>
#include <string> 
#include <time.h>
#include <cwchar>
#include <wchar.h>
#include <io.h>
#include <fcntl.h>

using namespace std;
const int WIDTH = 102;
const int HEIGHT = 36;
string SAVEGAME_LIST = "saveGameList.txt";
string SAVESCORE_LIST = "saveScoreList.txt";

string CAR[4] = {"   ___",
				  " _/  L\\__",
				  "'=o----o-'",
				  "" };

string TRUCK[4] = {" ________  h___",
				   "|        | |  L|_",
				   "|        |_|     |",
				   "'-OO----`OO----O-'" };

string VAN[4] = { " _____",
				 "|    L\\_",
				 "'-O---O-'" };

string PIG[4] = {"",
				 " ^..^",
				 "( oo )  )~",
				 "  ,,  ,,",
				 };

string BIRD[4] = {"<'),,,,,",
				 "( \\\\\\\\`",
				 " `n\\\\",
				 "     \\"};

string AMBULANCE[4] = { " ___._    ",
						"|  + L\\_ ",
						"'-O---O-' ",
						"          " };

void Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void text_animation(string a) {
	int x = 0;
	while (a[x] != '\0') {
		Color(2);
		cout << a[x];
		Sleep(50);
		x++;
	}
}

void fixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	RECT resolution;
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
	GetWindowRect(consoleWindow, &resolution);
	MoveWindow(consoleWindow, resolution.left, resolution.top, 1280, 720, TRUE);
}

void hideCursor() {
	CONSOLE_CURSOR_INFO cursor;
	cursor.dwSize = 100;
	cursor.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
}

void gotoXY(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GameMusic(bool music) {
	if (music == true)
		PlaySound(TEXT("game.wav"), NULL, SND_LOOP | SND_ASYNC);
	else
		PlaySound(TEXT(" "), NULL, SND_ASYNC);
}

void MenuMusic(bool music) {
	if (music == true)
		PlaySound(TEXT("music.wav"), NULL, SND_LOOP | SND_ASYNC);
	else
		PlaySound(TEXT(" "), NULL, SND_ASYNC);
}

void Exit() {
	system("cls");
	PlaySound(TEXT("End.wav"), NULL, SND_ASYNC);
	ifstream fi("Ending.txt");
	system("color 06");
	string s;
	while (!fi.eof()) {
		getline(fi, s);
		cout << s << '\n';
	}
	text_animation("Have a good day!");
	cout << '\n';
	text_animation("Thanks for playing...");
	Color(7);
	fi.close();
}

class CObject {
protected:
	string fig[4];
	int x;
public:
	CObject() { x = 0; }
	void set_x(int w) { x = w; }
	int get_x() { return x; }
	string getStr(int line) { return fig[line]; }
	int length() {
		int max = fig[0].length();
		for (int i = 1; i < 4; i++) {
			if (int(fig[i].length()) > max) {
				max = fig[i].length();
			}
		}
		return max;
	}
	virtual void Sound() = 0;
	virtual string getNameObj() = 0;
};

class CCar : public CObject {
public:
	CCar() {
		for (int i = 0; i < 4; i++) {
			fig[i] = CAR[i];
		}
		x = 0;
	}
	CCar(const CCar& car) {
		for (int i = 0; i < 4; i++) {
			fig[i] = car.fig[i];
		}
		x = car.x;
	}
	CCar& operator=(const CCar& car) {
		for (int i = 0; i < 4; i++) {
			fig[i] = car.fig[i];
		}
		x = car.x;
		return *this;
	}
	void Sound() {
		PlaySound(TEXT(" "), NULL, SND_ASYNC);
	}
	string getNameObj() { return "CAR"; }
};

class CTruck : public CObject {
public:
	CTruck() {
		for (int i = 0; i < 4; i++) {
			fig[i] = TRUCK[i];
		}
		x = 0;
	}
	CTruck(const CTruck& truck) {
		for (int i = 0; i < 4; i++) {
			fig[i] = truck.fig[i];
		}
		x = truck.x;
	}
	CTruck& operator=(const CTruck& truck) {
		for (int i = 0; i < 4; i++) {
			fig[i] = truck.fig[i];
		}
		x = truck.x;
		return *this;
	}
	void Sound() {
		PlaySound(TEXT(" "), NULL, SND_ASYNC);
	}
	string getNameObj() { return "TRUCK"; }
};

class CVan : public CObject {
public:
	CVan() {
		for (int i = 0; i < 4; i++) {
			fig[i] = VAN[i];
		}
		x = 0;
	}
	CVan(const CVan& van) {
		for (int i = 0; i < 4; i++) {
			fig[i] = van.fig[i];
		}
		x = van.x;
	}
	CVan& operator=(const CVan& van) {
		for (int i = 0; i < 4; i++) {
			fig[i] = van.fig[i];
		}
		x = van.x;
		return *this;
	}
	void Sound() {
		PlaySound(TEXT(" "), NULL, SND_ASYNC);
	}
	string getNameObj() { return "VAN"; }
};

class CPig : public CObject {
public:
	CPig() {
		for (int i = 0; i < 4; i++) {
			fig[i] = PIG[i];
		}
		x = 0;
	}
	CPig(const CPig& pig) {
		for (int i = 0; i < 4; i++) {
			fig[i] = pig.fig[i];
		}
		x = pig.x;
	}
	CPig& operator=(const CPig& pig) {
		for (int i = 0; i < 4; i++) {
			fig[i] = pig.fig[i];
		}
		x = pig.x;
		return *this;
	}
	void Sound() {
		PlaySound(TEXT("pig.wav"), NULL, SND_ASYNC);
	}
	string getNameObj() { return "PIG"; }
};

class CBird : public CObject {
public:
	CBird() {
		for (int i = 0; i < 4; i++) {
			fig[i] = BIRD[i];
		}
		x = 0;
	}
	CBird(const CBird& bird) {
		for (int i = 0; i < 4; i++) {
			fig[i] = bird.fig[i];
		}
		x = bird.x;
	}
	CBird& operator=(const CBird& bird) {
		for (int i = 0; i < 4; i++) {
			fig[i] = bird.fig[i];
		}
		x = bird.x;
		return *this;
	}
	virtual void Sound() {
		PlaySound(TEXT("bird.wav"), NULL, SND_ASYNC);
	}
	string getNameObj() { return "BIRD"; }
};

class CLane {
private:
	CObject* object;
	int y;
	bool direction;
public:
	CLane() {
		object = new CTruck[7]; 
		object[0].set_x(1 - object[0].length());
		for (int i = 1; i < 7; i++) {
			object[i].set_x(object[i - 1].get_x() - object[i - 1].length() * (rand() % 3 + 2));
		}
		y = 0;
		direction = true;
	}
	void playSoundObj() {
		object->Sound();
	}
	void set_y(int h);
	int get_y();
	void setDirection(bool);
	bool getDirection();
	CObject* getObject() {
		return object;
	} 
	void setObject(string s);
	void draw();
	~CLane() {
		delete[] object;
	}
};

void CLane::set_y(int h) {
	if (h > 0 && h < HEIGHT - 4) {
		y = h;
	}
}

int CLane::get_y() {
	return y;
}

void CLane::setDirection(bool b) {
	direction = b;
}

bool CLane::getDirection() {
	return direction;
}

void CLane::setObject(string s) {
	if (s == "CAR") {
		delete[] object;
		object = new CCar[7];
	}
	else if (s == "VAN") {
		delete[] object;
		object = new CVan[7];
	}
	else if (s == "PIG") {
		delete[] object;
		object = new CPig[7];
	}
	else if (s == "BIRD") {
		delete[] object;
		object = new CBird[7];
	}
	else if (s == "TRUCK") {
		delete[] object;
		object = new CTruck[7];
	}
	object[0].set_x(1 - object[0].length());
	for (int i = 1; i < 7; i++) {
		object[i].set_x(object[i - 1].get_x() - object[i - 1].length() * (rand() % 3 + 2));
	}
}

void CLane::draw() {
	for (int i = 0; i < 7; i++) {
		if (object->getNameObj() == "PIG")
			Color(252);
		else if (object->getNameObj() == "BIRD")
			Color(246);
		else if (object->getNameObj() == "CAR")
			Color(242);
		else if (object->getNameObj() == "VAN")
			Color(240);
		else Color(244);
		int pos = object[i].get_x();
		int pos_reverse = WIDTH - pos - object[i].length();
		if (pos + object[i].length() >= 1) {
			if (pos <= 1) {
				if (direction) {
					for (int j = 0; j < 4; j++) {
						int length = object[i].getStr(j).length();
						if (length + pos > 1) {
							gotoXY(1, y + j);
							cout << object[i].getStr(j).substr(1 - pos, length + pos);
						}
					}
				}
				else {
					for (int j = 0; j < 4; j++) {
						int length = object[i].getStr(j).length();
						if (pos_reverse < WIDTH - 1) {
							gotoXY(pos_reverse, y + j);
							cout << object[i].getStr(j).substr(0, WIDTH - 1 - pos_reverse);
						}
						if (pos_reverse + length < WIDTH - 1) {
							cout << " ";
						}
					}
				}
			}
			else if (pos < WIDTH - object[i].length()) {
				for (int j = 0; j < 4; j++) {
					if (direction) {
						gotoXY(pos - 1, y + j);
						cout << " " << object[i].getStr(j);
					}
					else {
						gotoXY(WIDTH - pos - object[i].length(), y + j);
						cout << object[i].getStr(j) << " ";
					}
				}
			}
			else if (pos < WIDTH - 1) {
				if (direction) {
					for (int j = 0; j < 4; j++) {
						gotoXY(pos - 1, y + j);
						cout << " " << object[i].getStr(j).substr(0, WIDTH - 1 - pos);
					}
				}
				else {
					for (int j = 0; j < 4; j++) {
						int length = object[i].getStr(j).length();
						if (length + pos_reverse > 1) {
							gotoXY(1, y + j);
							cout << object[i].getStr(j).substr(1 - pos_reverse, length + pos_reverse) << " ";
						}
						else {
							gotoXY(1, y + j);
							cout << " ";
						}
					}
				}
			}
			else {
				for (int j = 0; j < 4; j++) {
					if (direction) {
						gotoXY(pos - 1, y + j);
						cout << " ";
					}
					else {
						gotoXY(1, y + j);
						cout << " ";
					}
				}
				object[i].set_x(object[(i + 6) % 7].get_x() - object[(i + 6) % 7].length() * (rand() % 3 + 2));
				continue;
			}
		}
		object[i].set_x(++pos);
	}
}

class CPlayer {
private:
	string name;
	int x, y;
	int score;
	bool status;
	bool move;
public:
	CPlayer() {
		name = "";
		x = 1;
		y = 0;
		score = 0;
		status = true;
	}

	CPlayer(string s, int width) {
		name = s;
		x = width / 2;
		y = HEIGHT - 5;
		status = true;
		move = false;
	}

	void setName(string s);
	void set_x(int w);
	void set_y(int h);
	void setScore(int scr);
	void setStatus(bool b);
	string getName();
	int get_x();
	int get_y();
	int getScore();
	bool getStatus();
};

void CPlayer::setName(string s) {
	name = s;
}

void CPlayer::set_x(int w) {
	if (w > 0 && w < WIDTH - 2)
		x = w;
}

void CPlayer::set_y(int h) {
	if (h > 0 && h < HEIGHT - 4)
		y = h;
}

void CPlayer::setScore(int scr) {
	score = scr;
}

void CPlayer::setStatus(bool b) {
	status = b;
}

string CPlayer::getName() {
	return name;
}

int CPlayer::get_x() {
	return x;
}

int CPlayer::get_y() {
	return y;
}

int CPlayer::getScore() {
	return score;
}

bool CPlayer::getStatus() {
	return status;
}

void mainMenu();
void leaderboard();
void setting(bool &, bool&);
void saveScore(CPlayer player);
void gameConsole();
void createBox(int, int, int, int, string);
void printTitle();

class CGame {
private:
	bool quit;
	CLane lane[5];
	bool stop[5];
	int level;
	CPlayer player;
	bool pause;
public:
	CGame() {
		quit = false;
		for (int i = 0; i < 5; i++) {
			lane[i].set_y((i + 1) * 5 + 1);
			stop[i] = false;
		}
		lane[1].setDirection(false);
		lane[3].setDirection(false);
		level = 1;
		player.set_x(WIDTH / 2);
		player.set_y(HEIGHT - 5);
		pause = false;
		lane[0].setObject("CAR");
		lane[1].setObject("BIRD");
		lane[2].setObject("TRUCK");
		lane[3].setObject("PIG");
		lane[4].setObject("VAN");
	}
	void reset();
	void drawMap();
	void draw(chrono::time_point<chrono::system_clock>* last, chrono::time_point<chrono::system_clock>* lastStop);
	void input(bool &music, chrono::time_point<chrono::system_clock>* last, chrono::time_point<chrono::system_clock>* lastStop);
	void logic();
	void run(bool, bool&, bool&);
	void saveGame(string file);
	void loadGame(string file);
};

void CGame::reset() {
	quit = false;
	for (int i = 0; i < 5; i++) {
		lane[i].set_y((i + 1) * 5 + 1);
		stop[i] = false;
	}
	lane[1].setDirection(false);
	lane[3].setDirection(false);
	level = 1;
	player.setScore(0);
	player.set_x(WIDTH / 2);
	player.set_y(HEIGHT - 5);
	pause = false;
	lane[0].setObject("CAR");
	lane[1].setObject("BIRD");
	lane[2].setObject("TRUCK");
	lane[3].setObject("PIG");
	lane[4].setObject("VAN");
}

void CGame::drawMap() {
	int k = 5;
	system("color F9");
	Color(51);
	for (int i = 0; i < 8; i++) {
		gotoXY(0, i * 5);
		for (int j = 0; j < WIDTH; j++) {
			cout << char(196);
		}
	}
	for (int i = 0; i < HEIGHT; i++) {
		gotoXY(0, i);
		cout << char(179);
		gotoXY(WIDTH - 1, i);
		cout << char(179);
	}
	gameConsole();
}

void CGame::draw(chrono::time_point<chrono::system_clock>* last, chrono::time_point<chrono::system_clock>* lastStop) {
	int x = player.get_x(), y = player.get_y();
	gotoXY(x, y);
	cout << " ";
	Color(245);
	gotoXY(x, y + 1);
	cout << "o";
	gotoXY(x - 1, y + 2);
	cout << "/|\\";
	gotoXY(x - 1, y + 3);
	cout << "/ \\";
	for (int l = 0; l < 5; l++) {
		if (stop[l]) {
			if (!pause) {
				Color(240);
				gotoXY(WIDTH + 2, (l + 1) * 5 + 1);
				cout << "__";
				gotoXY(WIDTH + 1, (l + 1) * 5 + 2);
				cout << "|__|";
				gotoXY(WIDTH + 1, (l + 1) * 5 + 3);
				cout << "|";
				Color(192);
				cout << "__";
				Color(240);
				cout << "|";
			}
			auto now = chrono::system_clock::now();
			chrono::duration<double> dur = now - last[l];
			if (dur.count() >= (rand() % 3 + 2)) {
				stop[l] = false;
				last[l] = now;
				lastStop[l] = now;
			}
		}
		else {
			float speed = 1.0 * (rand() % 5 + 25) / 100 - level * 0.05;
			auto now = chrono::system_clock::now();
			chrono::duration<double> dur = now - last[l];
			if (!pause) {
				Color(240);
				gotoXY(WIDTH + 2, (l + 1) * 5 + 1);
				cout << "__";
				gotoXY(WIDTH + 1, (l + 1) * 5 + 2);
				cout << "|";
				Color(160);
				cout << "__";
				Color(240);
				cout << "|";
				gotoXY(WIDTH + 1, (l + 1) * 5 + 3);
				cout << "|__|";
			}
			if (dur.count() >= speed) {
				if (!pause)
					lane[l].draw();
				last[l] = chrono::system_clock::now();
			}
			dur = last[l] - lastStop[l];
			if (dur.count() >= (rand() % 3 + 5)) {
				stop[l] = true;
			}
		}
	}
	for (int i = 3; i < WIDTH - 3; i += 3) {
		gotoXY(i, 3);
		if (i % 2 == 0)
			Color(255);
		else Color(256);
		cout << "   ";
	}
	for (int i = 3; i < WIDTH - 3; i += 3) {
		gotoXY(i, 2);
		if (i % 2 != 0)
			Color(255);
		else Color(256);
		cout << "   ";
	}
	Color(241);
	gotoXY(WIDTH + 29, 11);
	cout << player.getScore();
	gotoXY(WIDTH + 29, 7);
	cout << level;
}

void CGame::input(bool &music, chrono::time_point<chrono::system_clock>* last, chrono::time_point<chrono::system_clock>* lastStop) {
	if (_kbhit()) {
		char cur = _getch();
		if (cur != 'p' && cur != 'l') {
			int x = player.get_x(), y = player.get_y();
			gotoXY(x, y);
			cout << " ";
			gotoXY(x, y + 1);
			cout << " ";
			gotoXY(x - 1, y + 2);
			cout << "   ";
			gotoXY(x - 1, y + 3);
			cout << "   ";
		}
		switch (cur) {
		case 'w': case 72: if (!pause) player.set_y(player.get_y() - 5); break;
		case 's': case 80: if (!pause) player.set_y(player.get_y() + 5); break;
		case 'a': case 75: if (!pause) player.set_x(player.get_x() - 3); break;
		case 'd': case 77: if (!pause) player.set_x(player.get_x() + 3); break;
		case 'p': {
			pause ? pause = false : pause = true;
			if (pause == false) {
				gotoXY(WIDTH + 32, 3);
				cout << "PLAYING";
			}
			else {
				gotoXY(WIDTH + 32, 3);
				cout << "PAUSE  ";
			}
		} break;
		case 'l': {
			string s;
			gotoXY(WIDTH + 32, 3);
			cout << "PAUSE  ";
			createBox(40, 16, 4, 31, "");
			gotoXY(43, 17);
			cout << "FILE NAME: ";
			cin >> s;
			for (int i = 0; i < 4; i++) {
				gotoXY(40, 16 + i);
				cout << "                               ";
			}
			saveGame(s);
			input(music, last, lastStop);
		} break;
		case 'm': {
			if (music == true)
				music = false;
			else music = true;
			GameMusic(music);
		}
		break;
		case 'q': case 27 : quit = true;
		}
	}
}

void CGame::logic() {
	int pos, length;
	for (int i = 0; i < 5; i++) {
		if (lane[i].get_y() == player.get_y()) {
			for (int j = 0; j < 7; j++) {
				length = lane[i].getObject()[j].length();
				if (lane[i].getDirection()) {
					pos = lane[i].getObject()[j].get_x();
				}
				else {
					pos = WIDTH - lane[i].getObject()[j].get_x() - length;
				}
				if (pos <= player.get_x() && pos + length >= player.get_x()) {
					player.setStatus(false);
					break;
				}
			}
		}
		if (!player.getStatus()) {
			break;
		}
	}
	if (player.get_y() == 1) {
		int x = player.get_x(), y = player.get_y();
		gotoXY(x, y);
		cout << " ";
		gotoXY(x, y + 1);
		cout << " ";
		gotoXY(x - 1, y + 2);
		cout << "   ";
		gotoXY(x - 1, y + 3);
		cout << "   ";
		player.setScore(player.getScore() + 100);
		if (player.getScore() % 500 == 0) {
			level++;
		}
		player.set_x(WIDTH / 2);
		player.set_y(HEIGHT - 5);
	}
}

void CGame::run(bool load, bool& menuMusic, bool& gameMusic) {
	string s;
	bool flag = true;
	system("color f0");
	if (!load) {
		system("cls");
		printTitle();
		int x = 77, y = 15;
		for (int i = 0; i < 15; i++) {
			Color(255);
			gotoXY(x - 3, y + i); cout << "                     ";
		}
		gotoXY(x, y); Color(240); cout << "PLAYER NAME: ";
		getline(cin, s);
		player.setName(s);
	}
	GameMusic(gameMusic);
	system("cls");
	drawMap();
	chrono::time_point<chrono::system_clock> last[5];
	chrono::time_point<chrono::system_clock> lastStop[5];
	for (int i = 0; i < 5; i++) {
		last[i] = chrono::system_clock::now();
		lastStop[i] = chrono::system_clock::now() + chrono::seconds((rand() % 10 + 1));
	}
	auto time = 0;
	auto start = chrono::steady_clock::now();
	while (!quit && player.getStatus()) {
		input(gameMusic, last, lastStop);
		gotoXY(WIDTH + 25, 22);
		if (gameMusic == true) {
			Color(244);
			cout << "on";
			Color(241);
			cout << "/off";
		}
		else {
			cout << "on/";
			Color(244);
			cout << "off";
		}
		draw(last, lastStop);
		logic();
		if (gameMusic == false) {
			auto end = chrono::steady_clock::now();
			time += chrono::duration_cast<chrono::seconds>(end - start).count();
			if (time > 1000 && flag == true) {
				lane[3].playSoundObj();
				flag = false;
			}
			if (time > 2000) {
				start = chrono::steady_clock::now();
				time = 0;
				lane[1].playSoundObj();
				flag = true;
			}
		}
	}
	gotoXY(0, HEIGHT);
	if (!player.getStatus()) {
		PlaySound(TEXT("crashing.wav"), NULL, SND_SYNC);
		PlaySound(TEXT("ambulance.wav"), NULL, SND_LOOP | SND_ASYNC);
		int x = 2, y = player.get_y();
		start = chrono::steady_clock::now();
		while (x <= WIDTH - 1) {
			chrono::duration<double> dur = chrono::steady_clock::now() - start;
			if (dur.count() >= 0.05) {
				for (int i = 0; i < 4; i++) {
					gotoXY(x - 1, y + i);
					if (x + AMBULANCE[0].length() >= WIDTH - 2)
						s = AMBULANCE[i].substr(0, WIDTH - 1 - x);
					else s = AMBULANCE[i];
					if (i == 0 || i == 1) {
						cout << " ";
						for (int j = 0; j < s.length(); j++) {
							if (s[j] == '.' || s[j] == '+') {
								Color(244);
								cout << s[j];
							}
							else {
								Color(241);
								cout << s[j];
							}
						}
					}
					else cout << " " << s;
				}
				start = chrono::steady_clock::now();
				x++;
			}
		}
		PlaySound(TEXT(" "), NULL, SND_ASYNC);
		createBox(40, 15, 7, 31, "");
		gotoXY(42, 16);
		cout << "Do you want to play again ?" << endl;
	}
	else {
		createBox(40, 15, 7, 31, "");
		gotoXY(42, 16);
		cout << "Are you sure want to quit ?" << endl;
	}
	int move = 0, cursor = 0;
	while (move != 13) {
		gotoXY(47, 19);
		if (cursor == 0) {
			Color(160);
		}
		createBox(47, 18, 3, 5, "YES");
		Color(241);
		gotoXY(62, 19);
		if (cursor == 1) {
			Color(64);
		}
		createBox(59, 18, 3, 5, "NO");
		Color(241);
		move = _getch();
		switch (move) {
		case 'a': case 75: cursor > 0 ? cursor-- : cursor = 1; break;
		case 'd': case 77: cursor < 1 ? cursor++ : cursor = 0; break;
		}
	}
	MenuMusic(menuMusic);
	if (!player.getStatus()) {
		saveScore(player);
	}
	if (cursor == 1 && player.getStatus()) {
		quit = false;
		run(true, menuMusic, gameMusic);
	}
	reset();
	if (cursor == 0 && !player.getStatus()) {
		player.setStatus(true);
		run(false, menuMusic, gameMusic);
	}
	if (cursor == 1 && !player.getStatus())
		player.setStatus(true);
	system("cls");
	printTitle();
}

void CGame::saveGame(string file) {
	ofstream ofs(file + ".txt");
	ofs << level << endl;
	ofs << quit << endl;
	ofs << pause << endl;
	for (int i = 0; i < 5; i++) {
		ofs << stop[i] << " ";
	}
	ofs << endl;
	for (int i = 0; i < 5; i++) { 
		for (int j = 0; j < 7; j++) {
			ofs << lane[i].getObject()[j].get_x() << " ";
		}
		ofs << endl;
	}
	ofs << player.get_x() << " " << player.get_y() << " " << player.getScore();
	ofs.close();
	ifstream ifs(SAVEGAME_LIST);
	if (!ifs) {
		ofstream ofs(SAVEGAME_LIST);
		ofs << 1 << endl;
		ofs << file;
		ofs.close();
		return;
	}
	int n;
	bool exist = false;
	ifs >> n;
	string* s = new string[n];
	getline(ifs, s[0]);
	for (int i = 0; i < n; i++) {
		getline(ifs, s[i]);
	}
	ifs.close();
	for (int i = 0; i < n; i++) {
		if (s[i] == file) {
			exist = true;
			break;
		}
	}
	if (!exist) {
		ofs.open(SAVEGAME_LIST);
		ofs << n + 1 << endl;
		for (int i = 0; i < n; i++) {
			ofs << s[i] << endl;
		}
		ofs << file;
		ofs.close();
	}
	delete[] s;
}

void CGame::loadGame(string file) {
	int tp;
	ifstream ifs(file + ".txt");
	ifs >> level >> quit >> pause;
	for (int i = 0; i < 5; i++) {
		ifs >> stop[i];
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			ifs >> tp;
			lane[i].getObject()[j].set_x(tp);
		}
	}
	ifs >> tp;
	player.set_x(tp);
	ifs >> tp;
	player.set_y(tp);
	ifs >> tp;
	player.setScore(tp);
	ifs.close();
	pause = false;
}

void saveMenu(CGame&, bool&, bool&);
void ConTro(int x_cu, int y_cu, int choose, int last_choose) {
	gotoXY(x_cu - 3, y_cu + last_choose * 3 + 1); Color(255); cout << "   ";
	gotoXY(x_cu + 15, y_cu + last_choose * 3 + 1); cout << "   ";
	gotoXY(x_cu - 3, y_cu + choose * 3 + 1); Color(249);  cout << ">>-";
	gotoXY(x_cu +15, y_cu + choose * 3 + 1); cout << "-->";
}

void createBox(int x, int y, int width, int length, const string str) {
	int val;
	val = _setmode(_fileno(stdout), _O_U16TEXT);
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < length; j++) {
			gotoXY(x + j, y + i);
			if (i == 0 && j == 0)
				wcout << L"╔";
			else if (i == 0 && j == length - 1)
				wcout << L"╗";
			else if (i == width - 1 && j == 0)
				wcout << L"╚";
			else if (i == width - 1 && j == length - 1)
				wcout << L"╝";
			else if (j == 0 || j == length - 1)
				wcout << L"║";
			else if (i == 0 || i == width - 1)
				wcout << L"═";
			else wcout << L" ";
		}
	}
	val = _setmode(_fileno(stdout), _O_TEXT);
	int x_middle = width / 2;
	int y_middle = ((length - 2) - str.length()) / 2+1;
	gotoXY(x + y_middle, y + x_middle); cout << str;
}
void deleteBox() {
	int x = 77, y = 15;
	for (int i = 0; i < 15; i++) {
		Color(255);
		gotoXY(x - 3, y + i); cout << "                      ";
	}
}
void printTitle() {
	string car1[9] = {"  o_______________}o{",
					 " |              |   \\ ",
					 " |    911       |____\\_____",
					 " | _____        |    |_o__ |",
					 " [/ ___ \\       |   / ___ \\ |",
					 "[]_/.-.\\_\\______|__/_/.-.\\_[]",
					 "   |(O)|             |(O)|",
					 "    '-'               '-'",
				     "-- - -- - -- - -- - -- - -- -",
	};
	string car2[8] ={"                                  @",
					 "               (__)    (__) _____/",
					 "            /| (oo) _  (oo)/----/_____    *",
					 "  _o\______/_|\_\/_/_|__\/|____|//////== *- *  * -",
					 " /_________   \   00 |   00  |      /== -* * -",
					 "[_____/^^\_____\_____|_____ /^^\_____]    *- * -",
					 "      \__ /                 \__/",
					 "--- --- -- - -- --- -- --- --- --- - -- -"
	};
	int x_title = 35, y_title = 4, val;
	val = _setmode(_fileno(stdout), _O_U16TEXT);
	gotoXY(x_title, y_title++); Color(240); wcout << L" ██████╗██████╗  ██████╗ ███████╗███████╗██╗███╗   ██╗ ██████╗     ██████╗  ██████╗  █████╗ ██████╗ " << endl;
	gotoXY(x_title, y_title++); wcout << L"██╔════╝██╔══██╗██╔═══██╗██╔════╝██╔════╝██║████╗  ██║██╔════╝     ██╔══██╗██╔═══██╗██╔══██╗██╔══██╗" << endl;
	gotoXY(x_title, y_title++); wcout << L"██║     ██████╔╝██║   ██║███████╗███████╗██║██╔██╗ ██║██║  ███╗    ██████╔╝██║   ██║███████║██║  ██║" << endl;
	gotoXY(x_title, y_title++); wcout << L"██║     ██╔══██╗██║   ██║╚════██║╚════██║██║██║╚██╗██║██║   ██║    ██╔══██╗██║   ██║██╔══██║██║  ██║" << endl;
	gotoXY(x_title, y_title++); wcout << L"╚██████╗██║  ██║╚██████╔╝███████║███████║██║██║ ╚████║╚██████╔╝    ██║  ██║╚██████╔╝██║  ██║██████╔╝" << endl;
	gotoXY(x_title, y_title++); wcout << L" ╚═════╝╚═╝  ╚═╝ ╚═════╝ ╚══════╝╚══════╝╚═╝╚═╝  ╚═══╝ ╚═════╝     ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚═════╝" << endl;
	val = _setmode(_fileno(stdout), _O_TEXT);
	x_title = 25; y_title = 20;
	Color(244);
	for (int i = 0; i < 9; i++) {
		gotoXY(x_title, y_title + i); cout << car1[i];
	}
	x_title = 110; y_title = 21;
	Color(241);
	for (int i = 0; i < 8; i++) {
		gotoXY(x_title, y_title + i); cout << car2[i];
	}
}
void mainMenu(bool &menuMusic, bool&gameMusic) {
	int cursor = 0, move = 0;
	MenuMusic(menuMusic);
	CGame game;
	system("color f0");
	printTitle();
	gotoXY(0, 0);
	int x_save = 77, y_save = 15, cursor_save = cursor;
	while (cursor != 4) {
		while (move != 13) {
			deleteBox(); 
			for (int i = 0; i < 5; i++) {
				switch (i) {
				case 0: if (cursor == i) Color(160); else Color(240); createBox(77, 15, 3, 15, "NEW GAME"); break;
				case 1: if (cursor == i) Color(160); else Color(240); createBox(77, 18, 3, 15, "LOAD GAME"); break;
				case 2: if (cursor == i) Color(96); else Color(240); createBox(77, 21, 3, 15, "LEADERBOARD"); break;
				case 3: if (cursor == i) Color(96); else Color(240); createBox(77, 24, 3, 15, "SETTINGS"); break;
				case 4: if (cursor == i) Color(64); else Color(240); createBox(77, 27, 3, 15, "EXIT"); break;
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
			}
			ConTro(x_save, y_save, cursor, cursor_save);
			move = _getch();
			switch (move) {
			case 'w': case 72: cursor > 0 ? cursor-- : cursor = 4; ConTro(x_save, y_save, cursor, cursor_save); cursor_save = cursor; break;
			case 's': case 80: cursor < 4 ? cursor++ : cursor = 0; ConTro(x_save, y_save, cursor, cursor_save); cursor_save = cursor; break;
			}
		}
		if (cursor == 0) {
			game.run(false, menuMusic, gameMusic);
			system("cls");
			printTitle();
			move = 17;
		}
		else if (cursor == 1) {
			saveMenu(game, menuMusic, gameMusic);
			move = 17;
		}
		else if (cursor == 2) {
			leaderboard();
			move = 17;
		}
		else if (cursor == 3) {
			setting(menuMusic, gameMusic);
			if (gameMusic == false)
				MenuMusic(menuMusic);
			move = 17;
		}
	}
	Exit();
}

void saveMenu(CGame& game, bool &menuMusic, bool &gameMusic) 
{
	int cursor = 0, move = 0;
	deleteBox();
	Color(240);
	createBox(76, 15, 3, 15, "LOAD GAME");
	ifstream ifs(SAVEGAME_LIST);
	if (ifs) {
		int nFileList;
		ifs >> nFileList;
		string* fileList = new string[nFileList];
		getline(ifs, fileList[0]);
		for (int i = 0; i < nFileList; i++) {
			getline(ifs, fileList[i]);
		}
		ifs.close();
		cursor = 0, move = 0;
		while (move != 13) {
			for (int i = 0; i < nFileList; i++) {
				if (cursor == i) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160);
				}
				gotoXY(80, 18 + i);
				cout << fileList[i];
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
			}
			move = _getch();
			switch (move) {
			case 'w': case 72: cursor > 0 ? cursor-- : cursor = nFileList - 1; break;
			case 's': case 80: cursor < nFileList - 1 ? cursor++ : cursor = 0; break;
				case 'q' : case 27 : deleteBox(); return;
			}
		}
		game.loadGame(fileList[cursor]);
		game.run(true, menuMusic, gameMusic);
	}
	else {
		do {
			move = _getch();
			if (move == 'q' || move == 27) {
				return;
			}
		} while (1);
	}
}

void saveScore(CPlayer player) {
	ifstream ifs(SAVESCORE_LIST);
	if (!ifs) {
		ofstream ofs(SAVESCORE_LIST);
		ofs << 1 << endl;
		ofs << player.getScore() << "," << player.getName();
		ofs.close();
		return;
	}
	int n;
	char c;
	ifs >> n;
	string* name = new string[n + 1];
	int* score = new int[n + 1];
	getline(ifs, name[0]);
	for (int i = 0; i < n; i++) {
		ifs >> score[i] >> c;
		getline(ifs, name[i]);
	}
	ifs.close();
	score[n] = player.getScore();
	name[n] = player.getName();
	for (int i = 0; i < n; i++) {
		int max = score[i];
		for (int j = i + 1; j < n + 1; j++) {
			if (score[j] > score[i]) {
				int tpScore = score[i];
				string tpName = name[i];
				score[i] = score[j];
				name[i] = name[j];
				score[j] = tpScore;
				name[j] = tpName;
			}
		}
	}
	ofstream ofs(SAVESCORE_LIST);
	n == 10 ? ofs << 10 : ofs << n + 1;
	ofs << endl;
	for (int i = 0; i < n + 1 && i < 10; i++) {
		ofs << score[i] << "," << name[i] << endl;
	}
	ofs.close();
	delete[] name;
	delete[] score;
}

void setting(bool &menuMusic, bool&gameMusic) {
	int cursor = 0, move = 0;
	gotoXY(0, 0);
	deleteBox();
	while (1) {
		for (int i = 0; i < 3; i++) {
			
			switch (i) {
			case 0: 
				if (cursor == i) Color(160); else Color(240);
				if (menuMusic == true)
					createBox(77, 18, 3, 19, "Menu music: On");
				else 
					createBox(77, 18, 3, 19, "Menu music: Off");
				break;
			case 1: 
				if (cursor == i) Color(160); else Color(240);
				if (gameMusic == true)
					createBox(77, 21, 3, 19, "Game music: On");
				else
					createBox(77, 21, 3, 19, "Game music: Off");
				break;
			case 2: 
				if (cursor == i) Color(160); else Color(240);
				createBox(77, 24, 3, 19, "Back");
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		}
		move = _getch();
		switch (move) {
		case 'w': case 72: cursor > 0 ? cursor-- : cursor = 2; break;
		case 's': case 80: cursor < 2 ? cursor++ : cursor = 0; break;
		case 'q': case 27: return;
		}
		if (cursor == 0 && move == 13) {
			if (menuMusic == true) 
				menuMusic = false;
			else menuMusic = true;
			MenuMusic(menuMusic);
		}
		if (cursor == 1 && move == 13) {
			if (gameMusic == true)
				gameMusic = false;
			else gameMusic = true;
		}
		if (cursor == 2 && move == 13) {
			int x = 77, y = 15;
			for (int i = 0; i < 15; i++) {
				Color(255);
				gotoXY(x - 3, y + i); cout << "                           ";
			}
			return;
		}
	}
}

void leaderboard() {
	int n, score;
	char c;
	gotoXY(77, 15);
	deleteBox();
	Color(240);
	createBox(76, 15, 3, 15, "LEADERBOARD");
	
	string name;
	ifstream ifs(SAVESCORE_LIST);
	if (ifs) {
		ifs >> n;
		for (int i = 0; i < n; i++) {
			ifs >> score >> c;
			getline(ifs, name);
			gotoXY(78, 18 + i);
			cout << i + 1 << ". " << name << " " << score << endl;
		}
		ifs.close();
	}
	do {
		int move = _getch();
		if (move == 'q' || move == 27) {
			system("cls");
			printTitle();
			return;
		}
	} while (1);
}

void guideBoard(int x, int y) {
	gotoXY(x, y);
}

void gameConsole() {
	ifstream fi("gameConsole.txt");
	string s;
	int score, cnt = 0, n, tmp = 1;
	char c;
	string name;
	while (!fi.eof()) {
		getline(fi, s);
		gotoXY(WIDTH + 8, cnt);
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '|')
				s[i] = char(179);
			if (s[i] == '-')
				s[i] = char(196);
		}
		Color(241); // 241
		cout << s;
		cnt++;
	}
	fi.close();
	cnt = 0;
	ifstream ifs(SAVESCORE_LIST);
	if (ifs) {
		ifs >> n;
		for (int i = 0; i < 5; i++) {
			ifs >> score >> c;
			getline(ifs, name);
			gotoXY(WIDTH + 15, 28 + cnt);
			if (i < n) {
				if (name == "") {
					name = "#unknown";
					cout << i + 1 << ". " << name << tmp << ": " << score << '\n';
					tmp++;
				}
				else cout << i + 1 << ". " << name << ": " << score << '\n';
			}	
			else cout << i + 1 << ". ----------------" << '\n';
			cnt++;
		}
		ifs.close();
	}
}

int main() {
	bool menuMusic = true, gameMusic = true;
	system("cls");
	srand(time(0));
	fixConsoleWindow();
	hideCursor();
	mainMenu(menuMusic, gameMusic);
}
