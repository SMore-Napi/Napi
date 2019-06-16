#ifndef ADDLIBRARY_H
#define ADDLIBRARY_H

#include <QDialog>

namespace Ui {
class AddLibrary;
}

class AddLibrary : public QDialog
{
    Q_OBJECT

public:
    explicit AddLibrary(QWidget *parent = 0);
    ~AddLibrary();

private slots:
    void addEnabled();
    void set_settings();
    void on_pushButton_2_clicked();
    void on_add_button_clicked();

private:
    Ui::AddLibrary *ui;
};

#endif // ADDLIBRARY_H
