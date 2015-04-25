#include <iostream>
#include <cmath>

using namespace std;

const double earthRadius = 3963.1676;	// the radius of earth in miles
const double PI = M_PI;					// PI constant in cmath header file.

class point{
	private:
		double longtitude;
		double latitude;

	public:
		// the constructor of point
		point(double lon, double lat){
			this->longtitude = lon;
			this->latitude = lat;
		}

		// get the value of longtitue and latitude
		double getLon(){
			return this->longtitude;
		}
		double getLat(){
			return this->latitude;
		}
};

inline double toRadians(double num){
	return num * (PI/180.0);  
}

/*
	getDistance:
		Args: point a and point b.
		Return: the distace between two points

	Algorithm: Haversine formula
		In this question, since we want to calculate the circle distances between two points 
		on a sphere (the earth) from latitudes and longtitudes. And the Haversine formular 
		is the special case in spherical trigonometry. The formular is in the following:
		lat1: latitude 1
		lat2: latitude 2
		lon1: longtitude 1
		lon2: longtitude 2

		distance 
			= 2 * radius * arcsin( sqrt(sin((lat1 - lat2)/2)^2 + cos(lat1) * cos(lat2) *  sin((long1 - long2)/2)^2)

*/
double getDistance(point *a, point *b){
	double aLat = toRadians(a->getLat());
	double bLat = toRadians(b->getLat());
	double aLon = toRadians(a->getLon());
	double bLon = toRadians(b->getLon());

	double latDiff = bLat - aLat;
	double lonDiff = bLon - aLon;

	// Haversine Foumula
	double valA = pow(sin(latDiff/2),2) + cos(aLat) * cos(bLat) * pow(sin(lonDiff/2),2);
	double distance = 2 * earthRadius * asin(sqrt(valA));
	
	return distance;
}

int main(){
	// generate a testcase
	point *pA = new point(42.032403,-87.741625);
	point *pB = new point(40.440625,-79.995886);
	point *pC = new point(23.697810,120.960515);
	point *pD = new point(22.627278,120.301435);

	// get distances (A->B and C->D)
	double distAB = getDistance(pA, pB);
	double distCD = getDistance(pC, pD);

	if(distAB > distCD)
		cout<<"A->C->D->B is the shortest path."<<endl;
	else if(distAB == distCD)
		cout<<"Two dirvers have the same distance."<<endl;
	else
		cout<<"C->A->B->D is the shortest path."<<endl;

	return 0;
}