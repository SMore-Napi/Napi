#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scan.h"
#include "addlibrary.h"
#include "editsettings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_scan_button_clicked()
{
    Scan wind(this);
    wind.show();
    wind.exec();
}

void MainWindow::on_add_to_library_button_clicked()
{
    AddLibrary wind(this);
    wind.show();
    wind.exec();
}

void MainWindow::on_edit_settings_button_clicked()
{
    EditSettings wind(this);
    wind.show();
    wind.exec();
}
