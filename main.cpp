#include <QApplication>
#include "mainwindow.h"
#include "views/signinform.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SignInForm sign;
    sign.show();
    MainWindow wind;
    QObject::connect(&sign,&SignInForm::showMainWindow,&wind, &MainWindow::show);
    return a.exec();
}
