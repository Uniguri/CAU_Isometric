#include "platform.h"
#include "Player.h"
#include "bullet.h"
#include "turret.h"

ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH];
int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], level = 0;

SceneID gameScene[MAX_LEVEL];

Player player;
Bullet bullets[100] = {0};
Turret turrets[MAX_LEVEL][MAX_NUMBER_OF_TURRET];

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


	for (level = 0; level < MAX_LEVEL; level++) {
		gameScene[level] = createScene("main", "img/mainScene.png");
		CreateRandomMap();
	}
	level = 0;
	for (int i = 0; i < MAX_NUMBER_OF_BULLET; ++i)
	{
		InitBullet(i);
	}
	InitBulletSystem();
	MakeMap();
	InitTurret();
	InitPlayer();
	startGame(gameScene[level]);
}

void timerCallback(TimerID timer) {
	PlayerTimerCallback(timer);
	BulletTimerCallback(timer, -player.x, -player.y);
}

void keyboardCallback(KeyCode code, KeyState state) {

	PlayerKeyboardCallback(code, state);

}