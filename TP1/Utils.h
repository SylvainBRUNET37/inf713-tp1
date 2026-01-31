#ifndef UTILS_H
#define UTILS_H

#include <span>
#include <string_view>
#include <ranges>

#include "Data.h"

namespace Utils
{
	[[maybe_unused]] void LogHistogramme(std::string_view message, const HistInfo::HistogramType& histo);

	template <typename T>
	[[nodiscard]] std::span<T> CreateImageDataSpan(const ImageInfo<T>& imageInfo)
	{
		const size_t imageSize = static_cast<size_t>(imageInfo.tailleX) * static_cast<size_t>(imageInfo.tailleY);

		return std::span{imageInfo.data, imageSize};
	}

	template <typename OutputImageDataType, typename BaseImageDataType, typename F>
	[[nodiscard]] ImageInfo<OutputImageDataType> ApplyTranformation(const ImageInfo<BaseImageDataType>& baseImageInfo,
	                                                                F&& transformation)
	{
		using namespace std;

		const ImageInfo<OutputImageDataType> newImageInfo{};

		const auto baseImageDatas = CreateImageDataSpan(baseImageInfo);
		const auto newImageDatas = CreateImageDataSpan(newImageInfo);

		for (auto&& [newImageData, baseImageData] : views::zip(baseImageDatas, newImageDatas))
		{
			newImageData = transformation(baseImageData);
		}

		return newImageInfo;
	}
}

#endif
