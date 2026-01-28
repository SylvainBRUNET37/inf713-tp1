/////////////////////////////////////////////////////////
// NOM: Sylvan Brunet
// INF 713 - TP 1 
// A mettre le 27 Fevrier 2026
/////////////////////////////////////////////////////////

#include <print>

#include "Data.h"
#include "ImageIO.h"
#include "HistogrammeAlgorithms.h"

using namespace std;
using HistogramType = HistInfo::HistogramType;

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
	const HistInfo baseHistInfo = HistogrammeAlgorithms::CalculHistogramme(imageInfo);

	// 2 - Faite une copie des donnees et travailler sur cette copie pour l'etape 3.
	const HistInfo histInfo = baseHistInfo;

	// 3a - Calculer l'histogramme cumulatif a partir de l'image orignal en sRGB
	HistogramType histoCumulatif = HistogrammeAlgorithms::CalculHistogrammeCumulatif(baseHistInfo.histogramme);

	// 3b - Appliquer une transformation d'egalisation d'histogramme.
	const size_t imageSize = static_cast<size_t>(imageInfo.tailleX) * static_cast<size_t>(imageInfo.tailleY);
	HistogrammeAlgorithms::ApplyEgalisation(histoCumulatif, imageSize);

	// 3c - Sauvegarder l'image sous le nom de "barbara_equalized.png"

	// 4a - A partir de l'image original, faite une transformation de sRGB a lineaire (faite la vraie transformation)

	// 4b - En lineaire, appliquer une transformation constraste f(a) = a * 1.2 sur le result de 4a

	// 4c - A partir de 4b, en lineaire, appliquer une transformation brillance f(a) = a - 10

	// 4d - Convertir le result de 4c en sRGB.

	// 4e - Sauvegarder le result de 4d sous le nom "barbara_modified.png"

	return 0;
}
