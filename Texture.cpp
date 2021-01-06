#include "Texture.h"

int colorBuffered[GRAPHIC_LENGTH][GRAPHIC_WIDTH];//缓冲区存放颜色
int pictureColor[PICTURE_LENGTH][PICTURE_WIDTH];//照片数组

//图片坐标转纹理坐标
Point picToTexture(int width, int height, int x, int y) {
	Point result;

	result.x = (double)x / (width - 1);
	result.y = (double)y / (height - 1);

	return result;
}

//纹理坐标转颜色缓冲区坐标
Point texttureToBuff(double x, double y, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	double a11;
	double a12;
	double a21;
	double a22;
	if (x <= y) {
		a11 = x3 - x2;
		a12 = x2 - x1;
		a21 = y3 - y2;
		a22 = y2 - y1;
	}
	else {
		a11 = x4 - x1;
		a12 = x3 - x4;
		a21 = y4 - y1;
		a22 = y3 - y4;
	}
	double resultx = a11 * x + a12 * y + x1;
	double resulty = a21 * x + a22 * y + y1;

	Point result = { resultx ,resulty };
	return result;
}

//实现把纹理的颜色加到一个四边形上去修改缓冲区
void addTexture(IMAGE img, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	int height = img.getheight();
	int width = img.getwidth();
	Point p;

	for (int j = 0; j < height - 10; j++) {
		for (int i = 0; i < width - 10; i++) {
			p = picToTexture(width, height, i, j);
			p = texttureToBuff(p.x, p.y, x1, y1, x2, y2, x3, y3, x4, y4);
			//colorBuffered[(int)(p.x + 0.5)][(int)(p.y + 0.5)] = add(pictureColor[i][j], colorBuffered[(int)(p.x + 0.5)][(int)(p.y + 0.5)]);
			if (p.x > 0 && p.y > 0 && p.y < WINDOW_BOTTOM)
				colorBuffered[(int)(p.x + 0.5)][(int)(p.y + 0.5)] = pictureColor[i][j];
		}
	}
}

void addTexture(COLORREF color, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	int height = 200;
	int width = 200;
	Point p;

	for (int j = 10; j < height - 10; j++) {
		for (int i = 10; i < width - 10; i++) {
			p = picToTexture(width, height, i, j);
			p = texttureToBuff(p.x, p.y, x1, y1, x2, y2, x3, y3, x4, y4);
			//colorBuffered[(int)(p.x + 0.5)][(int)(p.y + 0.5)] = add(pictureColor[i][j], colorBuffered[(int)(p.x + 0.5)][(int)(p.y + 0.5)]);
			if(p.x > 0 && p.y > 0)
				colorBuffered[(int)(p.x + 0.5)][(int)(p.y + 0.5)] = color;
		}
	}
}


//缓冲区算法
void showScreen() {
	for (int i = 0; i < GRAPHIC_LENGTH; i++) {
		for (int j = 0; j < GRAPHIC_WIDTH; j++) {
			if (i >= WINDOW_LEFT && i <= WINDOW_RIGHT && j >= WINDOW_TOP && j <= WINDOW_BOTTOM) {
				putpixel(i, j, colorBuffered[i][j]);
			}
			else {
				putpixel(i, j, BLACK);
			}
		}
	}
}
//缓冲区算法
void showScreen2() {
	for (int i = 0; i < GRAPHIC_LENGTH; i++) {
		for (int j = 0; j < GRAPHIC_WIDTH; j++) {
			putpixel(i, j, colorBuffered[i][j]);
		}
	}
}

void clearBuffer() {
	for (int i = 0; i < GRAPHIC_LENGTH; i++) {
		for (int j = 0; j < GRAPHIC_WIDTH; j++) {
			colorBuffered[i][j] = BLACK;
		}
	}
}