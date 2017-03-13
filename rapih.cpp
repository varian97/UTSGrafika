#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <cstdio>
#include <termios.h>
#include <math.h>
#include <thread>
#include <vector>

using namespace std;

#define HEIGHT 1250
#define WIDTH 650

struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
char *fbp = 0;

int redPixelMatrix[WIDTH][HEIGHT];
int greenPixelMatrix[WIDTH][HEIGHT];
int bluePixelMatrix[WIDTH][HEIGHT];
int posX;
int posY;
int lastCorrectState = 's';
bool exploded = false;

struct bullet
{
    int xStart;
    int yStart;
    int xEnd;
    int yEnd;
    float m;
    float c;
    int partisi;
    int iteration;
    int x1;
    int x2;
    int n;
};

vector<bullet> bullets;

void clearMatrix() {
    for (int i = 0; i < 600; ++i)
    {
        for (int j = 0; j < 1200; ++j)
        {
            redPixelMatrix[i][j] = 0;
            greenPixelMatrix[i][j] = 0;
            bluePixelMatrix[i][j] = 0;
        }
    }
}

void drawWhitePoint(int x1, int y1) {
    redPixelMatrix[x1][y1] = 255;
    greenPixelMatrix[x1][y1] = 255;
    bluePixelMatrix[x1][y1] = 255;
}

void drawRedPoint(int x1,int y1){
    redPixelMatrix[x1][y1] = 255;
    greenPixelMatrix[x1][y1] = 0;
    bluePixelMatrix[x1][y1] = 0;   
}

void drawBlackPoint(int x1,int y1){
    redPixelMatrix[x1][y1] = 0;
    greenPixelMatrix[x1][y1] = 0;
    bluePixelMatrix[x1][y1] = 0;   
}

void floodFill(int x,int y,int redBatas,int greenBatas,int blueBatas,int redColor,int greenColor,int blueColor){
    if((x>=0 && x<WIDTH) && (y>=0 && y<HEIGHT)){
        if(!((redPixelMatrix[x][y]==redBatas && greenPixelMatrix[x][y]==greenBatas && bluePixelMatrix[x][y]==blueBatas) || 
            (redPixelMatrix[x][y]==redColor && greenPixelMatrix[x][y]==greenColor && bluePixelMatrix[x][y]==blueColor))){
            redPixelMatrix[x][y] = redColor;
            greenPixelMatrix[x][y] = greenColor;
            bluePixelMatrix[x][y] = blueColor;
            floodFill(x,y+1,redBatas,greenBatas,blueBatas,redColor,greenColor,blueColor);
            floodFill(x+1,y,redBatas,greenBatas,blueBatas,redColor,greenColor,blueColor);
            floodFill(x,y-1,redBatas,greenBatas,blueBatas,redColor,greenColor,blueColor);
            floodFill(x-1,y,redBatas,greenBatas,blueBatas,redColor,greenColor,blueColor);
        }
    }
}

/* Rotasi UFO yang sudutnya bergantung pada
 * sudut yang terbentuk atas posisi UFO dan posisi shooter
 */
void rotateUFO(int xp, int yp, int *deltaX, int *deltaY){
	double dY = (double)(574 - yp)/500; //sin
	double dX = (double)(600 - xp)/500; //cos
	int dY1 = (*deltaY) - yp;
	int dX1 = (*deltaX) - xp;
	*deltaY = (int) (round(dY1*dX) + round(dX1*dY)) + yp;
	*deltaX = (int) (round(dX1*dX) - round(dY1*dY)) + xp;
}

void drawSemiCircle(int x0, int y0, int radius)
{
    int x = radius;
    int y = 0;
    int err = 0;
	int a, b;
	int centerX = x0-3; int centerY = y0;
    while (x >= y)
    {
		a = x0-x; b = y0+y;
		//rotateUFO(centerX, centerY, &a, &b);
        drawWhitePoint(a, b);
        a = x0-y; b = y0+x;
        //rotateUFO(centerX, centerY, &a, &b);
        drawWhitePoint(x0 - y, y0 + x); 
        a = x0-y; b = y0-x;
        //rotateUFO(centerX, centerY, &a, &b);
        drawWhitePoint(x0 - y, y0 - x);
        a = x0-y; b = y0-x;
        //rotateUFO(centerX, centerY, &a, &b);
        drawWhitePoint(x0 - x, y0 - y);

        if (err <= 0)
        {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }

    //warnain 
    floodFill(x0-5,y0,255,255,255,255,255,0);
}

void drawCircle(int x0, int y0, int radius)
{
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y)
    {
        drawWhitePoint(x0 - x, y0 + y);
        drawWhitePoint(x0 - y, y0 + x); 
        drawWhitePoint(x0 - y, y0 - x);
        drawWhitePoint(x0 - x, y0 - y);
        drawWhitePoint(x0 + x, y0 + y);
        drawWhitePoint(x0 + y, y0 + x); 
        drawWhitePoint(x0 + y, y0 - x);
        drawWhitePoint(x0 + x, y0 - y);

        if (err <= 0)
        {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}

bool drawWhiteLine(int x1, int y1, int x2, int y2) {
	//Than kode lu gua benerin dikit di sini, harusnya ngk usah pake absolut
    bool ret = false;

    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    int ix = deltaX > 0 ? 1 : -1;
    int iy = deltaY > 0 ? 1 : -1;
    deltaX = abs(deltaX);
    deltaY = abs(deltaY);

    int x = x1;
    int y = y1;

    drawWhitePoint(x,y);

    if (deltaX >= deltaY) {
        int error = 2 * deltaY - deltaX;

        while (x != x2) {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= deltaX;
                y += iy;
            }
 
            error += deltaY;
            x += ix;
 
            
            if (redPixelMatrix[x][y] == 255 && greenPixelMatrix[x][y] == 255 && bluePixelMatrix[x][y] == 255) {
                ret = true;
            }
            drawWhitePoint(x, y);
        }
    } else {
        int error = 2 * deltaX - deltaY;

        while (y != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= deltaY;
                x += ix;
            }
 
            error += deltaX;
            y += iy;
 
            
            if (redPixelMatrix[x][y] == 255 && greenPixelMatrix[x][y] == 255 && bluePixelMatrix[x][y] == 255) {
                ret = true;
            }
            drawWhitePoint(x, y);
        }
    }
    return ret;
}


void drawBlackLine(int x1, int y1, int x2, int y2) {
    //Than kode lu gua benerin dikit di sini, harusnya ngk usah pake absolut
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    int ix = deltaX > 0 ? 1 : -1;
    int iy = deltaY > 0 ? 1 : -1;
    deltaX = abs(deltaX);
    deltaY = abs(deltaY);

    int x = x1;
    int y = y1;

    drawBlackPoint(x,y);

    if (deltaX >= deltaY) {
        int error = 2 * deltaY - deltaX;

        while (x != x2) {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= deltaX;
                y += iy;
            }
 
            error += deltaY;
            x += ix;
 
            drawBlackPoint(x, y);
        }
    } else {
        int error = 2 * deltaX - deltaY;

        while (y != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= deltaY;
                x += ix;
            }
 
            error += deltaX;
            y += iy;
 
            drawBlackPoint(x, y);
        }
    }
}


void drawRedLine(int x1, int y1, int x2, int y2) {
    //Than kode lu gua benerin dikit di sini, harusnya ngk usah pake absolut
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    int ix = deltaX > 0 ? 1 : -1;
    int iy = deltaY > 0 ? 1 : -1;
    deltaX = abs(deltaX);
    deltaY = abs(deltaY);

    int x = x1;
    int y = y1;

    drawRedPoint(x,y);

    if (deltaX >= deltaY) {
        int error = 2 * deltaY - deltaX;

        while (x != x2) {
            if ((error >= 0) && (error || (ix > 0)))
            {
                error -= deltaX;
                y += iy;
            }
 
            error += deltaY;
            x += ix;
 
            drawRedPoint(x, y);
        }
    } else {
        int error = 2 * deltaX - deltaY;

        while (y != y2)
        {
            if ((error >= 0) && (error || (iy > 0)))
            {
                error -= deltaY;
                x += ix;
            }
 
            error += deltaX;
            y += iy;
 
            drawRedPoint(x, y);
        }
    }
}

int detectKeyStroke() {
    //deteksi adanya keyboard yang ditekan.
    //0 jika tidak, >=1 jika iya
    static bool flag = false;
    static const int STDIN = 0;

    if (!flag) {
        //Memakai termios untuk mematikan line buffering
        struct termios T;

        tcgetattr(STDIN, &T);
        T.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &T);
        setbuf(stdin, NULL);
        flag = true;
    }

    int NByte;
    ioctl(STDIN, FIONREAD, &NByte);  // STDIN = 0
    
    return NByte;
}

void drawShooter(int xp, int yp, char mode) {
    //gambar tembakan dengan titik pusat lingkaran tembakan 
    //(yp,xp)
    switch (mode) {
        case'd':
        case 'D': {
            posX = xp+50;
            posY = yp-50;
            drawCircle(yp,xp,25);
            floodFill(yp, xp, 255, 255, 255, 255, 0, 0);
            drawWhiteLine(yp,xp+25,yp-25,xp+50);
            drawWhiteLine(yp-25,xp,yp-50,xp+25);
            drawWhiteLine(yp-25,xp+50,yp-50,xp+25);            
            floodFill(yp-30, xp+10, 255, 255, 255, 0, 0, 255);
            break;
        }
            
        case 's':
        case 'S': {
            posX = xp;
            posY = 500;
            drawCircle(yp,xp,25);
            floodFill(yp, xp, 255, 255, 255, 255, 0, 0);
            drawWhiteLine(yp-15,xp+20,yp-50,xp+20);
            drawWhiteLine(yp-15,xp-20,yp-50,xp-20);
            drawWhiteLine(yp-50,xp+20,yp-50,xp-20);
            floodFill(yp-30, xp+10, 255, 255, 255, 0, 0, 255);
            break;
        }
                    

        case 'a':
        case 'A': {
            posX = xp-50;
            posY = yp-50;
            drawCircle(yp,xp,25);
            floodFill(yp, xp, 255, 255, 255, 255, 0, 0);
            drawWhiteLine(yp,xp-25,yp-25,xp-50);
            drawWhiteLine(yp-25,xp,yp-50,xp-25);
            drawWhiteLine(yp-25,xp-50,yp-50,xp-25);
            floodFill(yp-25, xp-40, 255, 255, 255, 0, 0, 255);
            break;
        } 
        default: {}
    }
}

void DrawToScreen(){
    /* prosedure yang menggambar ke layar dari matriks RGB (harusnya rata tengah)*/
    long int location = 0;
    int x , y;
    for (y = vinfo.yres/2 - WIDTH/2; y < WIDTH + vinfo.yres/2 - WIDTH/2; y++)
        for (x = vinfo.xres/2 - HEIGHT/2; x < HEIGHT + vinfo.xres/2 - HEIGHT/2; x++) {
            location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) + (y+vinfo.yoffset) * finfo.line_length;
            if (vinfo.bits_per_pixel == 32) { 
                //4byte
                    *(fbp + location) = bluePixelMatrix[y - vinfo.yres/2 + WIDTH/2][x - vinfo.xres/2 + HEIGHT/2];        // Some blue
                    *(fbp + location + 1) = greenPixelMatrix[y - vinfo.yres/2 + WIDTH/2][x - vinfo.xres/2 + HEIGHT/2];     // A little green
                    *(fbp + location + 2) = redPixelMatrix[y - vinfo.yres/2 + WIDTH/2][x - vinfo.xres/2 + HEIGHT/2];    // A lot of red
                    *(fbp + location + 3) = 0;      // No transparency
            //location += 4;
            } else  { //assume 16bpp
                int b = 0;
                int g = 100;     // A little green
                int r = 0;    // A lot of red
                unsigned short int t = r<<11 | g << 5 | b;
                *((unsigned short int*)(fbp + location)) = t;
            }
        }
}

void drawExplosion(int x,int y){
    //x = 70
    // bentuk bintang ada 8 garis sesuai dengan parameter titik pusat (x,y)
    int pointx1 = x-20, pointy1 =y+20;
    int pointx3 = x+20, pointy3 =y+20;
    int pointx5 = x+20, pointy5 =y-20;
    int pointx7 = x-20, pointy7 =y-20;

    int pointx2 = x, pointy2 = y+10;
    int pointx4 = x+10, pointy4 = y;
    int pointx6 = x, pointy6 = y-10;
    int pointx8 = x-10, pointy8 = y;

    //gambar ledakan
    drawRedLine(pointx1,pointy1,pointx2,pointy2);
    drawRedLine(pointx2,pointy2,pointx3,pointy3);
    drawRedLine(pointx3,pointy3,pointx4,pointy4);
    drawRedLine(pointx4,pointy4,pointx5,pointy5);
    drawRedLine(pointx5,pointy5,pointx6,pointy6);
    drawRedLine(pointx6,pointy6,pointx7,pointy7);
    drawRedLine(pointx7,pointy7,pointx8,pointy8);
    drawRedLine(pointx8,pointy8,pointx1,pointy1);
    
    //warnain 
    floodFill(x,y,255,0,0,255,255,0);
}


void drawExplosion2(int x,int y){
    //x = 70
    // bentuk bintang ada 8 garis sesuai dengan parameter titik pusat (x,y)
    int pointx1 = x-20, pointy1 =y+20;
    int pointx3 = x+30, pointy3 =y+30;
    int pointx5 = x+20, pointy5 =y-20;
    int pointx7 = x-30, pointy7 =y-30;

    int pointx2 = x, pointy2 = y+15;
    int pointx4 = x+10, pointy4 = y;
    int pointx6 = x, pointy6 = y-10;
    int pointx8 = x-15, pointy8 = y;

    //gambar ledakan
    drawRedLine(pointx1,pointy1,pointx2,pointy2);
    drawRedLine(pointx2,pointy2,pointx3,pointy3);
    drawRedLine(pointx3,pointy3,pointx4,pointy4);
    drawRedLine(pointx4,pointy4,pointx5,pointy5);
    drawRedLine(pointx5,pointy5,pointx6,pointy6);
    drawRedLine(pointx6,pointy6,pointx7,pointy7);
    drawRedLine(pointx7,pointy7,pointx8,pointy8);
    drawRedLine(pointx8,pointy8,pointx1,pointy1);
    
    //warnain 
    floodFill(x,y,255,0,0,255,0,0);
}

void drawUFO(int x1, int y1) {
	int a, b, c, d;
	int centerX, centerY;
	centerX = x1-3; centerY = y1-25;
	a = x1+20; b = y1+20;
	//cout << "SEGFAULTR1" << endl;
	//rotateUFO(centerX, centerY, &a, &b);
	//cout << "SEGFAULTDRAWL1" << endl;
	drawWhiteLine(x1, y1, a, b);
    a = x1; b = y1-50;
    //cout << "SEGFAULTR2" << endl;
    //rotateUFO(centerX, centerY, &a, &b);
	//cout << "SEGFAULTDRAWL2" << endl;
	drawWhiteLine(x1, y1, a, b);
	c = x1+20; d = y1-70; //(a,b) = rotate(centerX, centerY, x1, y1-50)
    //cout << "SEGFAULTR3" << endl;
    //rotateUFO(centerX, centerY, &c, &d);
	//cout << "SEGFAULTDRAWL3" << endl;
	drawWhiteLine(a, b, c, d);
    a = x1+20; b = y1+20; //(c,d) = rotate(centerX, centerY, x1+20, y1-70)
    //cout << "SEGFAULTR4" << endl;
    //rotateUFO(centerX, centerY, &a, &b);
    //cout << "SEGFAULTDRAWL4" << endl;
    drawWhiteLine(c, d, a, b);
    a = x1+5; b = y1;
    //cout << "SEGFAULTR5" << endl;
    //rotateUFO(centerX, centerY, &a, &b);
    //cout << "SEGFAULTFLOODFILL" << endl;
    floodFill(a, b, 255, 255, 255, 0, 255, 0);
    
    a = x1; b = y1-25;
    //cout << "SEGFAULTR6" << endl;
    //rotateUFO(centerX, centerY, &a, &b);
    //cout << "SEGFAULTDRAWSC" << endl;
    drawSemiCircle(a, b, 25);    
}

/* Rotating using xp and yp as its center
 * and angle in radian */
void rotate(int xp, int yp, int *x1, int *y1, int angle){
	int x = (*x1) - xp; int y = (*y1) - yp;
	*x1 = cos(angle)*(x) - sin(angle)*(y);
	*y1 = sin(angle)*(x) + cos(angle)*(y);
	*x1 += xp; *y1 += yp;
}

void drawPropeller(int xp, int yp, int angle){
	int radCircle = 20;
	drawCircle(xp, yp, radCircle);
	floodFill(xp, yp, 255, 255, 255, 0, 0, 255);
	int xPointA = xp - radCircle; int yPointA = yp;
	int xPointB = xp; int yPointB = yp + radCircle;
	int xPointC = xp + radCircle; int yPointC = yp;
	int xPointD = xp; int yPointD = yp - radCircle;
	int xPropOne1 = xp - 40; int yPropOne1 = yp + 30;
	int xPropOne2 = xp - 30; int yPropOne2 = yp + 40;
	int xPropTwo1 = xp + 30; int yPropTwo1 = yp + 40;
	int xPropTwo2 = xp + 40; int yPropTwo2 = yp + 30;
	int xPropThree1 = xp + 40; int yPropThree1 = yp - 30;
	int xPropThree2 = xp + 30; int yPropThree2 = yp - 40;
	int xPropFour1 = xp - 30; int yPropFour1 = yp - 40;
	int xPropFour2 = xp - 40; int yPropFour2 = yp - 30;	
	double angleinRad = angle * 3.14159265 / 180;
	rotate(xp, yp, &xPointA, &yPointA, angleinRad);
	rotate(xp, yp, &xPointB, &yPointB, angleinRad);
	rotate(xp, yp, &xPointC, &yPointC, angleinRad);
	rotate(xp, yp, &xPointD, &yPointD, angleinRad);
	rotate(xp, yp, &xPropOne1, &yPropOne1, angleinRad);
	rotate(xp, yp, &xPropOne2, &yPropOne2, angleinRad);
	rotate(xp, yp, &xPropTwo1, &yPropTwo1, angleinRad);
	rotate(xp, yp, &xPropTwo2, &yPropTwo2, angleinRad);
	rotate(xp, yp, &xPropThree1, &yPropThree1, angleinRad);
	rotate(xp, yp, &xPropThree2, &yPropThree2, angleinRad);
	rotate(xp, yp, &xPropFour1, &yPropFour1, angleinRad);
	rotate(xp, yp, &xPropFour2, &yPropFour2, angleinRad);
	//Propeller1
	drawWhiteLine(xPointA, yPointA, xPropOne1, yPropOne1);
	drawWhiteLine(xPropOne1, yPropOne1, xPropOne2, yPropOne2);
	drawWhiteLine(xPointB, yPointB, xPropOne2, yPropOne2);
	int xFirepoint1 = (int) (xPropOne1 + xPointB)/2;
	int yFirepoint1 = (int) (yPropOne1 + yPointB)/2;
	floodFill(xFirepoint1, yFirepoint1, 255, 255, 255, 255, 255, 0);
	//Propeller2
	drawWhiteLine(xPointB, yPointB, xPropTwo1, yPropTwo1);
	drawWhiteLine(xPropTwo1, yPropTwo1, xPropTwo2, yPropTwo2);
	drawWhiteLine(xPointC, yPointC, xPropTwo2, yPropTwo2);
	int xFirepoint2 = (int) (xPropTwo1 + xPointC)/2;
	int yFirepoint2 = (int) (yPropTwo1 + yPointC)/2;
	floodFill(xFirepoint2, yFirepoint2, 255, 255, 255, 255, 255, 0);
	//Propeller3
	drawWhiteLine(xPointC, yPointC, xPropThree1, yPropThree1);
	drawWhiteLine(xPropThree1, yPropThree1, xPropThree2, yPropThree2);
	drawWhiteLine(xPointD, yPointD, xPropThree2, yPropThree2);
	int xFirepoint3 = (int) (xPropThree1 + xPointD)/2;
	int yFirepoint3 = (int) (yPropThree1 + yPointD)/2;
	floodFill(xFirepoint3, yFirepoint3, 255, 255, 255, 255, 255, 0);
	//Propeller4
	drawWhiteLine(xPointD, yPointD, xPropFour1, yPropFour1);
	drawWhiteLine(xPropFour1, yPropFour1, xPropFour2, yPropFour2);
	drawWhiteLine(xPointA, yPointA, xPropFour2, yPropFour2);
	int xFirepoint4 = (int) (xPropFour1 + xPointA)/2;
	int yFirepoint4 = (int) (yPropFour1 + yPointA)/2;
	floodFill(xFirepoint4, yFirepoint4, 255, 255, 255, 255, 255, 0);
}

void drawStars() {
    drawExplosion(400, 100);
    drawExplosion(300, 200);
    drawExplosion(500, 200);
    drawExplosion(400, 300);
    drawExplosion(300, 400);
    drawExplosion(500, 400);
    drawExplosion(400, 500);
    drawExplosion(400, 700);
    drawExplosion(300, 800);
    drawExplosion(500, 800);
    drawExplosion(400, 900);
    drawExplosion(300, 1000);
    drawExplosion(500, 1000);
    drawExplosion(400, 1100);
}

void drawFrame() {
    drawWhiteLine(0, 0, 0, 1200);
    drawWhiteLine(0, 1200, 600, 1200);
    drawWhiteLine(600, 1200, 600, 0);
    drawWhiteLine(600, 0, 0, 0);
}

void addBullet(int x1, int y1, int x2, int y2 , int n)
//x1,y1 titik asal peluru
//x2,y2 titik sampai peluru
//n adalah pembagian tahap gerak peluru
{
    bullet newBullet;
    //persamaan garis
    newBullet.m = (y2-y1);
    newBullet.m /= (x2-x1);
    newBullet.c = y1 - newBullet.m * x1;

    newBullet.partisi = 0;
    for (int i=1;i<=n;i++) {
        newBullet.partisi += i;
    }

    newBullet.xStart = x1;
    newBullet.yStart = (int) floor(newBullet.m * newBullet.xStart + newBullet.c + 0.5);
    newBullet.xEnd = x1 + (x2-x1) * n / newBullet.partisi;
    newBullet.yEnd = (int) floor(newBullet.m * newBullet.xEnd + newBullet.c + 0.5);

    newBullet.x1 = x1;
    newBullet.x2 = x2;
    newBullet.iteration = n;
    newBullet.n = n;

    bullets.push_back(newBullet);
}

void drawKeyShooter(){
    while(!exploded){
        if(!detectKeyStroke()) {
                char KeyPressed = getchar();
                if ((KeyPressed=='A')||(KeyPressed=='a') ||(KeyPressed=='S') ||(KeyPressed=='s') ||(KeyPressed=='D') ||(KeyPressed=='d')) {
                    lastCorrectState = KeyPressed;
                } else if (KeyPressed==' ') {

                    if (lastCorrectState == 'a')
                        addBullet(posY,posX,0,0,20);
                    else if (lastCorrectState == 's')
                        addBullet(posY,posX,0,600,20);
                    else if (lastCorrectState == 'd')
                        addBullet(posY,posX,0,1200,20);
                
            }
        }
    }
        
}

void drawBullets() {
    //persamaan garis
    for (int i = bullets.size()-1; i >=0; --i)
    {
        if (bullets[i].iteration >0) {
            if (drawWhiteLine(bullets[i].xStart,bullets[i].yStart,bullets[i].xEnd,bullets[i].yEnd)) exploded = true;
            bullets[i].xStart = bullets[i].xEnd;
            bullets[i].yStart = bullets[i].yEnd;
            bullets[i].xEnd = bullets[i].xStart + (bullets[i].x2 - bullets[i].x1) * (bullets[i].iteration - 1) / bullets[i].partisi;
            bullets[i].yEnd = (int) floor(bullets[i].m * bullets[i].xEnd + bullets[i].c + 0.5);
            bullets[i].iteration--;
        }   
    }
}

int main() {
    clearMatrix();    
    
    int fbfd = 0;
    long int screensize = 0;
    exploded = false;
    
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }
    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    // mendapat screensize layar monitor
    screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, (off_t)0);

    //display merge center
    // Menulis ke layar tengah file
    //Gambar trapesium
    thread thread1(&drawKeyShooter);
    int xp = 600;
    int yp = 574;
    char KeyPressed;

    int xawal = 100, yawal = 574;
    bool left = true;
    
    do {
        clearMatrix();
        drawFrame();
        
        drawShooter(xp,yp,lastCorrectState);
        drawStars();

        // draw UFO
        drawUFO(xawal, yawal);
        if(yawal-170<=0) {
            left = false;
        } else if(yawal+200>=1200) {
            left = true;
        }
        if (left) {
            yawal -= 10;
        } else {
            yawal += 10;     
        }
        int deltaY = yawal - yp;
        xawal = 600 - sqrt(250000 - pow(deltaY, 2));
        
        // draw bullet
        drawBullets(); 

        DrawToScreen(); 
        usleep(50000);
    } while (KeyPressed!='C' && !exploded);
    thread1.detach();
	
	int xawal1 = xawal;
	int xawal2 = xawal;
	int yawal1 = yawal;
	int yawal2 = yawal;
	int yawal3 = yawal;
	int yawal4 = yawal;
	int angle = 0;
	while (xawal < 570) {
		clearMatrix();
		drawFrame();
		drawShooter(xp,yp,lastCorrectState);
		drawStars();
		/*
		drawExplosion2(xawal,yawal);
		drawExplosion2(xawal1,yawal1);
		drawExplosion2(xawal2,yawal2);
		drawExplosion2(xawal2,yawal3);
		drawExplosion2(xawal2,yawal4);
		*/
		//drawPropeller(xawal, yawal2, angle);
		//angle+= 15;


		DrawToScreen();
		xawal++; xawal1++; xawal2++;
		if (xawal % 2 == 0) { 		
			yawal1++;
			yawal2--;
			yawal3 += 2;
			yawal4 -= 2;
		}
		usleep(1);
	}
    
    munmap(fbp, screensize);
    close(fbfd);
    
    return 0;
}
