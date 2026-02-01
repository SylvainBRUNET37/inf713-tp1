#include "ImageTransformationAlgorithms.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include "Utils.h"

namespace
{
	// srgb -> linear

	[[nodiscard]] double SrgbToLinearLow(const double color)
	{
		return color / 12.92;
	}

	[[nodiscard]] double SrgbToLinearHigh(const double color)
	{
		return pow((color + 0.055) / 1.055, 2.4);
	}

	[[nodiscard]] double SrgbToLinear(const double color)
	{
		static constexpr double SRGB_TO_LINEAR_THRESHOLD = 0.04045;

		return color <= SRGB_TO_LINEAR_THRESHOLD
			       ? SrgbToLinearLow(color)
			       : SrgbToLinearHigh(color);
	}

	// linear -> srgb

	[[nodiscard]] double LinearToSrgbLow(const double color)
	{
		return color * 12.92;
	}

	[[nodiscard]] double LinearToSrgbHigh(const double color)
	{
		return 1.055 * pow(color, 1.0 / 2.4) - 0.055;
	}

	[[nodiscard]] double LinearToSrgb(const double color)
	{
		static constexpr double LINEAR_TO_SRGB_THRESHOLD = 0.0031308;

		return color <= LINEAR_TO_SRGB_THRESHOLD
			       ? LinearToSrgbLow(color)
			       : LinearToSrgbHigh(color);
	}
}

std::vector<double> ImageTransformationAlgorithms::ComputeLinearisedColors(const ImageInfo& baseImageInfo)
{
	std::vector<double> result;
	result.reserve(baseImageInfo.GetDataSize());

	const auto imageDatas = Utils::CreateImageDataSpan(baseImageInfo);
	for (const auto color : imageDatas)
	{
		const double normalisedColor = static_cast<double>(color) / HistInfo::MAX_COLOR_VALUE;

		result.push_back(SrgbToLinear(normalisedColor));
	}

	return result;
}

void ImageTransformationAlgorithms::ApplyCorrections(const ImageInfo& image, const std::vector<double>& correctionDatas)
{
	using namespace std;

	const auto imageDatas = Utils::CreateImageDataSpan(image);
	assert(imageDatas.size() == correctionDatas.size());

	for (size_t i = 0; i < imageDatas.size(); ++i)
	{
		const double srgbPixelValue = LinearToSrgb(correctionDatas[i]);

		imageDatas[i] = static_cast<uint8_t>
		(
			clamp(srgbPixelValue, 0.0, 1.0) * HistInfo::MAX_COLOR_VALUE
		);
	}
}
