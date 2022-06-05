#include "platform.h"

extern ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH];
extern int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], level;
extern SceneID gameScene[MAX_LEVEL], gameover_scene;
extern Door door[MAX_LEVEL];
extern Player player;


const char* TileFileName[MAX_LEVEL] = {
	"img/tiles/assets_pixel_50x50/isometric_pixel_9995.png",
	"img/tiles/assets_pixel_50x50/isometric_pixel_9994.png",
	"img/tiles/assets_pixel_50x50/isometric_pixel_9996.png",
	"img/tiles/assets_pixel_50x50/isometric_pixel_9997.png",
	"img/tiles/assets_pixel_50x50/isometric_pixel_9998.png"
};


void MakeMap() {
	for (int m = 0; m < MAX_LEVEL; m++) {
		for (int i = 1; i < BASE_Y; i++) {
			for (int j = 1; j < BASE_X; j++) {
				if (base[m][i][j] == 1) {
					for (int k = 0; k < CHUNK_SIZE; k++) {
						for (int l = 0; l < CHUNK_SIZE; l++) {
							ObjectID obj = createObject(TileFileName[m]);
							map[m][i * CHUNK_SIZE + k][j * CHUNK_SIZE + l] = obj;
							Coord loc = TransformCoord(j, i, l, k, 0, 0);
							locateObject(obj, gameScene[m], loc.x, loc.y);
							scaleObject(obj, SCALE);
							showObject(obj);
						}
					}
				}
			}
		}
	}
}

void MoveMap(int dx, int dy)
{
	for (int i = 1; i < BASE_Y; i++) {
		for (int j = 1; j < BASE_X; j++) {
			for (int k = 0; k < CHUNK_SIZE; k++) {
				for (int l = 0; l < CHUNK_SIZE; l++) {
					ObjectID obj = map[level][i * CHUNK_SIZE + k][j * CHUNK_SIZE + l];
					Coord loc = TransformCoord(j, i, l, k, dx, dy);
					locateObject(obj, gameScene[level], loc.x, loc.y);
				}
			}
		}
	}
}

int CreateRandomMap(int height, int width, int ck) {
	int d[4][2] = { 1, 0, -1, 0, 0, 1, 0, -1 };

	base[level][height][width] = 1;
	ck++;
	if (ck > BLOCK_LIMIT)
		return ck;
	srand(rand());
	int i = rand() % 4, cnt = 4;
	while (cnt-- && ck <= BLOCK_LIMIT) {
		int dn = height + d[i][0], dm = width + d[i][1];
		if (ck <= BLOCK_LIMIT && 1 <= dn && dn < BASE_Y && 1 <= dm && dm < BASE_X && base[level][dn][dm] == 0) {
			ck = CreateRandomMap(dn, dm, ck);
		}
		i++;
		if (i == 4)
			i = 0;
	}

	return ck;
}

void MakeDoor() {
	for (int m = 0; m < MAX_LEVEL; m++) {
		Coord tmp;
		while (1) {
			tmp = { 1 + rand() % (BASE_X - 1), 1 + rand() % (BASE_Y - 1) };
			if (base[m][tmp.y][tmp.x] == 1) break;
		}
		door[m].obj = createObject("img/door/portal_1.png");
		door[m].scene = gameScene[m];
		door[m].x = 1;
		door[m].y = 1;
		door[m].inner_x = CHUNK_SIZE / 2;
		door[m].inner_y = CHUNK_SIZE / 2;

		Coord loc = TransformCoord(door[m].x, door[m].x, door[m].inner_x, door[m].inner_y, 0, 0);
		locateObject(door[m].obj, door[m].scene, loc.x, loc.y);
		scaleObject(door[m].obj, SCALE);
		showObject(door[m].obj);
	}
}

void MoveDoor(const int dx, const int dy) {
	Coord loc = TransformCoord(door[level].x, door[level].y, door[level].inner_x, door[level].inner_y, dx, dy);
	locateObject(door[level].obj, door[level].scene, loc.x, loc.y);
	if (isnearDoor(player.x, player.y, DoorRange)) {
		if (door[level].active) {
			if (level == MAX_LEVEL - 1) {
				enterScene(gameover_scene);
				setMouseCallback(GameOverSceneMCB);
			}
			else {
				door[level].active = false;
				setObjectImage(door[level++].obj, "img/door/portal_1.png");
				ResetPlayer();
			}
		}
	}	
}

bool isnearDoor(const int dx, const int dy, int range) {
	Coord loc = TransformCoord(door[level].x, door[level].y, door[level].inner_x, door[level].inner_y, dx, dy);
	int rx = loc.x - PLAYER_BASIC_X, ry = loc.y - PLAYER_BASIC_Y;
	int r = int(sqrt(pow(rx, 2) + pow(ry, 2)));
	if (r < range) {
		return true;
	}
	return false;
}

void ActiveDoor() {
	setObjectImage(door[level].obj, "img/door/portal_2.png");
	door[level].active = true;
	return;
}
