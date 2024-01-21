#ifndef QDOCUMENTCONTROL_H
#define QDOCUMENTCONTROL_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <utility>
#include <memory>
#include <vector>
#include "qdocumentmodel.h"
class QSqlDatabase;
class QSqlQuery;
class QSqlError;
using std::shared_ptr;
using std::make_shared;

class QDocumentControl:public QObject
{
    Q_OBJECT
public:

    explicit QDocumentControl(shared_ptr<QSqlDatabase>_dBase, QObject * parent=nullptr);

    bool createTable();

    bool addDocument(const QDocument& qd);//Добавление нового документа

    bool delDocumentById(quint64 id);//Удаление записи по ID

    QDocument getDocument(quint64 personId);
    std::vector<QDocument> getAllDocuments()const;

    ~QDocumentControl();


private:
    shared_ptr<QSqlDatabase>m_base;

};

#endif // QDOCUMENTCONTROL_H
