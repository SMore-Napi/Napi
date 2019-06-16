#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

class Settings
{
private:    
    bool seg; //Делить на сегменты
    int	kadrov; //Количество кадров, поданных на вход
    int	y_sectors; //количество секторов по оси Y
    int	x_sectors; //количество секторов по оси X
    QString path_library; //путь к папке, являющейся базой данных
    QString path_films; //путь к папке, хранящей описание фильмов
    int frame_maybe; //минимальный порог рейтинга
    int frame_founded; //порог рейтинга искомой картинки
    int id;

public:   
    Settings();
    void load_settings();
    void save_settings();
    void default_settings();


    bool getseg();
    int getkadrov();
    int gety_sectors();
    int getx_sectors();
    QString getpath_library();
    QString getpath_films();
    int getframe_maybe();
    int getframe_founded();
    int getid();

    void setseg(bool x);
    void setkadrov(int x);
    void sety_sectors(int x);
    void setx_sectors(int x);
    void setpath_library(QString x);
    void setpath_films(QString x);
    void setframe_maybe(int x);
    void setframe_founded(int x);
    void setid(int x);

};

#endif // SETTINGS_H
