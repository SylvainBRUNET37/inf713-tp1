#include "HistogrammeAlgorithms.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>

#include "Data.h"
#include "Utils.h"

#define LOG_HISTO true
#define LOG_HISTO_CUMUL true

namespace
{
	[[nodiscard]] float ComputeMean(const HistInfo::HistogramType& histogramme)
	{
		float meanSum = 0.0f;
		float count = 0.0f;

		for (size_t i = 0; i < HistInfo::HISTOGRAMME_SIZE; ++i)
		{
			const float histoData = static_cast<float>(histogramme[i]);

			meanSum += static_cast<float>(i) * histoData;
			count += histoData;
		}

		return meanSum / count;
	}

	[[nodiscard]] float ComputeVariance(const HistInfo::HistogramType& histogramme, const float mean)
	{
		float varianceSum = 0.0f;
		float count = 0.0f;

		for (size_t i = 0; i < HistInfo::HISTOGRAMME_SIZE; ++i)
		{
			const float histoData = static_cast<float>(histogramme[i]);
			const float meanDiff = static_cast<float>(i) - mean;

			varianceSum += histoData * meanDiff * meanDiff;
			count += histoData;
		}

		return varianceSum / count;
	}

	[[nodiscard]] uint8_t ComputeMin(const HistInfo::HistogramType& histogramme)
	{
		for (size_t i = 0; i < HistInfo::HISTOGRAMME_SIZE; ++i)
		{
			if (histogramme[i] > 0)
			{
				return static_cast<uint8_t>(i);
			}
		}

		return 0;
	}

	[[nodiscard]] uint8_t ComputeMax(const HistInfo::HistogramType& histogramme)
	{
		for (size_t i = HistInfo::HISTOGRAMME_SIZE; i-- > 0;)
		{
			if (histogramme[i] > 0)
			{
				return static_cast<uint8_t>(i);
			}
		}

		return 0;
	}

	void FillHistInfoMetaData(HistInfo& histInfo)
	{
		const auto& histogramme = histInfo.histogramme;
		histInfo.moyenne = ComputeMean(histogramme);
		histInfo.variance = ComputeVariance(histogramme, histInfo.moyenne);
		histInfo.min = ComputeMin(histogramme);
		histInfo.max = ComputeMax(histogramme);

		const auto maxIt = std::ranges::max_element(histogramme);
		histInfo.mode = static_cast<uint8_t>(distance(begin(histogramme), maxIt));
	}
}

HistInfo HistogrammeAlgorithms::CalculHistogramme(const ImageInfo& imageInfo)
{
	HistInfo histInfo{};
	for (const auto data : imageInfo.pixels)
	{
		++histInfo.histogramme[data];
	}

	FillHistInfoMetaData(histInfo);

#if LOG_HISTO
	Utils::ConsoleLogHistogramme("Log histo value", histInfo);
	Utils::FileLogHistogramme("data/hist_base.csv", histInfo);
#endif

	return histInfo;
}

HistInfo HistogrammeAlgorithms::CalculHistogrammeCumulatif(const HistInfo::HistogramType& baseHisto)
{
	size_t i = 0;
	HistInfo histInfo{};

	histInfo.histogramme[i++] = baseHisto[0];
	for (; i < baseHisto.size(); ++i)
	{
		histInfo.histogramme[i] = histInfo.histogramme[i - 1] + baseHisto[i];
	}

	FillHistInfoMetaData(histInfo);

#if LOG_HISTO_CUMUL
	Utils::ConsoleLogHistogramme("Log histo cumul value", histInfo);
	Utils::FileLogHistogramme("data/hist_cumul.csv", histInfo);
#endif

	return histInfo;
}

void HistogrammeAlgorithms::EqualiseImage(ImageInfo& baseImageInfo,
                                          const HistInfo::HistogramType& equalisedHisto)
{
	const auto imageSize = baseImageInfo.GetDataSize();
	for (auto& imageData : baseImageInfo.pixels)
	{
		imageData = static_cast<uint8_t>(equalisedHisto[imageData] * HistInfo::MAX_COLOR_VALUE / imageSize);
	}
}

#undef LOG_HISTO_CUMUL
#undef LOG_HISTO
