#ifndef ADD_OBJECT_WINDOW_H
#define ADD_OBJECT_WINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class add_object_window;
}
QT_END_NAMESPACE

class add_object_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit add_object_window(QWidget *parent = nullptr);
    ~add_object_window();

private slots:

    void on_sf_current_sprite_button_clicked();

    void on_sprite_sheet_stateChanged(int arg1);

    void on_sprite_comboBox_currentIndexChanged(int index);

private:
    Ui::add_object_window *ui;

    // sprite sheets booleans. Will determie how sprite is stored

    bool is_current_sprite_sheet;
    bool is_sprite_1_sheet;
    bool is_sprite_2_sheet;
    bool is_sprite_3_sheet;
    bool is_sprite_4_sheet;
    bool is_sprite_5_sheet;

    // QString paths store the file path to said sprite sheet
    QString current_sprite_path;
    QString sprite_1_path;
    QString sprite_2_path;
    QString sprite_3_path;
    QString sprite_4_path;
    QString sprite_5_path;

};

#endif // ADD_OBJECT_WINDOW_H
