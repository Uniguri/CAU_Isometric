#include "main.h"

ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH];
int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], level = 0;

SceneID gameScene[MAX_LEVEL] = {0};

SceneID loading_scene;
SceneID start_scene, gameover_scene, clear_scene;
ObjectID loading_image;
ObjectID start_button, end_button1, restart_button1, end_button2;
ObjectID restart_button2, end_button3;
Door door[MAX_LEVEL];

TimerID loading_timer;

SoundID click_sound, bullet_sound, hit_sound, shield_sound, sword_sound, attack_sound, damage_sound;
SoundID start_sound, ingame_sound1, ingame_sound2, over_sound, clear_sound;

Player player;
Bullet bullets[MAX_NUMBER_OF_BULLET] = {0};
Turret turrets[MAX_LEVEL][MAX_NUMBER_OF_TURRET] = {0};

int turretCnt[MAX_LEVEL] = { 0 }, hiddenCnt[MAX_LEVEL] = { 0 };

heart_struct heart;
void LoadingTimerCallback(TimerID timer)
{
	if (timer == loading_timer)
	{
		stopTimer(timer);
		
		playSound(start_sound, true);

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
	locateObject(loading_image, loading_scene, 10, 0);
	showObject(loading_image);

	start_scene = createScene("", "img/mainScene.png");
	start_button = createObject("img/buttons/start.png");
	locateObject(start_button, start_scene, 547, 200);
	showObject(start_button);
	end_button1 = createObject("img/buttons/end.png");
	locateObject(end_button1, start_scene, 547, 150);
	showObject(end_button1);

	gameover_scene = createScene("", "img/mainScene.png");
	restart_button1 = createObject("img/buttons/restart.png");
	locateObject(restart_button1, gameover_scene, 547, 200);
	showObject(restart_button1);
	end_button2 = createObject("img/buttons/end.png");
	locateObject(end_button2, gameover_scene, 547, 150);
	showObject(end_button2);

	clear_scene = createScene("", "img/clearScene.png");
	restart_button2 = createObject("img/buttons/restart.png");
	locateObject(restart_button2, clear_scene, 547, 200);
	showObject(restart_button2);
	end_button3 = createObject("img/buttons/end.png");
	locateObject(end_button3, clear_scene, 547, 150);
	showObject(end_button3);

	click_sound = createSound("sounds/effect/ButtonClick.mp3");
	bullet_sound = createSound("sounds/effect/ShootBullet.mp3");
	hit_sound = createSound("sounds/effect/Hit.mp3");
	shield_sound = createSound("sounds/effect/Shield.mp3"); 
	sword_sound = createSound("sounds/effect/Sword.mp3");
	attack_sound = createSound("sounds/effect/Attack.mp3");
	damage_sound = createSound("sounds/effect/Damaged.mp3");
	start_sound = createSound("sounds/bgm/Start.mp3");
	ingame_sound1 = createSound("sounds/bgm/InGame1.mp3");
	ingame_sound2 = createSound("sounds/bgm/InGame2.mp3");
	over_sound = createSound("sounds/bgm/Over.mp3");
	clear_sound = createSound("sounds/bgm/GameClear.mp3");

	setMouseCallback(StartSceneMCB);
}

void MainGameSetting(void)
{
	for (level = 0; level < MAX_LEVEL; level++)
	{
		gameScene[level] = createScene("main", "img/blackScene.png");
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
	level = 0;
	heart.num_heart = PLAYER_MAX_HEART;

	ResetPlayer();

	for (int l = 0; l < MAX_LEVEL; ++l)
		for (int i = 0; i < turretCnt[l]; ++i) {
			turrets[l][i].active = true;
			showObject(turrets[l][i].obj);
		}

	for (int i = 0; i < MAX_NUMBER_OF_BULLET; ++i)
		DeleteBullet(i);

	for (int i = 0; i < MAX_LEVEL; ++i)
		hiddenCnt[i] = 0;
}

void NullTimerCallback(TimerID timer) {}

void timerCallback(TimerID timer) {
	PlayerTimerCallback(timer);

	if (player.state == PlayerState::ATTACK || player.state == PlayerState::BLOCK)
		BulletTimerCallback(timer, 0, 0);
	else
		BulletTimerCallback(timer, -player.dx, -player.dy);
	
	if (player.is_dead)
	{
		setTimerCallback(NullTimerCallback);
		stopSound(ingame_sound1);
		stopSound(ingame_sound2);
		playSound(over_sound, true);
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
		stopSound(start_sound);
		playSound(click_sound);

		setMouseCallback(mouseCallback);
		setKeyboardCallback(keyboardCallback);
		setTimerCallback(timerCallback);

		ResetGame();

		playSound(ingame_sound1, true);

		enterScene(gameScene[level]);
		return;
	}
	else if (obj == end_button1)
	{
		playSound(click_sound);
		endGame();
		return;
	}
}
void GameOverSceneMCB(ObjectID obj, int x, int y, MouseAction action)
{
	if (action != MouseAction::MOUSE_CLICK)
		return;

	if (obj == restart_button1)
	{
		stopSound(over_sound);
		playSound(click_sound);
		ResetGame();

		setMouseCallback(mouseCallback);
		setKeyboardCallback(keyboardCallback);
		setTimerCallback(timerCallback);

		playSound(ingame_sound1, true);

		enterScene(gameScene[level]);
		return;
	}
	else if (obj == end_button2)
	{
		playSound(click_sound);
		endGame();
		return;
	}
}
void ClearSceneMCB(ObjectID obj, int x, int y, MouseAction action)
{
	if (action != MouseAction::MOUSE_CLICK)
		return;

	if (obj == restart_button2)
	{
		playSound(click_sound);

		stopSound(clear_sound);

		playSound(ingame_sound1);

		ResetGame();

		setMouseCallback(mouseCallback);
		setKeyboardCallback(keyboardCallback);
		setTimerCallback(timerCallback);

		enterScene(gameScene[level]);
		return;
	}
	else if (obj == end_button3)
	{
		playSound(click_sound);

		endGame();
		return;
	}
}