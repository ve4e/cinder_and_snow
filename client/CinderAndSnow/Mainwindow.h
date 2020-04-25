
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Screensaver.h"
#include "NetworkManager.h"
#include "DialogChoiceMap.h"
#include "Area.h"

#include <QMainWindow>

#include <memory>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void showMenu();
    void showDialogChoiceMap();
    void showGameArea(const EMap &);

private:
    Ui::MainWindow *ui;

    NetworkManager* networkManager_;
    Screensaver* screensaver_;
    DialogChoiceMap* dialogChoiceMap_;
    Area* area_;
};

#endif // MAINWINDOW_H

