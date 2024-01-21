#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <utility>
#include <QtSql>

#include <personcontroller.h>
#include <qdatacontroller.h>
#include <qbooldcontroller.h>
#include <qdocumentcontrol.h>
#include "adddonorform.h"

#include <qdatavoew.h>

using std::shared_ptr;
using std::make_shared;

class PersonModel;
class PersonController;
class QDocument;
class QDocumentControl;
class QDataBold;
class QDataController;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_filterBtn_clicked();

    void on_nextPageBtn_2_clicked();

    void on_nextPageBtn_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_findDocBtn_clicked();

    void on_findBoldBtn_clicked();

    void on_addBtn_clicked();

private:
    void createConnection();
private:
    Ui::MainWindow *ui;
    std::shared_ptr<QSqlDatabase>m_db;
    std::shared_ptr<AddDonorForm>m_donorAdd;
    void setPersons();
    void setDocuments();
    void setBFactors();


};
#endif // MAINWINDOW_H
