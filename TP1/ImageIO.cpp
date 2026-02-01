#include "ImageIO.h"

#include <cassert>

#include "stb_image_write.h"
#include "stb_image.h"

std::optional<ImageInfo> ImageIO::LireImage(const char* const filename)
{
	using namespace std;

	assert(filename);

	// Nombre de canaux desirer. Si la valeur est 0, retourne le nombre de canaux dans l'image.
	static constexpr int nbCanauxDesire = 0;
	int tailleX{}, tailleY{}, nbCanaux{};

	auto* const data = stbi_load(filename, &tailleX, &tailleY, &nbCanaux, nbCanauxDesire);

	return data ? optional<ImageInfo>{in_place, data, tailleX, tailleY, nbCanaux} : nullopt;
}

bool ImageIO::EcrireImage(const ImageInfo& imageInfo, const char* const filename)
{
	assert(filename);

	static constexpr int byteParPixel = 1;
	// Taille en byte d 'une ligne horizontale de l' image
	const int strideEnByte = byteParPixel * imageInfo.tailleX;
	return stbi_write_png(filename, imageInfo.tailleX,
	                      imageInfo.tailleY, imageInfo.nbCanaux,
	                      imageInfo.data, strideEnByte);
}
