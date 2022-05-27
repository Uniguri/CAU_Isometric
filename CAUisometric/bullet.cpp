#include "bullet.h"

TimerID bullet_timer;
const char* BULLET_IMAGE[] = {
	"t.png"
};
void BulletTimerCallback(TimerID timer, Bullet bullets[MAX_NUMBER_OF_BULLET], const int dx, const int dy)
{
	if (timer != bullet_timer)
		return;

	for (int i = 0; i < MAX_NUMBER_OF_BULLET; ++i)
		RefreshBullet(bullets + i, dx, dy);

	setTimer(bullet_timer, 0.01f);
	startTimer(bullet_timer);
}

void InitBullet(Bullet* bullet, SceneID scene)
{
	bullet->obj = createObject(BULLET_IMAGE[0]);
	bullet->scene = scene;
	DeleteBullet(bullet);
}

void InitBulletSystem(void)
{
	bullet_timer = createTimer(0.01f);
	startTimer(bullet_timer);
}

void DeleteBullet(Bullet* bullet)
{
	bullet->is_deleted = true;
	hideObject(bullet->obj);
}

void SetBullet(Bullet* bullet, SceneID scene, const int x, const int y, const int speed, const Vec2d direction_vec)
{
	bullet->scene = scene;
	bullet->x = x;
	bullet->y = y;
	bullet->speed = speed;
	double len = sqrt(pow(direction_vec.x, 2) + pow(direction_vec.y, 2));
	//bullet->direction_vec = { speed * direction_vec.x / len, speed * direction_vec.y / len };
	bullet->direction_vec = { direction_vec.x, direction_vec.y};
	bullet->is_deleted = false;

	scaleObject(bullet->obj, SCALE / 2);
	locateObject(bullet->obj, scene, x, y);
	showObject(bullet->obj);
}

void MoveBullet(Bullet* bullet, const int additional_dx, const int additional_dy)
{
	if (bullet->is_deleted)
		return;

	bullet->x += bullet->speed * bullet->direction_vec.x + additional_dx;
	bullet->y += bullet->speed * bullet->direction_vec.y+ additional_dy;

	Coord loc = TransformCoord(BASE_X, BASE_Y, CHUNK_SIZE - 1, CHUNK_SIZE - 1, 0, 0);
	if (bullet->x < 0 || bullet->x > loc.x)
		DeleteBullet(bullet);
	loc = TransformCoord(0, BASE_Y, CHUNK_SIZE - 1, CHUNK_SIZE - 1, 0, 0);
	if (bullet->y < 0 || bullet->y > loc.y)
		DeleteBullet(bullet);
}

void RefreshBullet(Bullet* bullet, const int additional_dx, const int additional_dy)
{
	MoveBullet(bullet, 0, 0);
	locateObject(bullet->obj, bullet->scene, bullet->x + additional_dx, bullet->y + additional_dy);
}
