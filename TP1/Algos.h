#ifndef ALGOS_H
#define ALGOS_H

namespace Algos
{
	[[nodiscard]] inline double Normalize(const double value, const double maxValue)
	{
		return value / maxValue;
	}

	[[nodiscard]] double SrgbToLinear(double normalizedSrgbColor);
	[[nodiscard]] double LinearToSrgb(double normalizedLinearizedColor);
};

#endif
