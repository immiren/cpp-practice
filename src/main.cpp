#include <raylib.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int cellSize = 100;	// size in px
const int cellCountX = 9;
const int cellCountY = 9;

int cells[cellCountX][cellCountY] = {
	{0,1,0,0,0,4,0,0,0},
	{4,2,0,0,0,0,0,0,0},
	{0,3,0,0,0,0,4,0,0},
	{0,4,5,6,0,0,0,0,0},
	{0,0,0,7,0,0,0,0,4},
	{0,0,0,4,0,0,0,0,0},
	{0,0,4,0,0,0,0,0,0},
	{0,0,0,0,4,0,0,0,0},
	{0,0,0,0,0,0,0,4,0}
};
// TODO flip to correct x and y values

Vector2 cursorLocation = { 0,0 };

bool gameOver = false;

void drawCell(int posX, int posY, Color c) {
	DrawRectangle(posX * cellSize, posY * cellSize, cellSize, cellSize, c);
	
	// draw numbers on cells with values
	const int* cell = &cells[posX][posY];
	if (*cell != 0) {
		std::string text = std::to_string(*cell);
		DrawText(text.c_str(), posX * cellSize + 25, posY * cellSize + 10, 90, BLACK);
	}
}

void drawBackground() {
	Color tile;

	for (int x = 0; x < cellCountX; x++) {
		for (int y = 0; y < cellCountY; y++) {

			if ((x + y) % 2 == 1) {
				tile = { 100,100,100,255 };
			}
			else {
				tile = { 200,200,200,255 };
			}
			drawCell(x, y, tile);
		}
	}
}

int main(void) {
	// window
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);
	int windowWidth = cellSize * cellCountX;
	int windowHeight = cellSize * cellCountY ;
	InitWindow(windowWidth, windowHeight, "test window");

	int size = 100;
	int posX = 30;
	int posY = (windowHeight-size)/2;

	Color c;
	c.r = 100;
	c.g = 170;
	c.b = 255;
	c.a = 255;

	Vector2 direction = { 1, 0 };

	const float moveTimeDuration = 0.1;
	float timer = moveTimeDuration;

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground({50,50,50,255});

		drawBackground();

		if (!gameOver) {

			// Input
			direction = { 0,0 };
			if (IsKeyDown(KEY_UP)) { direction = { 0,-1 }; }
			if (IsKeyDown(KEY_DOWN)) { direction = { 0,1 }; }
			if (IsKeyDown(KEY_LEFT)) { direction = { -1,0 }; }
			if (IsKeyDown(KEY_RIGHT)) { direction = { 1,0 }; }
			if (IsKeyDown(KEY_ENTER)) {
				// next time: enter key to input values + ehk cell tyypitys?
				// input: switch to input mode somehow? vai miten tää ois hyvä handlaa
			}

			// Movement	
			timer -= GetFrameTime();
			if (timer <= 0) {
				timer += moveTimeDuration;

				cursorLocation.x += direction.x;
				cursorLocation.y += direction.y;
			}
			drawCell(cursorLocation.x, cursorLocation.y, GREEN);
		}
		else {
			DrawText("Game Over!", windowWidth / 2, windowHeight / 2, 20, RED);
			if (IsKeyDown(KEY_SPACE)) { gameOver = false; }
		}
		EndDrawing();
	}

	CloseWindow();

	return 0;
}

// TODO
// - numerot
//	- placeholder DONE
//	 - fiksaa x ja y
//  - oikeet
// - grid DONE
// - grid lines
// - numerotyypit (eri väriset)
//	- valmiit -> ei voi muuttaa
//  - uudet -> voi muuttaa
// - input numero
//	- testaa onko ok
// - random numerot
//	- tarkista että valid?
//