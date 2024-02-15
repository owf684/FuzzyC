#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <add_object_window.h>
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct FEI{
        bool play;
    };

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_play_pause_button_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
