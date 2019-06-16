#ifndef EDITSETTINGS_H
#define EDITSETTINGS_H

#include <QDialog>

namespace Ui {
class EditSettings;
}

class EditSettings : public QDialog
{
    Q_OBJECT

public:
    explicit EditSettings(QWidget *parent = 0);
    ~EditSettings();

private slots:
    void set_settings();
    void saveEnabled();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_cancel_button_clicked();

private:
    Ui::EditSettings *ui;
};

#endif // EDITSETTINGS_H
