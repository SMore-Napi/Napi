#include "addlibrary.h"
#include "ui_addlibrary.h"
#include <QFileDialog>
#include "settings.h"
#include <iostream>
#include <QDir>
#include <QFile>
#include "createframe.h"
#include <QDebug>



AddLibrary::AddLibrary(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLibrary)
{
    ui->setupUi(this);

    //загрузка настроек
    AddLibrary::set_settings();

    ui->progressBar->setVisible(false);


    connect(ui->film_name,SIGNAL(textChanged(QString)),this,SLOT(addEnabled()));
    connect(ui->path_images,SIGNAL(textChanged(QString)),this,SLOT(addEnabled()));



}

AddLibrary::~AddLibrary()
{
    delete ui;
}

void AddLibrary::on_pushButton_2_clicked()
{
    QString str = QFileDialog::getExistingDirectory(0, "Directory Dialog", "");
    ui->path_images->setText(str);
}



//загрузка настроек
void AddLibrary::set_settings()
{
    //загрузка настроек
    Settings stgs;
    //QWidgets получают значение в зависимости от настроек
    ui->seg->setChecked(stgs.getseg());
    if (stgs.getkadrov() == 3)
        ui->kadrov->setChecked(true);
    else ui->kadrov->setChecked(false);

    AddLibrary::addEnabled();

}


void AddLibrary::addEnabled()
{   
        if((ui->path_images->text() == "") ||(ui->film_name->text() == ""))
            ui->add_button->setEnabled(false);
        else ui->add_button->setEnabled(true);


}

//перевод в 16-ую систему
QString inttohex(int a)
{
    QString tmp("");
    do
    {
        int r(a%16);
        if (r>9) {r+=(int)'A'-10;}
        else  {r+=(int)'0';};
        tmp=(char)r+tmp;
        a/=16;
    } while (a);
    return tmp;
}


void AddLibrary::on_add_button_clicked()
{
    ui->progressBar->setVisible(true);
    ui->add_button->setVisible(false);



    Settings stgs;
    QString str;

    while(1)
    {
        str = stgs.getpath_films();
        str.append("//");
        str.append(inttohex(stgs.getid()));
        str.append(".txt");

        QFile file (str);
        if(file.exists())
            stgs.setid(stgs.getid()+1);
        else
        {
         stgs.setid(stgs.getid()+1);
         stgs.save_settings();
         file.close();
         break;
        }
        file.close();

    }

    QFile file(str);
    if(file.open(QIODevice::WriteOnly | QIODevice::Append ))
    {

        QTextStream stream(&file);

        stream << ui->film_name->text() << "\r\n";
        stream << ui->film_year->text() << "\r\n";
        stream << ui->film_country->text() << "\r\n";
        stream << ui->film_director->text() << "\r\n";
        stream << ui->film_script->text() << "\r\n";
        stream << ui->film_producer->text() << "\r\n";
        stream << ui->film_composer->text() << "\r\n";
        stream << ui->film_genre->text() << "\r\n";
        stream << ui->film_description->toPlainText() << "\r\n";


    }
    file.close();


    QDir mDir(ui->path_images->text());
    QString buffer;


    int countfiles(-2);

    for(QFileInfo temp : mDir.entryInfoList())
    {
        countfiles++;
    }

    if (ui->kadrov->isChecked())
    {
        QString *arr = new QString[countfiles];
        int check = 1;
        int ji(0);
        for(QFileInfo temp : mDir.entryInfoList())
        {

            arr[ji] = temp.absoluteFilePath();

            if (check <= 2)
            {
                check++;
            }
            else
            {
                ji++;

            }

        }

        ji = 0;

        for (int i(0); i < (countfiles - 2*ui->quantity->value()); i++)
        {
            ji++;
            ui->progressBar->setValue(i * 100 / countfiles);

            CreateFrame frame(arr[i], arr[i+ui->quantity->value()], arr[i+2*ui->quantity->value()], ui->seg->isChecked());
            QString key_path = stgs.getpath_library();
            key_path.append("//");
            key_path.append(frame.getkey());
            key_path.append(".txt");

            QFile f(key_path);
            if(f.open(QIODevice::WriteOnly | QIODevice::Append ))
                {
         QTextStream stream(&f);
                stream << frame.getframe() << i+1 << " " << ui->quantity->value() << " " << inttohex(stgs.getid()-1) << "\n";
                }
            f.close();

        }


        ui->progressBar->setValue(98);

        for (int i(ji); i < countfiles; i++)
        {

            CreateFrame frame(arr[i], ui->seg->isChecked());
            QString key_path = stgs.getpath_library();
            key_path.append("//");
            key_path.append(frame.getkey());
            key_path.append(".txt");

            QFile f(key_path);
            if(f.open(QIODevice::WriteOnly | QIODevice::Append ))
                {
         QTextStream stream(&f);
                stream << frame.getframe() << i+1 << " " << ui->quantity->value() << " " << inttohex(stgs.getid()-1) << "\n";
                }
            f.close();

        }


    }
    else
    {
        int check = 1;
        int number = 0;
        for(QFileInfo temp : mDir.entryInfoList())
        {

            buffer = temp.absoluteFilePath();

            if (check <= 2)
            {
                check++;
            }
            else
            {
                ui->progressBar->setValue(number * 100 / countfiles);
                number++;

                    CreateFrame frame(buffer, ui->seg->isChecked());

                    QString key_path = stgs.getpath_library();
                    key_path.append("//");
                    key_path.append(frame.getkey());
                    key_path.append(".txt");

                    QFile f(key_path);
                    if(f.open(QIODevice::WriteOnly | QIODevice::Append ))
                        {
                 QTextStream stream(&f);
                        stream << frame.getframe() << number << " " << ui->quantity->value() << " " << inttohex(stgs.getid()-1) << "\n";
                        }
                    f.close();

            }

        }
    }






    this->close();


}



