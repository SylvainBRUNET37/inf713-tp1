#ifndef IMAGE_TRANSFORMATION_ALGORITHMS_H
#define IMAGE_TRANSFORMATION_ALGORITHMS_H

#include <vector>

#include "Data.h"

namespace ImageTransformationAlgorithms
{
	[[nodiscard]] std::vector<double> ComputeLinearisedColors(const ImageInfo& imageInfo);
	void ApplyCorrections(const ImageInfo& image, const std::vector<double>& correctionDatas);
}

#endif
