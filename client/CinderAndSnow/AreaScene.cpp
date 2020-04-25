
#include "AreaScene.h"

#include <QDebug>
#include <QGraphicsSceneEvent>

AreaScene::AreaScene(QObject *parent):
    QGraphicsScene(parent)
{
}

void AreaScene::addObserver(SceneObserver* observer)
{
    observers_.push_back(observer);
}

void AreaScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
//    qDebug() << mouseEvent->scenePos().x();
//    qDebug() << mouseEvent->scenePos().y();
    for(auto& observer: observers_){
        observer->processMousePressEvent(mouseEvent);
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void AreaScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
//    qDebug() << mouseEvent->scenePos().x();
//    qDebug() << mouseEvent->scenePos().y();
    for(auto& observer: observers_){
        observer->processMouseReleaseEvent(mouseEvent);
    }
     QGraphicsScene::mouseReleaseEvent(mouseEvent);
}




