// Filename		: Tire.h
// Description	: Tire class. Can move forward and fall (if plane is destroyed)

#ifndef TIRE_H
#define TIRE_H
#include "framebufferPes.h"
#include "LinePes.h"

using namespace std;

class Tire : public framebufferPes {
	private:
		int original_x0;			// original tire's x-coordinate
		int original_y0;			// original tire's y-coordinate
		
		int x0;						// current tire's x-coordinate
		int y0;						// current tire's y-coordinate
		int radius;					// tire's radius (in pixel)
		int speed;					// tire's moving speed (in pixel)
		
		int falling_speed;			// tire's falling speed (in pixel)
		int bouncing_y;				// tire's bouncing ground
		bool is_falling;			// true if tire is falling
		bool is_bouncing;			// true if tire is bouncing from ground
		float momentum;				// shit used for bouncing
		float shit;					// another shit
	
	public:
		/*
		 * 	Initialize all tire's properties.
		 * 
		 * 	!! Should be called before any other methods.
		*/
		void init(int x0, int y0, int radius, int speed, 
			int falling_speed, int bouncing_y) {
			this->original_x0 = x0;
			this->original_y0 = y0;
			this->x0 = x0;
			this->y0 = y0;
			this->radius = radius;
			this->speed = speed;
			this->falling_speed = falling_speed;
			this->bouncing_y = bouncing_y;
			this->is_falling = false;		// set is_falling to false
			this->momentum = float(bouncing_y) - float(y0);
			this->shit = 0.;
		}
		
		/*
		 * 	Draw tire's OUTER circle.
		 * 
		 * 	Source:
		 *  	https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
		*/
		void draw_circle(int color)
		{
			LinePes l;
			int x = this->radius;
			int y = 0;
			int err = 0;
			int r, g, b;
			
			if(color == 0) { // GREEN (plane alive)
				r = 0;
				g = 255;
				b = 0;
			}
			else {	// RED (plane dead)
				r = 255;
				g = 0;
				b = 0;
			}

			while (x >= y)
			{
				// putPixelPes is framebuffer.h method
				// used color: WHITE (255, 255, 255)
				putPixelPes(this->x0 + x, this->y0 + y, r, g, b);
				putPixelPes(this->x0 + y, this->y0 + x, r, g, b);
				putPixelPes(this->x0 - y, this->y0 + x, r, g, b);
				putPixelPes(this->x0 - x, this->y0 + y, r, g, b);
				putPixelPes(this->x0 - x, this->y0 - y, r, g, b);
				putPixelPes(this->x0 - y, this->y0 - x, r, g, b);
				putPixelPes(this->x0 + y, this->y0 - x, r, g, b);
				putPixelPes(this->x0 + x, this->y0 - y, r, g, b);

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
			l.floodFillPes(x0,y0,255,0,0,0);
		}

		/*
		 * 	Clean a screen with a black box
		*/
		void clean(int mostleft, int mostright, int ymin, int ymax) {
			int y;
			int x;
			for (x = mostleft; x <= mostright; x++) {
				for (y = ymin; y <= ymax; y++) {
					putPixelPes(x,y,0,0,0);
				}
			}
		}
		
		/*
		 * 	Clean tire's drawing when moving.
		 * 	!!! Assuming the background is BLACK
		*/
		void clean_screen()
		{
			Line l;
			int x = this->radius;
			int y = 0;
			int err = 0;

			while (x >= y)
			{
				// putPixelPes is framebuffer.h method
				// used color: BLACK (0, 0, 0)
				putPixelPes(this->x0 + x, this->y0 + y, 0, 0, 0);
				putPixelPes(this->x0 + y, this->y0 + x, 0, 0, 0);
				putPixelPes(this->x0 - y, this->y0 + x, 0, 0, 0);
				putPixelPes(this->x0 - x, this->y0 + y, 0, 0, 0);
				putPixelPes(this->x0 - x, this->y0 - y, 0, 0, 0);
				putPixelPes(this->x0 - y, this->y0 - x, 0, 0, 0);
				putPixelPes(this->x0 + y, this->y0 - x, 0, 0, 0);
				putPixelPes(this->x0 + x, this->y0 - y, 0, 0, 0);

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
			int halfrad = this->radius;
			clean(this->x0-halfrad,this->x0+halfrad,this->y0-halfrad,this->y0+halfrad);
		}

		/*
		 * 	Move the tire forward 
		*/ 
		void move_forward(int ymasuk) {
			this->x0 += this->speed;
			if (ymasuk==1){
				this->y0--;			
			} else {
				this->y0++;
			}
			this->draw_circle(0); // GREEN
		}
		
		/*
		 * 	Reset tire's position to its original position
		*/ 
		void reset_position() {
			this->clean_screen();
			this->x0 = this->original_x0;
			this->y0 = this->original_y0;
			this->draw_circle(0); // GREEN
		}
		
		/*
		 * 	This is for tire's falling and bouncing
		*/ 
		void fall() {			
			if(this->momentum < 5) {
				this->is_falling = false;
			}
			else {
				if(this->is_falling && !this->is_bouncing) {
					this->clean_screen();
					this->y0 += int(this->falling_speed*this->shit);
					this->draw_circle(1); // RED
					
					if(this->y0 > this->bouncing_y) {
						this->momentum = this->momentum / 2;
						this->is_bouncing = true;
					}
					else {
						this->shit += float(this->falling_speed) / float(this->momentum);
					}
				}
				if(this->is_falling && this->is_bouncing) {
					this->clean_screen();
					this->y0 -= int(this->falling_speed*this->shit);
					this->draw_circle(1); // RED
					if(this->y0 < this->bouncing_y-this->momentum) {
						this->is_bouncing = false;
					}
					else {
						this->shit -= float(this->falling_speed) / float(this->momentum);
					}
				}
			}
		}
		
		/*
		 * 	Setter is_falling
		*/
		void set_is_falling(bool fall) {
			this->is_falling = fall;
		}
		
		/*
		 * 	Getter is_falling
		*/
		bool get_is_falling() {
			return this->is_falling;
		}
	
};
#endif
