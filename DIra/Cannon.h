#include "LinePes.h"
using namespace std;

/* This code is bad, everythings hardcoded */

class Cannon : public LinePes {

private:
	LinePes l;
	int a, b, c, d, e,f,g,h,i,j,k,m;
	bool isStopped;

public:
	void init() {
		a = 750;
		b = 800;
		c = 1000;
		d = 1050;
		e = 800;
		f = 800;
		g = 1000;
		h = 1000;
		i = 880;
		j = 880;
		k = 920;
		m = 920;

		/* deck kapal */
		l.insertLinePes(a,650-300,b,700-300,0,0,255); 
		l.insertLinePes(b,700-300,c,700-300,0,0,255); 
		l.insertLinePes(a,650-300,d,650-300,0,0,255); 
		l.insertLinePes(c,700-300,d,650-300,0,0,255);

		/* dock kapal */
		l.insertLinePes(e,650-300,f,600-300,0,0,255);
		l.insertLinePes(f,600-300,g,600-300,0,0,255);
		l.insertLinePes(g,600-300,h,650-300,0,0,255);

		/* meriam */
		l.insertLinePes(i,600-300,j,550-300,0,255,0);
		l.insertLinePes(j,550-300,k,550-300,0,255,0);
		l.insertLinePes(k,550-300,m,600-300,0,255,0);
		isStopped = false;
	}

	int getInitBulletLocation() {
		return ( j + k )/2;
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

		
	
	bool getStopped() {
		return isStopped;
	}

	void setCannonToStop() {
		isStopped = true;
	}

	void move () {
		bool stopped = false;
		int delta = -20;
		while(!stopped){
			
			a = 750;
			b = 800;
			c = 1000;
			d = 1050;
			e = 800;
			f = 800;
			g = 1000;
			h = 1000;
			i = 880;
			j = 880;
			k = 920;
			m = 920;

			clean(a,d,550-300,700-300);
			/* deck kapal */
			l.insertLinePes(a,650-300,b,700-300,0,0,255); 
			l.insertLinePes(b,700-300,c,700-300,0,0,255); 
			l.insertLinePes(a,650-300,d,650-300,0,0,255); 
			l.insertLinePes(c,700-300,d,650-300,0,0,255);

			/* dock kapal */
			l.insertLinePes(e,650-300,f,600-300,0,0,255);
			l.insertLinePes(f,600-300,g,600-300,0,0,255);
			l.insertLinePes(g,600-300,h,650-300,0,0,255);
			l.insertLinePes(e,650-300,h,650-300,0,0,255);
			/* meriam */
			l.insertLinePes(i,600-300,j,550-300,0,255,0);
			l.insertLinePes(j,550-300,k,550-300,0,255,0);
			l.insertLinePes(k,550-300,m,600-300,0,255,0);		
			l.floodFillPes(f+20,620-300,0,0,255,0);
			l.floodFillPes(a+20,652-300,0,0,255,0);

			while(a > 0){
				/* deck kapal */
				/*
				l.insertLinePes(a,650,b,700,0,0,0); 
				l.insertLinePes(b,700,c,700,0,0,0); 
				l.insertLinePes(a,650,d,650,0,0,0); 
				l.insertLinePes(c,700,d,650,0,0,0);
				*/

				/* dock kapal */
				/*
				l.insertLinePes(e,650,f,600,0,0,0);
				l.insertLinePes(f,600,g,600,0,0,0);
				l.insertLinePes(g,600,h,650,0,0,0);
				*/

				/* meriam */
				/*
				l.insertLinePes(i,600,j,550,0,0,0);
				l.insertLinePes(j,550,k,550,0,0,0);
				l.insertLinePes(k,550,m,600,0,0,0);
				*/
				clean(a,d,550-300,700-300);

				a += delta;
				b += delta;
				c += delta;
				d += delta;
				e += delta;	
				f += delta;
				g += delta;
				h += delta;
				i += delta;
				j += delta;
				k += delta;
				m += delta;

				/* deck kapal */
				l.insertLinePes(a,650-300,b,700-300,0,0,255); 
				l.insertLinePes(b,700-300,c,700-300,0,0,255); 
				l.insertLinePes(a,650-300,d,650-300,0,0,255); 
				l.insertLinePes(c,700-300,d,650-300,0,0,255);

				/* dock kapal */
				l.insertLinePes(e,650-300,f,600-300,0,0,255);
				l.insertLinePes(f,600-300,g,600-300,0,0,255);
				l.insertLinePes(g,600-300,h,650-300,0,0,255);

				/* meriam */
				l.insertLinePes(i,600-300,j,550-300,0,255,0);
				l.insertLinePes(j,550-300,k,550-300,0,255,0);
				l.insertLinePes(k,550-300,m,600-300,0,255,0);		
				l.floodFillPes(f+20,620-300,0,0,255,0);
				l.floodFillPes(a+20,652-300,0,0,255,0);
				l.floodFillPes(i+5,570-300,0,250,0,0);

				usleep(40000);
			}
			/* deck kapal */
			/*
			l.insertLinePes(a,650,b,700,0,0,0); 
			l.insertLinePes(b,700,c,700,0,0,0); 
			l.insertLinePes(a,650,d,650,0,0,0); 
			l.insertLinePes(c,700,d,650,0,0,0);
			*/

			/* dock kapal */
			/*
			l.insertLinePes(e,650,f,600,0,0,0);
			l.insertLinePes(f,600,g,600,0,0,0);
			l.insertLinePes(g,600,h,650,0,0,0);
			*/

			/* meriam */
			/*
			l.insertLinePes(i,600,j,550,0,0,0);
			l.insertLinePes(j,550,k,550,0,0,0);
			l.insertLinePes(k,550,m,600,0,0,0);
			*/
			stopped = getStopped();
			if(!stopped) {
				clean(a,d,550-300,700-300);
			}
		}
		clean(a,d,550-300,700-300);

	}
};
