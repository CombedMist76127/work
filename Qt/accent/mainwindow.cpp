#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "registerdialog.h"
#include "logindialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_registerButton_clicked()
{
    RegisterDialog dlg(&users, this);
    dlg.exec();
}

void MainWindow::on_loginButton_clicked()
{
    LoginDialog dlg(&users, this);
    dlg.exec();
}
