#include "ImageIO.h"

#include <cassert>

#include "stb_image_write.h"
#include "stb_image.h"

#include "Data.h"

bool ImageIO::LireImage(const char* filename, ImageInfo* outImageInfo)
{
	assert(filename);
	assert(outImageInfo);

	// Nombre de canaux desirer. Si la valeur est 0, retourne le nombre de
	// canaux dans l'image.
	constexpr int nbCanauxDesire = 0;
	outImageInfo->data = stbi_load(filename, &outImageInfo->tailleX, &outImageInfo->tailleY,
	                               &outImageInfo->nbCanaux, nbCanauxDesire);

	return outImageInfo->data ? true : false;
}

bool ImageIO::EcrireImage(const ImageInfo& imageInfo, const char* filename)
{
	assert(filename);

	constexpr int byteParPixel = 1;
	// Taille en byte d 'une ligne horizontale de l' image
	const int strideEnByte = byteParPixel * imageInfo.tailleX;
	return stbi_write_png(filename, imageInfo.tailleX,
	                      imageInfo.tailleY, imageInfo.nbCanaux,
	                      imageInfo.data, strideEnByte);
}
