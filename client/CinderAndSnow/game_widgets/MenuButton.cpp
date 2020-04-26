#include "MenuButton.h"

const QString FNAME_BUTTON_SOUND = "../mp3/menu_button.mp3";

MenuButton::MenuButton(QWidget *parent) :
    QPushButton(parent),
    player_(new QMediaPlayer)
{
    player_->setMedia(QUrl::fromLocalFile(FNAME_BUTTON_SOUND));

    connect(this, SIGNAL(clicked()), this, SLOT(playSound()));
}

MenuButton::MenuButton(const QString &text, QWidget *parent) :
    QPushButton(text, parent)
{ }

MenuButton::MenuButton(const QIcon &icon, const QString &text, QWidget *parent) :
    QPushButton (icon, text, parent)
{ }

void MenuButton::playSound()
{
    player_->play();
}
