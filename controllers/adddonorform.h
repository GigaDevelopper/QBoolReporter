#pragma once

#include "personcontroller.h"
#include "qdatacontroller.h"
#include "qbooldcontroller.h"
#include "qdocumentcontrol.h"


#include <QWidget>
#include <QSqlDatabase>
#include <utility>
#include <memory.h>

namespace Ui {
class AddDonorForm;
}

class AddDonorForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddDonorForm(std::shared_ptr<QSqlDatabase>db,QWidget *parent = nullptr);
    ~AddDonorForm();

private slots:
    void on_pushButton_clicked();

    void on_saveBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::AddDonorForm *ui;
    std::shared_ptr<QSqlDatabase>db;
};

