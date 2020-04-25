
#ifndef AREASCENE_H
#define AREASCENE_H

#include <QGraphicsScene>
#include <memory>

using namespace std;

class SceneObserver
{
public:
    virtual void processMousePressEvent(QGraphicsSceneMouseEvent *){}
    virtual void processMouseReleaseEvent(QGraphicsSceneMouseEvent *){}
};

class AreaScene : public QGraphicsScene
{
    Q_OBJECT
public:
    AreaScene(QObject *parent = nullptr);
    void addObserver(SceneObserver *observer);

private:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

    std::vector<SceneObserver*> observers_;
};

#endif // AREASCENE_H

















