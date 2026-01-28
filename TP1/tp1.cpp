/////////////////////////////////////////////////////////
// NOM: Sylvan Brunet
// INF 713 - TP 1 
// A mettre le 27 Fevrier 2026
/////////////////////////////////////////////////////////

#define LOG_IMAGE true

#include <print>
#include <span>

#include "Data.h"
#include "ImageIO.h"

using namespace std;
using HistogramType = HistInfo::HistogramType;

namespace
{
	// TODO: compute meta datas
	[[nodiscard]] HistInfo CalculHistogramme(const ImageInfo& imageInfo)
	{
		const size_t imageSize = static_cast<size_t>(imageInfo.tailleX) * static_cast<size_t>(imageInfo.tailleY);
		const span imageDatas{imageInfo.data, imageSize};

		HistInfo histInfo{};
		for (const auto data : imageDatas)
		{
			++histInfo.histogramme[data];
		}

#if LOG_IMAGE
		for (size_t i = 0; const auto histoValue : histInfo.histogramme)
			std::print("Grey channel {} value: {}\n", i++, histoValue);
#endif

		return histInfo; // https://azer.io/image-histogram/ to check if it's correct
	}

	void CalculHistogrammeCumulatif(const ImageInfo& imageInfo, HistogramType* outHistogrammeCumulatif)
	{
	}
}

int main()
{
	/////////////////////////////////////////////////////////
	// Charger une image en memoire
	/////////////////////////////////////////////////////////
	constexpr auto filename = "barbara.png";
	ImageInfo imageInfo;
	if (not ImageIO::LireImage(filename, &imageInfo))
	{
		std::print("Erreur de lecture de l'image {}", filename);
		return EXIT_FAILURE;
	}

	/////////////////////////////////////////////////////////
	// Traitement de l'image
	/////////////////////////////////////////////////////////

	// 1 - Calculer l'histogramme de la photos. implementer la fonction suivante.
	const HistInfo baseHistInfo = CalculHistogramme(imageInfo);

	// 2 - Faite une copie des donnees et travailler sur cette copie pour l'etape 3.
	const HistInfo histInfo = baseHistInfo;

	// 3a - Calculer l'histogramme cumulatif a partir de l'image orignal en sRGB
	HistogramType histoCumulatif;
	CalculHistogrammeCumulatif(imageInfo, &histoCumulatif);

	// 3b - Appliquer une transformation d'egalisation d'histogramme.

	// 3c - Sauvegarder l'image sous le nom de "barbara_equalized.png"

	// 4a - A partir de l'image original, faite une transformation de sRGB a lineaire (faite la vraie transformation)

	// 4b - En lineaire, appliquer une transformation constraste f(a) = a * 1.2 sur le result de 4a

	// 4c - A partir de 4b, en lineaire, appliquer une transformation brillance f(a) = a - 10

	// 4d - Convertir le result de 4c en sRGB.

	// 4e - Sauvegarder le result de 4d sous le nom "barbara_modified.png"

	return 0;
}
