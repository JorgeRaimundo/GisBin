#include <stdio.h>
#include <math.h>

#define TOTAL_DEGREES        360.0
#define MAJOR_RADIUS         6378136.6 //meters
#define MINOR_RADIUS         6356751.9 //meters
#define ECCENTRICITY_SQUARED 0.006694385
#define EQUATORIAL_PERIMETER 40075017.0  //meters
#define POLAR_PERIMETER      40007860.0  //meters
#define PI                   3.14159265358979323846

typedef struct
{
	double array[80001];
} Bin100;

double toRadian(double degrees) {
	return degrees * PI / 180;
}

double round(double d) {
  return floor(d + 0.5);
}

double roundWithPrecision(double value, int precision) {
	return round(value * pow(10.0, precision)) / pow(10.0, precision);
}

int main(int argc, char* argv[])
{
    Bin100 bin100;

	int i = 0;

	for(; i < 80001; ++i) {

		double latitude = i / 1000.0;

		double lat_rad = toRadian(latitude);
		double meters_per_lon_bin = PI * MAJOR_RADIUS * cos(lat_rad) / (180000.0 * (sqrt(1.0 - ECCENTRICITY_SQUARED * pow(sin(lat_rad), 2.0))));
		double perimeter_at_lat = meters_per_lon_bin * 360000.0;
		int division_factor = floor(perimeter_at_lat / 100);
		double bin = perimeter_at_lat / division_factor;
		double longitude_step = roundWithPrecision(TOTAL_DEGREES / division_factor, 4);

		bin100.array[i] = longitude_step;
	}

	

	printf("DONE");
	getchar();
    return 0;
}