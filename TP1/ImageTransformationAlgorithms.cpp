#include "ImageTransformationAlgorithms.h"

#include <cmath>

#include "Utils.h"

namespace
{
	[[nodiscard]] double FirstMagicTransformation(const double color)
	{
		return color / 12.92f;
	}

	[[nodiscard]] double SecondMagicTransformation(const double color)
	{
		return pow((color + 0.055) / 1.055, 2.4);
	}
}

ImageInfo ImageTransformationAlgorithms::CreateLinearisedImage(const ImageInfo& baseImageInfo)
{
	return Utils::ApplyTranformation(baseImageInfo, [&](const ImageInfo::DataType& color)
	{
		static constexpr double MAGIC_NUMBER = 0.04045;

		return static_cast<double>(color) <= MAGIC_NUMBER
			       ? FirstMagicTransformation(color)
			       : SecondMagicTransformation(color);
	});
}
