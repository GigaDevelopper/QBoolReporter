#include "signinform.h"
#include "ui_signinform.h"

#include <QMessageBox>

SignInForm::SignInForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SignInForm)
{
    ui->setupUi(this);
    setWindowTitle("Sign In");

}

SignInForm::~SignInForm()
{
    delete ui;
}

void SignInForm::on_signInBtn_clicked()
{
    const QString &phone = ui->phoneEdit->text();
    const QString &password = ui->passwordEdit->text();
    //qDebug() <<phone <<"  "<<password;
    if(phone == "+7-123-4567-891" && password=="maradov")
    {
        emit showMainWindow();
        this->close();
    }
    else
    {
        QMessageBox::critical(this,"Error","Password or phone incorrect");
        ui->passwordEdit->clear();
        ui->phoneEdit->clear();
    }
}

