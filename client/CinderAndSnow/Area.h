#ifndef GAME_AREA_H
#define GAME_AREA_H

#include <memory.h>

#include "GM.h"
#include "map/EMap.h"
#include "game_widgets/UnitInfo.h"
#include "game_widgets/UnitPanel.h"
#include "AreaScene.h"
#include <QGraphicsView>
#include <QGraphicsScene>

class Area : public QGraphicsView, SceneObserver
{
    Q_OBJECT

public:
    explicit Area(QWidget *parent = nullptr);
    ~Area();

    void drawMap(const EMap &map);
    //void drawUnits(const cns::Game game);

    // TODO : move to a separate header
    static std::pair<int, int> hexToPixels(const std::pair<int, int>& hex);
    static QPoint pixelsToHex(const QPoint& point);

//private slots:
//    void showUnit(int id);

private:
//    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void resizeEvent(QResizeEvent *);
    void processMousePressEvent(QGraphicsSceneMouseEvent* event);
    void processMouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent);

    AreaScene* scene_;
    UnitPanel* panel_;
    UnitInfo* unitInfo_;
    shared_ptr<GM> gm_ = nullptr;
};

#endif // GAME_AREA_H



