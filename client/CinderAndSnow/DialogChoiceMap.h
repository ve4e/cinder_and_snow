#ifndef DIALOGCHOICEMAP_H
#define DIALOGCHOICEMAP_H

#include "map/EMap.h"
#include <QDialog>
#include <QMap>

namespace Ui {
class DialogChoiceMap;
}

class DialogChoiceMap : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChoiceMap(QWidget *parent = nullptr);
    ~DialogChoiceMap();

signals:
    void back();
    void mapChoiced(const EMap&);

private slots:
    void choiceMap();

private:
    Ui::DialogChoiceMap *ui;
    QMap<int, QString> mapFnames; // <table row, map fname>
};

#endif // DIALOGCHOICEMAP_H






