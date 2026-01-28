#ifndef HISTROGRAMME_ALGORTHMS_H
#define HISTROGRAMME_ALGORTHMS_H

#include "Data.h"

namespace HistogrammeAlgorithms
{
	// TODO: compute meta datas
	[[nodiscard]] HistInfo CalculHistogramme(const ImageInfo& imageInfo);

	// J'ai change pour prendre l'histogramme de base en parametre plutot que l'image
	[[nodiscard]] HistInfo::HistogramType CalculHistogrammeCumulatif(const HistInfo::HistogramType& baseHisto);

	void ApplyEgalisation(HistInfo::HistogramType& histo, size_t imageSize);
}

#endif
