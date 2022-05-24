#include "player.h"

TimerID playerMoveTimer;

void Player_init(Player* player, SceneID scene) {
    player->obj = createObject("player.png");
    player->scene = scene;
    player->speed = 5;
    player->x = 600;
    player->y = 360;
    locateObject(player->obj, scene, player->x, player->y);
    showObject(player->obj);

    playerMoveTimer = createTimer(0.01f);
    startTimer(playerMoveTimer);
}

void Player_keyboardCallback(KeyCode code, KeyState state, Player* player) {
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

void Player_timerCallback(TimerID timer, Player* player) {
    if (timer == playerMoveTimer) {
        player->x += player->dx;
        player->y += player->dy;
        locateObject(player->obj, player->scene, player->x, player->y);
        setTimer(playerMoveTimer, 0.01f);
        startTimer(playerMoveTimer);
    }
}