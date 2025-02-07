#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMap>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QMap<QString, QString>* users, QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_loginBtn_clicked();

private:
    Ui::LoginDialog *ui;
    QMap<QString, QString>* userMap;
};

#endif // LOGINDIALOG_H
