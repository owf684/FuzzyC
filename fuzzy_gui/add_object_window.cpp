#include "add_object_window.h"
#include "ui_add_object_window.h"

add_object_window::add_object_window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::add_object_window)
{
    ui->setupUi(this);
    QStringList const sprite_selection = {"current sprite","sprite 1","sprite 2", "sprite 3", "sprite 4", "sprite 5"};
    QStringList const layers = {"1","2","3","4"}; //1 is most behind. 4 is most infront

    is_current_sprite_sheet = false;
    is_sprite_1_sheet = false;
    is_sprite_2_sheet = false;
    is_sprite_3_sheet = false;
    is_sprite_4_sheet = false;
    is_sprite_5_sheet = false;

    // QString paths store the file path to said sprite sheet
    current_sprite_path="";
    sprite_1_path="";
    sprite_2_path="";
    sprite_3_path="";
    sprite_4_path="";
    sprite_5_path="";

    ui->sprite_comboBox->addItems(sprite_selection);
    ui->draw_layer_comboBox->addItems(layers);
}

add_object_window::~add_object_window()
{
    delete ui;
}


void add_object_window::on_sf_current_sprite_button_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Select File");
    if (!filePath.isEmpty())
    {
        ui->sf_current_label->setText(filePath);

        switch(ui->sprite_comboBox->currentIndex())
        {
            case 0:
            current_sprite_path = filePath;
            break;

            case 1:
            sprite_1_path = filePath;
            break;

            case 2:
            sprite_2_path = filePath;
            break;

            case 3:
            sprite_3_path = filePath;
            break;

            case 4:
            sprite_4_path = filePath;
            break;

            case 5:
            sprite_5_path = filePath;
            break;
        }
    }
}


void add_object_window::on_sprite_sheet_stateChanged(int arg1)
{
    switch(ui->sprite_comboBox->currentIndex())
        {
            case 0:
            if (ui->sprite_sheet->isChecked()) is_current_sprite_sheet = true;
            else is_current_sprite_sheet = false;
            break;

            case 1:
            if (ui->sprite_sheet->isChecked()) is_sprite_1_sheet = true;
            else is_sprite_1_sheet = false;
            break;

            case 2:
            if (ui->sprite_sheet->isChecked()) is_sprite_2_sheet = true;
            else is_sprite_2_sheet = false;
            break;

            case 3:
            if (ui->sprite_sheet->isChecked()) is_sprite_3_sheet = true;
            else is_sprite_3_sheet = false;
            break;

            case 4:
            if (ui->sprite_sheet->isChecked()) is_sprite_4_sheet = true;
            else is_sprite_4_sheet = false;
            break;

            case 5:
            if (ui->sprite_sheet->isChecked()) is_sprite_5_sheet = true;
            else is_sprite_5_sheet = false;
            break;
        }
}


void add_object_window::on_sprite_comboBox_currentIndexChanged(int index)
{
        switch(index)
        {
        case 0:
            ui->sf_current_label->setText(current_sprite_path);
            break;
        case 1:
            ui->sf_current_label->setText(sprite_1_path);
            break;
        case 2:
            ui->sf_current_label->setText(sprite_2_path);
            break;
        case 3:
            ui->sf_current_label->setText(sprite_3_path);
            break;
        case 4:
            ui->sf_current_label->setText(sprite_4_path);
            break;
        case 5:
            ui->sf_current_label->setText(sprite_5_path);
            break;
        }
}

