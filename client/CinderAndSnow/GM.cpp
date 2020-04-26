#include "GM.h"

#include <QDebug>

#include <vector>
#include <iostream>

void Cell::moveHero(Cell &cell)
{
    shared_ptr<Character> hero = nullptr;
    hero.swap(hero_);
    cell.setHero(hero);
}

GM::GM(QObject *parent):
    QObject(parent)
{
    timer_.setInterval(150);
    timer_.start();
    connect(&timer_, SIGNAL(timeout()), this, SLOT(makeTick()));
}

void GM::makeTick()
{
    for(const auto& h : heroes_){
        h->controller()->tick();
    }
}

void GM::setMap(const EMap& map)
{
    // passability

    const uint width = map.info().width();
    const uint height = map.info().height();
    vector<vector<int> > passabilityMtrx(width, vector<int>(height));

    for(uint i = 0; i < width; ++i){
        for(uint j = 0; j < height; ++j){
            passabilityMtrx[i][j] = map.hexMtrx()[i][j]->passsability();
        }
    }
    tracer_.setPassabilityMtrx(passabilityMtrx);

    // region
    for(uint i = 0; i < width; ++i){
        region_.push_back(vector<Cell>());
        for(uint j = 0; j < height; ++j){
            Cell cell;
            region_[i].push_back(cell);
        }
    }

    // heroes
    for(const auto & h : map.heroes()){
        region_[h->position().first][h->position().second].setHero(h);
        heroes_.push_back(h);
    }

    // mosters
    for(const auto & m : map.monsters()){
        region_[m->position().first][m->position().second].setMonster(m);
        monsters_.push_back(m);
    }

    // hexes
    for(uint i = 0; i < width; ++i){
        for(uint j = 0; j < height; ++j){
            region_[i][j].setHex(map.hexMtrx()[i][j]);
        }
    }

    // player hero
    if(!map.heroes().empty()){
        playerHero_ = map.heroes()[0];
    }
}

bool GM::isFreeCell(const std::pair<int, int> &hex) const
{
    return region_[hex.first][hex.second].isFree();
}

std::vector <std::pair<int, int> > GM::trace(int ax, int ay, int bx, int by)
{
    auto way = tracer_.trace(ax, ay, bx, by);

    auto errors = tracer_.lastErrors();
    for(const auto& e : errors){
        std::cout << tracer_.errorToText(e) << std::endl;
    }
    return way;
}

void GM::handleClick(int x, int y)
{

    if(activeCell_ == region_[x][y].hex()){
        playerHero_->controller()->processTarget(x, y);
    }
    else{
        if(activeCell_){
            activeCell_->hexController()->setHighlight(false);
        }

        activeCell_ = region_[x][y].hex();
        activeCell_->hexController()->setHighlight(true);
    }
}

bool GM::moveHero(pair<int, int> hexFrom, pair<int, int> hexTo)
{
    if(region_[hexTo.first][hexTo.second].isFree()){
        region_[hexFrom.first][hexFrom.second].hero()->setPosition(hexTo);
        //region_[hex.first][hex.second].setHero(hero);
        region_[hexFrom.first][hexFrom.second].moveHero(region_[hexTo.first][hexTo.second]);

        return true;
    }
    else{
        return false;
    }
}



















