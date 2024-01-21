#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //create connection
    this->createConnection();
    //seting Persons date
    this->setPersons();
    this->setDocuments();
    this->setBFactors();
    m_donorAdd = std::make_shared<AddDonorForm>(this->m_db);
}

MainWindow::~MainWindow()
{
    delete ui;
    m_db->close();
}


void MainWindow::on_filterBtn_clicked()
{
    QDate from = ui->fromDateEdit->date();
    QDate to = ui->dateEdit_2->date();

    QDataController dCntrl(m_db);
    auto all = dCntrl.getAll(from,to);

    qDebug() <<"Size of "<<all.size();
    ui->listWidget->clear();

    for(const auto &it:all)
    {
         auto perId = it.getPersonId();
         PersonController pCntrl(m_db);
         auto curPerson = pCntrl.getPersonById(perId);

         QBooldController qbCntrl(m_db);
         auto curBold = qbCntrl.getBooldByPersonId(perId);
         QDataVoew *view = new QDataVoew();
         view->setPerson(curPerson);
         view->setBold(curBold);
         view->setDescription(it.getDescription());
         QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
         item->setSizeHint(view->sizeHint());
         ui->listWidget->setItemWidget(item,view);
    }

}

void MainWindow::createConnection()
{

    m_db=std::make_shared<QSqlDatabase>(QSqlDatabase::addDatabase("QSQLITE"));
    m_db->setDatabaseName(QApplication::applicationDirPath()+"/base/my_bold_db.sqlite");
    if(m_db->open())
    {
         ui->statusbar->showMessage("Connected to data base",4);
    }
    else
         ui->statusbar->showMessage("Didnot connect to data base",4);
    PersonController per(m_db);

    if(per.createPersonTable())
         ui->statusbar->showMessage("Create Person table",4);
    else
         ui->statusbar->showMessage("Person Table has exists",4);

    QBooldController contr(m_db);

    if(contr.createTable())
         ui->statusbar->showMessage("BFactor table created",4);
    else
         ui->statusbar->showMessage("BFactor table has exists",4);

    QDocumentControl dcon(m_db);
    if(dcon.createTable())
         ui->statusbar->showMessage("Document table created",4);
    else
         ui->statusbar->showMessage("Document table has exists",4);

    QDataController dcnt(m_db);
    if(!dcnt.createDataTable())
         ui->statusbar->showMessage("Cannot create a new table",4);
    else
         ui->statusbar->showMessage("All of yes create table QDataControl");
    ui->fromDateEdit->setDate(QDate(2001,8,12));
    ui->dateEdit_2->setDate(QDate::currentDate());

}

void MainWindow::setPersons()
{
    ui->tableWidget->clearContents();

    PersonController pCntr(m_db);
    auto all = pCntr.getAllPerson();
    int curRow = 0;
    ui->tableWidget->setRowCount(all.size());

    for(const auto& it:all)
    {
         ui->tableWidget->setItem(curRow,0, new QTableWidgetItem(QString::number((it.getId()))));
         ui->tableWidget->setItem(curRow,1, new QTableWidgetItem(it.getName()));
         ui->tableWidget->setItem(curRow,2, new QTableWidgetItem(it.getSurName()));
         ui->tableWidget->setItem(curRow,3, new QTableWidgetItem(it.getMiddleName()));
         ui->tableWidget->setItem(curRow,4, new QTableWidgetItem(it.getBirthDay()));
         ui->tableWidget->setItem(curRow,5, new QTableWidgetItem(it.getSexString()));
         ui->tableWidget->setItem(curRow,6, new QTableWidgetItem(it.getAdress()));
         ui->tableWidget->setItem(curRow,7, new QTableWidgetItem(it.getPhone()));
         curRow++;
    }
}

void MainWindow::setDocuments()
{
    ui->docTableWidget->clearContents();

    QDocumentControl pCntr(m_db);
    auto all = pCntr.getAllDocuments();
    int curRow = 0;
    ui->docTableWidget->setRowCount(all.size());

    for(const auto& it:all)
    {

         ui->docTableWidget->setItem(curRow,0, new QTableWidgetItem(QString::number((it.getDocumentId()))));
         ui->docTableWidget->setItem(curRow,1, new QTableWidgetItem(QDocument::docTypeToString(it.getTypeDocument())));
         ui->docTableWidget->setItem(curRow,2, new QTableWidgetItem(it.getDateWhen().toString("yyyy-MM-dd")));
         ui->docTableWidget->setItem(curRow,3, new QTableWidgetItem(QString::number((it.getFromPerson()))));
         ui->docTableWidget->setItem(curRow,4, new QTableWidgetItem(QString::number((it.getOwnerId()))));
         curRow++;
    }
}

void MainWindow::setBFactors()
{
    ui->boldTableWidget->clearContents();

    QBooldController pCntr(m_db);
    auto all = pCntr.getAllBFactors();
    int curRow = 0;
    ui->boldTableWidget->setRowCount(all.size());

    for(const auto& it:all)
    {

         ui->boldTableWidget->setItem(curRow,0, new QTableWidgetItem(QString::number((it.getId()))));
         ui->boldTableWidget->setItem(curRow,1, new QTableWidgetItem(it.getRFactor()));
         ui->boldTableWidget->setItem(curRow,2, new QTableWidgetItem(it.getBGroupRim()));
         ui->boldTableWidget->setItem(curRow,3, new QTableWidgetItem(QString::number((it.getWhoBooldId()))));
         curRow++;
    }
}


void MainWindow::on_nextPageBtn_2_clicked()
{
    const QString &surName = ui->surNameEdit->text();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    PersonController pCntr(m_db);
    auto all = pCntr.getAllPerson();
    int curRow = 0;
    for(const auto& it:all)
    {
         if(!it.getSurName().contains(surName, Qt::CaseInsensitive))
             continue;
         ui->tableWidget->insertRow(curRow);
         ui->tableWidget->setItem(curRow,0, new QTableWidgetItem(QString::number((it.getId()))));
         ui->tableWidget->setItem(curRow,1, new QTableWidgetItem(it.getName()));
         ui->tableWidget->setItem(curRow,2, new QTableWidgetItem(it.getSurName()));
         ui->tableWidget->setItem(curRow,3, new QTableWidgetItem(it.getMiddleName()));
         ui->tableWidget->setItem(curRow,4, new QTableWidgetItem(it.getBirthDay()));
         ui->tableWidget->setItem(curRow,5, new QTableWidgetItem(it.getSexString()));
         ui->tableWidget->setItem(curRow,6, new QTableWidgetItem(it.getAdress()));
         ui->tableWidget->setItem(curRow,7, new QTableWidgetItem(it.getPhone()));
         curRow++;
    }
}


void MainWindow::on_nextPageBtn_clicked()
{
    ui->tabWidget->setCurrentIndex(1);
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 2)
    {
         setDocuments();
    }
    else
         if(index == 0)
         setPersons();
    else
         if(index == 3)
         setBFactors();
}


void MainWindow::on_findDocBtn_clicked()
{
    ui->docTableWidget->clearContents();
    ui->docTableWidget->setRowCount(0);

    QDocumentControl pCntr(m_db);
    auto all = pCntr.getAllDocuments();
    int curRow = 0;
    quint64 id = ui->personEditDocument->text().toUInt();
    for(const auto& it:all)
    {
         if(it.getOwnerId()!=id)
             continue;

         ui->docTableWidget->insertRow(curRow);
         ui->docTableWidget->setItem(curRow,0, new QTableWidgetItem(QString::number((it.getDocumentId()))));
         ui->docTableWidget->setItem(curRow,1, new QTableWidgetItem(QDocument::docTypeToString(it.getTypeDocument())));
         ui->docTableWidget->setItem(curRow,2, new QTableWidgetItem(it.getDateWhen().toString("yyyy-MM-dd")));
         ui->docTableWidget->setItem(curRow,3, new QTableWidgetItem(QString::number((it.getFromPerson()))));
         ui->docTableWidget->setItem(curRow,4, new QTableWidgetItem(QString::number((it.getOwnerId()))));
         curRow++;
    }
}


void MainWindow::on_findBoldBtn_clicked()
{
    ui->boldTableWidget->clearContents();
    ui->boldTableWidget->setRowCount(0);

    QBooldController pCntr(m_db);
    auto all = pCntr.getAllBFactors();
    int curRow = 0;
    ui->boldTableWidget->setRowCount(all.size());
    auto isB = [&](const QBooldGroup& gr)
    {
        bool cur[4] = {ui->firstCheckBold->isChecked(),
                        ui->secondCheckBold->isChecked(),
                        ui->secondCheckBold_2->isChecked(),
                       ui->secondCheckBold_3->isChecked()};
        switch(gr.getBooldGroup())
        {
        case QBooldGroup::BOOLD_GROUP::O:
            return  cur[0];
        case QBooldGroup::BOOLD_GROUP::A:
            return cur[1];
        case QBooldGroup::BOOLD_GROUP::B:
            return  cur[2];
        case QBooldGroup::BOOLD_GROUP::AB:
            return cur[3];
        default:
            return false;
        }
    };

    for(const auto& it:all)
    {
         if(!isB(it))
             continue;
         ui->boldTableWidget->insertRow(curRow);
         ui->boldTableWidget->setItem(curRow,0, new QTableWidgetItem(QString::number((it.getId()))));
         ui->boldTableWidget->setItem(curRow,1, new QTableWidgetItem(it.getRFactor()));
         ui->boldTableWidget->setItem(curRow,2, new QTableWidgetItem(it.getBGroupRim()));
         ui->boldTableWidget->setItem(curRow,3, new QTableWidgetItem(QString::number((it.getWhoBooldId()))));
         curRow++;
    }
}

void MainWindow::on_addBtn_clicked()
{
    this->m_donorAdd->show();
}

