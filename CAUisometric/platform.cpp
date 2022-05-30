#include "platform.h"


const char* TileFileName[MAX_LEVEL] = {
	"img/tiles/assets_pixel_50x50/isometric_pixel_9995.png",
	"img/tiles/assets_pixel_50x50/isometric_pixel_9994.png",
	"img/tiles/assets_pixel_50x50/isometric_pixel_9996.png",
	"img/tiles/assets_pixel_50x50/isometric_pixel_9997.png",
	"img/tiles/assets_pixel_50x50/isometric_pixel_9998.png"
};


void MakeMap(int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH], const SceneID scene, const int level) {
	for (int i = 1; i < BASE_Y; i++) {
		for (int j = 1; j < BASE_X; j++) {
			if (base[level][i][j] == 1) {
				for (int k = 0; k < CHUNK_SIZE; k++) {
					for (int l = 0; l < CHUNK_SIZE; l++) {
						ObjectID obj = createObject(TileFileName[level]);
						map[level][i * CHUNK_SIZE + k][j * CHUNK_SIZE + l] = obj;
						Coord loc = TransformCoord(j, i, l, k, 0, 0);
						locateObject(obj, scene, loc.x, loc.y);
						scaleObject(obj, SCALE);
						showObject(obj);
					}
				}
			}
		}
	}
}

void MoveMap(ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH], ObjectID scene, int level, int dx, int dy)
{
	for (int i = 1; i < BASE_Y; i++) {
		for (int j = 1; j < BASE_X; j++) {
			for (int k = 0; k < CHUNK_SIZE; k++) {
				for (int l = 0; l < CHUNK_SIZE; l++) {
					ObjectID obj = map[level][i * CHUNK_SIZE + k][j * CHUNK_SIZE + l];
					Coord loc = TransformCoord(j, i, l, k, dx, dy);
					locateObject(obj, scene, loc.x, loc.y);
				}
			}
		}
	}
}

int CreateRandomMap(int base[MAX_LEVEL][BASE_Y + 1][BASE_X + 1], int level, int height, int width, int ck) {
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
			ck = CreateRandomMap(base, level, dn, dm, ck);
		}
		i++;
		if (i == 4)
			i = 0;
	}

	return ck;
}