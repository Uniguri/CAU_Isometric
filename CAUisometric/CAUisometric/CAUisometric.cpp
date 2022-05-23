#include "platform.h"
#include "Player.h"

extern SceneID mainScene;

void timerCallback(TimerID timer);
void keyboardCallback(KeyCode code, KeyState state);

int main() {
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	/*setMouseCallback(mouseCallback);
	setSoundCallback(soundCallback);*/
	setTimerCallback(timerCallback);
	setKeyboardCallback(keyboardCallback);

	mainScene = createScene("main", "mainScene.png");

	for (int i = 0; i < L; i++) {
		randomCreatePlatform(i, 1, 1);
	}
	printPlatform();
	Player_init();
	startGame(mainScene);
}

void timerCallback(TimerID timer) {
	Player_timerCallback(timer);
}

void keyboardCallback(KeyCode code, KeyState state) {

	Player_keyboardCallback(code, state);

}