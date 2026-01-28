#include "HistogrammeAlgorithms.h"

#include <cassert>
#include <print>
#include <span>
#include <ranges>

#include "Data.h"

#define LOG_HISTO false
#define LOG_HISTO_CUMUL false
#define LOG_HISTO_EQUALISED false

using namespace std;
using HistogramType = HistInfo::HistogramType;
using ImageDataType = ImageInfo::DataType;

//

namespace
{
	[[maybe_unused]] void LogHistogramme(const string_view message, const HistogramType& histo)
	{
		print("{}:\n", message);
		for (size_t i = 0; const auto histoValue : histo)
		{
			print("Grey channel {} value: {}\n", i++, histoValue);
		}
	}


	[[nodiscard]] span<ImageDataType> CreateImageDataSpan(const ImageInfo& imageInfo)
	{
		const size_t imageSize = static_cast<size_t>(imageInfo.tailleX) * static_cast<size_t>(imageInfo.tailleY);

		return span{imageInfo.data, imageSize};
	}
}

//

HistInfo HistogrammeAlgorithms::CalculHistogramme(const ImageInfo& imageInfo)
{
	const span imageDatas = CreateImageDataSpan(imageInfo);

	HistInfo histInfo{};
	for (const ImageDataType data : imageDatas)
	{
		++histInfo.histogramme[data];
	}

#if LOG_HISTO
	LogHistogramme("Log histo value", histInfo.histogramme);
#endif

	return histInfo; // https://azer.io/image-histogram/ to check if it's correct
}

HistInfo::HistogramType HistogrammeAlgorithms::CalculHistogrammeCumulatif(const HistInfo::HistogramType& baseHisto)
{
	size_t i = 0;
	HistogramType histoCumulatif{};

	histoCumulatif[i++] = 0;
	for (; i < baseHisto.size(); ++i)
	{
		histoCumulatif[i] = histoCumulatif[i - 1] + baseHisto[i];
	}

#if LOG_HISTO_CUMUL
	LogHistogramme("Log histo cumul value", histoCumulatif);
#endif

	return histoCumulatif;
}

void HistogrammeAlgorithms::ApplyEqualisation(HistInfo::HistogramType& histo, const size_t imageSize)
{
	static constexpr size_t MAX_VALUE = HistInfo::HISTOGRAMME_SIZE - 1; // K - 1

	assert(imageSize > 0 && "Image size cannot be 0");

	for (unsigned int& histoData : histo)
	{
		histoData = histoData * MAX_VALUE / imageSize;
	}

#if LOG_HISTO_EQUALISED
	LogHistogramme("Log histo equalised value", histo);
#endif
}

ImageInfo HistogrammeAlgorithms::CreateEqualisedImage(const ImageInfo& baseImageInfo,
                                                      const HistInfo::HistogramType& equalisedHisto)
{
	const ImageInfo equalisedImageInfo{baseImageInfo};

	const span baseImageDatas = CreateImageDataSpan(baseImageInfo);
	const span equalisedImageDatas = CreateImageDataSpan(baseImageInfo);

	for (auto [baseData, equalisedData] : views::zip(baseImageDatas, equalisedImageDatas))
	{
		equalisedData = static_cast<ImageDataType>(equalisedHisto[baseData]);
	}

	return equalisedImageInfo; // https://pinetools.com/equalize-image to check if it's correct
}
