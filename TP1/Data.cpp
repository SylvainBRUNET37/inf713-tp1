#include "Data.h"

#include <algorithm>

#include "stb_image.h"

ImageInfo::~ImageInfo() noexcept
{
	stbi_image_free(data);
}

ImageInfo::ImageInfo(uint8_t* data, const int tailleX, const int tailleY, const int nbCanaux)
	: data{data}, tailleX{tailleX}, tailleY{tailleY}, nbCanaux{nbCanaux}
{
}

ImageInfo::ImageInfo(const ImageInfo& other)
	: tailleX{other.tailleX},
	  tailleY{other.tailleY},
	  nbCanaux{other.nbCanaux}
{
	if (other.data)
	{
		const size_t size = GetDataSize();

		data = new uint8_t[size];
		std::copy_n(other.data, size, data);
	}
}
