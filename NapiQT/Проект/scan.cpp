#include "scan.h"
#include "ui_scan.h"
#include <QFileDialog>
#include "settings.h"
#include "createframe.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>
#include "film.h"
#include <iostream>

using namespace std;

Scan::Scan(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Scan)
{
    ui->setupUi(this);

    //загрузка настроек
    Scan::set_settings();


    connect(ui->path_a,SIGNAL(textChanged(QString)),this,SLOT(scanEnabled()));
    connect(ui->path_b,SIGNAL(textChanged(QString)),this,SLOT(scanEnabled()));
    connect(ui->path_c,SIGNAL(textChanged(QString)),this,SLOT(scanEnabled()));

}

Scan::~Scan()
{
    delete ui;
}

void Scan::on_pushButton_2_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open", "", tr("Images (*.png *.xpm *.jpg *.jpeg)"));
    ui->path_a->setText(str);
}

void Scan::on_pushButton_3_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open", "", tr("Images (*.png *.xpm *.jpg *.jpeg)"));
    ui->path_b->setText(str);
}

void Scan::on_pushButton_4_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open", "", tr("Images (*.png *.xpm *.jpg *.jpeg)"));
    ui->path_c->setText(str);
}

//загрузка настроек
void Scan::set_settings()
{
    //загрузка настроек
    Settings stgs;

    //QWidgets получают значение в зависимости от настроек   
    ui->seg->setChecked(stgs.getseg());
    if (stgs.getkadrov() == 3)
        ui->kadrov->setChecked(true);
    else ui->kadrov->setChecked(false);

    //отображение возможности выбора количества кадров
    Scan::show_kadrov();

}

void Scan::show_kadrov()
{
    if(ui->kadrov->isChecked())
    {
        ui->label_b->setVisible(true);
        ui->path_b->setVisible(true);
        ui->pushButton_3->setVisible(true);
        ui->label_c->setVisible(true);
        ui->path_c->setVisible(true);
        ui->pushButton_4->setVisible(true);
    }
    else
    {
        ui->label_b->setVisible(false);
        ui->path_b->setVisible(false);
        ui->pushButton_3->setVisible(false);
        ui->label_c->setVisible(false);
        ui->path_c->setVisible(false);
        ui->pushButton_4->setVisible(false);
    }
    Scan::scanEnabled();
}

void Scan::on_kadrov_stateChanged(int arg1)
{
    Scan::show_kadrov();
}

void Scan::scanEnabled()
{
    if(!ui->kadrov->isChecked())
    {
        if(ui->path_a->text() == "")
            ui->scan_button->setEnabled(false);
        else ui->scan_button->setEnabled(true);

    }
    else
    {
        if((ui->path_a->text() == "") ||(ui->path_b->text() == "") || (ui->path_c->text() == ""))
            ui->scan_button->setEnabled(false);
        else ui->scan_button->setEnabled(true);


    }
}

int compare_frame(QString qframe, QString qx, int lenght, QString &qtemp_name)
{
    string frame, x, temp_name;

    frame = qframe.toStdString();
    x = qx.toStdString();
    temp_name = qtemp_name.toStdString();

    int sum(0);
    int x_frame(0);
    int x_x(0);

    for (int j(0); j < lenght; j++)
    {
        int frame_number(0);
        while (frame[x_frame] != ' ')
        {
            frame_number = frame_number * 10 + (frame[x_frame] - '0');
            x_frame++;
        }
        x_frame++;

        int x_number(0);
        while (x[x_x] != ' ')
        {
            x_number = x_number * 10 + (x[x_x] - '0');
            x_x++;
        }
        x_x++;

        if (frame_number == x_number)
            sum++;

     }

     temp_name = x.erase(0, x_x);
     qtemp_name = QString::fromStdString(temp_name);

     return sum;

}

void show_res(int max_rang, int lenght, QString name, bool pr)
{
    QFile f("film.txt");
    if(f.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&f);
        stream << name;
    }
    f.close();

    Film wind(0);
    wind.show();
    wind.exec();

}

void Scan::on_scan_button_clicked()
{
    QString frame, key;
    if (ui->kadrov->isChecked())
    {
        CreateFrame fram(ui->path_a->text(), ui->path_b->text(), ui->path_c->text(), ui->seg->isChecked());
        frame = fram.getframe();
        key = fram.getkey();
    }
    else
    {
        CreateFrame fram(ui->path_a->text(), ui->seg->isChecked());
        frame = fram.getframe();
        key = fram.getkey();
    }








        Settings stgs;

        QString path_key = stgs.getpath_library();
        path_key.append("//");
        path_key.append(key);
        path_key.append(".txt");



        QFile file (path_key);

        if (!file.exists())
        {            
            QMessageBox::information(this, "Не найден","Фильм не найден");

        } else if(file.open(QIODevice::ReadOnly))
        {

            int max_rang(0);
            QString name, temp_name, x;
            QTextStream stream(&file);

            while (1)
            {
              x  = stream.readLine();
              if (x == "")
               {

                   if (max_rang >= ((stgs.gety_sectors() * stgs.getx_sectors() * stgs.getframe_maybe()) / 100) * stgs.getkadrov())
                   {

                                //если обнаружился
                                //system("cls");
                                show_res(max_rang, stgs.gety_sectors() * stgs.getx_sectors() * stgs.getkadrov(), name, true);
                   }
                    else
                        QMessageBox::information(this, "Не найден","Фильм не найден");

                     break;
              }


                   int rang = compare_frame(frame, x, stgs.gety_sectors()*stgs.getx_sectors()*stgs.getkadrov(), temp_name);


                   if (rang >= ((stgs.gety_sectors() * stgs.getx_sectors() * stgs.getframe_founded()) / 100) * stgs.getkadrov())
                   {

                            //если обнаружился
                            name = temp_name;
                            //system("cls");
                            show_res(rang, stgs.gety_sectors() * stgs.getx_sectors() * stgs.getkadrov(), name, true);
                            break;
                    }
                    else if (rang > max_rang)
                    {
                        max_rang = rang;
                        name = temp_name;
                    }
                 }

        }

        file.close();
}
