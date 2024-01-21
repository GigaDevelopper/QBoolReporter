#include "qdatacontroller.h"

QDataController::QDataController(shared_ptr<QSqlDatabase> _dBase)
{
    m_base = _dBase;
}

QDataController::~QDataController()
{

}

bool QDataController::createDataTable()
{
    QSqlQuery query(*m_base);
    QString squery = "CREATE TABLE  Data("
                     "id INTEGER PRIMARY KEY,"
                     "date TEXT DEFAULT \'2000-01-01\',"
                     "personId INTEGER NOT NULL,"
                     "description TEXT DEFAULT \'-\')";

    auto bl = query.exec(squery);
    qDebug()<<query.lastError().text();
    if(bl)
        m_base->commit();
    return bl;
}

bool QDataController::insertData(const QDataBold &qd)
{
    QString query = "INSERT INTO Data(date,description)"
                    "VALUES(?,?,?)";

    QSqlQuery qr(*m_base);
    qr.prepare(query);
    auto dString = qd.getDate().toString("yyyy-MM-dd");
    qr.bindValue(0,dString);
    qr.bindValue(1,qd.getDescription());
    auto bl = qr.exec();
    if(!bl)
        qDebug() << qr.lastError().text();
    else
        qDebug() << "All ok inserted to Data table";
    return bl;
}

vector<QDataBold> QDataController::getAll()
{
    QString all = "SELECT * FROM Data";
    QSqlQuery query(*m_base);
    query.exec(all);
    vector<QDataBold>ans;
    while(query.next())
    {
        quint64 id = query.value(0).toUInt();
        QDate date = query.value(1).toDate();
        quint64 personId = query.value(2).toUInt();
        QString des = query.value(3).toString();
        ans.emplace_back(date,personId,des,id);
    }
    return ans;
}

vector<QDataBold> QDataController::getAll(const QDate &from, const QDate &to)
{

    QString all = "SELECT * FROM Data";
    QSqlQuery query(*m_base);
    query.exec(all);
    vector<QDataBold>ans;
    while(query.next())
    {
        quint64 id = query.value(0).toUInt();
        QDate date = query.value(1).toDate();
        quint64 personId = query.value(2).toUInt();
        QString des = query.value(3).toString();
        if(date>=from && date <= to)
        ans.emplace_back(date,personId,des,id);
    }
    return ans;
}

