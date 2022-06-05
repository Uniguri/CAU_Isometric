#include "bullet.h"

extern int level;
extern SceneID gameScene[MAX_LEVEL];
extern Bullet bullets[MAX_NUMBER_OF_BULLET];

extern SoundID bullet_sound;

TimerID bullet_timer;

const char* BULLET_IMAGES[] = {
	"img/bullets/All_Fire_Bullet_Pixel/mint_bullet.png",
	"img/bullets/All_Fire_Bullet_Pixel/purple_bullet.png",
	"img/bullets/All_Fire_Bullet_Pixel/gray_bullet.png",
	"img/bullets/All_Fire_Bullet_Pixel/ice_bullet.png",
	"img/bullets/All_Fire_Bullet_Pixel/red_bullet.png",
	"img/bullets/All_Fire_Bullet_Pixel/white_bullet.png"
};
void BulletTimerCallback(TimerID timer, const int dx, const int dy)
{
	if (timer != bullet_timer)
		return;

	for (int i = 0; i < MAX_NUMBER_OF_BULLET; ++i)
		RefreshBullet(dx, dy, i);

	setTimer(bullet_timer, 0.01f);
	startTimer(bullet_timer);
}

void InitBullet(int i)
{
	bullets[i].obj = createObject(BULLET_IMAGES[0]);
	bullets[i].scene = gameScene[level];
	DeleteBullet(i);
}

void InitBulletSystem(void)
{
	bullet_timer = createTimer(0.01f);
	startTimer(bullet_timer);
}

void DeleteBullet(int i)
{
	bullets[i].is_deleted = true;
	hideObject(bullets[i].obj);
}

void SetBullet(const int x, const int y, const int speed, const Vec2d direction_vec, int i)
{
	bullets[i].scene = gameScene[level];
	bullets[i].x = x;
	bullets[i].y = y;
	bullets[i].speed = speed;
	double len = sqrt(pow(direction_vec.x, 2) + pow(direction_vec.y, 2));
	bullets[i].direction_vec = { sqrt(speed) * direction_vec.x / len, sqrt(speed) * direction_vec.y / len };
	//bullets[i].direction_vec = { direction_vec.x, direction_vec.y};
	bullets[i].is_deleted = false;

	setObjectImage(bullets[i].obj, BULLET_IMAGES[level]);
	scaleObject(bullets[i].obj, SCALE / 2);
	locateObject(bullets[i].obj, gameScene[level], x, y);
	showObject(bullets[i].obj);
	playSound(bullet_sound);
}

void ChangeBulletType(BulletType type, int i)
{
	setObjectImage(bullets[i].obj, BULLET_IMAGES[type]);
}

void MoveBullet(const int additional_dx, const int additional_dy, int i)
{
	Vec2d dir_vec = bullets[i].direction_vec;

	float sign_of_f = (dir_vec.x >= 0) ? 1 : -1;
	bullets[i].x += sign_of_f * pow(dir_vec.x,2) + additional_dx;
	sign_of_f = (dir_vec.y >= 0) ? 1 : -1;
	bullets[i].y += sign_of_f * pow(dir_vec.y,2) + additional_dy;

	Coord loc = TransformCoord(BASE_X, BASE_Y, CHUNK_SIZE - 1, CHUNK_SIZE - 1, 0, 0);
	if (bullets[i].x < 0 || bullets[i].x > loc.x)
		DeleteBullet(i);
	loc = TransformCoord(0, BASE_Y, CHUNK_SIZE - 1, CHUNK_SIZE - 1, 0, 0);
	if (bullets[i].y < 0 || bullets[i].y > loc.y)
		DeleteBullet(i);
}

void RefreshBullet(const int additional_dx, const int additional_dy, int i)
{
	if (bullets[i].is_deleted)
		return;

	MoveBullet(additional_dx, additional_dy, i);
	locateObject(bullets[i].obj, bullets[i].scene, bullets[i].x, bullets[i].y);
}
