#include "film.h"
#include "ui_film.h"
#include <QDebug>
#include <QFile>
#include <iostream>
#include "settings.h"

using namespace std;

Film::Film(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Film)
{
    ui->setupUi(this);

    Film::get_description();


}

Film::~Film()
{
    delete ui;
}

void Film::get_description()
{
    Settings stgs;
    QString name_temp, kadr_temp, time;

    QFile file ("film.txt");
    if(file.open(QIODevice::ReadOnly))
    {
       QTextStream stream(&file);
       name_temp  = stream.readLine();
    }

    file.remove();
    file.close();


    string name;
    name = name_temp.toStdString();


    int h(0), kadr(0), quantity(0);
    while (name[h] != ' ')
    {
        kadr = kadr * 10 + name[h] - '0';
        h++;
    }
    h++;
    while (name[h] != ' ')
    {
        quantity = quantity * 10 + name[h] - '0';
        h++;
    }


    kadr_temp = QString::number(kadr);

    int sec, min, hour;
    sec = kadr/quantity;
    min = sec/60;
    hour = min/60;
    kadr = ((kadr % quantity)*60)/quantity;
    sec = sec % 60;
    min = min % 60;

    time = QString::number(hour);
    time.append("h.");
    time.append(QString::number(min));
    time.append("m.");
    time.append(QString::number(sec));
    time.append("s.");
    time.append(QString::number(kadr));
    time.append("ms.");


    name.erase(0, h+1);
    name_temp = stgs.getpath_films();
    name_temp.append("/");
    name_temp.append(QString::fromStdString(name));
    name_temp.append(".txt");

    Film::set_description(kadr_temp, time, name_temp);

}
void Film::set_description(QString kadr, QString time, QString name)
{
    ui->label_kadr->setText(kadr);
    ui->label_time->setText(time);


    QFile file (name);

    if(file.open(QIODevice::ReadOnly))
    {

       QTextStream stream(&file);


       ui->film_name->setText(stream.readLine());
       ui->film_year->setText(stream.readLine());
       ui->film_country->setText(stream.readLine());
       ui->film_director->setText(stream.readLine());
       ui->film_script->setText(stream.readLine());
       ui->film_producer->setText(stream.readLine());
       ui->film_composer->setText(stream.readLine());
       ui->film_genre->setText(stream.readLine());

       ui->film_description->setText(stream.readAll());


    }

    file.close();

}



