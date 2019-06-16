#include "settings.h"
#include <fstream>
#include <QTextStream>
#include <QFile>

using namespace std;


Settings::Settings()
{
    Settings::default_settings();
    Settings::load_settings();

}

void Settings::load_settings()
{
    QFile file ("settings.txt");

    if(file.open(QIODevice::ReadOnly))
    {

       QTextStream stream(&file);
       QString str;

       str  = stream.readLine();
       if (str == "0")
           Settings::seg = false;
       else Settings::seg = true;

       str = stream.readLine();
       Settings::kadrov = str.toInt();

       str = stream.readLine();
       Settings::y_sectors = str.toInt();

       str = stream.readLine();
       Settings::x_sectors = str.toInt();

       Settings::path_library = stream.readLine();
       Settings::path_films = stream.readLine();

       str = stream.readLine();
       Settings::frame_maybe = str.toInt();

       str = stream.readLine();
       Settings::frame_founded = str.toInt();

       str = stream.readLine();
       Settings::id = str.toInt();
    }

    file.close();
}

void Settings::save_settings()
{
    ofstream fout("settings.txt");

    fout << Settings::seg << endl;
    fout << Settings::kadrov << endl;
    fout << Settings::y_sectors << endl;
    fout << Settings::x_sectors << endl;
    fout << Settings::path_library.toStdString() << endl;
    fout << Settings::path_films.toStdString() << endl;
    fout << Settings::frame_maybe << endl;
    fout << Settings::frame_founded << endl;
    fout << Settings::id << endl;

    fout.close();

}

void Settings::default_settings()
{
    Settings::seg = false;
    Settings::kadrov = 1;
    Settings::y_sectors = 9;
    Settings::x_sectors = 16;
    Settings::path_library = "//";
    Settings::path_films = "//";
    Settings::frame_maybe = 70;
    Settings::frame_founded = 90;
    Settings::id = 1;

}


bool Settings::getseg()
{
    return Settings::seg;
}
int Settings::getkadrov()
{
    return Settings::kadrov;
}
int Settings::gety_sectors()
{
    return Settings::y_sectors;
}
int Settings::getx_sectors()
{
    return Settings::x_sectors;
}
QString Settings::getpath_library()
{
    return Settings::path_library;
}
QString Settings::getpath_films()
{
    return Settings::path_films;
}
int Settings::getframe_maybe()
{
    return Settings::frame_maybe;
}
int Settings::getframe_founded()
{
    return Settings::frame_founded;
}

int Settings::getid()
{
    return Settings::id;
}

void Settings::setseg(bool x)
{
    Settings::seg = x;
}
void Settings::setkadrov(int x)
{
    Settings::kadrov = x;
}
void Settings::sety_sectors(int x)
{
    Settings::y_sectors = x;
}
void Settings::setx_sectors(int x)
{
    Settings::x_sectors = x;
}
void Settings::setpath_library(QString x)
{
    Settings::path_library = x;
}
void Settings::setpath_films(QString x)
{
    Settings::path_films = x;
}
void Settings::setframe_maybe(int x)
{
    Settings::frame_maybe = x;
}
void Settings::setframe_founded(int x)
{
    Settings::frame_founded = x;
}
void Settings::setid(int x)
{
    Settings::id = x;
}
