#include "qdatavoew.h"
#include "ui_qdatavoew.h"

QDataVoew::QDataVoew(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QDataVoew)
{
    ui->setupUi(this);
}

QDataVoew::~QDataVoew()
{
    delete ui;
}

void QDataVoew::setPerson(const PersonModel &per)
{
    ui->lblFio->setText(per.getSurName());
    ui->lblAdress->setText(per.getAdress());
    ui->lblBirth->setText(per.getBirth().toString());
    ui->lblPhone->setText(per.getPhone());
    if(per.getSex()==PersonModel::QSEX::MAN)
        ui->maleRadiBtn->setChecked(true);
    else
        ui->fmRadioBtn->setChecked(true);
}

void QDataVoew::setBold(const QBooldGroup &bold)
{
    ui->lblBoldGroup->setText(bold.getBGroupRim());
    ui->lblRezus->setText(bold.getRFactor());
}

void QDataVoew::setDescription(const QString &desc)
{
    ui->descTxt->setPlainText(desc);
}

QSize QDataVoew::sizeHint() const
{
    return QSize(450,450);
}
