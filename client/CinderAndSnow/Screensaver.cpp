#include "Screensaver.h"

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QMouseEvent>

Screensaver::Screensaver(QWidget* parent) :
    QLabel(parent)
{
    this->setText("Cinder & Snow");

    QFont font = this->font();
    font.setPointSize(40);
    font.setStyleStrategy(QFont::PreferAntialias);
    this->setFont(font);
    this->setAlignment(Qt::AlignCenter);

    QGraphicsOpacityEffect* eff = new QGraphicsOpacityEffect(this);
    this->setGraphicsEffect(eff);
    QPropertyAnimation* animation = new QPropertyAnimation(eff, "opacity");
    animation->setDuration(7000);
    animation->setStartValue(0.1);
    animation->setEndValue(1);
    animation->setEasingCurve(QEasingCurve::InBack);
    animation->start(QPropertyAnimation::DeleteWhenStopped);

}

Screensaver::~Screensaver()
{

}

void Screensaver::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton || e->button() == Qt::RightButton)
    {
        emit finished();
    }
}




