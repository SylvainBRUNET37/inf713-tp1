#ifndef UTILS_H
#define UTILS_H

#include <span>
#include <string_view>

#include "Data.h"

namespace Utils
{
	[[maybe_unused]] void ConsoleLogHistogramme(std::string_view message, const HistInfo& histInfo);
	[[maybe_unused]] void FileLogHistogramme(const char* filename, const HistInfo& histInfo);

	[[nodiscard]] std::span<uint8_t> CreateImageDataSpan(const ImageInfo& imageInfo);
}

#endif
