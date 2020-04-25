#ifndef HERO_CONTROLLER_H
#define HERO_CONTROLLER_H

#include "characters/Character.h"
#include "characters/CharacterView.h"
#include "map/EMap.h"
#include "map/Hex.h"
#include "map/HexView.h"
#include "map/HexController.h"
#include "GM.h"
#include <QDebug>
#include <memory>

using namespace std;

class GM;
class Character;
class CharacterView;

class CharacterController
{
public:
    void setView(shared_ptr<CharacterView> view);
    void setModel(shared_ptr<Character> model){model_ = model;}
    void setGm(shared_ptr<GM> Gm)
    {
        Gm_ = Gm;
    }

    void tick();
    void processTarget(int x, int y); // FIXME: rename

private:
    shared_ptr<GM> Gm_ = nullptr;
    shared_ptr<CharacterView> view_ = nullptr;
    shared_ptr<Character> model_ = nullptr;

    bool movement_ = false;
    std::vector <std::pair<int, int> > way_;
    int wayIndex_ = 0;

    void makeStep();
};

#endif
