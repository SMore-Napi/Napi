#include "editsettings.h"
#include "ui_editsettings.h"
#include <QFileDialog>
#include "settings.h"

EditSettings::EditSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditSettings)
{
    ui->setupUi(this);

    //загрузка настроек
    EditSettings::set_settings();


    connect(ui->path_library,SIGNAL(textChanged(QString)),this,SLOT(saveEnabled()));
    connect(ui->path_films,SIGNAL(textChanged(QString)),this,SLOT(saveEnabled()));

}

EditSettings::~EditSettings()
{
    delete ui;
}

void EditSettings::on_pushButton_3_clicked()
{
    QString str = QFileDialog::getExistingDirectory(0, "Directory Dialog", "");
    ui->path_library->setText(str);
}

void EditSettings::on_pushButton_4_clicked()
{
    QString str = QFileDialog::getExistingDirectory(0, "Directory Dialog", "");
    ui->path_films->setText(str);
}

void EditSettings::on_pushButton_clicked()
{
    //загрузка настроек
    Settings stgs;
    stgs.default_settings();
    stgs.save_settings();
    EditSettings::set_settings();


}

//загрузка настроек
void EditSettings::set_settings()
{
    //загрузка настроек
    Settings stgs;
    //QWidgets получают значение в зависимости от настроек    
    ui->seg->setChecked(stgs.getseg());
    if (stgs.getkadrov() == 3)
        ui->kadrov->setChecked(true);
    else ui->kadrov->setChecked(false);
    ui->y_sectors->setValue(stgs.gety_sectors());
    ui->x_sectors->setValue(stgs.getx_sectors());
    ui->path_library->setText(stgs.getpath_library());
    ui->path_films->setText(stgs.getpath_films());
    ui->frame_maybe->setValue(stgs.getframe_maybe());
    ui->frame_founded->setValue(stgs.getframe_founded());

}


//сохранение настроек
void EditSettings::on_pushButton_2_clicked()
{
    //загрузка настроек
    Settings stgs;
    //настройки получают значение в зависимости от значений QWidgets
    stgs.setseg(ui->seg->isChecked());
    if (ui->kadrov->isChecked())
        stgs.setkadrov(3);
    else stgs.setkadrov(1);
    stgs.sety_sectors(ui->y_sectors->value());
    stgs.setx_sectors(ui->x_sectors->value());
    stgs.setpath_library(ui->path_library->text());
    stgs.setpath_films(ui->path_films->text());
    stgs.setframe_maybe(ui->frame_maybe->value());
    stgs.setframe_founded(ui->frame_founded->value());
    //сохранение настроек
    stgs.save_settings();

    this->close();
}

//кнопка отмены
void EditSettings::on_cancel_button_clicked()
{
    this->close();
}

void EditSettings::saveEnabled()
{
    if((ui->path_library->text() == "") || (ui->path_films->text() == ""))
        ui->pushButton_2->setEnabled(false);
    else ui->pushButton_2->setEnabled(true);


}
