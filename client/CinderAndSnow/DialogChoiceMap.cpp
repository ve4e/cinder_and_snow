#include "DialogChoiceMap.h"
#include "ui_dialogchoicemap.h"
#include "MapRW.h"
#include <QDir>
#include <QDebug>
#include <QDataStream>
#include <QTableWidgetSelectionRange>
#include <QString>

const QString DIRNAME_MAPS =  "/home/ve4e/develop/cinder_and_snow/client/maps/";

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
        /*
        QFile mapFile(DIRNAME_MAPS + fn);
        mapFile.open(QIODevice::ReadOnly);
        cns::Game game;
        if(!game.ParseFromFileDescriptor(mapFile.handle()))
        {
            QTextStream(stdout) << "Error. Can not parse file: " << DIRNAME_MAPS + fn << endl;
            continue;
        }

        cns::Map map = game.map();
        */

        EMap map= MapRW::read((DIRNAME_MAPS + fn).toStdString());

        int i = ui->tableWidgetMap->rowCount();
        ui->tableWidgetMap->setRowCount(ui->tableWidgetMap->rowCount() + 1);
        ui->tableWidgetMap->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(map.info().name())));
        ui->tableWidgetMap->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(map.info().description())));

        mapFnames.insert(ui->tableWidgetMap->rowCount() - 1, DIRNAME_MAPS + fn);
        
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

    /*
    QFile mapFile(maps_.value(row));
    mapFile.open(QIODevice::ReadOnly);
    cns::Game game;
    game.ParseFromFileDescriptor(mapFile.handle());
    mapFile.close();
    */
    const EMap map = MapRW::read(mapFnames.value(row).toStdString());


    emit mapChoiced(map);
}


