#pragma once

#include <QWidget>

namespace Ui {
class SignInForm;
}

class SignInForm : public QWidget
{
    Q_OBJECT

public:
    explicit SignInForm(QWidget *parent = nullptr);
    ~SignInForm();
signals:
    void showMainWindow();

private slots:
    void on_signInBtn_clicked();

private:
    Ui::SignInForm *ui;
};

