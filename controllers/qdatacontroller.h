#pragma once

#include <QObject>
#include <utility>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include "qdatabold.h"
#include <vector>

using std::shared_ptr;
using std::make_shared;

using std::vector;

class QDataController:public QObject
{
    Q_OBJECT
public:
    explicit QDataController(shared_ptr<QSqlDatabase>_dBase);
    ~QDataController();

    bool createDataTable();
    bool insertData(const QDataBold& qd);
    vector<QDataBold> getAll();
    //getAll from a to b Date
    vector<QDataBold> getAll(const QDate &from, const QDate &to);


private:
   shared_ptr<QSqlDatabase>m_base;
};

