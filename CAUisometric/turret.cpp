#include "turret.h"

extern int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], level;
extern SceneID gameScene[MAX_LEVEL];
extern Bullet bullets[100];
extern Turret turrets[MAX_LEVEL][MAX_NUMBER_OF_TURRET];
//struct Turret
//{
//   ObjectID obj;
//   SceneID scene;
//   int x, y;
//   int inner_x, inner_y;
//};



void InitTurret() {
    for (int m = 0; m < MAX_LEVEL; m++) {
        int idx = 0;
        for (int i = 1; i < BASE_Y; i++) {
            for (int j = 1; j < BASE_X; j++) {
                if (base[m][i][j] == 1) {
                    int pickCnt = rand() % 100, cnt = 0;
                    if (pickCnt < 40) cnt = 1;
                    else if (40 <= pickCnt && pickCnt < 50) cnt = 2;
                    for (int k = 0; k < cnt; k++) {
                        Coord tmp = { rand() % CHUNK_SIZE, rand() % CHUNK_SIZE };
                        turrets[m][idx].obj = createObject("img/turret.png");
                        turrets[m][idx].scene = gameScene[m];
                        turrets[m][idx].x = j;
                        turrets[m][idx].y = i;
                        turrets[m][idx].inner_x = tmp.x;
                        turrets[m][idx].inner_y = tmp.y;
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
    for(int i = 0; ; i++){
        if (turrets[level][i].obj == 0) break;
        Coord loc = TransformCoord(turrets[level][i].x, turrets[level][i].y, turrets[level][i].inner_x, turrets[level][i].inner_y, dx, dy);
        locateObject(turrets[level][i].obj, turrets[level][i].scene, loc.x, loc.y);
    }
}

void TurretFire() {
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

//bool IsHitted() {
// 
//}

//
//bool isnearPlayer(Turret turrets[MAX_LEVEL][MAX_NUMBER_OF_TURRET], const int dx, const int dy, int level) {
//    for (int i = 0; ; i++) {
//        if (turrets[level][i].obj == 0) break;
//        Coord loc = TransformCoord(turrets[level][i].x, turrets[level][i].y, turrets[level][i].inner_x, turrets[level][i].inner_y, dx, dy);
//        int rx = loc.x - PLAYER_BASIC_X, ry = loc.y - PLAYER_BASIC_Y;
//        int r = sqrt(pow(rx, 2) + pow(ry, 2));
//        if (-100 < r < 100) {
//            return true;
//        }
//    }
//    return false;
//}
//
//bool isnearAttack(Turret turrets[MAX_LEVEL][MAX_NUMBER_OF_TURRET], const int dx, const int dy, int level) {
//    /*for (int i = 0; ; i++) {
//        if (turrets[level][i].obj == 0) break;
//        Coord loc = TransformCoord(turrets[level][i].x, turrets[level][i].y, turrets[level][i].inner_x, turrets[level][i].inner_y, dx, dy);
//        int rx = loc.x - PLAYER_BASIC_X, ry = loc.y - PLAYER_BASIC_Y;
//        int r = sqrt(pow(rx, 2) + pow(ry, 2));
//        if (-10 < r < 10) {
//            return true;
//        }
//    }*/
//    return false;
//}
//
//bool IsHitted(Turret turrets[MAX_LEVEL][MAX_NUMBER_OF_TURRET], Bullet* bullet, int level) {
//    /* for (int i = 0; ; i++) {
//         if (turrets[level][i].obj == 0) break;
//         if (isnearAttack) {
//             hideObject(turrets[level][i].obj);
//             return true;
//         }
//     }*/
//    return false;
//}