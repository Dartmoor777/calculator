#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "widget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    Widget *calculator;
    ~MainWindow();

private:
    QTimer *timer;
    Ui::MainWindow *ui;
    int value;
    int timerSpeed;
public slots:
    void updateProgressBar();
private slots:
    void on_actionHelp_triggered();
    void on_actionAbout_triggered();
};

#endif // MAINWINDOW_H
