#include "map/HexView.h"
#include "Configure.h"

#include <QBrush>
#include <QPen>
#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

const auto CELL_WIDTH = 32;
const auto CELL_HEIGHT = 48;

const QString AREA_HEX_FNAME = "../assets/plain/areahex.png";

const QMap<Surface, QPoint> IMAGE_CELL_OFFSET = {
    {Surface::Grassland,           QPoint(0*CELL_WIDTH, 0*CELL_HEIGHT)},
    {Surface::GrasslandBoscage,    QPoint(1*CELL_WIDTH, 0*CELL_HEIGHT)},
    {Surface::GrasslandForest,     QPoint(2*CELL_WIDTH, 0*CELL_HEIGHT)},
    {Surface::GrasslandHill,       QPoint(3*CELL_WIDTH, 0*CELL_HEIGHT)},
    {Surface::GrasslandForestHill, QPoint(4*CELL_WIDTH, 0*CELL_HEIGHT)},
    {Surface::Mountain,            QPoint(5*CELL_WIDTH, 0*CELL_HEIGHT)},
    {Surface::Sea,                 QPoint(6*CELL_WIDTH, 0*CELL_HEIGHT)},
    {Surface::Ocean,               QPoint(7*CELL_WIDTH, 0*CELL_HEIGHT)},
    {Surface::IceSea,              QPoint(5*CELL_WIDTH, 2*CELL_HEIGHT)},

    {Surface::Plain,               QPoint(6*CELL_WIDTH, 1*CELL_HEIGHT)},
    {Surface::PlainMarsh,          QPoint(5*CELL_WIDTH, 1*CELL_HEIGHT)},
    {Surface::PlainForest,         QPoint(4*CELL_WIDTH, 1*CELL_HEIGHT)},
    {Surface::Floodplain,          QPoint(7*CELL_WIDTH, 1*CELL_HEIGHT)},

    {Surface::Snow,                QPoint(0*CELL_WIDTH, 2*CELL_HEIGHT)},
    {Surface::SnowBoscage,         QPoint(1*CELL_WIDTH, 2*CELL_HEIGHT)},
    {Surface::SnowForest,          QPoint(2*CELL_WIDTH, 2*CELL_HEIGHT)},
    {Surface::SnowForestHill,      QPoint(3*CELL_WIDTH, 2*CELL_HEIGHT)},
    {Surface::SnowHill,            QPoint(4*CELL_WIDTH, 2*CELL_HEIGHT)},

    {Surface::Desert,              QPoint(0*CELL_WIDTH, 3*CELL_HEIGHT)},
    {Surface::DesertHill,          QPoint(1*CELL_WIDTH, 3*CELL_HEIGHT)},
    {Surface::DesertDune,          QPoint(2*CELL_WIDTH, 3*CELL_HEIGHT)},
    {Surface::DesertMountain,      QPoint(3*CELL_WIDTH, 3*CELL_HEIGHT)}
};

HexView::HexView(const QPolygonF &polygon, const QPointF &position, QGraphicsItem *parent):
    QGraphicsPolygonItem(polygon, parent)
{
    this->setPen(QPen(Qt::NoPen));

    QGraphicsItem::setAcceptHoverEvents(true);

    setZValue(1);

    position_ = position;
}

void HexView::drawBackground(Surface surface)
{
    QGraphicsItem* cellItem = scene()->addPixmap(getCellPixmap(surface));
    cellItem->setPos(position_); // FIXME

//    passability_ = surfacePassability(surface);
}

QPixmap HexView::getCellPixmap(Surface surface)
{
    QPixmap plainAssetsImage(AREA_HEX_FNAME); //FIXME : open only one
    QPixmap cellImage = plainAssetsImage.copy(QRect(QPoint(0,0) + IMAGE_CELL_OFFSET.value(surface),
                                              QPoint(CELL_WIDTH, CELL_HEIGHT) + IMAGE_CELL_OFFSET.value(surface)));

    cellImage = cellImage.scaledToWidth(CELL_SIZE);
    return cellImage;
}

void HexView::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton
            && event->source() != Qt::MouseEventSynthesizedByApplication)
    {
        hexController_->handleMousePress();
    }

    QGraphicsItem::mousePressEvent(event);
}

void HexView::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    setBrush(QBrush(Qt::gray, Qt::Dense4Pattern));
    QGraphicsItem::hoverMoveEvent(event);
}

void HexView::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setBrush(QBrush(Qt::gray, Qt::NoBrush));
    QGraphicsItem::hoverLeaveEvent(event);
}

void HexView::setHighlight(bool s)
{
    if(s){
        QPen pen;
        pen.setColor(QColor(243, 239, 132, 200));
        pen.setWidth(4);
        setPen(pen);
    }
    else{
        QPen pen;
        pen.setStyle(Qt::NoPen);
        setPen(pen);
    }
}




