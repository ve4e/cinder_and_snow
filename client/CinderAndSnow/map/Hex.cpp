#include "map/Hex.h"

Hex::Hex(int x, int y, Surface surface)
{
    x_ = x;
    y_ = y;
    setSurface(surface);
}

void Hex::setSurface(Surface surface)
{
    surface_ = surface;

    std::vector<Surface> inpassable = {
        Surface::Sea, Surface::Ocean, Surface::IceSea,
        Surface::Mountain,  Surface::DesertMountain, Surface::GrasslandForestHill
    };
    if(std::find(inpassable.begin(), inpassable.end(), surface_) != inpassable.end()){
        passability_ = -1;
    }
    else{
        passability_ = 1;
    }
}
