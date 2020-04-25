//#include "ui_Area.h"

#include "Area.h"
#include "AreaScene.h"
#include "map/HexView.h"
#include "map/HexController.h"
#include "game_widgets/UnitPanel.h"
#include "Configure.h"

#include <QDebug>
#include <QScrollBar>
#include <QMouseEvent>
#include <QGraphicsProxyWidget>
#include <QtCore/qmath.h>
#include <QGraphicsSceneMouseEvent>

#include <memory>

const int xBorder = 80;
const int yBorder = 80;

const double R = CELL_SIZE/2;
const double R_2 = R/2;
const double r = qSqrt(3)/2*R;

pair<int, int> Area::hexToPixels(const pair<int, int> &hex)
{
    int x = static_cast<int>(xBorder + hex.first*(R + R_2));
    int y = static_cast<int>(yBorder + hex.second*2*r);

    if(hex.first%2 != 0){
        y += r;
    }
    return std::pair<int, int>(x,y);
}

QPoint Area::pixelsToHex(const QPoint& pixels)
{
    int x = pixels.x() - xBorder - r/2;
    int y = pixels.y() - yBorder - r/2;

    // Find out which major row and column we are on:
    int row = (int)(y / r);
    int column = (int)(x / (R + R_2));

    // Compute the offset into these row and column:
    float dy = y - (float)row * r;
    float dx = x - (float)column * (R + R_2);

    // Are we on the left of the hexagon edge, or on the right?
    if (((row ^ column) & 1) == 0)
        dy = r - dy;
    int right = dy * (R - R_2) < r * (dx - R_2) ? 1 : 0;

    // Now we have all the information we need, just fine-tune row and column.
    row += (column ^ row ^ right) & 1;
    column += right;

    //
    row /= 2;

    return QPoint(column, row);
}

Area::Area(QWidget *parent) :
    QGraphicsView(parent),
    scene_(new AreaScene(this)),
    panel_(new UnitPanel(this)),
    unitInfo_(new UnitInfo(this)),
    gm_(make_shared<GM>())
{
    setScene(scene_);
    setBackgroundBrush(QBrush(QColor("#bbbbbb"), Qt::SolidPattern));
    scene_->setSceneRect(QRectF(QPointF(0, 0), QPointF(5500, 5000))); // FIXME

//    connect(this->horizontalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scene_->update(int)));
//    connect(this->ui->graphicsViewArea->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(update(int)));

    scene_->views()[0]->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

//    scene_->views()[0]->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    scene_->addObserver(this);

    unitInfo_->show();
    unitInfo_->hide();

    connect(panel_, SIGNAL(unitClicked(int)), unitInfo_, SLOT(showUnit(int)));
}

Area::~Area()
{
}

void Area::drawMap(const EMap &map)
{
    // draw hexes

    for(uint i = 0; i < map.info().width(); ++i){
        for(uint j = 0; j < map.info().height(); ++j){
//            double xShift = (1.5 * R) * j;
//            double yShift = (j % 2 == 0) ? 2*r*i : 2*r*i + r;

            double xShift = (1.5 * R) * i;
            double yShift = (i % 2 == 0) ? 2*r*j : 2*r*j + r;


            QPointF O (xBorder + xShift, yBorder + yShift);

            QPointF a(O.x() - R/2, O.y() - r);
            QPointF b(O.x() + R/2, O.y() - r);
            QPointF c(O.x() + R, O.y());
            QPointF d(O.x() + R/2, O.y() + r);
            QPointF e(O.x() - R/2, O.y() + r);
            QPointF f(O.x() - R, O.y());

            shared_ptr<HexView> hexView = make_shared<HexView>(
                        QPolygonF(QVector<QPointF>() = {a, b, c, d, e, f}),
                        QPointF(O.x() - R, O.y() - r*2 - 4)
            );

            scene_->addItem(hexView.get());
            hexView->drawBackground(map.hexMtrx()[i][j]->surface());

            shared_ptr<Hex> hex = map.hexMtrx()[i][j];
            shared_ptr<HexController> hexController = make_shared<HexController>();
            hexController->setGm(gm_);

            hex->setHexController(hexController);
            hexController->setHex(hex);

            hexController->setHexView(hexView);
            hexView->setController(hexController);
        }
    }

    // draw and activate heroes // FIXME: why here?
    for(const auto &h : map.heroes()){
        shared_ptr<CharacterView> heroView = make_shared<CharacterView>(CharacterType::Elf);
        shared_ptr<CharacterController> heroController = make_shared<CharacterController>();

        heroController->setModel(h);
        heroController->setView(heroView);
        h->setController(heroController);

        heroController->setGm(gm_);

        scene_->addItem(heroView.get());
    }
    panel_->setDefaultCharacter(map.heroes()[0]);

    // draw and activate monsters
    for(const auto &m : map.monsters()){
        shared_ptr<CharacterView> monsterView = make_shared<CharacterView>(m->type());
        shared_ptr<CharacterController> monsterController = make_shared<CharacterController>();

        monsterController->setModel(m);
        monsterController->setView(monsterView);
        m->setController(monsterController);

        monsterController->setGm(gm_);

        scene_->addItem(monsterView.get());
    }
//    panel_->setDefaultCharacter(map.heroes()[0]);



    // draw units
/*
    for(const auto &u : map.users()){
        for(const auto &h : u->heroes()){
            shared_ptr<Hero>hero = HeroesFactory::createHero(h->type());
            h->setView(hero);
            scene_->addItem(hero.get());
        }
    }
*/

    gm_->setMap(map);
}

//void Area::showUnit(int id)
//{
//    unitInfo_->showUnit(id);
//}
/*
void Area::drawUnits(const cns::Game game)
{
    cns::User user = game.users(0);

    for (int i = 0, size = user.heroes_size(); i < size; ++i)
    {
        Hero* hero = HeroesFactory::createHero(user.heroes(i).type(), this);
        if(hero ==  nullptr){
            continue;
        }
        scene_->addItem(hero);
        hero->setHex(QPoint(user.heroes(i).x(), user.heroes(i).y()));
        controller_.addHero(hero, user.heroes(i));
    }
}
*/

//void Area::mousePressEvent(QMouseEvent *event)
//{
//    if(event->button() == Qt::RightButton){
//        //ui->graphicsViewArea->setDragMode(QGraphicsView::ScrollHandDrag);
//        //ui->graphicsViewArea->setInteractive(false);
//    }
//    else if(event->button() == Qt::LeftButton){
//        int hv = ui->graphicsViewArea->horizontalScrollBar()->value();
//        int vv = ui->graphicsViewArea->verticalScrollBar()->value();

//        QPoint pos = Area::pixelsToHex(event->pos() + QPoint(hv, vv));
//        gm_->handleClick(pos.x(), pos.y());

//        qDebug() << event->pos().x();
//        qDebug() << event->pos().y();
//    }

//    QWidget::mousePressEvent(event);


//    // ui->graphicsViewArea->setDragMode(QGraphicsView::ScrollHandDrag);
//    // ui->graphicsViewArea->setInteractive(false);

//}

/*
void Area::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "TEST mouseReleaseEvent";
    if(event->button() == Qt::RightButton){
       //ui->graphicsViewArea->setDragMode(QGraphicsView::NoDrag);
       // ui->graphicsViewArea->setInteractive(true);
    }

    QWidget::mouseReleaseEvent(event);
}
*/

void Area::processMousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button() == Qt::RightButton){
        QMouseEvent releaseEvent(QEvent::MouseButtonRelease, event->screenPos(), Qt::LeftButton, 0, event->modifiers());
        QGraphicsView::mouseReleaseEvent(&releaseEvent);

        setDragMode(QGraphicsView::ScrollHandDrag);

//        QMouseEvent fakeEvent(QEvent::MouseButtonRelease, mapFromGlobal(event->screenPos()), Qt::LeftButton, event->buttons() | Qt::LeftButton, event->modifiers());

        QMouseEvent fakeEvent(event->type(), mapFromGlobal(event->screenPos()), event->pos(), event->screenPos(),
                              Qt::LeftButton, event->buttons() | Qt::LeftButton, event->modifiers(), Qt::MouseEventSynthesizedByApplication);
        QGraphicsView::mousePressEvent(&fakeEvent);
    }
//    else if(event->button() == Qt::LeftButton && !(event->buttons()&Qt::RightButton)){
//        int hv = horizontalScrollBar()->value();
//        int vv = verticalScrollBar()->value();

//        QPoint pos = Area::pixelsToHex(event->scenePos().toPoint() + QPoint(hv, vv));
//        gm_->handleClick(pos.x(), pos.y());
//    }
}

void Area::processMouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
    if(mouseEvent->button() == Qt::RightButton){
       setDragMode(QGraphicsView::NoDrag);
    }
}

void Area::mouseMoveEvent(QMouseEvent* event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void Area::resizeEvent(QResizeEvent*)
{
    panel_ -> move ((this->width() - panel_->width())/2, this->height() - panel_->height() - 30);
}

















