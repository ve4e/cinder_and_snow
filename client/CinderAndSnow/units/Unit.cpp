#include "Unit.h"

#include <QFile>
#include <QUrl>

#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


map<int, Unit*> Unit::unitsCollection_ = {};
void Unit::loadUnitsCollections()
{
    QFile file(":/units/json/units.json");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument document = QJsonDocument::fromJson(jsonData);
    QJsonArray jsonUnits = document.array();
    for(auto const & jsonUnit : jsonUnits){
        Unit* unit = new Unit;
        unit->setInd(jsonUnit.toObject().value("id").toInt());
        unit->setName(jsonUnit.toObject().value("name").toString());
        unit->setImg(jsonUnit.toObject().value("img").toString());
        unit->setLvl(jsonUnit.toObject().value("lvl").toInt());
        unit->setHealth(jsonUnit.toObject().value("health").toInt());
        unit->setAttack(jsonUnit.toObject().value("attack").toInt());
        unit->setShooting(jsonUnit.toObject().value("shooting").toInt());
        unit->setShootingDistance(jsonUnit.toObject().value("shooting_distance").toInt());
        unit->setMovement(jsonUnit.toObject().value("movement").toInt());

        unitsCollection_.insert({unit->ind(), unit});
    }
}

Unit* Unit::getUnit(int id)
{
    if(unitsCollection_.empty()){
        loadUnitsCollections();
    }

    try {
        return unitsCollection_.at(id);
    }
    catch (const std::out_of_range& oor) {
      qDebug() << "Out of Range error: " << oor.what();
      return nullptr;
    }
}
