#include "platform.h"
#include "Player.h"
#include "bullet.h"

ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH];
int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1];

SceneID mainScene;

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

	mainScene = createScene("main", "img/mainScene.png");

	for (int i = 0; i < MAX_LEVEL; i++) {
		CreateRandomMap(base, i);
	}
	for (int i = 0; i < MAX_NUMBER_OF_BULLET; ++i)
	{
		InitBullet(bullets + i, mainScene);
	}
	InitBulletSystem();
	MakeMap(base, map, mainScene, 0);
	InitPlayer(&player, mainScene);
	startGame(mainScene);
}

void timerCallback(TimerID timer) {
	PlayerTimerCallback(timer, &player, map, base);
	BulletTimerCallback(timer, bullets, -player.x, -player.y);
}

void keyboardCallback(KeyCode code, KeyState state) {

	PlayerKeyboardCallback(code, state, &player);

}