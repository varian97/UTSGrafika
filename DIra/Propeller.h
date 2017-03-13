//Propeller.h
//dibuat oleh kelompok 2
//kelas untuk baling-baling pesawat. Baling2 hanya berupa garis saat pesawat berjalan
//baling2 berubah menjadi lingkarang yang berputar saat pesawat ditembak

/* Gambaran baling2 pesawat sederhana
 * 			 a
 * 		  f /\ b  30
 * 		    ||
 * 			||
 * 		  center
 * 			||
 * 		  e || c
 * 			\/	  30
 * 			d	*/
 
 /* gambar setelah meledak dalam bentuk kipas */
 

#ifndef PROPELLER_H
#define PROPELLER_H
#include <math.h>
#include "LinePes.h"
using namespace std;

class Propeller : public LinePes {
	private:
		int xt; //titik pusat (x) baling-baling (awal)
		int yt; //titik pusat (y) baling-baling (awal)
		int xa, ya, xb, yb, xc, yc, xd, yd, xe, ye, xf, yf;
		int h, w;
		
		//variable setelah ledakan
		double xg, yg, xh, yh, xi, yi, xj, yj, xk, yk, xl, yl, xm, ym, xn, yn;
		double xtemp, ytemp;
		
		int delta; // beda tinggi garis lurus dengan garis miring
		
		int xt_; //current
		int yt_; //current
		
		LinePes l;	


		
	public:
		/* prosedur untuk inisialisasi baling-baling pesawat
		 * dipanggil di awal penggunaan 
		 * h0 adalah panjang dari baling-baling, 
		 * w0 adalah lebar dari baling-baling,  */
		void init (int xt0, int yt0) {
			xt = xt0;
			yt = yt0;
			
			h = 80;
			w = 16;
			
			xa = xt; 
			xb = xt + w/2;
			xc = xb;
			xd = xa;
			xe = xd - w/2;
			xf = xe;

			ya = yt - h/2;
			yb = yt - h/2 + 5;
			yc = yt + h/2 - 5;
			yd = yt + h/2; 
			ye = yc;
			yf = yb;
		}
		
		/* prosedur untuk membuat baling-baling dalam posisi normal (sebelum pesawat tertembak) */
		void create (int r, int g, int b) {


		// ada yg ditambah 1 karena bochor bochor 
		l.insertLinePes(xa, ya, xb, yb, r, g, b);
		l.insertLinePes(xb, yb, xc, yc+1, r, g, b);
		l.insertLinePes(xc+1, yc-1, xd, yd, r, g, b);
		l.insertLinePes(xd, yd, xe, ye, r, g, b);
		l.insertLinePes(xe, ye, xf, yf, r, g, b);
		l.insertLinePes(xf, yf, xa, ya, r, g, b);
			
			 
		}
		
		/*
		 *  prosedur untuk menggerakkan baling-baling pesawat mengikuti pergerakan pesawat 
		 * s stand for speed 
		 */
		void move_forward (int s, int ymasuk) {
			xa -= s;
			xb -= s;
			xc -= s;
			xd -= s;
			xe -= s;
			xf -= s;
			xt -= s;
			if (ymasuk==0) {
				ya++;
				yb++;
				yc++;
				yd++;
				ye++;
				yf++;	
			} else {
				ya--;
				yb--;
				yc--;
				yd--;
				ye--;
				yf--;	
			}
			create(0,255,0);			
		}
		
		
		/* clear baling-baling saat berjalan (kondisi normal sebelum kena bom)
		 * bad practice code here */
		void clear_normal() {
			int leftmost_x = xf;
			int rightmost_x = xb;
			int upper_y	= ya;
			int lower_y	= yd;
			
			for (int i = leftmost_x; i <= rightmost_x; i++) {
				for (int j = upper_y; j < lower_y; j++) {
					putPixelPes(i,j,0,0,0);
				}
			}	
		}
		
		/* prosedur untuk membuat baling - baling setelah meledak */
		void create_boom (int r, int g, int b) {
			int delta = 50;
			
			xg = xt;
			yg = yt - h/2;
			xh = xt + h/2;
			yh = yt - h/2;
			xi = xt + h/2;
			yi = yt;
			xj = xt + h/2;
			yj = yt + h/2;
			xk = xt;
			yk = yt + h/2;
			xl = xt - h/2;
			yl = yt + h/2;
			xm = xt - h/2;
			ym = yt;
			xn = xt - h/2;
			yn = yt - h/2;
			
			l.insertLinePes(xt, yt, xg, yg, r, g, b);
			l.insertLinePes(xt, yt, xh, yh, r, g, b);
			l.insertLinePes(xt, yt, xi, yi, r, g, b);
			l.insertLinePes(xt, yt, xj, yj, r, g, b);
			l.insertLinePes(xt, yt, xk, yk, r, g, b);
			l.insertLinePes(xt, yt, xl, yl, r, g, b);
			l.insertLinePes(xt, yt, xm, ym, r, g, b);
			l.insertLinePes(xt, yt, xn, yn, r, g, b);
			l.insertLinePes(xg, yg, xh, yh, r, g, b);
			l.insertLinePes(xi, yi, xj, yj, r, g, b);
			l.insertLinePes(xk, yk, xl, yl, r, g, b);
			l.insertLinePes(xm, ym, xn, yn, r, g, b);
		}
		
		/*
		 * clear baling-baling saat setelah terkena bom
		 * */
		void clear_boom() {
			int delta = 100;
			int leftmost_x = xt-90;
			int rightmost_x = xt+90;
			int upper_y	= yt-90;
			int lower_y	= yt+90;
			
			for (int i = leftmost_x; i <= rightmost_x; i++) {
				for (int j = upper_y; j < lower_y; j++) {
					putPixelPes(i,j,0,0,0);
				}
			}	
		}

		/* rotate the propeller */
		void rotate (int r, int g, int b, int deg) {

			xtemp = xt;
			ytemp = yt;
			rotatePoint(&xtemp, &ytemp, deg, xtemp, ytemp);
			rotatePoint(&xg, &yg, deg, xtemp, ytemp);
			rotatePoint(&xh, &yh, deg, xtemp, ytemp);
			rotatePoint(&xi, &yi, deg, xtemp, ytemp);
			rotatePoint(&xj, &yj, deg, xtemp, ytemp);
			rotatePoint(&xk, &yk, deg, xtemp, ytemp);
			rotatePoint(&xl, &yl, deg, xtemp, ytemp);
			rotatePoint(&xm, &ym, deg, xtemp, ytemp);
			rotatePoint(&xn, &yn, deg, xtemp, ytemp);

			xt = (int) xtemp;
			yt = (int) ytemp;		
			
			l.insertLinePes(xt, yt, xg, yg, r, g, b);
			l.insertLinePes(xt, yt, xh, yh, r, g, b);
			l.insertLinePes(xt, yt, xi, yi, r, g, b);
			l.insertLinePes(xt, yt, xj, yj, r, g, b);
			l.insertLinePes(xt, yt, xk, yk, r, g, b);
			l.insertLinePes(xt, yt, xl, yl, r, g, b);
			l.insertLinePes(xt, yt, xm, ym, r, g, b);
			l.insertLinePes(xt, yt, xn, yn, r, g, b);
			l.insertLinePes(xg, yg, xh, yh, r, g, b);
			l.insertLinePes(xi, yi, xj, yj, r, g, b);
			l.insertLinePes(xk, yk, xl, yl, r, g, b);
			l.insertLinePes(xm, ym, xn, yn, r, g, b);

			 yt += 10;
			 xt -= 10;

		}
		
		int getXT() {return xt;}
		int getYT() {return yt;}
		int getH() {return h;}
		int getW() {return w;}
		int getD() {return delta;}
		int getXFront() {return xe;}
		int getXBack() {return xc;}
		int getYMin() {return ya;}
		int getYMax() {return yd;}
		
		double toRadian(double deg) {
			return (deg / 180) * ((double) M_PI);
		}	

		/* to rotate a point */
		void rotatePoint(double *x, double *y, double deg, double offx, double offy){
			double rad = toRadian(deg);
			double x1 = *x - offx;
			double y1 = *y - offy;
			*x = (x1 * cos(rad)) - (y1 * sin(rad));
			*y = (x1 * sin(rad)) + (y1 * cos(rad));
			*x = *x + offx;
			*y = *y + offy;
			//cout << *x << " " << *y << " " << deg << "\n";
		}
};

#endif
