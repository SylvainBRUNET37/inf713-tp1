#include "Utils.h"

#include <format>
#include <fstream>
#include <iostream>

void Utils::ConsoleLogHistogramme(const std::string_view message, const HistInfo& histInfo)
{
	using namespace std;

	cout << "------------------------------------------------\n";
	cout << format("{}:\n", message);
	cout << format("Min: {}\n", histInfo.min);
	cout << format("Max: {}\n", histInfo.max);
	cout << format("Mean: {}\n", histInfo.moyenne);
	cout << format("Variance: {}\n", histInfo.variance);
	cout << format("Mode: {}\n", histInfo.mode);

	cout << "Histogramme:\n";
	for (size_t i = 0; const auto histoValue : histInfo.histogramme)
	{
		cout << format("  Grey channel {} value: {}\n", i++, histoValue);
	}
	cout << "------------------------------------------------\n";
}

void Utils::FileLogHistogramme(const char* const filename, const HistInfo& histInfo)
{
	std::ofstream outputFile{filename};

	outputFile << static_cast<unsigned int>(histInfo.min) << ","
		<< static_cast<unsigned int>(histInfo.max) << ","
		<< static_cast<unsigned int>(histInfo.moyenne) << ","
		<< static_cast<unsigned int>(histInfo.variance) << ","
		<< static_cast<unsigned int>(histInfo.mode);

	for (const auto data : histInfo.histogramme)
	{
		outputFile << "," << data;
	}

	outputFile << "\n";
}

std::span<uint8_t> Utils::CreateImageDataSpan(const ImageInfo& imageInfo)
{
	const size_t imageSize = imageInfo.GetDataSize();

	return {imageInfo.data, imageSize};
}
