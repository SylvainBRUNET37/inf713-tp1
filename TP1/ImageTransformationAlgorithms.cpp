#include "ImageTransformationAlgorithms.h"

#include <algorithm>
#include <cmath>

#include "Utils.h"

namespace
{
	[[nodiscard]] double FirstMagicLinearTransformation(const double color)
	{
		return color / 12.92;
	}

	[[nodiscard]] double SecondMagicLinearTransformation(const double color)
	{
		return pow((color + 0.055) / 1.055, 2.4);
	}

	[[nodiscard]] double FirstMagicSrgbTransformation(const double color)
	{
		return color * 12.92;
	}

	[[nodiscard]] double SecondMagicSrgbTransformation(const double color)
	{
		return 1.055 * pow(color, 1.0 / 2.4) - 0.055;
	}
}

std::vector<double> ImageTransformationAlgorithms::CreateLinearisedImage(const ImageInfo& baseImageInfo)
{
	static constexpr double MAGIC_NUMBER = 0.04045;

	std::vector<double> result;
	result.reserve(baseImageInfo.GetDataSize());

	const auto newImageDatas = Utils::CreateImageDataSpan(baseImageInfo);
	for (const uint8_t color : newImageDatas)
	{
		const double normalisedColor = static_cast<double>(color) / 255.0;

		result.push_back(
			normalisedColor <= MAGIC_NUMBER
				? FirstMagicLinearTransformation(normalisedColor)
				: SecondMagicLinearTransformation(normalisedColor)
		);
	}

	return result;
}

void ImageTransformationAlgorithms::CreateSrbgImage(const ImageInfo& newImage, const std::vector<double>& baseImageInfo)
{
	using namespace std;

	static constexpr double MAGIC_NUMBER = 0.0031308;

	auto newImageDatas = Utils::CreateImageDataSpan(newImage);

	const size_t count =
		min(baseImageInfo.size(), newImageDatas.size());

	for (size_t i = 0; i < count; ++i)
	{
		const double baseData = baseImageInfo[i];
		auto& newData = newImageDatas[i];

		const double srgb =
			baseData <= MAGIC_NUMBER
				? FirstMagicSrgbTransformation(baseData)
				: SecondMagicSrgbTransformation(baseData);

		newData = static_cast<uint8_t>(
			clamp(srgb, 0.0, 1.0) * 255.0
		);
	}
}
