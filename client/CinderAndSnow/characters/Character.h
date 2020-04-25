#ifndef HERO_H
#define HERO_H

#include "CharacterController.h"
#include "characters/CharacterView.h"
#include <iostream>

using namespace std;

enum class CharacterType {Troll = 1, Human = 2, Elf = 3, Dendroid = 4, Gin = 5, Sith = 6};

class Character
{
public:
    Character()
    {}

    void setId(int id) {id_ = id;}
    int id() const {return id_;}

    string name() const {return name_;}
    void setName(const string& name) {name_ = name;}

    void setType(CharacterType type) {type_ = type;}  // deprecated
    CharacterType type() const {return type_;}

    void setPosition(const pair<int, int> &position) {position_ = position;}
    pair<int, int> position() const {return position_;}

    void setUnits(const vector<int> &units){units_ = units;}
    vector<int> units() const {return units_;}

    void setController(shared_ptr<CharacterController> controller){controller_ = controller;}
    shared_ptr<CharacterController> controller() const {return controller_;}

private:
    int id_ = 0;
    string name_ = "noname";
    CharacterType type_ = CharacterType::Elf;
    pair<int, int> position_ = {0,0};

    vector<int> units_;

    shared_ptr<CharacterController> controller_ = nullptr;
};

#endif


