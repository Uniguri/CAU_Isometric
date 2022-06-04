#include "main.h"

ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH];
int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], level = 0;

SceneID gameScene[MAX_LEVEL] = {0};

SceneID loading_scene;
SceneID start_scene, gameover_scene;
ObjectID loading_image;
ObjectID start_button, end_button1, restart_button, menu_button,end_button2;
Door door[MAX_LEVEL];

TimerID loading_timer;

Player player;
Bullet bullets[MAX_NUMBER_OF_BULLET] = {0};
Turret turrets[MAX_LEVEL][MAX_NUMBER_OF_TURRET] = {0};

int turretCnt[MAX_LEVEL] = { 0 }, hiddenCnt=0;

heart_struct heart;
void LoadingTimerCallback(TimerID timer)
{
	if (timer == loading_timer)
	{
		stopTimer(timer);
		
		MainGameSetting();
		
		InitBulletSystem();
		InitTurret();
		InitPlayer();

		enterScene(start_scene);
		setMouseCallback(StartSceneMCB);
		setTimerCallback(timerCallback);
	}
}

int main() {
	srand((unsigned int)time(NULL));

	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	GameSetting();

	setTimerCallback(LoadingTimerCallback);
	loading_timer = createTimer(0.3f);
	startTimer(loading_timer);

	startGame(loading_scene);
}

void GameSetting(void)
{
	loading_scene = createScene("", "img/mainScene.png");
	loading_image = createObject("img/loading.png");
	scaleObject(loading_image, 2.f);
	locateObject(loading_image, loading_scene, 0, 0);
	showObject(loading_image);

	start_scene = createScene("", "img/mainScene.png");
	start_button = createObject("img/buttons/start.png");
	locateObject(start_button, start_scene, 547, 200);
	showObject(start_button);
	end_button1 = createObject("img/buttons/end.png");
	locateObject(end_button1, start_scene, 547, 150);
	showObject(end_button1);

	gameover_scene = createScene("", "img/mainScene.png");
	restart_button = createObject("img/buttons/restart.png");
	locateObject(restart_button, gameover_scene, 547, 200);
	showObject(restart_button);
	menu_button = createObject("img/buttons/menu.png");
	locateObject(menu_button, gameover_scene, 547, 150);
	showObject(menu_button);
	end_button2 = createObject("img/buttons/end.png");
	locateObject(end_button2, gameover_scene, 547, 100);
	showObject(end_button2);

	setMouseCallback(StartSceneMCB);
}

void MainGameSetting(void)
{
	for (level = 0; level < MAX_LEVEL; level++)
	{
		gameScene[level] = createScene("main", "img/mainScene.png");
		CreateRandomMap();
	}
	level = 0;
	for (int i = 0; i < MAX_NUMBER_OF_BULLET; ++i)
		InitBullet(i);

	MakeMap();

	heart_function();

	MakeDoor();
}

void ResetGame(void) 
{
	ResetPlayer();
	heart.num_heart = 5;

	for (int l = 0; l < MAX_LEVEL; ++l)
		for (int i = 0; i < turretCnt[l]; ++i) {
			turrets[l][i].active = true;
			showObject(turrets[l][i].obj);
		}

	for (int i = 0; i < MAX_NUMBER_OF_BULLET; ++i)
		DeleteBullet(i);

	level = 0;
}

void timerCallback(TimerID timer) {
	PlayerTimerCallback(timer);

	if (player.state == PlayerState::ATTACK || player.state == PlayerState::BLOCK)
		BulletTimerCallback(timer, 0, 0);
	else
		BulletTimerCallback(timer, -player.dx, -player.dy);
	
	if (player.is_dead)
	{
		enterScene(gameover_scene);
		setMouseCallback(GameOverSceneMCB);
	}
}

void keyboardCallback(KeyCode code, KeyState state) {

	PlayerKeyboardCallback(code, state);

}

void mouseCallback(ObjectID obj, int x, int y, MouseAction action) {};

void StartSceneMCB(ObjectID obj, int x, int y, MouseAction action)
{
	if (action != MouseAction::MOUSE_CLICK)
		return;

	if (obj == start_button)
	{
		setMouseCallback(mouseCallback);
		setKeyboardCallback(keyboardCallback);
		setTimerCallback(timerCallback);

		ResetGame();

		enterScene(gameScene[level]);
		return;
	}
	else if (obj == end_button1)
	{
		endGame();
		return;
	}
}
void GameOverSceneMCB(ObjectID obj, int x, int y, MouseAction action)
{
	if (action != MouseAction::MOUSE_CLICK)
		return;

	if (obj == restart_button)
	{
		ResetGame();

		setMouseCallback(mouseCallback);
		setKeyboardCallback(keyboardCallback);
		setTimerCallback(timerCallback);

		enterScene(gameScene[level]);
		return;
	}
	else if (obj == menu_button)
	{
		setMouseCallback(StartSceneMCB);
		enterScene(start_scene);
		return;
	}
	else if (obj == end_button2)
	{
		endGame();
		return;
	}
}