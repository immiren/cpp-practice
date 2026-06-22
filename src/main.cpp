#include <raylib.h>
#include <iostream>
#include <vector>

int cellSize = 100;
int cellCountX = 15;
int cellCountY = 10;

float g = 9.81f;

float dt = 1.0 / 60.0;

struct Player {
	Vector2 position = { 5.0f * cellSize, 5.0f * cellSize };
	Vector2 direction = { 1,0 };
	Vector2 velocity = { 0,0 };
	Color color = { 157, 19, 217, 255 };
	float maxSpeed = 5;
	float speed = 5;
	float acceleration = 3;
	float deceleration = 2;
	bool grounded = false;
} player;

Color skyColor = { 107,213,255,255 };
Color grassColor = { 6, 169, 35,255 };
Color groundColor = { 73, 44, 13 ,255 };
int grassLevel = 8;
int groundLevel = grassLevel + 1;

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
		// setup -----------------------------------------
		BeginDrawing();
		ClearBackground(skyColor);

		// ground
		DrawRectangle(0, grassLevel * cellSize, cellCountX * cellSize, cellSize, grassColor);
		DrawRectangle(0, groundLevel * cellSize, cellCountX * cellSize, (10 - groundLevel) * cellSize, groundColor);

		// movement -----------------------------------------
		player.direction = { 0,0 };
		if (IsKeyDown(KEY_UP) && player.grounded) { player.velocity.y = 50; }
		if (IsKeyDown(KEY_LEFT)) {
			player.velocity.x = player.velocity.x + (-player.maxSpeed * player.acceleration * dt);
		}
		if (IsKeyDown(KEY_RIGHT)) {
			player.velocity.x = player.velocity.x + (player.maxSpeed * player.acceleration * dt);
		}
		if (player.velocity.x < 0) {
			player.velocity.x = player.velocity.x + (player.maxSpeed * player.deceleration * dt);
			if (player.velocity.x > 0) {
				player.velocity.x = 0;
			}
		}
		else if (player.velocity.x > 0) {
			player.velocity.x = player.velocity.x - (player.maxSpeed * player.deceleration * dt);
			if (player.velocity.x < 0) { player.velocity.x = 0; }
		}

		// cap velocity
		if (player.velocity.x > player.maxSpeed) { player.velocity.x = player.maxSpeed; }
		else if (player.velocity.x < -player.maxSpeed) { player.velocity.x = -player.maxSpeed; }

		// update position
		player.position.x += player.velocity.x * player.speed;
		player.position.y += player.velocity.y * player.speed + g;

		// chain to screen
		if (player.position.x > (cellCountX - 1) * cellSize) {
			player.position.x = (cellCountX - 1) * cellSize;
			player.velocity.x = 0;
		}
		if (player.position.x < 0) {
			player.position.x = 0;
			player.velocity.x = 0;
		}
		if (player.position.y > (grassLevel - 1) * cellSize) { player.position.y = (grassLevel - 1) * cellSize; }
		if (player.position.y < 0) { player.position.y = 0; }

		// grounded check -----------------------------------------
		if (player.position.y > ((grassLevel - 1) * cellSize - 10)) { player.grounded = true; }
		else { player.grounded = false; }

		if (player.grounded) { DrawText("grounded", 100, 100, 20, BLACK); }
		else { DrawText("not grounded", 100, 100, 20, BLACK); }
		// draw player -----------------------------------------
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
