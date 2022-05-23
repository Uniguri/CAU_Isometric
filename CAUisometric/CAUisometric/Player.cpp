#include "player.h"

extern SceneID mainScene;
TimerID playerMoveTimer;
ObjectID player;
int dx, dy, speed = 5, playerX = 600, playerY = 300;

void Player_init() {
    player = createObject("player.png");
    locateObject(player, mainScene, playerX, playerY);
    showObject(player);

    playerMoveTimer = createTimer(0.01f);
    startTimer(playerMoveTimer);
}

void Player_keyboardCallback(KeyCode code, KeyState state) {
    if (code == KeyCode::KEY_UP_ARROW) {
        if (state == KeyState::KEY_PRESSED)
            dy += speed;
        else dy -= speed;
    }
    if (code == KeyCode::KEY_RIGHT_ARROW) {
        if (state == KeyState::KEY_PRESSED)
            dx += speed;
        else dx -= speed;
    }
    if (code == KeyCode::KEY_DOWN_ARROW) {
        if (state == KeyState::KEY_PRESSED)
            dy -= speed;
        else dy += speed;
    }
    if (code == KeyCode::KEY_LEFT_ARROW) {
        if (state == KeyState::KEY_PRESSED)
            dx -= speed;
        else dx += speed;
    }
}

void Player_timerCallback(TimerID timer) {
    if (timer == playerMoveTimer) {
        playerX += dx;
        playerY += dy;
        locateObject(player, mainScene, playerX, playerY);
        setTimer(playerMoveTimer, 0.01f);
        startTimer(playerMoveTimer);
    }
}