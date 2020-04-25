#ifndef EMAP_H
#define EMAP_H

#include "characters/Character.h"
#include "map/Hex.h"

#include <memory>
#include <vector>

using namespace std;

class Character;
class Hex;


class EMap
{
public:
    class Info
    {
    public:
        void setWidth(uint width) {width_ = width;}
        uint width() const {return width_;}

        void setHeight(uint height) {height_ = height;}
        uint height() const {return height_;}

        void setName(const string &name) {name_ = name;}
        string name() const {return name_;}

        void setDescription(const string &description) {description_ = description;}
        string description() const {return description_;}

    private:
        uint width_ = 0;
        uint height_ = 0;

        std::string name_;
        std::string description_;
    };

    void setInfo(const Info & info){info_ = info;}
    Info info() const {return info_;}

    void setHeroes(const vector<shared_ptr<Character> > &heroes){heroes_ = heroes;}
    vector<shared_ptr<Character> > heroes() const {return heroes_;}

    void setMonsters(const vector<shared_ptr<Character> > &monsters){monsters_ = monsters;}
    vector<shared_ptr<Character> > monsters() const {return monsters_;}

    void setHexMtrx(const vector<vector<shared_ptr<Hex> > > &hexMtrx){hexMtrx_ = hexMtrx;}
    vector<vector<shared_ptr<Hex> > > hexMtrx() const {return hexMtrx_;}
private:
    Info info_;

    vector<shared_ptr<Character> > heroes_;
    vector<shared_ptr<Character> > monsters_;
    vector<vector<shared_ptr<Hex> > > hexMtrx_;
};


#endif // EMAP_H



