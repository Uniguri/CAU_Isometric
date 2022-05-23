#include "platform.h"

SceneID mainScene;
ObjectID map[L][N][M];
int base[L][baseN + 1][baseM + 1];

char TileFileName[L][50] = {
	"tiles/assets_pixel_50x50/isometric_pixel_9999.png"
};
int level = 0;
int d[4][2] = { 1, 0, -1, 0, 0, 1, 0, -1 }, ck = 0;

void printPlatform() {
	int i, j, k, l;
	for (i = 1; i <= baseN; i++) {
		for (j = 1; j <= baseM; j++) {
			if (base[level][i][j] == 1) {
				for (k = 1; k <= block; k++) {
					for (l = 1; l <= block; l++) {
						map[level][i * block + k][j * block + l] = createObject(TileFileName[level]);
						locateObject(map[level][i * block + k][j * block + l], mainScene, j * l * size * scale / 2, i * k * size * scale / 2);
						scaleObject(map[level][i * block + k][j * block + l], scale);
						showObject(map[level][i * block + k][j * block + l]);
					}
				}
			}
		}
	}
}

void randomCreatePlatform(int l, int n, int m) {
	base[l][n][m] = 1;
	ck++;
	if (ck > blockLimit)
		return;
	int i = rand() % 4, cnt = 4;
	while (cnt-- && ck <= blockLimit) {
		int dn = n + d[i][0], dm = m + d[i][1];
		if (ck <= blockLimit && 1 <= dn && dn < baseN && 1 <= dm && dm < baseM && base[l][dn][dm] == 0) {
			randomCreatePlatform(l, dn, dm);
		}
		i++;
		if (i == 4)
			i = 0;
	}
}