////quan ly vung choi
//const int height = 20;
//const int width = 10;
//
//int field[height][width] = { 0 };
//
//struct position {
//	int x;
//	int y;
//}
//shape1[4],
//shape2[4];
//
//int block[7][4] = {
//	1, 3, 5, 7, //I
//	2, 4, 5, 7, //Z nguoc nam doc
//	3, 5, 4, 6, //Z nam doc
//	3, 5, 4, 7, //T nam doc
//	2, 3, 5, 7, //L bi nguoc
//	3, 5, 7, 6, // j
//	2, 3, 4, 5, //o vuong
//};


////ve cac khoi
//void draw(int n) {
//	for (int i = 0; i < 4; i++) {
//		shape1[i].x = block[n][i] % 2;
//		shape1[i].y = block[n][i] / 2;
//	}
//	for (int i = 0; i < 4; i++) {
//		cout << shape1[i].x << " " << shape1[i].y << endl;
//	}
//}
//
//bool loadSurfaceMedia(string path)
//{
//	tetris_background = loadSurface(path.c_str());
//	if (tetris_background == NULL) return false;
//	return true;
//}#pragma once
