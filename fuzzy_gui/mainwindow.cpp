#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->move(1060,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_play_pause_button_clicked()
{
    if (ui->play_pause_button->text() == "play")
    {
        ui->play_pause_button->setText("pause");
    } else {
        ui->play_pause_button->setText("play");
    }

    // ftok to generate unique key
    key_t key = ftok("fuzzy_engine_interface", 65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, sizeof(FEI), 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    FEI* data = (FEI*)shmat(shmid, (void*)0, 0);

    data->play = !data->play;

    // detach from shared memory
    shmdt(data);

}


void MainWindow::on_pushButton_clicked()
{
    add_object_window* new_window = new add_object_window();
    new_window->show();
}

