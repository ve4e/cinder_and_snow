#ifndef MAPRW_H
#define MAPRW_H

#include "map/EMap.h"
#include "GM.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QJsonArray>
#include <QJsonParseError>
#include <QDebug>

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

class MapRW
{
public:

    static void write(const std::string& fileName, const EMap& map)
    {
        std::ofstream outfile (fileName);

        outfile << "[MAP]\n";
        outfile << "name: " << map.info().name() << "\n";
        outfile << "description: " << map.info().description() << "\n";
        outfile << "size: " << map.info().width() << " " << map.info().height() << "\n";
        outfile << "cells:";
//        for(const auto &s : map.surfaceMtrx){
//            outfile << " " << (int)s->type;
//        }
        for(const auto &row : map.hexMtrx()){
            for(const auto & hex : row){
                outfile << " " << static_cast<int>(hex->surface());
            }
        }
        outfile << "\n";
        /*
        for(const auto &u : map.users()){
            outfile << "[USER]" << "\n";
            outfile << "name: " << u->name() << "\n";
            for(auto h : u->heroes()){
                outfile << "[HERO]" << "\n";
                outfile << "type: " << (int)h->type() << "\n";
                outfile << "name: " << h->name() << "\n";
                outfile << "pos: " << h->position().first << " " << h->position().second << "\n";
                outfile << "[@HERO]" << "\n";
            }
            outfile << "[@USER]" << "\n";
        }
        */
    }

    /*
    static EMap read(const std::string& fileName)
    {
        EMap map;

        std::ifstream infile (fileName);
        std::string line;
        std::string key;
        ReadMode readMode = ReadMode::None;

//        shared_ptr<EUser> user;
        shared_ptr<Hero> hero;
        EMap::Info mapInfo;

        while (std::getline(infile, line)){
            std::istringstream iss(line);
            iss >> key;
            if(key == "[MAP]"){
                readMode = ReadMode::Map;
                continue;
            }
            else if(key == "[HERO]"){
                readMode = ReadMode::Hero;
                hero = make_shared<Hero>();
                continue;
            }
            else if(key == "[@HERO]"){
                //user->addHero(hero);
                continue;
            }


            if(readMode == ReadMode::Map){
                if(key == "name:"){
                    mapInfo.setName(get_word(iss));
                }
                else if(key == "description:"){
                    mapInfo.setDescription(get_word(iss));
                }
                else if(key == "size:"){
                    mapInfo.setHeight(get_num(iss));
                    mapInfo.setWidth(get_num(iss));

                }
                else if(key == "cells:"){
                    vector<vector<shared_ptr<ESurface> > > surfaceMtrx(mapInfo.width(), std::vector<shared_ptr<ESurface> >(mapInfo.height()));\
                    for(uint i = 0; i < mapInfo.width() && !iss.eof(); ++i){
                        for(uint j = 0; j < mapInfo.height() && !iss.eof(); ++j){
                            surfaceMtrx[i][j] = make_shared<ESurface>((ESurface::Type) get_num(iss));
                        }
                    }
                    map.setSurfaceMtrx(surfaceMtrx);
                }
            }
            else if(readMode == ReadMode::User){
                if(key == "name:"){
                    //user->setName(get_word(iss));
                }
            }
            else if(readMode == ReadMode::Hero){
                if(key == "name:"){
                    hero->setName(get_word(iss));
                }
                else if(key == "type:"){
                    hero->setType(static_cast<Hero::Type>(get_num(iss)));
                }
                else if(key == "pos:"){
                    int x = get_num(iss);
                    int y = get_num(iss);
                    hero->setPosition(pair<int, int>(x,y));
                }
            }
        }

        map.setInfo(mapInfo);
        return map;
    }
    */

    static EMap read(const std::string& fileName)
    {
        QFile file(QString::fromStdString(fileName));
        if(!file.open(QIODevice::ReadOnly)){
            std::cout << "Can't open file: " << fileName << std::endl;
        }

        EMap::Info mapInf;
        QJsonParseError* jError = new QJsonParseError;
        auto jDoc = QJsonDocument::fromJson(file.readAll(), jError);
        auto jObject = jDoc.object();

        // area
        mapInf.setName(jObject["mapInfo"].toObject()["name"].toString().toStdString());
        mapInf.setDescription(jObject["mapInfo"].toObject()["description"].toString().toStdString());
        mapInf.setWidth(jObject["mapInfo"].toObject()["width"].toInt());
        mapInf.setHeight(jObject["mapInfo"].toObject()["height"].toInt());

        auto cells = jObject["area"].toArray().toVariantList();
        vector<vector<shared_ptr<Hex> > > hexMtrx(mapInf.width(), std::vector<shared_ptr<Hex> >(mapInf.height()));
        uint ind = 0;
        for(uint i = 0; i < mapInf.width(); ++i){
            for(uint j = 0; j < mapInf.height(); ++j){
                hexMtrx[i][j] = std::make_shared<Hex>(Hex(i, j, static_cast<Surface>(cells[ind].toInt())));
                ++ind;
            }
        }

        // units
        vector<shared_ptr<Character> > heroes;
        for(auto c : jObject["heroes"].toArray()){
            Character hero;
            hero.setId(c.toObject()["ind"].toInt());
            hero.setName(c.toObject()["name"].toString().toStdString());
            hero.setPosition(pair<int, int>(c.toObject()["x"].toInt(), c.toObject()["y"].toInt()));

            vector<int> units;
            for(auto u: c.toObject()["units"].toArray()){
                units.push_back(u.toInt());
            }
            hero.setUnits(units);

            heroes.push_back(make_shared<Character>(hero));
        }

        // monsters
        vector<shared_ptr<Character> > monsters;
        for(auto c : jObject["monsters"].toArray()){
            Character monster;
            monster.setId(c.toObject()["ind"].toInt());
            monster.setType(static_cast<CharacterType>(c.toObject()["type"].toInt()));
            monster.setName(c.toObject()["name"].toString().toStdString());
            monster.setPosition(pair<int, int>(c.toObject()["x"].toInt(), c.toObject()["y"].toInt()));

            vector<int> units;
            for(auto u: c.toObject()["units"].toArray()){
                units.push_back(u.toInt());
            }
            monster.setUnits(units);
            monsters.push_back(make_shared<Character>(monster));
        }

        EMap emap;
        emap.setHexMtrx(hexMtrx);
        emap.setHeroes(heroes);
        emap.setMonsters(monsters);
        emap.setInfo(mapInf);

        return emap;
    }


private:
    static std::string get_word(std::istringstream &iss)
    {
        string str;
        iss >> str;
        return str;
    }

    static int get_num(std::istringstream &iss)
    {
        int num{0};
        iss >> num;
        return num;
    }

    enum class ReadMode {None, Map, Cell, User, Hero};
};

#endif // MAPRW_H
