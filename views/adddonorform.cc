#include "adddonorform.h"
#include "ui_adddonorform.h"

AddDonorForm::AddDonorForm(std::shared_ptr<QSqlDatabase>db,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDonorForm)
{
    ui->setupUi(this);
    this->db = db;
}

AddDonorForm::~AddDonorForm()
{
    delete ui;
}

void AddDonorForm::on_pushButton_clicked()
{

}


void AddDonorForm::on_saveBtn_clicked()
{
    auto namePerson = ui->nameEdit->text();
    auto surnamePerson = ui->surNameEdit->text();
    auto middlenamePerson = ui->middleNameEdit->text();
    auto addres = ui->adressEdit->text();
    db->transaction();
    auto phone = ui->phoneEdit->text();
    QDate birth = ui->dateEdit->date();
    PersonModel::QSEX sx = PersonModel::QSEX::MAN;
    if(ui->fmlRadioBtn->isChecked())
        sx = PersonModel::QSEX::WOMAN;
    PersonModel per(namePerson,
                    surnamePerson,middlenamePerson,
                    birth,phone,(quint8)sx,addres);

    PersonController pCntr(this->db);
    pCntr.addPerson(per);
    quint64  perId = pCntr.getIdByPhone(per.getPhone());
    //add bold group
    quint8 btype = ui->groupComboBox->currentIndex();
    auto rezus = ui->rezusEdit->text();
    QBooldGroup bgroup(btype,rezus,perId);

    //add bold to database
    QBooldController bCntr(db);
    bCntr.addBooldGroup(bgroup);

    QDocumentControl dCntr(db);
    if(ui->medCarCheck->isChecked())
    {
        QDocument curD(0,perId,QDate::currentDate(),perId);
        dCntr.addDocument(curD);
    }

    if(ui->medAnalyseCheck->isChecked())
    {
        QDocument curD(1,perId,QDate::currentDate(),perId);
        dCntr.addDocument(curD);
    }

    if(ui->PassportCheck->isChecked())
    {
        QDocument curD(1,perId,QDate::currentDate(),perId);
        dCntr.addDocument(curD);
    }

    //Add DataController
    QDataController dataCntrl(db);
    QDataBold dbold(QDate::currentDate(),perId,"---");
    dataCntrl.insertData(dbold);
    db->commit();
    this->close();

}


void AddDonorForm::on_cancelBtn_clicked()
{
    this->close();
}

