#include <raylib.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int cellSize = 100;	// size in px
const int cellCountX = 9;
const int cellCountY = 9;

struct Cell {
	int value = 0; // 0 = empty
	bool prefilled = false;
	bool notes[9] = { false,false,false,false,false,false,false,false,false };
};

Cell cells[cellCountX][cellCountY];

int cellNumbers[cellCountX][cellCountY] = {
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
// TODO flip to correct x and y values or just replace

vector<int> cursorLocation = { 0,0 };

bool gameOver = false;
bool takingNotes = false;

static void fillCells() {
	for (int x = 0; x < cellCountX; x++) {
		for (int y = 0; y < cellCountY; y++) {
			bool prefilled = false;
			if (cellNumbers[x][y] != 0) prefilled = true;

			Cell cell = {
				cellNumbers[x][y],
				prefilled,
				{ false,false,false,false,false,false,false,false,false },
			};
			cells[x][y] = cell;
		}
	}
}

static void drawHighlight(int posX, int posY) {
	Color c = { 145, 220, 255,255 };
	if (takingNotes) c = { 234, 184, 255, 255 };

	// row & cell highlight
	DrawRectangle(posX * cellSize, 0, cellSize, cellCountX * cellSize, { 230,230,230,255 });
	DrawRectangle(0, posY * cellSize, cellCountX * cellSize, cellSize, {230,230,230,255});
	
	// main highlight
	DrawRectangle(posX * cellSize, posY * cellSize, cellSize, cellSize, c);

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
	const int* cellValue = &cells[posX][posY].value;
	if (*cellValue != 0) {
		Color c = BLACK;
		if (!cells[posX][posY].prefilled) c = DARKPURPLE;
		std::string text = std::to_string(*cellValue);

		int letterWidth = 90;
		int xOffset = 0;
		int yOffset = 11;

		// highlight selected numbers
		if (*cellValue == cells[cursorLocation[0]][cursorLocation[1]].value) {
			letterWidth += 10;
			xOffset += -3;
			yOffset += -3;
		} 
		// shift 1-cells to the right for symmetry
		if (*cellValue == 1) DrawText(text.c_str(), posX * cellSize + 40 + xOffset, posY * cellSize + yOffset, letterWidth, c);
		else DrawText(text.c_str(), posX * cellSize + 30 + xOffset, posY * cellSize + yOffset, letterWidth, c);
	}
	else {
		// draw notes
		for (int n = 0; n < cellCountX; n++) {
			if (cells[posX][posY].notes[n] == true) {
				// draw note
				int noteX;
				int noteY;

				// get placement
				if (n >= 0 && n < 3) noteY = 10; // top row
				else if (n >= 3 && n < 6) noteY = 40; // middle row
				else noteY = 70; // bottom row
				if (n == 0 ) noteX = 15; // offset 1 to the right
				else if (n == 3 || n == 6) noteX = 10; // left column
				else if (n == 1 || n == 4 || n == 7) noteX = 40; // middle column
				else noteX = 70; // right column

				// draw number
				std::string text = std::to_string(n + 1);
				DrawText(text.c_str(), posX * cellSize + noteX, posY * cellSize + noteY, 30, GRAY);
			}


		}
	}
}

void drawBackground() {
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
	InitWindow(windowWidth, windowHeight, "Sudoku");

	Vector2 direction = { 1, 0 };

	const float moveTimeDuration = 0.1;
	float timer = moveTimeDuration;
	
	fillCells();

	while (!WindowShouldClose()) {
		BeginDrawing();
		if (!gameOver) {
			// Input
			direction = { 0,0 };
			if (IsKeyDown(KEY_UP)) { direction = { 0,-1 }; }
			if (IsKeyDown(KEY_DOWN)) { direction = { 0,1 }; }
			if (IsKeyDown(KEY_LEFT)) { direction = { -1,0 }; }
			if (IsKeyDown(KEY_RIGHT)) { direction = { 1,0 }; }

			// switch between writing and notetaking
			if (IsKeyPressed(KEY_P)) {
				takingNotes = !takingNotes;
			}

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
				// switch modes: pen/pencil
				if (cells[cursorLocation[0]][cursorLocation[1]].prefilled == false) {
					if (takingNotes) cells[cursorLocation[0]][cursorLocation[1]].notes[input - 1] = !cells[cursorLocation[0]][cursorLocation[1]].notes[input - 1];
					else {
						// check for conflicts
						bool isConflicting = false;
						for (int x = 0; x < cellCountX; x++) {
							if (x != cursorLocation[0] && cells[x][cursorLocation[1]].value == input) {
								isConflicting = true; 
								DrawText("ongelma x", 10, 10, 400, RED);
							}
						}
						if (!isConflicting) {
							for (int y = 0; y < cellCountY; y++) {
								if (y != cursorLocation[1] && cells[cursorLocation[0]][y].value == input) isConflicting = true;
							}
						}
						if (!isConflicting) {
							cells[cursorLocation[0]][cursorLocation[1]].value = input;
						}
						else input = 0;
					}
				}
			}

			// Movement	
			timer -= GetFrameTime();
			if (timer <= 0) {
				timer += moveTimeDuration;
				
				if (cursorLocation[0] + direction.x < cellCountX && cursorLocation[0] + direction.x >= 0) {
					cursorLocation[0] += direction.x;
				}
				if (cursorLocation[1] + direction.y < cellCountX && cursorLocation[1] + direction.y >= 0) {
					cursorLocation[1] += direction.y;
				}
			}
			ClearBackground(WHITE);

			drawHighlight(cursorLocation[0], cursorLocation[1]);

			drawBackground();
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
//  - oikeitten generointi
// - grid DONE
// - grid lines DONE
// - numerotyypit (eri väriset) DONE
//	- valmiit -> ei voi muuttaa  DONE
//  - uudet -> voi muuttaa  DONE
// - input numero DONE
//	- testaa onko nro ok
// - random numerot
//	- tarkista että valid?
// - nätimpi highlight DONE
// - highlight row ja column DONE
// - highlight muut samat numerot DONE
//