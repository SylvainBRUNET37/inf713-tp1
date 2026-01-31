#include "ImageTransformationAlgorithms.h"

#include <algorithm>
#include <cmath>
#include <ranges>

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
	result.reserve(baseImageInfo.tailleX * baseImageInfo.tailleY * baseImageInfo.nbCanaux);

	const auto newImageDatas = Utils::CreateImageDataSpan(baseImageInfo);
	for (const uint8_t color : newImageDatas)
	{
		const double c = static_cast<double>(color) / 255.0;

		result.push_back(
			c <= MAGIC_NUMBER
			? FirstMagicLinearTransformation(c)
			: SecondMagicLinearTransformation(c)
		);
	}

	return result;
}

void ImageTransformationAlgorithms::CreateSrbgImage(const ImageInfo& newImage, const std::vector<double>& baseImageInfo)
{
	static constexpr double MAGIC_NUMBER = 0.0031308;

	const auto newImageDatas = Utils::CreateImageDataSpan(newImage);

	for (auto&& [baseData, newData] : std::views::zip(baseImageInfo, newImageDatas))
	{
		double srgb =
			baseData <= MAGIC_NUMBER
			? FirstMagicSrgbTransformation(baseData)
			: SecondMagicSrgbTransformation(baseData);

		srgb = std::clamp(srgb, 0.0, 1.0);

		newData = static_cast<uint8_t>(srgb * 255.0);
	}
}
