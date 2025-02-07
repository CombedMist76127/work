#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QMessageBox>

RegisterDialog::RegisterDialog(QMap<QString, QString>* users, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
    , userMap(users)
{
    ui->setupUi(this);
    ui->passwordEdit->setEchoMode(QLineEdit::Password);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_registerBtn_clicked()
{
    QString username = ui->usernameEdit->text().trimmed();
    QString password = ui->passwordEdit->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "注册失败", "用户名和密码不能为空");
        return;
    }

    if (userMap->contains(username)) {
        QMessageBox::warning(this, "注册失败", "用户名已存在");
    } else {
        userMap->insert(username, password);
        QMessageBox::information(this, "注册成功", "账户创建成功");
        accept();
    }
}
