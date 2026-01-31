#ifndef IMAGE_TRANSFORMATION_ALGORITHMS_H
#define IMAGE_TRANSFORMATION_ALGORITHMS_H

#include <vector>

#include "Data.h"

namespace ImageTransformationAlgorithms
{
	[[nodiscard]] std::vector<double> CreateLinearisedImage(const ImageInfo<uint8_t>& imageInfo);
	void CreateSrbgImage(ImageInfo<uint8_t>& newImage, const std::vector<double>& baseImageInfo);

	void ApplyContrast(const ImageInfo<double>& imageInfo, double contrast);
	void ApplyShine(const ImageInfo<double>& imageInfo, double shine);
}

#endif
