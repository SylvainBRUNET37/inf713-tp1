#ifndef UTILS_H
#define UTILS_H

#include <span>
#include <string_view>
#include <ranges>

#include "Data.h"

namespace Utils
{
	[[maybe_unused]] void LogHistogramme(std::string_view message, const HistInfo::HistogramType& histo);

	[[nodiscard]] std::span<ImageInfo::value_type> CreateImageDataSpan(const ImageInfo& imageInfo);
}

#endif
