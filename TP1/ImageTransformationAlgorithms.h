#ifndef IMAGE_TRANSFORMATION_ALGORITHMS_H
#define IMAGE_TRANSFORMATION_ALGORITHMS_H

#include <vector>

#include "Data.h"

namespace ImageTransformationAlgorithms
{
	[[nodiscard]] std::vector<double> CreateLinearisedImage(const ImageInfo& imageInfo);
	void CreateSrbgImage(const ImageInfo& newImage, const std::vector<double>& baseImageInfo);
}

#endif
