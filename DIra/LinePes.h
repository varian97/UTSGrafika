#ifndef LINEPES_H
#define LINEPES_H

#include "framebufferPes.h"
using namespace std;

class LinePes : public framebufferPes {
	private:
		framebufferPes fb;

	public:
		void insertLinePes(float x1, float y1,float x2, float y2, int r, int g, int b)
		{
		    // Bresenham's line algorithm
			const bool steep = (fabs(y2 - y1) > fabs(x2 - x1));
			if(steep)
			{
			  std::swap(x1, y1);
			  std::swap(x2, y2);
			}
			 
			if(x1 > x2)
			{
			  std::swap(x1, x2);
			  std::swap(y1, y2);
			}
			 
			const float dx = x2 - x1;
			const float dy = fabs(y2 - y1);
			 
			float error = dx / 2.0f;
			const int ystep = (y1 < y2) ? 1 : -1;
			int y = (int)y1;
			 
			const int maxX = (int)x2;
			 
			for(int x=(int)x1; x<maxX; x++)
			{
			  if(steep)
			  {
			      putPixelPes(y,x,r,g,b);
			  }
			  else
			  {
			      putPixelPes(x,y,r,g,b);
			  }
			 
			  error -= dy;
			  if(error < 0)
			  {
			      y += ystep;
			      error += dx;
			  }
			}	
		}
		void floodFillPes(float x1, float y1, int r, int g, int b,int intColor){
			if(getPixelPesawat(x1,y1) == intColor){
				putPixelPes(x1,y1,r,g,b);
				floodFillPes(x1-1,y1,r,g,b,intColor);
				floodFillPes(x1+1,y1,r,g,b,intColor);
				floodFillPes(x1,y1+1,r,g,b,intColor);
				floodFillPes(x1,y1-1,r,g,b,intColor);

			}
		}

};
#endif
