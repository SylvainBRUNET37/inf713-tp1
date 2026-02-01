/////////////////////////////////////////////////////////
// NOM: Sylvan Brunet
// INF 713 - TP 1 
// A mettre le 27 Fevrier 2026
/////////////////////////////////////////////////////////

#include <format>
#include <iostream>

#include "stb_image.h"

#include "Data.h"
#include "ImageIO.h"
#include "HistogrammeAlgorithms.h"
#include "ImageTransformationAlgorithms.h"

int main()
{
	using namespace std;

	/////////////////////////////////////////////////////////
	// Charger une image en memoire
	/////////////////////////////////////////////////////////
	static constexpr auto INPUT_FILE_NAME = "barbara.png";
	const auto imageInfo = ImageIO::LireImage(INPUT_FILE_NAME);
	if (not imageInfo)
	{
		cerr << format("Erreur de lecture de l'image {}", INPUT_FILE_NAME);
		return EXIT_FAILURE;
	}

	/////////////////////////////////////////////////////////
	// Traitement de l'image (1)
	/////////////////////////////////////////////////////////

	{
		// 1 - Calculer l'histogramme de la photos. implementer la fonction suivante.
		const HistInfo histInfo = HistogrammeAlgorithms::CalculHistogramme(*imageInfo);

		// 2 - Faite une copie des donnees et travailler sur cette copie pour l'etape 3.
		const ImageInfo equalisedImage = *imageInfo;

		// 3a - Calculer l'histogramme cumulatif a partir de l'image orignal en sRGB
		HistInfo histoCumulatif = HistogrammeAlgorithms::CalculHistogrammeCumulatif(histInfo.histogramme);

		// 3b - Appliquer une transformation d'egalisation d'histogramme.
		HistogrammeAlgorithms::ApplyEqualisation(histoCumulatif, equalisedImage.GetDataSize());

		// 3c - Sauvegarder l'image sous le nom de "barbara_equalized.png"
		static constexpr auto EQUALISED_OUTPUT_FILE_NAME = "barbara_equalized.png";
		HistogrammeAlgorithms::EqualiseImage(equalisedImage, histoCumulatif.histogramme);
		if (not ImageIO::EcrireImage(equalisedImage, EQUALISED_OUTPUT_FILE_NAME))
		{
			cerr << format("Failed to write equalised image in file {}\n", EQUALISED_OUTPUT_FILE_NAME);
			return EXIT_FAILURE;
		}
	}

	/////////////////////////////////////////////////////////
	// Traitement de l'image (2)
	/////////////////////////////////////////////////////////

	{
		// 4a - A partir de l'image original, faite une transformation de sRGB a lineaire (faite la vraie transformation)
		auto linearisedColors = ImageTransformationAlgorithms::ComputeLinearisedColors(*imageInfo);

		// 4b - En lineaire, appliquer une transformation constraste f(a) = a * 1.2 sur le result de 4a
		static constexpr double CONTRAST = 1.2;
		for (auto& color : linearisedColors)
			color *= CONTRAST;

		// 4c - A partir de 4b, en lineaire, appliquer une transformation brillance f(a) = a - 10
		static constexpr double SHINE = -10.0 / HistInfo::MAX_COLOR_VALUE;
		for (auto& pixel : linearisedColors)
			pixel += SHINE;

		// 4d - Convertir le result de 4c en sRGB.
		ImageTransformationAlgorithms::ApplyCorrections(*imageInfo, linearisedColors);

		// 4e - Sauvegarder le result de 4d sous le nom "barbara_modified.png"
		static constexpr auto MODIFIED_OUTPUT_FILE_NAME = "barbara_modified.png";
		if (not ImageIO::EcrireImage(*imageInfo, MODIFIED_OUTPUT_FILE_NAME))
		{
			cerr << format("Failed to write modified image in file {}\n", MODIFIED_OUTPUT_FILE_NAME);
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}
