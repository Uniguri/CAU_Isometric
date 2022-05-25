#include "platform.h"


const char const* TileFileName[MAX_LEVEL] = {
	"img/tiles/assets_pixel_50x50/isometric_pixel_9999.png"
};


void MakeMap(int base[MAX_LEVEL][baseN + 1][baseM + 1], ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH], const SceneID scene, const int level) {
	for (int i = 1; i <= baseN; i++) {
		for (int j = 1; j <= baseM; j++) {
			if (base[level][i][j] == 1) {
				for (int k = 1; k <= CHUNK_SIZE; k++) {
					for (int l = 1; l <= CHUNK_SIZE; l++) {
						ObjectID obj = createObject(TileFileName[0]);
						map[level][i * CHUNK_SIZE + k][j * CHUNK_SIZE + l] = obj;
						Coord loc = TransformCoord(i, j, k, l, 0, 0);
						locateObject(obj, scene, loc.x, loc.y);
						scaleObject(obj, SCALE);
						showObject(obj);
					}
				}
			}
		}
	}
}

void MoveMap(ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH], ObjectID scene, int dx, int dy)
{
	for (int i = 1; i <= baseN; i++) {
		for (int j = 1; j <= baseM; j++) {
			for (int k = 1; k <= CHUNK_SIZE; k++) {
				for (int l = 1; l <= CHUNK_SIZE; l++) {
					ObjectID obj = map[0][i * CHUNK_SIZE + k][j * CHUNK_SIZE + l];
					Coord loc = TransformCoord(i, j, k, l, dx, dy);
					locateObject(obj, scene, loc.x, loc.y);
				}
			}
		}
	}
}

int CreateRandomMap(int base[MAX_LEVEL][baseN + 1][baseM + 1], int level, int height, int width, int ck) {
	int d[4][2] = { 1, 0, -1, 0, 0, 1, 0, -1 };

	base[level][height][width] = 1;
	ck++;
	if (ck > blockLimit)
		return ck;
	srand(rand());
	int i = rand() % 4, cnt = 4;
	while (cnt-- && ck <= blockLimit) {
		int dn = height + d[i][0], dm = width + d[i][1];
		if (ck <= blockLimit && 1 <= dn && dn < baseN && 1 <= dm && dm < baseM && base[level][dn][dm] == 0) {
			ck = CreateRandomMap(base, level, dn, dm, ck);
		}
		i++;
		if (i == 4)
			i = 0;
	}

	return ck;
}