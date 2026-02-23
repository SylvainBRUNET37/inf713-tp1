#ifndef UTILS_H
#define UTILS_H

#include <string_view>

#include "Data.h"

namespace Utils
{
	[[maybe_unused]] void ConsoleLogHistogramme(std::string_view message, const HistInfo& histInfo);
	[[maybe_unused]] void FileLogHistogramme(const char* filename, const HistInfo& histInfo);
}

#endif
