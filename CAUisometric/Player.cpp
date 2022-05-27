#include "player.h"
#include "platform.h"

TimerID playerMoveTimer;

void InitPlayer(Player* player, const SceneID scene) {
    player->obj = createObject("t.png");
    player->scene = scene;
    player->speed = 10;
    player->x = 0;
    player->y = 0;
    locateObject(player->obj, scene, PLAYER_BASIC_X, PLAYER_BASIC_Y);
    showObject(player->obj);

    playerMoveTimer = createTimer(0.01f);
    startTimer(playerMoveTimer);
}

extern ObjectID mainScene;
bool IsOutOfMap(Player* player, const int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], const int level)
{
    Coord player_loc = {PLAYER_BASIC_X, PLAYER_BASIC_Y };

    for (int y = 0; y <= BASE_Y; ++y)
    {
        for (int x = 0; x <= BASE_X; ++x)
        {
            if (base[level][y][x]) continue;

            Coord points[4] = { 0 };
            Coord d_coord = { player->x, player->y };
            points[0] = TransformCoord({ x, y }, { 0, 0 }, d_coord);
            points[1] = TransformCoord({ x, y }, { 0, CHUNK_SIZE - 1 }, d_coord);
            points[2] = TransformCoord({ x, y }, { CHUNK_SIZE - 1, CHUNK_SIZE - 1 }, d_coord);
            points[3] = TransformCoord({ x, y }, { CHUNK_SIZE - 1, 0 }, d_coord);

            points[0].x += TILE_WIDTH_OFFSET_FROM_LEFT;
            points[0].y += TILE_SIZE*1.5;
            points[1].x += TILE_WIDTH_OFFSET_FROM_LEFT + 21 * SCALE / 2;
            points[1].y += TILE_SIZE;
            points[2].x += TILE_SIZE;
            points[2].y += TILE_SIZE*1.5;
            points[3].x += TILE_SIZE;
            points[3].y += TILE_SIZE * 1.5;

            //// For square tile
            //points[1].y += TILE_HEIGHT;
            //points[2].x += TILE_WIDTH;
            //points[2].y += TILE_HEIGHT;
            //points[3].x += TILE_WIDTH;

            if (IsCollision(player_loc, 4, points))
                return true;
        }
    }

    return false;
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

void PlayerTimerCallback(TimerID timer, Player* player, ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH], const int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1]) {
    if (timer == playerMoveTimer) {
        player->x += player->dx;
        player->y += player->dy;
        MoveMap(map, player->scene, 0, player->x, player->y);
        if (IsOutOfMap(player, base, 0))
            printf("Out of map: %lld, %ld\n", time(NULL), clock());
        setTimer(playerMoveTimer, 0.01f);
        startTimer(playerMoveTimer);
    }
}