#include "HistogrammeAlgorithms.h"

#include <algorithm>
#include <cassert>
#include <numeric>
#include <span>
#include <ranges>

#include "Data.h"
#include "Utils.h"

#define LOG_HISTO true
#define LOG_HISTO_CUMUL true
#define LOG_HISTO_EQUALISED true

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
		
		assert(false && "Invalid image");
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

		assert(false && "Invalid image");
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
	const auto imageDatas = Utils::CreateImageDataSpan(imageInfo);

	HistInfo histInfo{};
	for (const auto data : imageDatas)
	{
		++histInfo.histogramme[data];
	}

	FillHistInfoMetaData(histInfo);

#if LOG_HISTO
	Utils::ConsoleLogHistogramme("Log histo value", histInfo);
	Utils::FileLogHistogramme("csv/hist_base.csv", histInfo);
#endif

	return histInfo;
}

HistInfo HistogrammeAlgorithms::CalculHistogrammeCumulatif(const HistInfo::HistogramType& baseHisto)
{
	size_t i = 0;
	HistInfo histInfo{};

	histInfo.histogramme[i++] = 0;
	for (; i < baseHisto.size(); ++i)
	{
		histInfo.histogramme[i] = histInfo.histogramme[i - 1] + baseHisto[i];
	}

	FillHistInfoMetaData(histInfo);

#if LOG_HISTO_CUMUL
	Utils::ConsoleLogHistogramme("Log histo cumul value", histInfo);
	Utils::FileLogHistogramme("csv/hist_cumul.csv", histInfo);
#endif

	return histInfo;
}

void HistogrammeAlgorithms::ApplyEqualisation(HistInfo& histInfo, const size_t imageSize)
{
	assert(imageSize > 0 && "Image size cannot be 0");

	for (auto& histoData : histInfo.histogramme)
	{
		histoData = histoData * HistInfo::MAX_COLOR_VALUE / imageSize;
	}

	FillHistInfoMetaData(histInfo);

#if LOG_HISTO_EQUALISED
	Utils::ConsoleLogHistogramme("Log histo equalised value", histInfo);
	Utils::FileLogHistogramme("csv/hist_eq.csv", histInfo);
#endif
}

void HistogrammeAlgorithms::EqualiseImage(const ImageInfo& baseImageInfo,
                                          const HistInfo::HistogramType& equalisedHisto)
{
	const std::span baseImageDatas = Utils::CreateImageDataSpan(baseImageInfo);

	for (auto& imageData : baseImageDatas)
	{
		imageData = static_cast<ImageInfo::value_type>(equalisedHisto[imageData]);
	}
}
