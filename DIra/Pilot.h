
#ifndef PILOT_H
#define PILOT_H
#include "LinePes.h"


class Pilot: public LinePes {
	private:
		framebufferPes fb;
		LinePes l;
	public:
		void circlePilot(int ra, int xc, int yc, int full, int r, int g, int b){
/* r = jari-jari; xc = koordinar X pusat lingkaran;
 * yc= koordinat Y pusat lingkaran;
 * full = 1: lingkaran penuh, 0: setengah lingkaran bgn atas;
 * color= warna garis lingkaran
 * Prosedur untuk ngegambar lingkaran Bresenham*/
 
	int xn=0, yn=ra;
	int p = 3-2*ra; 
	
	fb.putPixelPes(xc+ra,yc+0.5*ra,r,g,b);
	fb.putPixelPes(xc-ra,yc+0.5*ra,r,g,b);
	fb.putPixelPes(xc,yc-0.5*ra,r,g,b);
	
	if (full==1) fb.putPixelPes(xc,yc+1.5*ra,r,g,b);

	while (xn<=yn){
		xn++;
		if (p>=0){
			yn--;
			p+=4*(xn-yn)+10;
		}else{
			p+=4*(xn)+6;
		}
		int x3=xn;
		int y3=yn*(-1)+0.5*ra;
				
		//Sisi kanan atas
		fb.putPixelPes(x3+xc,y3+yc,r,g,b);
		fb.putPixelPes(-1*y3+xc+0.5*ra,-1*x3+yc+0.5*ra,r,g,b);
		
		//Sisi kiri atas
		fb.putPixelPes(x3*(-1)+xc,y3+yc,r,g,b);
		fb.putPixelPes(y3+xc-0.5*ra,-1*x3+yc+0.5*ra,r,g,b);
		
		if (full==1){
			//sisi kanan bawah
			fb.putPixelPes(xn+xc,yn+yc+0.5*ra,r,g,b);
			fb.putPixelPes(yn+xc,xn+yc+0.5*ra,r,g,b);
		
			//sisi kiri bawah
			fb.putPixelPes(-1*x3+xc,-1*y3+yc+ra,r,g,b);
			fb.putPixelPes(y3+xc-0.5*ra,x3+yc+0.5*ra,r,g,b);
		}
	}
}

void poseAwal(int xc, int yc, int r, int g, int b){
	circlePilot(10,xc,yc,1,r,g,b);//kepala
	l.floodFillPes(xc,yc,r,g,b,0);

	l.insertLinePes(xc,yc+15,xc+20,yc+50,r,g,b);//badan
	l.insertLinePes(xc+10,yc+30,xc+20,yc+25,r,g,b);//kaki kanan atas
	l.insertLinePes(xc+20,yc+25,xc+18,yc+40,r,g,b);//kaki kanan bawah
	l.insertLinePes(xc+3,yc+20,xc-20,yc+10,r,g,b);//tangan kiri
	l.insertLinePes(xc+3,yc+20,xc+20,yc+10,r,g,b);//tangan kanan	
}

void poseParasut1(int xc, int yc, int r, int g, int b){
	circlePilot(30,xc,yc-40,0,r,g,b);//parasut
	l.insertLinePes(xc-30,yc-25,xc+30,yc-25,r,g,b);//parasut bawah
	l.insertLinePes(xc-30,yc-25,xc,yc+24,r,g,b);//tali kiri parasut
	l.insertLinePes(xc+30,yc-25,xc+6,yc+24,r,g,b);
	circlePilot(10,xc,yc,1,r,g,b);//kepala
	l.insertLinePes(xc,yc+15,xc+20,yc+50,r,g,b);//badan
	l.insertLinePes(xc+10,yc+30,xc+30,yc+37,r,g,b);//kaki kanan atas
	l.insertLinePes(xc+3,yc+20,xc-5,yc+32,r,g,b);//tangan kiri
	l.insertLinePes(xc+3,yc+20,xc+20,yc+25,r,g,b);//tangan kanan
	l.floodFillPes(xc,yc-40,r,g,b,0);
	l.floodFillPes(xc,yc,r,g,b,0);
}

void poseParasut2(int xc, int yc, int r, int g, int b){
	circlePilot(30,xc,yc-40,0,r,g,b);//parasut
	l.insertLinePes(xc-30,yc-25,xc+30,yc-25,r,g,b);//parasut bawah
	l.insertLinePes(xc-30,yc-25,xc-3,yc+24,r,g,b);//tali kiri parasut
	l.insertLinePes(xc+30,yc-25,xc+3,yc+24,r,g,b);
	circlePilot(10,xc,yc,1,r,g,b);//kepala
	l.insertLinePes(xc,yc+15,xc-15,yc+50,r,g,b);//badan
	l.insertLinePes(xc-5,yc+30,xc-25,yc+37,r,g,b);//kaki kiri atas
	l.insertLinePes(xc-2,yc+20,xc-17,yc+27,r,g,b);//tangan kiri
	l.insertLinePes(xc-2,yc+20,xc+10,yc+30,r,g,b);//tangan kanan*/
	l.floodFillPes(xc,yc-40,r,g,b,0);
	l.floodFillPes(xc,yc,r,g,b,0);
}

void clean(int mostleft, int mostright, int ymin, int ymax) {
		int y;
		int x;
		for (x = mostleft; x <= mostright; x++) {
			for (y = ymin; y <= ymax; y++) {
				putPixelPes(x,y,0,0,0);
			}
		}
	}

void terjunPilot(int xc, int yc){
	int kiri = 0;
int i;
//poseAwal(xc,yc,0,255,0);
	//	usleep(10000);
		//poseAwal(xc,yc,0,0,0);
	for (i=0;i<50;i++){
		poseAwal(xc,yc,0,255,0);
		usleep(10000);
		clean(xc-20, xc+30, yc-5, yc+50);
		//poseAwal(xc,yc,0,0,0);
		yc++;xc++;
	}
	i=1000;
	while (xc<i){
		if (!kiri) {
			poseParasut2(xc,yc,0,255,0);
			
			usleep(90000);
			
			clean(xc-30, xc+30, yc-60, yc+50);
			if (yc%10==0) kiri =1;
		}else{
			poseParasut1(xc,yc,0,255,0);
			usleep(90000);
			clean(xc-30, xc+30, yc-60, yc+50);
			
			if (yc%10==0) kiri=0;
		}
		if (yc%3==0) xc++;
		yc++;
	}
	}
};
#endif
