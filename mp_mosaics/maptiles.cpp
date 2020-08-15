/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    vector<Point<3>> theTilePoints;
    size_t s = theTiles.size();
    for(size_t i = 0; i < s; i++){
        auto avcolor = theTiles[i].getAverageColor();
        auto avcolorPoint = convertToXYZ(avcolor);
        theTilePoints.push_back(avcolorPoint);
    }
    KDTree<3> tilesTree = KDTree<3>(theTilePoints);
    int r = theSource.getRows();
    int c = theSource.getColumns();
    MosaicCanvas * MC = new MosaicCanvas(r,c);
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            auto regionColor = theSource.getRegionColor(i, j);
            auto regionColorPoint = convertToXYZ(regionColor);
            auto tileAvColor = tilesTree.findNearestNeighbor(regionColorPoint);
            for(size_t k = 0; k < s; k++){
                auto avcolor = theTiles[k].getAverageColor();
                auto avcolorPoint = convertToXYZ(avcolor);
                if(avcolorPoint == tileAvColor){
                    MC->setTile(i, j, &theTiles[k]);
                    k = s;
                }
            }
        }
    }
    //delete tilesTree;
    return MC;
}

