#ifndef UNITINFO_H
#define UNITINFO_H

#include "units/Unit.h"

#include <QDialog>

namespace Ui {
    class UnitInfo;
}

class UnitInfo : public QDialog
{
    Q_OBJECT

public:
    explicit UnitInfo(QWidget *parent = nullptr);
    ~UnitInfo();

public slots:
    void showUnit(int id);

private:
    Ui::UnitInfo *ui;
};

#endif // UNITINFO_H
