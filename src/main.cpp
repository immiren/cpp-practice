#include <raylib.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int cellSize = 100;	// size in px
int cellCountX = 9;
int cellCountY = 9;

Vector2 selectedCell = { 0,0 };

bool gameOver = false;

void drawCell(int posX, int posY, Color c) {
	std::string text = std::to_string(posX) + ", " + std::to_string(posY);
	DrawRectangle(posX * cellSize, posY * cellSize, cellSize, cellSize, c);
	DrawText(text.c_str(), posX * cellSize + 10, posY * cellSize+ 10, 20, BLACK);
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

			// Movement	
			timer -= GetFrameTime();
			if (timer <= 0) {
				timer += moveTimeDuration;

				selectedCell.x += direction.x;
				selectedCell.y += direction.y;
			}
			drawCell(selectedCell.x, selectedCell.y, GREEN);
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
//	- placeholder
//  - oikeet
// - grid
// - numerotyypit (eri väriset)
//	- valmiit -> ei voi muuttaa
//  - uudet -> voi muuttaa
// - input numero
//	- testaa onko ok
// - random numerot
//	- tarkista että valid?
//