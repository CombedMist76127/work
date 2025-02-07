#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QMap>

namespace Ui {
class RegisterDialog;
}

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegisterDialog(QMap<QString, QString>* users, QWidget *parent = nullptr);
    ~RegisterDialog();

private slots:
    void on_registerBtn_clicked();

private:
    Ui::RegisterDialog *ui;
    QMap<QString, QString>* userMap;
};

#endif // REGISTERDIALOG_H
