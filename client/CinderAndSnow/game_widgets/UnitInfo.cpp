#include "UnitInfo.h"
#include "ui_UnitInfo.h"

#include <QQuickView>
#include <QQuickItem>
#include <QQmlProperty>


UnitInfo::UnitInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UnitInfo)
{
    ui->setupUi(this);
}

UnitInfo::~UnitInfo()
{
    delete ui;
}

void UnitInfo::showUnit(const int id)
{
    Unit* unit = Unit::getUnit(id);

    QObject* object = ui->quickWidget->rootObject();
    QQmlProperty::write(object, "unit", QVariant::fromValue(unit));


    show();
}



