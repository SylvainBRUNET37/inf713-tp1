#ifndef UTILS_H
#define UTILS_H

#include <span>
#include <string_view>
#include <ranges>

#include "Data.h"

namespace Utils
{
	[[maybe_unused]] void LogHistogramme(std::string_view message, const HistInfo::HistogramType& histo);
	[[nodiscard]] std::span<ImageInfo::DataType> CreateImageDataSpan(const ImageInfo& imageInfo);

	template <typename F>
	[[nodiscard]] ImageInfo ApplyTranformation(const ImageInfo& baseImageInfo, F&& transformation)
	{
		using namespace std;

		const ImageInfo newImageInfo{baseImageInfo};

		const span baseImageDatas = CreateImageDataSpan(baseImageInfo);
		const span newImageDatas = CreateImageDataSpan(baseImageInfo);

		for (auto [newImageData, baseImageData] : views::zip(baseImageDatas, newImageDatas))
		{
			newImageData = transformation(baseImageData);
		}

		return newImageInfo;
	}
}

#endif
