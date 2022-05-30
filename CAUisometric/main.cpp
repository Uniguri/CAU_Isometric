#include "platform.h"
#include "Player.h"
#include "bullet.h"

ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH];
int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], level = 0;

SceneID gameScene[MAX_LEVEL];

Player player;
Bullet bullets[100] = {0};

void timerCallback(TimerID timer);
void keyboardCallback(KeyCode code, KeyState state);

int main() {
	srand((unsigned int)time(NULL));

	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	/*setMouseCallback(mouseCallback);
	setSoundCallback(soundCallback);*/
	setTimerCallback(timerCallback);
	setKeyboardCallback(keyboardCallback);


	for (int i = 0; i < MAX_LEVEL; i++) {
		gameScene[i] = createScene("main", "img/mainScene.png");
		CreateRandomMap(base, i);
	}
	for (int i = 0; i < MAX_NUMBER_OF_BULLET; ++i)
	{
		InitBullet(bullets + i, gameScene[0]);
	}
	InitBulletSystem();
	for (int i = 0; i < MAX_LEVEL; i++) {
		MakeMap(base, map, gameScene[i], i);
	}
	InitPlayer(&player, gameScene[0]);
	startGame(gameScene[level]);
}

void timerCallback(TimerID timer) {
	PlayerTimerCallback(timer, &player, map, base, &level, gameScene);
	BulletTimerCallback(timer, bullets, -player.x, -player.y);
}

void keyboardCallback(KeyCode code, KeyState state) {

	PlayerKeyboardCallback(code, state, &player);

}