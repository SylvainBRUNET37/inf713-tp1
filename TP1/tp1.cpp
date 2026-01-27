/////////////////////////////////////////////////////////
// NOM: 
// INF 713 - TP 1 
// A mettre le 29 mars 2021
/////////////////////////////////////////////////////////

#include "stb_image.h"
#include "stb_image_write.h"

#include <algorithm>
#include <array>

#include <cassert>
#include <cstdio>
#include <cstdlib>

using HistogramType = std::array<uint32_t, 256>;

struct HistInfo
{
    HistogramType histogramme;
    float moyenne;
    float variance;
    uint8_t min;
    uint8_t max;
    uint8_t mode;
};

struct ImageInfo
{
    ImageInfo() : data(nullptr) {}
    uint8_t* data;
    int tailleX;  // nb de pixel en X
    int tailleY;  // nb de pixel en Y
    int nbCanaux; // nb de canaux par pixel. Ici 1, parce que l'image est en
                  // noir et blanc
};

// LireImage
// en entree
// - filename : le nom du fichier a lire sur le disque.
// - imageInfo : recevera le contenue de l'image lue sur le disque
// en sortie
// 0 indique un echec. != 0 indique un succes.
int LireImage(const char* filename, ImageInfo* outImageInfo)
{
    assert(filename);
    assert(outImageInfo);

    // Nombre de canaux desirer. Si la valeur est 0, retourne le nombre de
    // canaux dans l'image.
    const int nbCanauxDesire = 0;
    outImageInfo->data = static_cast<uint8_t*>(
        stbi_load(filename, &outImageInfo->tailleX, &outImageInfo->tailleY,
                  &outImageInfo->nbCanaux, nbCanauxDesire));

    return outImageInfo->data ? 1 : 0;
}

// EcrireImage
// en entree
// - imageInfo : l'image a ecrire sur disque.
// - filename : le nom du fichier a ecrire sur le disque.
// en sortie
//  0 indique un echec. != 0 indique un succes.
int EcrireImage(const ImageInfo imageInfo, const char* filename)
{
    assert(filename);

    const int byteParPixel = 1;
    // Taille en byte d 'une ligne horizontale de l' image
    const int strideEnByte = byteParPixel * imageInfo.tailleX;
    return stbi_write_png(filename, imageInfo.tailleX,
                                     imageInfo.tailleY, imageInfo.nbCanaux,
                                     (void*)imageInfo.data, strideEnByte);
}

void CalculHistogramme(const ImageInfo& imageInfo, HistInfo* outHistogramme) {}

void CalculHistogrammeCumulatif(const ImageInfo& imageInfo, HistogramType* outHistogrammeCumulatif) {}

int main()
{
    /////////////////////////////////////////////////////////
    // Charger une image en memoire
    /////////////////////////////////////////////////////////
    const char* filename = "barbara.png";
    ImageInfo imageInfo;
    int result = LireImage(filename, &imageInfo);
    if (result == 0) {
    	std::printf("Erreur de lecture de l'image %s", filename);
    	std::exit(1);
    }


    /////////////////////////////////////////////////////////
    // Traitement de l'image
    /////////////////////////////////////////////////////////

    // 1 - Calculer l'histogramme de la photos. implementer la fonction suivante.
    HistInfo histInfo;
    CalculHistogramme(imageInfo, &histInfo);

    // 2 - Faite une copie des donnees et travailler sur cette copie pour l'etape 3.

    // 3a - Calculer l'histogramme cumulatif à partir de l'image orignal en sRGB
    HistogramType histoCumulatif;
    CalculHistogrammeCumulatif(imageInfo, &histoCumulatif);

    // 3b - Appliquer une transformation d'égalisation d'histogramme.

    // 3c - Sauvegarder l'image sous le nom de "barbara_equalized.png"

    // 4a - A partir de l'image original, faite une transformation de sRGB a lineaire (faite la vraie transformation)
    
    // 4b - En lineaire, appliquer une transformation constraste f(a) = a * 1.2 sur le result de 4a

    // 4c - A partir de 4b, en lineaire, appliquer une transformation brillance f(a) = a - 10

    // 4d - Convertir le result de 4c en sRGB.

    // 4e - Sauvegarder le result de 4d sous le nom "barbara_modified.png"
    
    return 0;
}
