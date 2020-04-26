#include "UnitPanel.h"
#include "ui_UnitPanel.h"

#include "units/Unit.h"

#include <QtQuickWidgets/QQuickWidget>
#include <QQuickItem>
#include <QDebug>
#include <QQmlProperty>
#include <QQmlEngine>
#include <QQmlContext>
#include <QMap>

UnitPanel::UnitPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UnitPanel)
{
    ui->setupUi(this);

    QObject* item = ui->quickWidget->rootObject();
    connect(item, SIGNAL(unitClicked(int)), this, SIGNAL(unitClicked(int)));
}

UnitPanel::~UnitPanel()
{
    delete ui;
}


void UnitPanel::setDefaultCharacter(shared_ptr<const Character> defaultCharacter)
{
    defaultCharacter_ = defaultCharacter;

    QList<QObject*> dataList;
    for(const auto& u: defaultCharacter_->units()){
        auto unit = Unit::getUnit(u);
        if(unit != nullptr){
            dataList.append(unit);
        }
    }

    ui->quickWidget->engine()->rootContext()->setContextProperty("unitModel", QVariant::fromValue(dataList));
}








