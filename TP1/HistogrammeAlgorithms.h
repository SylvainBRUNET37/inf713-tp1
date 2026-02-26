#ifndef HISTROGRAMME_ALGORTHMS_H
#define HISTROGRAMME_ALGORTHMS_H

#include "Data.h"

// To check if it's correct:
// Historigram: https://azer.io/image-histogram/
// Equalise: https://pinetools.com/equalize-image
namespace HistogrammeAlgorithms
{
	[[nodiscard]] HistInfo CalculHistogramme(const ImageInfo& imageInfo);
	[[nodiscard]] HistInfo CalculHistogrammeCumulatif(const HistInfo::HistogramType& baseHisto);

	void EqualiseImage(ImageInfo& baseImageInfo, const HistInfo::HistogramType& equalisedHisto);
}

#endif
