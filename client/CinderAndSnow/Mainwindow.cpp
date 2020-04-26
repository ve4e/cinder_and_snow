#include "Mainwindow.h"
#include "ui_mainwindow.h"
#include "Screensaver.h"

#include <QDir>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QDebug>
//#include <QMediaPlayer>

//const QString FNAME_START_MUSIC = "";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    networkManager_(new NetworkManager),
    screensaver_(new Screensaver(this)),
    dialogChoiceMap_(new DialogChoiceMap(this)),
    area_(new Area(this))
{
    ui->setupUi(this);

    this->setWindowTitle(qAppName());


    //QMediaPlayer *player = new QMediaPlayer(this);
    //player->setMedia(QUrl::fromLocalFile(FNAME_START_MUSIC));
    //player->play();

    // setting widgets
    ui->frameMenu->hide();
    dialogChoiceMap_->hide();
    area_->hide();
    ui->centralWidget->layout()->addWidget(screensaver_);
    ui->centralWidget->layout()->addWidget(dialogChoiceMap_);
    ui->centralWidget->layout()->addWidget(area_);

    connect(screensaver_, SIGNAL(finished()), this, SLOT(showMenu()));
    connect(ui->pushButtonNewGame, SIGNAL(clicked()), this, SLOT(showDialogChoiceMap()));
    connect(ui->pushButtonClose, SIGNAL(clicked()), this, SLOT(close()));
    connect(dialogChoiceMap_, SIGNAL(back()), this, SLOT(showMenu()));
    connect(dialogChoiceMap_, SIGNAL(mapChoiced(const EMap&)), this, SLOT(showGameArea(const EMap &)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMenu()
{
    screensaver_->hide();

    ui->frameMenu->show();
    dialogChoiceMap_->hide();
    area_->hide();
}

void MainWindow::showDialogChoiceMap()
{
    ui->frameMenu->hide();
    dialogChoiceMap_->show();
    area_->hide();
}

void MainWindow::showGameArea(const EMap & map)
{
    ui->frameMenu->hide();
    dialogChoiceMap_->hide();
    area_->show();

    area_->drawMap(map);
    //area_->drawUnits(game);
}


