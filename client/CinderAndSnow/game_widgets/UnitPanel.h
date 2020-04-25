#ifndef UNITPANEL_H
#define UNITPANEL_H

#include "characters/Character.h"
#include <QWidget>
#include <memory>

using namespace std;

namespace Ui {
    class UnitPanel;
}

class UnitPanel : public QWidget
{
    Q_OBJECT

public:
    void setDefaultCharacter(shared_ptr<const Character> defaultCharacter);

    explicit UnitPanel(QWidget *parent = nullptr);
    ~UnitPanel();

signals:
    void unitClicked(int ind);

private:
    Ui::UnitPanel *ui;
    shared_ptr<const Character> defaultCharacter_;
};

#endif // UNITPANEL_H
