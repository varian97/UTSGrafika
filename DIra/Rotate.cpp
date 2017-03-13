#include <math.h>
#include <iostream>
using namespace std;

double toRadian(double deg) {
	return (deg / 180) * ((double) M_PI);
}

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

/*
int main () {
	double x;
	double y;
	double deg;
	cin >> x;
	cin >> y;
	cin >> deg;
	cout << x << " " << y << " " << deg << "\n";
	rotate(&x,&y,deg);
	cout << round(x) << " " << round(y) << " " << deg << "\n";
	cout << x << " " << y << " " << deg << "\n";
	return 0;
}
*/
