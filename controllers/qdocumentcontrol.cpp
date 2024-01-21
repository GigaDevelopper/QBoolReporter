#include "qdocumentcontrol.h"

QDocumentControl::QDocumentControl(shared_ptr<QSqlDatabase> _dBase, QObject *parent)
    :QObject(parent)
{
    m_base = _dBase;
}

bool QDocumentControl::createTable()
{
  QString tb = "CREATE TABLE document("
                 "id INTEGER PRIMARY KEY,"
                 "type INTEGER NOT NULL DEFAULT 0,"
                 "date_when TEXT NOT NULL DEFAULT \'2022-01-01\',"
                 "fromId INTEGER,"
                 "ownerId INTEGER,"
                 "FOREIGN KEY(fromId) REFERENCES person(id) ON DELETE SET NULL,"
                 "FOREIGN KEY(ownerId) REFERENCES person(id) ON DELETE SET NULL)";
    QSqlQuery query(*m_base);
  auto b = query.exec(tb);
    if(b)
  {
      m_base->commit();
  }
  else
      qDebug()<<query.lastError().text();
  return b;
}

bool QDocumentControl::addDocument(const QDocument &qd)
{
    QString add = "INSERT INTO document(type,date_when,fromId,ownerId)"
                " VALUES(?,?,?,?)";
    QSqlQuery q(*m_base);
    q.prepare(add);
    q.bindValue(0,static_cast<quint8>(qd.getTypeDocument()));
    q.bindValue(1,qd.getDateWhen());
    q.bindValue(2,qd.getFromPerson());
    q.bindValue(3,qd.getOwnerId());
    auto b = q.exec();
    if(b)
      m_base->commit();
    else
      qDebug()<<q.lastError().text();
    return b;
}

bool QDocumentControl::delDocumentById(quint64 id)
{
    QString dl = "DELETE FROM document "
                 "WHERE id=?";
    QSqlQuery q(*m_base);
    q.prepare(dl);
    q.bindValue(0,id);
    auto b = q.exec();
    if(b)
      m_base->commit();
    else
      qDebug()<<q.lastError().text();

    return b;
}

QDocument QDocumentControl::getDocument(quint64 personId)
{
   QString sql = "SELECT * FROM document"
                  "WHERE ownerId = ?";
    QSqlQuery query(*m_base);
    query.prepare(sql);
    query.bindValue(0,personId);
    query.exec();
    while(query.next())
    {
      quint64 id = query.value(0).toUInt();
      QDocument::DOCUMENT_TYPE type = static_cast<QDocument::DOCUMENT_TYPE>(query.value(1).toInt());
      QDate date = query.value(3).toDate();
      quint64 fromId = query.value(4).toUInt();
      quint64 ownerId = query.value(5).toUInt();
      return QDocument(type,fromId,date,ownerId,id);
    }
    return QDocument();
}

QDocumentControl::~QDocumentControl()
{

}

std::vector<QDocument> QDocumentControl::getAllDocuments() const
{
    QString all = "SELECT * FROM document";

    QSqlQuery query(*m_base);
    query.exec(all);

    std::vector<QDocument>v_base;

    while(query.next())
    {
      quint64 id = query.value(0).toULongLong();
      QDocument::DOCUMENT_TYPE type = static_cast<QDocument::DOCUMENT_TYPE>(query.value(1).toUInt());
      QDate date = query.value(2).toDate();

      quint64 fromId = query.value(3).toUInt();
      quint64 ownerId = query.value(4).toUInt();

      qDebug() << id << " "<<date.toString() << "  "<<fromId <<"  "<<ownerId;

      v_base.emplace_back(type,fromId,date,ownerId,id);
    }
    return v_base;
}
