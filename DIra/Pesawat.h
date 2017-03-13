#include "LinePes.h"
#include "Tire.h"
#include "Rotate.cpp"
#include "Pilot.h"
#include "Propeller.h"
using namespace std;

// Resolution = 1366x768

void movePilot(int xLedak) {
	Pilot p;
	p.terjunPilot(xLedak,50);
}

class Pesawat : public LinePes {

/* This code is bad, everythings hardcoded */

/* LEGEND

	wing: 	   
   f_____ i
	\	 \
	 \____\
	 g 		h

	body
		   b  c___ d
	  a ______/  /
	   /________/ 
	  xFront 	 e

*/
private:
	LinePes l;
	double xFront = 900;
	bool isDestroy = false;
	double a,b,c,d,e,f,g,h,i;
	Tire tire;					// tire, located in plane's back
	Propeller prop;		//baling-baling terletak di ujung depan pesawat

public:
	void init() {
		/* hardcode */
		a = 950; b = 1200; c = 1300; d = 1200;
		e = 1100; f = 1000; g = 1100; h = 1200; i = 1100;

		/* body */
		l.insertLinePes(xFront,200-100,a,150-100,0,255,0);
		l.insertLinePes(xFront,200-100,b,200-100,0,255,0);
		l.insertLinePes(b,200-100,c,100-100,0,255,0);
		l.insertLinePes(c,100-100,d,100-100,0,255,0);
		l.insertLinePes(d,100-100,e,150-100,0,255,0);
		l.insertLinePes(a,150-100,e,150-100,0,255,0);

		/*sayap*/
		l.insertLinePes(f,175-100,g,250-100,0,255,0);
		l.insertLinePes(g,250-100,h,250-100,0,255,0);
		l.insertLinePes(h,250-100,i,175-100,0,255,0);
		
		/* Initialize tire */
		int x0_tire = b - 20;
		int y0_tire = 200-100;
		int radius_tire = 20;
		int speed_tire = -20;
		int falling_speed_tire = 20;
		int bouncing_y_tire = 450;
		tire.init(x0_tire, y0_tire, radius_tire, 
			speed_tire, falling_speed_tire, bouncing_y_tire);
			
		/* inisialisasi baling-baling */
		// int x = xFront - 800;
		// int y = 500; //sesuai dengan yFront (yFront tidak tertulis)
		// int h = 75;
		// int w = 47;
		// int d = 15;
		prop.create(0,255,0);
		
	}

	int getXFront(){
		return xFront;
	}

	int getXBehind(){
		return c;
	}

	bool getIsDestroy() {
		return isDestroy;
	}

	void setDestroy(){
		isDestroy = true;
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
	
	void move() {
		clean(10,1300,100,250);
		int delta = -20;
		while(!isDestroy){
			a = 950; b = 1200; c = 1300; d = 1200;
			e = 1100; f = 1000; g = 1100; h = 1200; i = 1100;

			/* body */
			l.insertLinePes(xFront,200-100,a,150-100,0,255,0);
			l.insertLinePes(xFront,200-100,b,200-100,0,255,0);
			l.insertLinePes(b,200-100,c,100-100,0,255,0);
			l.insertLinePes(c,100-100,d,100-100,0,255,0);
			l.insertLinePes(d,100-100,e,150-100,0,255,0);
			l.insertLinePes(a,150-100,e,150-100,0,255,0);

			/*sayap*/
			l.insertLinePes(f,175-100,g,250-100,0,255,0);
			l.insertLinePes(g,250-100,h,250-100,0,255,0);
			l.insertLinePes(h,250-100,i,175-100,0,255,0);

			/* baling-baling */
			prop.init(xFront, 200-103);
			prop.create(0, 255, 0);

			l.floodFillPes(f-21,165-100,0,250,0,0); //warna badan
			l.floodFillPes(g+21,235-100,0,250,0,0); //warna sayap
			l.floodFillPes(prop.getXT(), prop.getYMin()+20, 0, 250, 0, 0); //warna baling-baling

			int updown=0;
			int stat=0;
			while(xFront > 0){
				if (updown>10){
					stat=1;
				}
				if (updown<1){
					stat=0;
				}
				if (stat=0){
					updown++;
				} else {
					updown--;
				}
				/* body */
				clean(xFront,c,100-100,250-100-updown);

				clean(prop.getXFront(), prop.getXBack(), prop.getYMin(), prop.getYMax());

				xFront += delta;
				a += delta;
				b += delta;
				c += delta;
				d += delta;
				e += delta;	
				f += delta;
				g += delta;
				h += delta;
				i += delta;

				/* body */
				l.insertLinePes(xFront,200-100-updown,a,150-100-updown,0,255,0);
				l.insertLinePes(xFront,200-100-updown,b,200-100-updown,0,255,0);
				l.insertLinePes(b,200-100-updown,c,100-100-updown,0,255,0);
				l.insertLinePes(c,100-100-updown,d,100-100-updown,0,255,0);
				l.insertLinePes(d,100-100-updown,e,150-100-updown,0,255,0);
				l.insertLinePes(a,150-100-updown,e,150-100-updown,0,255,0);

				/*sayap*/
				l.insertLinePes(f,175-100-updown,g,250-100-updown,0,255,0);
				l.insertLinePes(g,250-100-updown,h,250-100-updown,0,255,0);
				l.insertLinePes(h,250-100-updown,i,175-100-updown,0,255,0);
				
				l.floodFillPes(f-21,165-100-updown,0,250,0,0); //warna badan
				l.floodFillPes(g+21,235-100-updown,0,250,0,0); //warna sayap

				/* move the tire forward */
				
				tire.move_forward(stat);
				
				/* move baling-baling */
				prop.move_forward(20,stat);
				l.floodFillPes(prop.getXT(), prop.getYMin()+20, 0, 250, 0, 0);

				if(isDestroy)
					break;

				usleep(100000);
				l.floodFillPes(f-21,165-100-updown,0,0,0,-6);
				l.floodFillPes(g+21,235-100-updown,0,0,0,-6);
				l.floodFillPes(prop.getXT(), prop.getYMin()+20, 0, 0, 0, -6); 
				clean(prop.getXFront(), prop.getXBack(), prop.getYMin(), prop.getYMax());
			}
			/* body */
			l.insertLinePes(xFront,200-100-updown,a,150-100-updown,0,0,0);
			l.insertLinePes(xFront,200-100-updown,b,200-100-updown,0,0,0);
			l.insertLinePes(b,200-100-updown,c,100-100-updown,0,0,0);
			l.insertLinePes(c,100-100-updown,d,100-100-updown,0,0,0);
			l.insertLinePes(d,100-100-updown,e,150-100-updown,0,0,0);
			l.insertLinePes(a,150-100-updown,e,150-100-updown,0,0,0);

			/*sayap*/
			l.insertLinePes(f,175-100-updown,g,250-100-updown,0,0,0);
			l.insertLinePes(g,250-100-updown,h,250-100-updown,0,0,0);
			l.insertLinePes(h,250-100-updown,i,175-100-updown,0,0,0);
			
			/* reset tire's position */
			if(!isDestroy)
				tire.reset_position();
			
			clean(xFront,c,100-100,250-100-updown);

			if(isDestroy)
				break;
			a = 950; b = 1200; c = 1300; d = 1200;
			e = 1100; f = 1000; g = 1100; h = 1200; i = 1100;
			xFront = 900;
		}
		
		// ledakan 
		/* kode untuk meledak */
		clean(prop.getXFront(), prop.getXBack(), prop.getYMin(), prop.getYMax());
		int xLedak = (getXBehind()+getXFront())/2;

		//the explosion
		clean(xLedak-100,xLedak+100,100-100,400-100);
		l.insertLinePes(xLedak,100-100,xLedak+20,200-100,255,0,0);
		l.insertLinePes(xLedak+20,200-100,xLedak+100,255-100,255,0,0);
		l.insertLinePes(xLedak+100,250-100,xLedak+20,300-100,255,0,0);
		l.insertLinePes(xLedak+20,300-100,xLedak,400-100,255,0,0);
		l.insertLinePes(xLedak,400-100,xLedak-20,300-100,255,0,0);
		l.insertLinePes(xLedak-20,300-100,xLedak-100,250-100,255,0,0);
		l.insertLinePes(xLedak-100,250-100,xLedak-20,200-100,255,0,0);
		l.insertLinePes(xLedak-30,210-100,xLedak,100-100,255,0,0);

		//floodfill explosion
		l.floodFillPes(xLedak,250-100,240-100,0,0,0);			

		usleep(300000);
		clean(xLedak-100,xLedak+100,100-100,400-100);
		usleep(300000);
		
		//clean explosion
		usleep(20000);

		//variabel untuk bagian2 pesawat
		double deltaX = 5;
		double deltaY = 10;
		double x0,a1,b1,c1,d1,e1,f1,g1,h1,i1;
		double deg = 10;

		thread dive(movePilot,xLedak);

		//komponen x titik body
		xFront -= 100;
		a -= 100;
		b -= 100;
		c -= 100;
		d -= 100;
		e -= 100;	

		//komponen x titik pesawat
		f += 100;
		g += 100;
		h += 100;
		i += 100;

		//komponen y titik-titik body pesawat
		x0 = 200;
		a1 = 150;
		b1 = 200;
		c1 = 100;
		d1 = 100;
		e1 = 150;

		//komponen y titik-titik sayap pesawat
		f1 = 175;
		g1 = 250;
		h1 = 250;
		i1 = 175;
		
		//sleep(1);
		// set tire's is_falling to true
		tire.set_is_falling(true);
		prop.create_boom(255, 0, 0);

		//titik-titik fire point body dan sayap pesawat, akan dirotasi juga
		double xFireBody = a+5;
		double yFireBody = a1+5;

		double xFireWing = f+21;
		double yFireWing = f1+15;

		int as;


//nyobain pake manipulasi iterasi 
/*
		for (as=0;as<10;as++) {
			if(a1 < 450) {
				//body
				l.insertLinePes(xFront,x0,a,a1,255,0,0);
				l.insertLinePes(xFront,x0,b,b1,255,0,0);
				l.insertLinePes(b,b1,c,c1,255,0,0);
				l.insertLinePes(c,c1,d,d1,255,0,0);
				l.insertLinePes(d,d1,e,e1,255,0,0);
				l.insertLinePes(a,a1,e,e1,255,0,0);

				//sayap
				l.insertLinePes(f,f1,g,g1,255,0,0);
				l.insertLinePes(g,g1,h,h1,255,0,0);
				l.insertLinePes(h,h1,i,i1,255,0,0);
				l.insertLinePes(f,f1,i,i1,255,0,0);
				//l.floodFillPes(xFireBody,yFireBody,255,0,0,0);	
				l.floodFillPes(xFireWing,yFireWing,255,0,0,0);			

				//floodfill body
				//l.floodFillPes(xFireBody,yFireBody,255,0,0,0);	
				

				//floodfill wing
				//l.floodFillPes(xFireWing,yFireWing,255,0,0,0);			


				//propeler				
				prop.rotate(255, 0, 0, 45);

				usleep(20000);
				
				//clean body
				l.insertLinePes(xFront,x0,a,a1,0,0,0);
				l.insertLinePes(xFront,x0,b,b1,0,0,0);
				l.insertLinePes(b,b1,c,c1,0,0,0);
				l.insertLinePes(c,c1,d,d1,0,0,0);
				l.insertLinePes(d,d1,e,e1,0,0,0);
				l.insertLinePes(a,a1,e,e1,0,0,0);				
				
				//clean sayap
				l.insertLinePes(f,f1,g,g1,0,0,0);
				l.insertLinePes(g,g1,h,h1,0,0,0);
				l.insertLinePes(h,h1,i,i1,0,0,0);
				l.insertLinePes(f,f1,i,i1,0,0,0);
			
				// //clean propeler
				prop.clear_boom();

				//change points of body
				//change x
				xFront -= deltaX;
				a -= deltaX;
				b -= deltaX;
				c -= deltaX;
				d -= deltaX;
				e -= deltaX;	
				xFireBody -=deltaX;

				//change y
				x0 += deltaY;
				a1 += deltaY;
				b1 += deltaY;
				c1 += deltaY;
				d1 += deltaY;
				e1 += deltaY;	
				yFireBody +=deltaY;

				//change points of wing
				//change x
				f += deltaX;
				g += deltaX;
				h += deltaX;
				i += deltaX;
				xFireWing +=deltaX;

				//change y
				f1 += deltaY;
				g1 += deltaY;
				h1 += deltaY;
				i1 += deltaY;
				yFireWing +=deltaY;
				
				//rotate body
				//cout << "Loop\n";
				rotatePoint(&xFront,&x0,10,xFront,x0);
				rotatePoint(&a,&a1,10,xFront,x0);
				rotatePoint(&b,&b1,10,xFront,x0);
				rotatePoint(&c,&c1,10,xFront,x0);
				rotatePoint(&d,&d1,10,xFront,x0);
				rotatePoint(&e,&e1,10,xFront,x0);
				rotatePoint(&xFireBody,&yFireBody,10,xFront,x0);
				
				//rotate wing
				//cout << "Loop\n";
				rotatePoint(&f,&f1,10,f,f1);
				rotatePoint(&g,&g1,10,f,f1);
				rotatePoint(&h,&h1,10,f,f1);
				rotatePoint(&i,&i1,10,f,f1);
				rotatePoint(&xFireWing,&yFireWing,10,f,f1);


			}
			
			// let the tire fall
			tire.fall();

			usleep(100000);
		}

*/

		do {
			if(a1 < 450) {
				//body
				l.insertLinePes(xFront,x0,a,a1,255,0,0);
				l.insertLinePes(xFront,x0,b,b1,255,0,0);
				l.insertLinePes(b,b1,c,c1,255,0,0);
				l.insertLinePes(c,c1,d,d1,255,0,0);
				l.insertLinePes(d,d1,e,e1,255,0,0);
				l.insertLinePes(a,a1,e,e1,255,0,0);

				//sayap
				l.insertLinePes(f,f1,g,g1,255,0,0);
				l.insertLinePes(g,g1,h,h1,255,0,0);
				l.insertLinePes(h,h1,i,i1,255,0,0);
				l.insertLinePes(f,f1,i,i1,255,0,0);
				//l.floodFillPes(xFireBody,yFireBody,255,0,0,0);	
				//l.floodFillPes(xFireWing,yFireWing,255,0,0,0);			

				//floodfill body
				//l.floodFillPes(xFireBody,yFireBody,255,0,0,0);	
				

				//floodfill wing
				//l.floodFillPes(xFireWing,yFireWing,255,0,0,0);			


				//propeler				
				prop.rotate(255, 0, 0, 45);

				usleep(20000);
				
				//clean body
				l.insertLinePes(xFront,x0,a,a1,0,0,0);
				l.insertLinePes(xFront,x0,b,b1,0,0,0);
				l.insertLinePes(b,b1,c,c1,0,0,0);
				l.insertLinePes(c,c1,d,d1,0,0,0);
				l.insertLinePes(d,d1,e,e1,0,0,0);
				l.insertLinePes(a,a1,e,e1,0,0,0);				
				
				//clean sayap
				l.insertLinePes(f,f1,g,g1,0,0,0);
				l.insertLinePes(g,g1,h,h1,0,0,0);
				l.insertLinePes(h,h1,i,i1,0,0,0);
				l.insertLinePes(f,f1,i,i1,0,0,0);
			
				// //clean propeler
				prop.clear_boom();

				//change points of body
				//change x
				xFront -= deltaX;
				a -= deltaX;
				b -= deltaX;
				c -= deltaX;
				d -= deltaX;
				e -= deltaX;	
				xFireBody -=deltaX;

				//change y
				x0 += deltaY;
				a1 += deltaY;
				b1 += deltaY;
				c1 += deltaY;
				d1 += deltaY;
				e1 += deltaY;	
				yFireBody +=deltaY;

				//change points of wing
				//change x
				f += deltaX;
				g += deltaX;
				h += deltaX;
				i += deltaX;
				xFireWing +=deltaX;

				//change y
				f1 += deltaY;
				g1 += deltaY;
				h1 += deltaY;
				i1 += deltaY;
				yFireWing +=deltaY;
				
				//rotate body
				//cout << "Loop\n";
				rotatePoint(&xFront,&x0,10,xFront,x0);
				rotatePoint(&a,&a1,10,xFront,x0);
				rotatePoint(&b,&b1,10,xFront,x0);
				rotatePoint(&c,&c1,10,xFront,x0);
				rotatePoint(&d,&d1,10,xFront,x0);
				rotatePoint(&e,&e1,10,xFront,x0);
				rotatePoint(&xFireBody,&yFireBody,10,xFront,x0);
				
				//rotate wing
				//cout << "Loop\n";
				rotatePoint(&f,&f1,10,f,f1);
				rotatePoint(&g,&g1,10,f,f1);
				rotatePoint(&h,&h1,10,f,f1);
				rotatePoint(&i,&i1,10,f,f1);
				rotatePoint(&xFireWing,&yFireWing,10,f,f1);


			}
			
			// let the tire fall
			tire.fall();

			usleep(100000);

		} while(a1<450 || tire.get_is_falling());

		
		// destroy the tire after a while
		usleep(2000000);
		tire.clean_screen();
	}
};



