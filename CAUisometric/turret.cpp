#include "turret.h"
#include "Player.h"


extern int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], level;
extern SceneID gameScene[MAX_LEVEL];
extern Bullet bullets[100];
extern Turret turrets[MAX_LEVEL][MAX_NUMBER_OF_TURRET];
extern Player player;

void InitTurret() {
    for (int m = 0; m < MAX_LEVEL; m++) {
        int idx = 0;
        for (int i = 1; i < BASE_Y; i++) {
            for (int j = 1; j < BASE_X; j++) {
                if (base[m][i][j] == 1 && base[m][i - 1][j - 1] == 1) {
                    int pickCnt = rand() % 100, cnt = 0;
                    if (pickCnt < 40) cnt = 3;
                    else if (40 <= pickCnt && pickCnt < 50) cnt = 2;
                    for (int k = 0; k < cnt; k++) {
                        Coord tmp = { 1 + rand() % (CHUNK_SIZE - 1), 1 + rand() % (CHUNK_SIZE)-1 };
                        turrets[m][idx].obj = createObject("img/turret.png");
                        turrets[m][idx].scene = gameScene[m];
                        turrets[m][idx].x = j;
                        turrets[m][idx].y = i;
                        turrets[m][idx].inner_x = tmp.x;
                        turrets[m][idx].inner_y = tmp.y;
                        turrets[m][idx].fire_late = TURRET_FIRE_LATE;
                        turrets[m][idx].last_fire_time = time(NULL);
                        Coord loc = TransformCoord(turrets[m][idx].x, turrets[m][idx].y, turrets[m][idx].inner_x, turrets[m][idx].inner_y, 0, 0);
                        locateObject(turrets[m][idx].obj, turrets[m][idx].scene, loc.x, loc.y);
                        scaleObject(turrets[m][idx].obj, SCALE);
                        showObject(turrets[m][idx].obj);
                        idx++;
                    }
                }
            }
        }
    }
}


void MoveTurret(const int dx, const int dy) {
    //640 360
    for(int i = 0; i < MAX_NUMBER_OF_BULLET; i++){
        if (turrets[level][i].obj == 0) break;
        Coord loc = TransformCoord(turrets[level][i].x, turrets[level][i].y, turrets[level][i].inner_x, turrets[level][i].inner_y, dx, dy);
        locateObject(turrets[level][i].obj, turrets[level][i].scene, loc.x, loc.y);
        if (turrets[level][i].active && isnearPlayer(player.x, player.y, TurretRange, i)) TurretFire(dx, dy, i);
    }
}

void TurretFire(const int dx, const int dy, int i) {
    if (time(NULL) - turrets[level][i].last_fire_time < turrets[level][i].fire_late)
        return;
    Coord loc = TransformCoord(turrets[level][i].x, turrets[level][i].y, turrets[level][i].inner_x, turrets[level][i].inner_y, dx, dy);
    for (int index_of_bullet = 0; index_of_bullet < MAX_NUMBER_OF_BULLET; ++index_of_bullet)
    {
        if (bullets[index_of_bullet].is_deleted)
        {
            SetBullet(loc.x, loc.y, PLAYER_BASIC_SPEED, { (double)PLAYER_BASIC_X - loc.x, (double)PLAYER_BASIC_Y - loc.y }, index_of_bullet);
            break;
        }
    }

    turrets[level][i].last_fire_time = time(NULL);
}

bool isnearPlayer(const int dx, const int dy, int range, int i) {
    Coord loc = TransformCoord(turrets[level][i].x, turrets[level][i].y, turrets[level][i].inner_x, turrets[level][i].inner_y, dx, dy);
    int rx = loc.x - PLAYER_BASIC_X, ry = loc.y - PLAYER_BASIC_Y;
    int r = sqrt(pow(rx, 2) + pow(ry, 2));
    if (r < range) {
        return true;
    }
    return false;
}

void isTurretHitted(int i) {
    turrets[level][i].active = false;
    hideObject(turrets[level][i].obj);
    printf("aya\n");
    return;
}