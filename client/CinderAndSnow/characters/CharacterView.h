#ifndef CHARACTER_VIEW_H
#define CHARACTER_VIEW_H

#include <QGraphicsItem>
#include <QPoint>
#include <QPainter>

#include "characters/Character.h"

enum class CharacterType;

class CharacterView : public QGraphicsItem
{
public:
    CharacterView(CharacterType characterType);

    enum class Orientation{RightTop = 0, RightDown = 1, Down = 2, LeftDown = 3, LeftTop = 4, Top = 5};
    void setOrientation(Orientation orientation) {orientation_ = orientation;}

    enum class Animation{Idle = 0, Attack, Walk};
    void setAnimation(Animation animation) {animation_ = animation;}

    void setCurrentPixel(const std::pair<int, int>& pixel);
    void setTargetPixel(const std::pair<int, int>& pixel);
    void takeStep();
    int stepCount() const {return stepCount_;}

    // the number of steps required to move to the next cell
    int pathLength() {return PATH_LENGTH;}

    void tick();

protected:
    QString getAssetPrefix();
    QPixmap getSprite();

    int PATH_LENGTH = 16;
    Orientation orientation_ = Orientation::Down;
    Animation animation_ = Animation::Idle;

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void repaint();

    QString assetPrefix_;
    QPoint currentPixel_;
    QPoint targetPixel_;
    int stepCount_ = 0;
};

#endif // CHARACTER_H







