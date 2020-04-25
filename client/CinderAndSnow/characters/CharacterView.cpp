#include "CharacterView.h"
#include "characters/Asset.h"
#include "Configure.h"

#include <QDebug>
#include <QGraphicsView>
#include <QScrollBar>
#include <iostream>

const int MOVING_PARTS = 16;

CharacterView::CharacterView(CharacterType characterType)
{
    setZValue(2);

    if (characterType == CharacterType::Elf){
        assetPrefix_ = ":/character/swordman";
    }
    else if(characterType == CharacterType::Sith){
        assetPrefix_ = ":/character/sith";
    }
    else{
        assetPrefix_ = ":/character/swordman";
    }
}

QPixmap CharacterView::getSprite()
{
    auto asset = Asset::getAsset(getAssetPrefix(), orientation_, animation_);

    QPixmap cellImage = asset->nextPixmap();
    cellImage = cellImage.scaledToHeight(CELL_SIZE);

    return cellImage;
}

QString CharacterView::getAssetPrefix()
{
    return assetPrefix_;
}

void CharacterView::tick()
{
    repaint();
}

QRectF CharacterView::boundingRect() const
{
//    return QRectF(currentPixel_.x() - CELL_WIDTH/2, currentPixel_.y() - CELL_HEIGHT/2, CELL_WIDTH, CELL_HEIGHT);
    return QRectF(0, 0, 5000, 5000); // FIXME: this is very very bad
}

void CharacterView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap sprite = getSprite();

    painter->drawPixmap(currentPixel_.x() - CELL_SIZE/2, currentPixel_.y() - CELL_SIZE/2, sprite);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void CharacterView::repaint()
{
    update();
}

void CharacterView::setCurrentPixel(const std::pair<int, int> &pixel)
{
    currentPixel_ = QPoint(pixel.first, pixel.second);
    targetPixel_ = QPoint(0,0);
}

void CharacterView::setTargetPixel(const std::pair<int, int> &pixel)
{
    targetPixel_ = QPoint(pixel.first, pixel.second);
    stepCount_ = 0;
}

void CharacterView::takeStep()
{
    static float dx = 0;
    static float dy = 0;

    static QPoint startPixel = QPoint(0,0);

    if(stepCount_ == 0) {
        startPixel = currentPixel_;

        dx = (float)(targetPixel_.x() - currentPixel_.x()) / MOVING_PARTS;
        dy = (float)(targetPixel_.y() - currentPixel_.y()) / MOVING_PARTS;
    }
    
    ++stepCount_;

   currentPixel_ = startPixel + QPoint(stepCount_ * dx, stepCount_ * dy);
}










