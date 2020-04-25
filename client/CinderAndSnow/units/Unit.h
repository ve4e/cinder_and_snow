#ifndef UNIT_H
#define UNIT_H

#include <QString>
#include <QObject>
#include <QDebug>
#include <map>

using namespace std;


class Unit : public QObject
{
    Q_OBJECT
public:
    Unit(QObject* parent = 0){ Q_UNUSED(parent);}
    ~Unit(){}

    static Unit* getUnit(int id);

    Q_PROPERTY(int ind READ ind CONSTANT)
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString img READ img CONSTANT)
    Q_PROPERTY(int lvl READ lvl CONSTANT)
    Q_PROPERTY(int health READ health CONSTANT)
    Q_PROPERTY(int movement READ movement CONSTANT)
    Q_PROPERTY(int attack READ attack CONSTANT)
    Q_PROPERTY(int shooting READ shooting CONSTANT)
    Q_PROPERTY(int shootingDistance READ shootingDistance CONSTANT)

    int ind() const {return id_;}
    void setInd(int id) {id_ = id;}

    QString name() const {return name_;}
    void setName(const QString& name) {name_ = name;}

    QString img() const {return img_;}
    void setImg(const QString& img) {img_ = img;}

    int lvl() const {return lvl_;}
    void setLvl(int lvl) {lvl_ = lvl;}

    int health() const {return health_;}
    void setHealth(int health) {health_ = health;}

    int movement() const {return movement_;}
    void setMovement(int movement) {movement_ = movement;}

    int attack() const {return attack_;}
    void setAttack(int attack) {attack_ = attack;}

    int shooting() const {return shooting_;}
    void setShooting(int shooting) {shooting_ = shooting;}

    int shootingDistance() const {return shootingDistance_;}
    void setShootingDistance(int shootingDistance) {shootingDistance_ = shootingDistance;}

private:
    static void loadUnitsCollections();
    static map<int, Unit*> unitsCollection_;

    int id_ {-1};
    QString name_ {""};
    QString img_ {""};
    int lvl_ {-1};
    int health_ {-1};
    int movement_ {-1};
    int attack_ {-1};
    int shooting_ {-1};
    int shootingDistance_ {-1};

};

#endif // UNIT_H
