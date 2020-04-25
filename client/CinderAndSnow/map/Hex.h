#ifndef HEX_H
#define HEX_H

#include "map/HexController.h"

#include <vector>
#include<memory>
#include <algorithm>

enum class Surface
{
    Grassland = 1,
    GrasslandBoscage = 2,
    GrasslandForest = 3,
    GrasslandHill = 4,
    GrasslandForestHill = 5,
    Mountain = 6,
    Sea = 7,
    Ocean = 8,
    IceSea = 9,
    Plain = 10,
    PlainMarsh = 11,
    PlainForest = 12,
    Floodplain = 13,
    Snow = 14,
    SnowBoscage = 15,
    SnowForest = 16,
    SnowHill = 17,
    SnowForestHill = 18,
    Savanna = 19,
    Desert = 20,
    DesertHill = 21,
    DesertDune = 22,
    DesertMountain = 23
};

using namespace std;

class HexController;

class Hex
{
public:
    Hex(){}
    Hex(int x, int y, Surface surface);

    void setX(int x) {x_ = x;}
    int x() const {return x_;}

    void setY(int y) {y_ = y;}
    int y() const {return y_;}

    void setSurface(Surface surface);
    Surface surface() const {return surface_;}

    int passsability() {return passability_;}

    void setHexController(shared_ptr<HexController> hexController){hexController_ = hexController;}
    shared_ptr<HexController> hexController() {return hexController_;}


private:
    int x_ = -1;
    int y_ = -1;

    Surface surface_ = Surface::Grassland;
    int passability_ = 1;

    shared_ptr<HexController> hexController_;
};

#endif // HEX_H




















