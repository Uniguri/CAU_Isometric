#include "player.h"
#include "platform.h"

TimerID playerMoveTimer;

void InitPlayer(Player* player, const SceneID scene) {
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

void PlayerTimerCallback(TimerID timer, Player* player, ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH]) {
    if (timer == playerMoveTimer) {
        player->x += player->dx;
        player->y += player->dy;
        MoveMap(map, player->scene, player->x, player->y);
        setTimer(playerMoveTimer, 0.01f);
        startTimer(playerMoveTimer);
    }
}