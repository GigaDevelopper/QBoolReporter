#include "personcontroller.h"


PersonController::PersonController(shared_ptr<QSqlDatabase> _dBase)
{
    this->m_base = _dBase;
}

bool PersonController::createPersonTable()
{
    QSqlQuery query(*m_base);
    QString squery = "CREATE TABLE  person("
        "id INTEGER PRIMARY KEY,"
        "name VARCHAR(50) NOT NULL,"
        "surname VARCHAR(50) NOT NULL,"
        "middlename VARCHAR(50) NOT NULL,"
        "birth TEXT DEFAULT \'2000-01-01\',"
        "sx INTEGER,"
        "addres TEXT DEFAULT \'Moscow\',"
        "phone VARCHAR(25) UNIQUE)";
    auto bl = query.exec(squery);
    qDebug()<<query.lastError().text();
    if(bl)
        m_base->commit();
    return bl;
}

bool PersonController::addPerson(const PersonModel &mdl)
{
  QString query = "INSERT INTO person(name,surname,middlename,birth,sx,addres,phone)"
        "VALUES(?,?,?,?,?,?,?)";
    QSqlQuery s_query(*m_base);
  s_query.prepare(query);
  s_query.bindValue(0,mdl.getName());
  s_query.bindValue(1,mdl.getSurName());
  s_query.bindValue(2,mdl.getMiddleName());
  s_query.bindValue(3,mdl.getBirthDay());
  quint8 s = static_cast<quint8>(mdl.getSex());
  s_query.bindValue(4,s);
  s_query.bindValue(5,mdl.getAdress());
  s_query.bindValue(6,mdl.getPhone());
  auto b = s_query.exec();
  if(b)
  {
        qDebug()<<"Inserted";
        m_base->commit();
  }
  return b;
}

bool PersonController::dropPerson(quint64 id)
{
   QString del_query = "DELETE FROM person "
                      "WHERE id=?";
   QSqlQuery query(*m_base);
   query.prepare(del_query);
   query.bindValue(0,id);
   auto b = query.exec();
   if(b)
   {
        //qDebug()<<"Deleted id"<<id;
        m_base->commit();
   }
   return b;
}

std::vector<PersonModel> PersonController::getAllPerson() const
{
   QString all = "SELECT * FROM person";
   QSqlQuery query(*m_base);
   query.exec(all);
   vector<PersonModel>v_base;
   while(query.next())
   {
        quint64 id = query.value(0).toULongLong();
        QString name = query.value(1).toString();
        QString surname = query.value(2).toString();
        QString middlename = query.value(3).toString();
        QDate birth = query.value(4).toDate();
        quint8 s = static_cast<quint8>(query.value(5).toUInt());
        QString adress = query.value(6).toString();
        QString phone = query.value(7).toString();
        v_base.emplace_back(name,surname,middlename,
                            birth,phone,s,adress,id);
   }
   return v_base;
}

PersonModel PersonController::getPersonById(quint64 id)
{
   QString all = "SELECT * FROM person WHERE id=" + QString::number(id);

   QSqlQuery query(*m_base);
   query.exec(all);
   qDebug()<<query.lastError().text();
   qDebug() <<"Hello getPersonById"<<id;
   while(query.next())
   {
        quint64 id = query.value(0).toULongLong();
        QString name = query.value(1).toString();
        QString surname = query.value(2).toString();
        QString middlename = query.value(3).toString();
        QDate birth = query.value(4).toDate();
        quint8 s = static_cast<quint8>(query.value(5).toUInt());
        QString adress = query.value(6).toString();
        QString phone = query.value(7).toString();
        qDebug() <<"Name "<<name;
        return PersonModel(name,surname,middlename,
                            birth,phone,s,adress,id);
   }
   qDebug() <<"Hello after";
   return PersonModel();
}

quint64 PersonController::getIdByPhone(const QString &phone)
{

   QString all = "SELECT * FROM person WHERE phone=" + phone;
   QSqlQuery query(*m_base);
   query.exec(all);
   while(query.next())
   {
        return query.value(0).toUInt();
   }
   return 0;
}

PersonController::~PersonController()
{

}
