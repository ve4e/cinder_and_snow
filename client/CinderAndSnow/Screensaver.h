#ifndef SCREENSAVER_H
#define SCREENSAVER_H

#include <QLabel>

class Screensaver : public QLabel
{
    Q_OBJECT

public:
    Screensaver(QWidget* parent);
    ~Screensaver();

signals:
    void finished();

private:
    void mousePressEvent(QMouseEvent *e);
};

#endif // SCREENSAVER_H
