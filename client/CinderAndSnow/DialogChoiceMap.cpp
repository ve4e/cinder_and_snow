#include "DialogChoiceMap.h"
#include "ui_dialogchoicemap.h"
#include "MapRW.h"
#include <QDir>
#include <QDebug>
#include <QDataStream>
#include <QTableWidgetSelectionRange>
#include <QString>

const QString DIRNAME_MAPS =  "../maps";

DialogChoiceMap::DialogChoiceMap(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogChoiceMap)
{
    ui->setupUi(this);

    connect(ui->pushButtonBack, SIGNAL(clicked()), this, SIGNAL(back()));
    connect(ui->pushButtonChoice, SIGNAL(clicked()), this, SLOT(choiceMap()));
    
    ui->tableWidgetMap->setSelectionBehavior(QAbstractItemView::SelectRows);


    QDir mapdir (DIRNAME_MAPS);

    QStringList fnames = mapdir.entryList(QDir::Files);

    for(auto fn : fnames)
    {
        EMap map= MapRW::read((mapdir.absolutePath() + '/' + fn).toStdString());

        int i = ui->tableWidgetMap->rowCount();
        ui->tableWidgetMap->setRowCount(ui->tableWidgetMap->rowCount() + 1);
        ui->tableWidgetMap->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(map.info().name())));
        ui->tableWidgetMap->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(map.info().description())));

        mapFnames.insert(ui->tableWidgetMap->rowCount() - 1, DIRNAME_MAPS + '/' + fn);
    }
}

DialogChoiceMap::~DialogChoiceMap()
{
    delete ui;
}

void DialogChoiceMap::choiceMap()
{
    QList<QTableWidgetSelectionRange> selectedRanges = ui->tableWidgetMap->selectedRanges();
    if(selectedRanges.empty()){
        return;
    }
    int row = selectedRanges.first().topRow();

    const EMap map = MapRW::read(mapFnames.value(row).toStdString());


    emit mapChoiced(map);
}


