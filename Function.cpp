#include <Function.h>

float RandOutput(const int& range_min, const int& range_max, float& result) {
	return result = ((float)rand() / RAND_MAX) * (range_max + 1 - range_min) + range_min;
}
float RandScaleOutput(const float& range_min, const float& range_max, float& result) {
	return result = ((float)rand() / RAND_MAX) * (range_max + 1 - range_min) + range_min;
}
int iRandOutput(const int& range_min, const int& range_max, int& result) {
	return result = int(((float)rand() / RAND_MAX) * (range_max + 1 - range_min) + range_min);
}
void VoidRand(const int& range_min, const int& range_max, int& result) {
	result = int(((float)rand() / RAND_MAX) * (range_max + 1 - range_min) + range_min);
}