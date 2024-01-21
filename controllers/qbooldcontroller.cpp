#include "qbooldcontroller.h"

QBooldController::QBooldController(shared_ptr<QSqlDatabase> _dBase,
                                   QObject* parent):
    QObject(parent)
{
    this->m_base = _dBase;
}

bool QBooldController::createTable()
{
   QString q = "CREATE TABLE bfactor("
                "id INTEGER PRIMARY KEY,"
                "rezus VARCHAR(50) NOT NULL,"
                "b_group INTEGER NOT NULL,"
                "who_id INTEGER,"
                  "FOREIGN KEY(who_id) REFERENCES person(id))";
    QSqlQuery query(*m_base);
   auto b = query.exec(q);
    if(b)
   {
       m_base->commit();
        return b;
   }
   else
        qDebug()<<query.lastError().text();
   return false;
}

bool QBooldController::addBooldGroup(const QBooldGroup &qb)
{
    QString add = "INSERT INTO bfactor(rezus,b_group,who_id)"
                 " VALUES(?,?,?)";
   QSqlQuery q(*m_base);
    q.prepare(add);
   q.bindValue(0,qb.getRFactor());
    quint8 gr = static_cast<quint8>(qb.getBooldGroup());
   q.bindValue(1,gr);
   q.bindValue(2,qb.getWhoBooldId());
   auto b = q.exec();
   if(b)
   {
        m_base->commit();
        return b;
   }
   else
        qDebug()<<q.lastError().text();
   return b;
}

QBooldGroup QBooldController::getBooldByPersonId(quint64 id)
{
   QString qr = "SELECT * FROM bfactor "
                "WHERE who_id=?";
   QSqlQuery query(*m_base);
   query.prepare(qr);
   qDebug() <<id<<" id";
   query.bindValue(0,id);
   query.exec();
   while(query.next())
   {
        quint64  id_ = query.value(0).toULongLong();
        QString rez = query.value(1).toString();
        quint8 bldGroup = query.value(2).toUInt();
        return QBooldGroup(bldGroup, rez, id,id_);
   }
   throw std::invalid_argument("data base doesnt exists boold for this group");
}

vector<QBooldGroup> QBooldController::getAllBFactors() const
{
   QString all = "SELECT * FROM bfactor";
   QSqlQuery query(*m_base);
   query.exec(all);
   vector<QBooldGroup>v_base;
   while(query.next())
   {
        quint64 id = query.value(0).toULongLong();
        QString rezus = query.value(1).toString();
        quint8 type = query.value(2).toUInt();
        quint64 ownerId = query.value(3).toUInt();
        v_base.emplace_back(type,rezus,ownerId,id);
   }
   return v_base;
}
