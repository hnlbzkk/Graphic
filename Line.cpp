#include "Line.h"
#include <iostream>
#include <easyx.h>
//#include "data.h"
#include "Blinn-Phong.h"
#include "transform.h"
#include "Texture.h"

using namespace std;


//画点
void drawPoint(int x, int y, int color) {//采用的就是easyX中的画点函数
    if(x >= 0 && y > 0 && x < GRAPHIC_LENGTH && y < GRAPHIC_WIDTH)
        colorBuffered[x][y] = color;
    //putpixel(x, y, color);
}
//根据亮度修改对应的颜色
int changeColorByLight(int color, float light) {
    if (light < 0) {
        light = 0;
    }
    if (light > 1)
        light = 1;
    float h, s, l;
    float* H = &h, * S = &s, * L = &l;
    RGBtoHSL(color, H, S, L);
    float olight = *L;
    //light = olight+(2-4 * olight)* light*light + (4 * olight -1)*light-0.5;
    //light = olight;
    return HSLtoRGB(*H, *S, light);
}

//增加了Light亮度参数
void drawPoint(int x, int y, int color, double light) {
    int changedColor = changeColorByLight(color, light);
    drawPoint(x, y, changedColor);
}

//画线段函数
//起点(x1,y1)到终点(x2,y2)的颜色，虚实线 默认实线
void drawLine(int  x1, int  y1, int  x2, int  y2, int color, int type /*= SOLID_LINE*/) {
    if (x1 == x2) {//斜率不存在时
        if (y1 <= y2) {
            for (int y = y1; y <= y2; y++) {
                if (type == SOLID_LINE) {
                    drawPoint(x1, y, color);
                };
                if (type == DASH_LINE) {//虚线，隔3个点显示
                    if ((y / 3) % 2 == 0) {
                        drawPoint(x1, y, color);
                    }
                };
            }
        }
        else {
            for (int y = y2; y <= y1; y++) {
                if (type == SOLID_LINE) {
                    drawPoint(x1, y, color);
                };
                if (type == DASH_LINE) {//虚线，隔3个点显示
                    if ((y / 3) % 2 == 0) {
                        drawPoint(x1, y, color);
                    }
                };
            }
        }
        return;
    };//斜率不存在的情况完成

    int dx = x2 - x1;
    int dy = y2 - y1;
    double k = (float)dy / (float)dx;//斜率

    if (k >= -1 && k <= 1) {//-1<=斜率<=1的
        if (x1 <= x2) {//p1 x坐标小时
            double y = y1;
            for (int x = x1; x <= x2; x++) {
                if (type == DASH_LINE) {//虚线，隔3个点显示
                    if ((x / 3) % 2 == 0) {
                        drawPoint(x, (int)(y + 0.5), color);
                    }
                };
                if (type == SOLID_LINE) {
                    drawPoint(x, (int)(y + 0.5), color);
                };
                y += k;
            }
        }
        else {
            double y = y2;
            for (int x = x2; x <= x1; x++) {
                if (type == DASH_LINE) {//虚线，隔3个点显示
                    if ((x / 3) % 2 == 0) {
                        drawPoint(x, (int)(y + 0.5), color);
                    }
                };
                if (type == SOLID_LINE) {
                    drawPoint(x, (int)(y + 0.5), color);
                };
                y += k;
            }
        }
    }
    else {//斜率绝对值大于1的情况
        double k = (float)dx / (float)dy;//斜率
        if (y1 <= y2) {
            double x = x1;
            for (int y = y1; y <= y2; y++) {
                if (type == DASH_LINE) {//虚线，隔3个点显示
                    if ((y / 3) % 2 == 0) {
                        drawPoint((int)(x + 0.5), y, color);
                    }
                };
                if (type == SOLID_LINE) {
                    drawPoint((int)(x + 0.5), y, color);
                };
                x += k;
            }
        }
        else {
            double x = x2;
            for (int y = y2; y < y1; y++) {
                if (type == DASH_LINE) {//虚线，隔3个点显示
                    if ((y / 3) % 2 == 0) {
                        drawPoint((int)(x + 0.5), y, color);
                    }
                };
                if (type == SOLID_LINE) {
                    drawPoint((int)(x + 0.5), y, color);
                };
                x += k;
            }
        }
    }
}
void drawLine(Point p1, Point p2, int color, int type /*= SOLID_LINE*/) {
    drawLine((int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y, color, type);
}

//在屏幕上划分出一部分作为显示窗口
void drawWindow() {
    drawLine(WINDOW_LEFT, WINDOW_BOTTOM, WINDOW_LEFT, WINDOW_TOP, WHITE);//left
    drawLine(WINDOW_RIGHT, WINDOW_BOTTOM, WINDOW_RIGHT, WINDOW_TOP, WHITE);//right
    drawLine(WINDOW_LEFT, WINDOW_BOTTOM, WINDOW_RIGHT, WINDOW_BOTTOM, WHITE);//bottom    
    drawLine(WINDOW_LEFT, WINDOW_TOP, WINDOW_RIGHT, WINDOW_TOP, WHITE);//top
}
