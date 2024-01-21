#ifndef QBOOLDCONTROLLER_H
#define QBOOLDCONTROLLER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <memory>
#include <utility>
#include <vector>
#include "qbooldgroup.h"


using std::vector;

class QSqlDatabase;
class QSqlQuery;
class QSqlError;
using std::shared_ptr;
using std::make_shared;
class QBooldGroup;

class QBooldController:QObject
{
    Q_OBJECT
public:
    explicit QBooldController(shared_ptr<QSqlDatabase>_dBase, QObject*parent=nullptr);
    bool createTable();
    bool addBooldGroup(const QBooldGroup& qb);
    QBooldGroup getBooldByPersonId(quint64 id);

    vector<QBooldGroup> getAllBFactors()const;


private:
    shared_ptr<QSqlDatabase>m_base;
};

#endif // QBOOLDCONTROLLER_H
