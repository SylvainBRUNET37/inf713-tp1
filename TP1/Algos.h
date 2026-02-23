#ifndef ALGOS_H
#define ALGOS_H

class Algos
{
public:
	[[nodiscard]] static double Normalize(const double value, const double maxValue)
	{
		return value / maxValue;
	}

	[[nodiscard]] static double SrgbToLinear(double normalizedSrgbColor);
	[[nodiscard]] static double LinearToSrgb(double normalizedLinearizedColor);

private:
	[[nodiscard]] static double SrgbToLinearHigh(double color);
	[[nodiscard]] static double SrgbToLinearLow(const double color)
	{
		return color / 12.92;
	}

	[[nodiscard]] static double LinearToSrgbHigh(double color);
	[[nodiscard]] static double LinearToSrgbLow(const double color)
	{
		return color * 12.92;
	}

};

#endif
