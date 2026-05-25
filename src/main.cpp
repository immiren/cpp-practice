#include <raylib.h>
#include <iostream>
#include <vector>

using namespace std;

int cellSize = 100;	// size in px
int cellCountX = 10;
int cellCountY = 10;

vector<Vector2> snake;
Vector2 fruitPos = { 0,0 };

bool gameOver = false;

void setFruit() {
	while (true) {
		fruitPos.x = GetRandomValue(0, cellCountX - 1);
		fruitPos.y = GetRandomValue(0, cellCountY - 1);

		bool touchesSnake = false;

		// iterator? tarkista
		for (auto& i : snake) {
			if (i.x == fruitPos.x && i.y == fruitPos.y) {
				touchesSnake = true;
				break;
			}
		}

		if (!touchesSnake) {
			break;
		}
	}
}

void drawCell(int posX, int posY, Color c) {
	DrawRectangle(posX * cellSize, posY * cellSize, cellSize, cellSize, c);
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
	Vector2 newDirection = { 1, 0 };

	const float moveTimeDuration = 0.2;
	float timer = moveTimeDuration;

	snake.push_back({ 5,5 });

	setFruit();

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground({50,50,50,255});

		drawBackground();

		if (!gameOver) {

			// Input
			if (IsKeyDown(KEY_UP)) { newDirection = { 0,-1 }; }
			if (IsKeyDown(KEY_DOWN)) { newDirection = { 0,1 }; }
			if (IsKeyDown(KEY_LEFT)) { newDirection = { -1,0 }; }
			if (IsKeyDown(KEY_RIGHT)) { newDirection = { 1,0 }; }

			// Movement	
			timer -= GetFrameTime();
			if (timer <= 0) {
				timer += moveTimeDuration;

				for (int i = snake.size() - 1; i > 0; i--) {
					snake[i] = snake[i - 1];
				}

				// block backtracking
				if (newDirection.x == -direction.x && newDirection.y == -newDirection.y) {
					newDirection = direction;
				}
				direction = newDirection;
				snake[0].x += direction.x;
				snake[0].y += direction.y;

				// wrap around
				for (auto& i : snake) {
					if (i.x >= cellCountX) { i.x = 0; }
					if (i.y >= cellCountY) { i.y = 0; }
					if (i.x < 0) { i.x = cellCountX - 1; }
					if (i.y < 0) { i.y = cellCountY - 1; }
				}

				// detect collision
				for (int i = 1; i < snake.size(); i++) {
					if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
						gameOver = true;
						snake.clear();
						snake.push_back({ 5,5 });
					}
				}
			}

			if (snake[0].x == fruitPos.x && snake[0].y == fruitPos.y) {
				setFruit();
				snake.push_back(snake[snake.size() - 1]);
			}

			//snake
			for (auto& i : snake) {
				drawCell(i.x, i.y, GREEN);
			}

			//fruit
			drawCell(fruitPos.x, fruitPos.y, RED);
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