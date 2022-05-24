#include "player.h"

TimerID playerMoveTimer;

void PlayerInit(Player* player, SceneID scene) {
    player->obj = createObject("img/player.png");
    player->scene = scene;
    player->speed = 5;
    player->x = 0;
    player->y = 0;
    locateObject(player->obj, scene, 640, 360);
    showObject(player->obj);

    playerMoveTimer = createTimer(0.01f);
    startTimer(playerMoveTimer);
}

void PlayerKeyboardCallback(KeyCode code, KeyState state, Player* player) {
    if (code == KeyCode::KEY_UP_ARROW) {
        if (state == KeyState::KEY_PRESSED)
            player->dy += player->speed;
        else player->dy -= player->speed;
    }
    if (code == KeyCode::KEY_RIGHT_ARROW) {
        if (state == KeyState::KEY_PRESSED)
            player->dx += player->speed;
        else player->dx -= player->speed;
    }
    if (code == KeyCode::KEY_DOWN_ARROW) {
        if (state == KeyState::KEY_PRESSED)
            player->dy -= player->speed;
        else player->dy += player->speed;
    }
    if (code == KeyCode::KEY_LEFT_ARROW) {
        if (state == KeyState::KEY_PRESSED)
            player->dx -= player->speed;
        else player->dx += player->speed;
    }
}

extern ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH];
extern SceneID mainScene;
void PlayerTimerCallback(TimerID timer, Player* player) {
    if (timer == playerMoveTimer) {
        player->x += player->dx;
        player->y += player->dy;
        for (int i = 1; i <= baseN; i++) {
            for (int j = 1; j <= baseM; j++) {
                    for (int k = 1; k <= CHUNK_SIZE; k++) {
                        for (int l = 1; l <= CHUNK_SIZE; l++) {
                            ObjectID obj = map[0][i * CHUNK_SIZE + k][j * CHUNK_SIZE + l];
                            locateObject(obj, mainScene, (-player->x + ((j+i-2) * CHUNK_SIZE + l + k - 1) * TILE_WIDTH) * SCALE / 2, (- player->y + ((i - j + 1) * CHUNK_SIZE + k - l) * TILE_HEIGHT) * SCALE / 2);
                        }
                    }
            }
        }
        //locateObject(player->obj, player->scene, player->x, player->y);
        setTimer(playerMoveTimer, 0.01f);
        startTimer(playerMoveTimer);
    }
}