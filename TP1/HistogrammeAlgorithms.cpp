#include "HistogrammeAlgorithms.h"

#include <cassert>
#include <print>
#include <span>
#include <ranges>

#include "Data.h"
#include "Utils.h"

#define LOG_HISTO false
#define LOG_HISTO_CUMUL false
#define LOG_HISTO_EQUALISED false

HistInfo HistogrammeAlgorithms::CalculHistogramme(const ImageInfo& imageInfo)
{
	const std::span imageDatas = Utils::CreateImageDataSpan(imageInfo);

	HistInfo histInfo{};
	for (const auto data : imageDatas)
	{
		++histInfo.histogramme[data];
	}

#if LOG_HISTO
	Utils::LogHistogramme("Log histo value", histInfo.histogramme);
#endif

	return histInfo; // https://azer.io/image-histogram/ to check if it's correct
}

HistInfo::HistogramType HistogrammeAlgorithms::CalculHistogrammeCumulatif(const HistInfo::HistogramType& baseHisto)
{
	size_t i = 0;
	HistInfo::HistogramType histoCumulatif{};

	histoCumulatif[i++] = 0;
	for (; i < baseHisto.size(); ++i)
	{
		histoCumulatif[i] = histoCumulatif[i - 1] + baseHisto[i];
	}

#if LOG_HISTO_CUMUL
	Utils::LogHistogramme("Log histo cumul value", histoCumulatif);
#endif

	return histoCumulatif;
}

void HistogrammeAlgorithms::ApplyEqualisation(HistInfo::HistogramType& histo, const size_t imageSize)
{
	static constexpr size_t MAX_VALUE = HistInfo::HISTOGRAMME_SIZE - 1; // K - 1

	assert(imageSize > 0 && "Image size cannot be 0");

	for (auto& histoData : histo)
	{
		histoData = histoData * MAX_VALUE / imageSize;
	}

#if LOG_HISTO_EQUALISED
	Utils::LogHistogramme("Log histo equalised value", histo);
#endif
}

ImageInfo HistogrammeAlgorithms::CreateEqualisedImage(const ImageInfo& baseImageInfo,
                                                      const HistInfo::HistogramType& equalisedHisto)
{
	// https://pinetools.com/equalize-image to check if it's correct
	return Utils::ApplyTranformation(baseImageInfo, [&](const ImageInfo::DataType& color)
	{
		return static_cast<ImageInfo::DataType>(equalisedHisto[color]);
	});
}
