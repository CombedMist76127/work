#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QMap<QString, QString>* users, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
    , userMap(users)
{
    ui->setupUi(this);
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    QString username = ui->usernameEdit->text().trimmed();
    QString password = ui->passwordEdit->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "登录失败", "用户名和密码不能为空");
        return;
    }

    if (!userMap->contains(username)) {
        QMessageBox::warning(this, "登录失败", "用户名不存在");
    } else if (userMap->value(username) != password) {
        QMessageBox::warning(this, "登录失败", "密码错误");
    } else {
        QMessageBox::information(this, "登录成功", "欢迎回来，" + username);
        accept();
    }
}
