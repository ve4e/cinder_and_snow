#ifndef GM_H
#define GM_H

#include "map/HexView.h"
#include "Tracer.h"
#include "map/EMap.h"
#include "map/HexController.h"
#include "map/Hex.h"
#include "map/HexView.h"
#include "characters/Character.h"
#include <list>
#include <utility>
#include <memory>
#include <QTimer>

using namespace std;

class Character;
class Hex;
class EMap;

class Cell
{
public:
    Cell(){}

    void setHero(shared_ptr<Character> hero) {hero_ = hero;}
    void setMonster(shared_ptr<Character> monster) {monster_ = monster;}
    shared_ptr<Character> hero() const {return hero_;}
    bool isFree() const {return !(hero_.get() != nullptr /*|| hasBuilding()*/ /*|| hasMob()*/);}
    void moveHero(Cell &cell);

    void setHex(shared_ptr<Hex> hex){hex_ = hex;}
    shared_ptr<Hex> hex() const {return hex_;}

private:
    shared_ptr<Character> hero_ = nullptr;
    shared_ptr<Character> monster_ = nullptr;
    shared_ptr<Hex> hex_ = nullptr;
};

class GM : public QObject
{
    Q_OBJECT

public:
    GM(QObject *parent = nullptr);

    void setMap(const EMap& map);

    bool isFreeCell(const std::pair<int, int>& hex) const;
    std::vector <std::pair<int, int> > trace(int ax, int ay, int bx, int by);

    vector<shared_ptr<Character> > nearHeroes(uint R) const;
    //vector<shared_ptr<EBuilding> > nearBuildings(uint R) const;
    //vector<shared_ptr<EMob> > nearMobs(uint R) const;

    bool moveHero(pair<int, int> hexFrom, pair<int, int> hexTo);
    //bool moveMob(shared_ptr<const EMob> mob, pair<int, int> hex);

signals:
//    void heroWasActivated(shared_ptr<const Hero>);
    //void buildingWasActivated(const EBuilding *);
    //void mobWasActivated(const EMob *);

public slots:
    void handleClick(int x, int y);

private slots:
    void makeTick();

private:

    Tracer tracer_;
    QTimer timer_;

    shared_ptr<Character> playerHero_;
    vector<shared_ptr<Character> > heroes_;  //FIXME: useless?
    vector<shared_ptr<Character> > monsters_;//FIXME: useless?
    vector<vector<Cell> > region_;

    shared_ptr<Hex> activeCell_;
};

#endif // CONTROLLER_H



