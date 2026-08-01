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

vector<int> cursorLocation = { 0,0 };

bool gameOver = false;
bool redraw = true;

void drawHighlight(int posX, int posY) {
	DrawRectangle(posX * cellSize, posY * cellSize, cellSize, cellSize, SKYBLUE);
}

void drawCell(int posX, int posY) {
	int lineSize = 3;

	// grey borders
	if (posX != 2 && posX != 5 && posX != 8) DrawRectangle((posX + 1) * cellSize, (posY + 1) * cellSize, lineSize, cellSize, LIGHTGRAY);
	if (posX != 3 && posX != 6 && posX != 0) DrawRectangle(posX * cellSize, posY * cellSize, lineSize, cellSize, LIGHTGRAY);
	if (posY != 2 && posY != 5 && posY != 8) DrawRectangle(posX * cellSize - lineSize, (posY + 1) * cellSize, cellSize, lineSize, LIGHTGRAY);
	if (posY != 3 && posY != 6 && posY != 0) DrawRectangle(posX * cellSize, posY * cellSize, cellSize, lineSize, LIGHTGRAY);

	// black borders
	if (posX == 2 || posX == 5 || posX == 8) DrawRectangle((posX + 1) * cellSize, (posY + 1) * cellSize, lineSize, cellSize, BLACK);
	if (posX == 3 || posX == 6 || posX == 0) DrawRectangle(posX * cellSize, posY * cellSize, lineSize, cellSize, BLACK);
	if (posY == 2 || posY == 5 || posY == 8) DrawRectangle(posX * cellSize - lineSize, (posY + 1) * cellSize, cellSize, lineSize, BLACK);
	if (posY == 3 || posY == 6 || posY == 0) DrawRectangle(posX * cellSize, posY * cellSize, cellSize, lineSize, BLACK);

	// draw numbers on cells with values
	const int* cell = &cells[posX][posY];
	if (*cell != 0) {
		std::string text = std::to_string(*cell);
		if (*cell == 1) DrawText(text.c_str(), posX * cellSize + 40, posY * cellSize + 10, 90, BLACK);
		else DrawText(text.c_str(), posX * cellSize + 30, posY * cellSize + 10, 90, BLACK);
	}
}

void drawBackground() {
	Color tile;

	for (int x = 0; x < cellCountX; x++) {
		for (int y = 0; y < cellCountY; y++) {			
			drawCell(x, y);
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
		if (!gameOver) {

			// Input
			direction = { 0,0 };
			if (IsKeyDown(KEY_UP)) { direction = { 0,-1 }; }
			if (IsKeyDown(KEY_DOWN)) { direction = { 0,1 }; }
			if (IsKeyDown(KEY_LEFT)) { direction = { -1,0 }; }
			if (IsKeyDown(KEY_RIGHT)) { direction = { 1,0 }; }
			if (direction.x != 0 || direction.y != 0) redraw = true;

			// number input: toimii mut paranna
			int input = 0;
			if (IsKeyPressed(KEY_ONE))  input = 1;
			if (IsKeyPressed(KEY_TWO))  input = 2;
			if (IsKeyPressed(KEY_THREE))  input = 3;
			if (IsKeyPressed(KEY_FOUR))  input = 4;
			if (IsKeyPressed(KEY_FIVE))  input = 5;
			if (IsKeyPressed(KEY_SIX))  input = 6;
			if (IsKeyPressed(KEY_SEVEN))  input = 7;
			if (IsKeyPressed(KEY_EIGHT))  input = 8;
			if (IsKeyPressed(KEY_NINE))  input = 9;
			if (input != 0) {
				cells[cursorLocation[0]][cursorLocation[1]] = input;
				redraw = true;
			}

			// Movement	
			timer -= GetFrameTime();
			if (timer <= 0) {
				timer += moveTimeDuration;

				cursorLocation[0] += direction.x;
				cursorLocation[1] += direction.y;
			}
			if (redraw) {
				ClearBackground(WHITE);

				drawHighlight(cursorLocation[0], cursorLocation[1]);

				drawBackground();
			}
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
// - grid lines DONE
// - numerotyypit (eri väriset)
//	- valmiit -> ei voi muuttaa
//  - uudet -> voi muuttaa
// - input numero DONE
//	- testaa onko nro ok
// - random numerot
//	- tarkista että valid?
// - nätimpi highlight DONE
// - highlight row ja column + muut samat numerot
//