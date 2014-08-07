#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TOTAL_DEGREES        360.0
#define MAJOR_RADIUS         6378136.6 //meters
#define MINOR_RADIUS         6356751.9 //meters
#define ECCENTRICITY_SQUARED 0.006694385
#define EQUATORIAL_PERIMETER 40075017.0  //meters
#define POLAR_PERIMETER      40007860.0  //meters
#define PI                   3.14159265358979323846

typedef struct
{
	double array[80001][1];
} Bin100;

typedef struct
{
	double array[80001][2];
} Bin50;

typedef struct
{
	double array[80001][4];
} Bin25;

typedef struct
{
	double array[800001][1];
} Bin10;

double toRadian(double degrees) {
	return degrees * PI / 180;
}

double round(double d) {
  return floor(d + 0.5);
}

double roundWithPrecision(double value, int precision) {
	return round(value * pow(10.0, precision)) / pow(10.0, precision);
}

/**
 * Bin factor table:
 * 
 * ┌────────────┬─────────────────┐
 * │ Bin factor │ Meters (aprox.) │
 * ├────────────┼─────────────────┤
 * │ 10         │ 11              │
 * ├────────────┼─────────────────┤
 * │ 25         │ 27              │
 * ├────────────┼─────────────────┤
 * │ 50         │ 55              │
 * ├────────────┼─────────────────┤
 * │ 100        │ 110             │
 * └────────────┴─────────────────┘
 */
double getLonStep(double latitude, double lat_bin_factor) {
	double lat_rad = toRadian(latitude);
	double meters_per_lon_bin = PI * MAJOR_RADIUS * cos(lat_rad) / ((180.0 * 100000.0 / lat_bin_factor) * (sqrt(1.0 - ECCENTRICITY_SQUARED * pow(sin(lat_rad), 2.0))));
	double perimeter_at_lat = meters_per_lon_bin * TOTAL_DEGREES * 100000 / lat_bin_factor;
	int division_factor = floor(perimeter_at_lat / lat_bin_factor);
	//double bin_in_meters = perimeter_at_lat / division_factor;
	return roundWithPrecision(TOTAL_DEGREES / division_factor, 5);
}

void fillBinningLatitudesAndLongitudeSteps (Bin10  *bin10, Bin25  *bin25, Bin50  *bin50, Bin100 *bin100) {
	int i = 0;
	int index25 = 0;

	for(; i < 800001; ++i) {

		int possible25part;

		double latitude = i / 10000.0;

		bin10->array[i][0] = getLonStep(latitude, 10);

		if (i % 5 == 0) {
			if (i % 10 == 0) {
				bin100->array[i/10][0] = getLonStep(latitude, 100);
				bin50->array[i/10][0] = getLonStep(latitude, 50);
				bin25->array[i/10][0] = getLonStep(latitude, 25);
			} else {
				bin50->array[i/10][1] = getLonStep(latitude, 50);
				bin25->array[i/10][2] = getLonStep(latitude, 25);
			}
		}
		
		//25 factor part
		possible25part = i * 10 + 5;

		if (possible25part % 25 == 0) {
			index25 = possible25part % 100 / 25;
			latitude = possible25part / 100000.0;

			bin25->array[i/10][index25] = getLonStep(latitude, 25);
		}
	}
}



int main(int argc, char* argv[])
{
	Bin10  *bin10  = (Bin10*) malloc(sizeof (Bin10));
	Bin25  *bin25  = (Bin25*) malloc(sizeof (Bin25));
	Bin50  *bin50  = (Bin50*) malloc(sizeof (Bin50));
	Bin100 *bin100 = (Bin100*)malloc(sizeof (Bin100));

	double latitudes[] = {38.756006, 38.756036, 38.756066, 38.756096, 38.756126, 38.756156, 38.756186, 38.756216, 38.756246, 38.756276, 38.756306, 38.756336, 38.756366, 38.756396, 38.756426, 38.756456, 38.756486, 38.756516, 38.756546, 38.756576, 38.756606, 38.756636, 38.756666, 38.756696, 38.756726, 38.756756, 38.756786, 38.756816, 38.756846, 38.756876, 38.756906, 38.756936, 38.756966, 38.756996, 38.757026, 38.757056, 38.757086, 38.757116, 38.757146, 38.757176, 38.757206, 38.757236, 38.757266, 38.757296, 38.757326, 38.757356, 38.757386, 38.757416, 38.757446, 38.757476, 38.757506, 38.757536, 38.757566, 38.757596, 38.757626, 38.757656, 38.757686, 38.757716, 38.757746, 38.757776, 38.757806, 38.757836, 38.757866, 38.757896, 38.757926, 38.757956, 38.757986, 38.758016, 38.758046, 38.758076, 38.758106, 38.758136, 38.758166, 38.758196, 38.758226, 38.758256, 38.758286, 38.758316, 38.758346, 38.758376, 38.758406, 38.758436, 38.758466, 38.758496, 38.758526, 38.758556, 38.758586, 38.758616, 38.758646, 38.758676, 38.758706, 38.758736, 38.758766, 38.758796, 38.758826, 38.758856, 38.758886, 38.758916, 38.758946, 38.758976, 38.759006, 38.759036, 38.759066, 38.759096, 38.759126, 38.759156, 38.759186, 38.759216, 38.759246, 38.759276, 38.759306, 38.759336, 38.759366, 38.759396, 38.759426, 38.759456, 38.759486, 38.759516, 38.759546, 38.759576, 38.759606, 38.759636, 38.759666, 38.759696, 38.759726, 38.759756, 38.759786, 38.759816, 38.759846, 38.759876, 38.759906, 38.759936};
	double longitudes[] = {-9.133004, -9.132974, -9.132944, -9.132914, -9.132884, -9.132854, -9.132824, -9.132794, -9.132764, -9.132734, -9.132704, -9.132674, -9.132644, -9.132614, -9.132584, -9.132554, -9.132524, -9.132494, -9.132464, -9.132434, -9.132404, -9.132374, -9.132344, -9.132314, -9.132284, -9.132254, -9.132224, -9.132194, -9.132164, -9.132134, -9.132104, -9.132074, -9.132044, -9.132014, -9.131984, -9.131954, -9.131924, -9.131894, -9.131864, -9.131834, -9.131804, -9.131774, -9.131744, -9.131714, -9.131684, -9.131654, -9.131624, -9.131594, -9.131564, -9.131534, -9.131504, -9.131474, -9.131444, -9.131414, -9.131384, -9.131354, -9.131324, -9.131294, -9.131264, -9.131234, -9.131204, -9.131174, -9.131144, -9.131114, -9.131084, -9.131054, -9.131024, -9.130994, -9.130964, -9.130934, -9.130904, -9.130874, -9.130844, -9.130814, -9.130784, -9.130754, -9.130724, -9.130694, -9.130664, -9.130634, -9.130604, -9.130574, -9.130544, -9.130514, -9.130484, -9.130454, -9.130424, -9.130394, -9.130364, -9.130334, -9.130304, -9.130274, -9.130244, -9.130214, -9.130184, -9.130154, -9.130124, -9.130094, -9.130064, -9.130034, -9.130004, -9.129974, -9.129944, -9.129914, -9.129884, -9.129854, -9.129824, -9.129794, -9.129764, -9.129734, -9.129704, -9.129674, -9.129644, -9.129614, -9.129584, -9.129554, -9.129524, -9.129494, -9.129464, -9.129434, -9.129404, -9.129374, -9.129344, -9.129314, -9.129284, -9.129254, -9.129224, -9.129194, -9.129164, -9.129134, -9.129104, -9.129074};

	int i = 0;

	fillBinningLatitudesAndLongitudeSteps(bin10, bin25, bin50, bin100);
	/*
	for (; i < 80001; ++i) {
		printf("Latitude: %2.4f - step: %1.5f\n", i / 1000.0, bin100->array[i][0]);
	}
	*/

	for (; i < 132; ++i) {

		/**
		 *    BIN 100
		 */
		int index100 = (int)round(latitudes[i] * 1000.0);

		double binnedLatitude100 = index100 / 1000.0;
		double longitudeStep100 = bin100->array[index100][0];
		double binnedLongitude100 = longitudeStep100 * round(longitudes[i] / longitudeStep100);

		/**
		 *    BIN 50
		 */
		int binnedLatitude50int = (int)round(latitudes[i] * 10000.0 / 5.0) * 5;
		double binnedLatitude50 = binnedLatitude50int / 10000.0;

		int index50 = (binnedLatitude50int % 10) / 5;

		double longitudeStep50 = bin50->array[index100][index50];
		double binnedLongitude50 = longitudeStep50 * round(longitudes[i] / longitudeStep50);

		/**
		 *    BIN 25
		 */
		int binnedLatitude25int = (int)round(latitudes[i] * 100000.0 / 25.0) * 25.0;
		double binnedLatitude25 = binnedLatitude25int / 100000.0;

		int index25 = (binnedLatitude25int % 100) / 25;

		double longitudeStep25 = bin25->array[index100][index25];
		double binnedLongitude25 = longitudeStep25 * round(longitudes[i] / longitudeStep25);

		/**
		 *    BIN 10
		 */
		int index10 = (int)round(latitudes[i] * 10000.0);

		double binnedLatitude10 = index10 / 10000.0;
		double longitudeStep10 = bin10->array[index10][0];
		double binnedLongitude10 = longitudeStep10 * round(longitudes[i] / longitudeStep10);

		//printf("Latitude: %2.4f - step: %1.5f\n", binnedLatitude, longitudeStep);
		//printf("Binned Latitude: %2.4f - Binned Longitude: %2.4f\n", binnedLatitude, binnedLongitude);

		//printf("%2.5f %2.5f\n", binnedLatitude10, binnedLongitude10);
		//printf("%2.5f %2.5f\n", binnedLatitude50, binnedLongitude50);
		//printf("%2.5f %2.5f\n", binnedLatitude25, binnedLongitude25);
		//printf("%2.5f %2.5f\n", binnedLatitude100, binnedLongitude100);
	}

	free(bin10);
	free(bin25);
	free(bin50);
	free(bin100);

	printf("DONE");
	getchar();
    return 0;
}