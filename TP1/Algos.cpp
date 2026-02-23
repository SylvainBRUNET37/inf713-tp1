#include "Algos.h"

#include <cassert>

#include "Utils.h"

double Algos::LinearToSrgbHigh(const double color)
{
	return 1.055 * pow(color, 1.0 / 2.4) - 0.055;
}

double Algos::LinearToSrgb(const double normalizedLinearizedColor)
{
	static constexpr double LINEAR_TO_SRGB_THRESHOLD = 0.0031308;

	assert(normalizedLinearizedColor >= 0.0 && normalizedLinearizedColor <= 1.0);

	return normalizedLinearizedColor <= LINEAR_TO_SRGB_THRESHOLD
		? LinearToSrgbLow(normalizedLinearizedColor)
		: LinearToSrgbHigh(normalizedLinearizedColor);
}

double Algos::SrgbToLinearHigh(const double color)
{
	return pow((color + 0.055) / 1.055, 2.4);
}

double Algos::SrgbToLinear(const double normalizedSrgbColor)
{
	static constexpr double SRGB_TO_LINEAR_THRESHOLD = 0.04045;

	assert(normalizedSrgbColor >= 0.0 && normalizedSrgbColor <= 1.0);

	return normalizedSrgbColor <= SRGB_TO_LINEAR_THRESHOLD
		? SrgbToLinearLow(normalizedSrgbColor)
		: SrgbToLinearHigh(normalizedSrgbColor);
}
