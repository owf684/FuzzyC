#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    struct FEI{
        bool play;
    };
    ~MainWindow();

private slots:
    void on_play_button_clicked();

    void on_pause_button_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
