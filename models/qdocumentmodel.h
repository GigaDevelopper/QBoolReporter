#ifndef QDOCUMENTMODEL_H
#define QDOCUMENTMODEL_H

#include <QObject>
#include <QDate>

class QDate;

class QDocument:public QObject
{
    Q_OBJECT

public:
    enum class DOCUMENT_TYPE:quint8
    {
        MED_CART,//Полис:
        MED_ANALYSE,//Направлене от врача
        PASSPORT,//Паспорт
    };
    QDocument()=default;
    QDocument(quint8 type,quint64 fromId,const QDate& when,quint64 idOwner,
                 quint64 id=0);

    QDocument(QDocument::DOCUMENT_TYPE type,quint64 fromId,const QDate& when,quint64 idOwner,
                 quint64 id=0);

    QDocument(const QDocument& other);

    QDocument(QDocument&& o);

    QDocument &operator = (const QDocument& o);

    ~QDocument();

    QDocument::DOCUMENT_TYPE getTypeDocument()const;

    quint64 getFromPerson()const;

    QDate getDateWhen()const;

    quint64 getOwnerId()const;

    quint64 getDocumentId()const;

    static QString docTypeToString(QDocument::DOCUMENT_TYPE type);

private:
    quint64 m_IdOwner;//Кому принадлежит это документ
    quint64 m_id;//ИД документа
    quint64 m_fromPersonId;//Кем видан
    DOCUMENT_TYPE m_type;//Тип документа
    QDate m_when;//Когда было выдана документ

};

#endif // QLKKDOCUMENT_H
