#ifndef DATA_H
#define DATA_H

#include <array>
#include <cstdint>

struct HistInfo
{
	static constexpr size_t HISTOGRAMME_SIZE = 256;
	using HistogramType = std::array<uint32_t, HISTOGRAMME_SIZE>;

	HistogramType histogramme;
	float moyenne;
	float variance;
	uint8_t min;
	uint8_t max;
	uint8_t mode;
};

struct ImageInfo
{
	using DataType = uint8_t;

	DataType* data{};
	int tailleX{}; // nb de pixel en X
	int tailleY{}; // nb de pixel en Y
	int nbCanaux{}; // nb de canaux par pixel. Ici 1, parce que l'image est en noir et blanc
};

#endif