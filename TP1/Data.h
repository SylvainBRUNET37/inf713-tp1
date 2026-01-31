#ifndef DATA_H
#define DATA_H

#include <array>
#include <cstdint>
#include <algorithm>

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

template <typename T>
struct ImageInfo
{
	using DataType = T;

	DataType* data{};
	int tailleX{}; // nb de pixel en X
	int tailleY{}; // nb de pixel en Y
	int nbCanaux{}; // nb de canaux par pixel. Ici 1, parce que l'image est en noir et blanc

	ImageInfo() = default;
	ImageInfo(const ImageInfo& other)
		: tailleX(other.tailleX),
		  tailleY(other.tailleY),
		  nbCanaux(other.nbCanaux)
	{
		if (other.data)
		{
			const size_t size = static_cast<size_t>(tailleX) * tailleY * nbCanaux;

			data = new DataType[size];
			std::copy(other.data, other.data + size, data);
		}
	}
};

#endif
