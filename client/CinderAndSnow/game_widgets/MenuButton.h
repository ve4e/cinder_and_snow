#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QPushButton>
#include <QMediaPlayer>

class MenuButton : public QPushButton
{
    Q_OBJECT

public:
    explicit MenuButton(QWidget *parent = nullptr);
    explicit MenuButton(const QString &text, QWidget *parent = nullptr);
    explicit MenuButton(const QIcon &icon, const QString &text, QWidget *parent = nullptr);


private slots:
    void playSound();

private:
    QMediaPlayer* player_;
};

#endif // MENUBUTTON_H
