#include "platform.h"


const char const* TileFileName[MAX_LEVEL] = {
	"img/tiles/assets_pixel_50x50/isometric_pixel_9999.png"
};


void ShowMap(int base[MAX_LEVEL][baseN + 1][baseM + 1], ObjectID map[MAX_LEVEL][MAX_HEIGHT][MAX_WIDTH], SceneID scene, int level) {
	for (int i = 1; i <= baseN; i++) {
		for (int j = 1; j <= baseM; j++) {
			if (base[level][i][j] == 1) {
				for (int k = 1; k <= CHUNK_SIZE; k++) {
					for (int l = 1; l <= CHUNK_SIZE; l++) {
						ObjectID obj = createObject(TileFileName[0]);
						map[level][i * CHUNK_SIZE + k][j * CHUNK_SIZE + l] = obj;
						locateObject(obj, scene, (((j + i - 2) * CHUNK_SIZE + l + k - 1) * TILE_WIDTH) * SCALE / 2, (((i - j + 1) * CHUNK_SIZE + k - l) * TILE_HEIGHT) * SCALE / 2);
						scaleObject(obj, SCALE);
						showObject(obj);
					}
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