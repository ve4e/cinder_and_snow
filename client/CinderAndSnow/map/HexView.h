#ifndef HEX_ITEM_H
#define HEX_ITEM_H

#include "map/EMap.h"
#include "map/Hex.h"
#include "map/HexController.h"
#include <QGraphicsPolygonItem>

using namespace std;

enum class Surface;

class HexController;

class HexView : public QGraphicsPolygonItem
{
public:
    HexView(const QPolygonF &polygon, const QPointF &position, QGraphicsItem *parent = nullptr);
    void drawBackground(Surface surface);

    void setHighlight(bool s);

    void setController(shared_ptr<HexController> hexController){hexController_ = hexController;}
    shared_ptr<HexController> controller() const {return hexController_;}

private:
    QPixmap getCellPixmap(Surface surface);

    //virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    QPointF position_;

    shared_ptr<HexController> hexController_ = nullptr;
};

#endif // HEX_ITEM_H
