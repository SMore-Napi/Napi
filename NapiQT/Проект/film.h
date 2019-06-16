#ifndef FILM_H
#define FILM_H

#include <QDialog>

namespace Ui {
class Film;
}

class Film : public QDialog
{
    Q_OBJECT

public:
    explicit Film(QWidget *parent = 0);
    ~Film();
private slots:
    void get_description();
    void set_description(QString kadr, QString quantity, QString name_temp);

private:
    Ui::Film *ui;
};

#endif // FILM_H
