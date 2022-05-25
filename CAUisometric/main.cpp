#include "platform.h"
#include "Player.h"

ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH];
int base[MAX_LEVEL][baseN + 1][baseM + 1];

SceneID mainScene;

Player player;

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
	MakeMap(base, map, mainScene, 0);
	InitPlayer(&player, mainScene);
	startGame(mainScene);
}

void timerCallback(TimerID timer) {
	PlayerTimerCallback(timer, &player, map);
}

void keyboardCallback(KeyCode code, KeyState state) {

	PlayerKeyboardCallback(code, state, &player);

}