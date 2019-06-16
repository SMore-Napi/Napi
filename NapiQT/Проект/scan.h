#ifndef SCAN_H
#define SCAN_H

#include <QDialog>

namespace Ui {
class Scan;
}

class Scan : public QDialog
{
    Q_OBJECT

public:
    explicit Scan(QWidget *parent = 0);
    ~Scan();

private slots:
    void scanEnabled();
    void set_settings();
    void show_kadrov();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_kadrov_stateChanged(int arg1);

    void on_scan_button_clicked();

private:
    Ui::Scan *ui;
public:
    QString name;


};

#endif // SCAN_H
