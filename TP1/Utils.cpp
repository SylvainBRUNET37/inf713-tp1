#include "Utils.h"

#include <print>

void Utils::LogHistogramme(const std::string_view message, const HistInfo::HistogramType& histo)
{
	using namespace std;

	print("{}:\n", message);
	for (size_t i = 0; const auto histoValue : histo)
	{
		print("Grey channel {} value: {}\n", i++, histoValue);
	}
}

std::span<ImageInfo::DataType> Utils::CreateImageDataSpan(const ImageInfo& imageInfo)
{
	const size_t imageSize = imageInfo.GetDataSize();

	return std::span{ imageInfo.data, imageSize };
}
