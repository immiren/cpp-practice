#include <raylib.h>
#include <iostream>
#include <vector>

int cellSize = 100;
int cellCountX = 15;
int cellCountY = 10;

float g = 9.81f;

struct Player {
	Vector2 position = { 5.0f * cellSize, 5.0f * cellSize };
	Vector2 direction = { 1,0 };
	Vector2 velocity = { 0,0 };
	Color color = { 157, 19, 217, 255 };
	float speed = 7;
	bool grounded = false;
} player;

Color skyColor = { 107,213,255,255 };
Color grassColor = { 6, 169, 35,255 };
Color groundColor = { 73, 44, 13 ,255 };
int grassLevel = 8;
int groundLevel = grassLevel+1;

void drawCell(int posX, int posY, Color c) {
	DrawRectangle(posX * cellSize, posY * cellSize, cellSize, cellSize, c);
}

int main() {
	// Setup
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);
	InitWindow(cellSize * cellCountX, cellSize * cellCountY, "test window");

	// Game loop
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(skyColor);

		// ground
		DrawRectangle(0, grassLevel* cellSize, cellCountX * cellSize, cellSize, grassColor);
		DrawRectangle(0, groundLevel * cellSize, cellCountX * cellSize, (10 - groundLevel) * cellSize, groundColor);

		// movement
		player.direction = { 0,0 };
		if (IsKeyDown(KEY_UP) && player.grounded) { player.direction.y = -50; }
		if (IsKeyDown(KEY_LEFT)) { player.direction.x = -1; }
		if (IsKeyDown(KEY_RIGHT)) { player.direction.x = 1; }
		// TODO vaiha käyttää velocity

		player.position.x += player.direction.x * player.speed;
		player.position.y += player.direction.y * player.speed + g;

		if (player.position.x > (cellCountX - 1) * cellSize) { player.position.x = (cellCountX - 1) * cellSize; }
		if (player.position.x < 0) { player.position.x = 0; }
		if (player.position.y > (grassLevel - 1) * cellSize) { player.position.y = (grassLevel - 1) * cellSize; }
		if (player.position.y < 0) { player.position.y = 0; }

		// grounded check
		if (player.position.y > ((grassLevel - 1) * cellSize -10)) { player.grounded = true; }
		else { player.grounded = false; }

		if (player.grounded) { DrawText("grounded", 100, 100, 20, BLACK); }
		else { DrawText("not grounded", 100, 100, 20, BLACK); }
		// draw player
		DrawRectangle(player.position.x, player.position.y, cellSize, cellSize, player.color);

		EndDrawing();
	}
	
	CloseWindow();

	return 0;
}


// TODO:
// - jump
// - gravity
//	- bonus: check if tile under -> apply only if in air
//
//
