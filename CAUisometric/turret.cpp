#include "turret.h"


//struct Turret
//{
//   ObjectID obj;
//   SceneID scene;
//   int x, y;
//   int inner_x, inner_y;
//};



void InitTurret(Turret turrets[MAX_LEVEL][MAX_NUMBER_OF_TURRET], SceneID scene, int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], int level) {

    int idx = 0;
    for (int i = 1; i < BASE_Y; i++) {
        for (int j = 1; j < BASE_X; j++) {
            if (base[level][i][j] == 1) {
                int pickCnt = rand() % 100, cnt = 0;
                if (pickCnt < 40) cnt = 1;
                else if (40 <= pickCnt && pickCnt < 50) cnt = 2;
                for (int k = 0; k < cnt; k++) {
                    Coord tmp = { rand() % CHUNK_SIZE, rand() % CHUNK_SIZE };
                    turrets[level][idx].obj = createObject("img/turret.png");
                    turrets[level][idx].scene = scene;
                    turrets[level][idx].x = j;
                    turrets[level][idx].y = i;
                    turrets[level][idx].inner_x = tmp.x;
                    turrets[level][idx].inner_y = tmp.y;
                    Coord loc = TransformCoord(turrets[level][idx].x, turrets[level][idx].y, turrets[level][idx].inner_x, turrets[level][idx].inner_y, 0, 0);
                    locateObject(turrets[level][idx].obj, turrets[level][idx].scene, loc.x, loc.y);
                    scaleObject(turrets[level][idx].obj, SCALE);
                    showObject(turrets[level][idx].obj);
                    idx++;
                }
            }
        }
    }
}


void MoveTurret(Turret turrets[MAX_LEVEL][MAX_NUMBER_OF_TURRET], const int dx, const int dy, const int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], int level) {
    //640 360
    for(int i = 0; ; i++){
        if (turrets[level][i].obj == 0) break;
        Coord loc = TransformCoord(turrets[level][i].x, turrets[level][i].y, turrets[level][i].inner_x, turrets[level][i].inner_y, dx, dy);
        locateObject(turrets[level][i].obj, turrets[level][i].scene, loc.x, loc.y);
    }
}

void TurretFire(Turret* turrets[2], Bullet* bullet, int level) {
    /*int cnt = 1;
    set <Coord> randcoord[BASE_Y + 1][BASE_X + 1];
    for (int i = 1; i < BASE_Y; i++) {
       for (int j = 1; j < BASE_X; j++) {
          if (base[level][i][j] == 1) {
             while (randcoord[i][j].size() < cnt) {
                if (-100 < turrets[cnt].x + dx - 640 && turrets[cnt].x + dx - 640 < 100 && -50 < turrets[cnt].y + dy - 360 && turrets[cnt].y + dy - 360 < 50) {
                   if (code == KeyCode::KEY_SPACE)
                   {
                      if (state == KeyState::KEY_PRESSED)
                      {
                         player->state = PlayerState::ATTACK;
                         player->image_frame = 0;
                      }

                }
             }
          }
       }
    }

 */

}

//bool IsHitted(Turret* turret, Bullet* bullet) {
// 
//}