#ifndef HISTROGRAMME_ALGORTHMS_H
#define HISTROGRAMME_ALGORTHMS_H

#include "Data.h"

namespace HistogrammeAlgorithms
{
	[[nodiscard]] HistInfo CalculHistogramme(const ImageInfo& imageInfo);

	// J'ai change pour prendre l'histogramme de base en parametre plutot que l'image
	[[nodiscard]] HistInfo::HistogramType CalculHistogrammeCumulatif(const HistInfo::HistogramType& baseHisto);

	void ApplyEqualisation(HistInfo::HistogramType& histo, size_t imageSize);

	void EqualiseImage(const ImageInfo& baseImageInfo, const HistInfo::HistogramType& equalisedHisto);
}

#endif
