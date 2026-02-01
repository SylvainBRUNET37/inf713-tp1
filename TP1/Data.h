#ifndef DATA_H
#define DATA_H

#include <array>
#include <cstdint>

struct HistInfo
{
	static constexpr size_t HISTOGRAMME_SIZE = 256;
	static constexpr size_t MAX_COLOR_VALUE = HISTOGRAMME_SIZE - 1;
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
	using value_type = uint8_t;

	value_type* data{};
	int tailleX{}; // nb de pixel en X
	int tailleY{}; // nb de pixel en Y
	int nbCanaux{}; // nb de canaux par pixel. Ici 1, parce que l'image est en noir et blanc

	ImageInfo() = delete;
	~ImageInfo() noexcept;

	ImageInfo(value_type* data, int tailleX, int tailleY, int nbCanaux);

	ImageInfo(const ImageInfo& other);
	ImageInfo& operator=(const ImageInfo&) = delete;

	ImageInfo(ImageInfo&&) = delete;
	ImageInfo& operator=(ImageInfo&&) = delete;

	[[nodiscard]] size_t GetDataSize() const noexcept { return static_cast<size_t>(tailleX) * tailleY * nbCanaux; }
};

#endif
