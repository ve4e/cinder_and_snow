#ifndef HEXCONTROLLER_H
#define HEXCONTROLLER_H

#include "characters/Character.h"
#include "map/HexView.h"
#include "map/Hex.h"
#include "characters/Character.h"
#include "GM.h"

#include <utility>
#include <memory>

using namespace std;

class Hero;
class HexView;
class Hex;

class GM;

class HexController
{
public:
    HexController();

    // GM

    void setGm(shared_ptr<GM> Gm){Gm_ = Gm;}

    // Hex item

    void setHexView(shared_ptr<HexView> hexView){hexView_ = hexView;}
    shared_ptr<HexView> hexView() const {return hexView_;}

    void setHex(shared_ptr<Hex> hex) {hex_ = hex;}
    shared_ptr<Hex> hex() const {return hex_;}

    void handleMousePress();

    void setHighlight(bool s);

private:
    shared_ptr<GM> Gm_ = nullptr;
    shared_ptr<HexView> hexView_ = nullptr;
    shared_ptr<Hex> hex_ = nullptr;
};

#endif // HEXCONTROLLER_H
