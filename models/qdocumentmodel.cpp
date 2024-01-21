#include "qdocumentmodel.h"

QDocument::QDocument(quint8 type, quint64 fromId, const QDate &when, quint64 idOwner,
                           quint64 id)
    :m_fromPersonId{fromId},m_IdOwner{idOwner},m_id{id}
{
    this->m_type=(QDocument::DOCUMENT_TYPE)type;
    this->m_when=when;
}

QDocument::QDocument(DOCUMENT_TYPE type, quint64 fromId, const QDate &when, quint64 idOwner, quint64 id)
    :m_fromPersonId{fromId},m_IdOwner{idOwner},m_id{id}
{
    this->m_type=type;
    this->m_when = when;
}

QDocument::QDocument(const QDocument &other)
{
    this->m_fromPersonId=other.getFromPerson();
    this->m_id = other.getDocumentId();
    this->m_IdOwner = other.getOwnerId();
    this->m_type = other.getTypeDocument();
    this->m_when = other.getDateWhen();
}

QDocument::QDocument(QDocument &&o)
    :m_id{o.m_id},m_type{o.m_type},m_IdOwner{o.m_IdOwner},m_when{o.m_when},m_fromPersonId{o.m_fromPersonId}
{

}

QDocument &QDocument::operator =(const QDocument &other)
{
    if(this!=&other)
    {
        this->m_fromPersonId=other.getFromPerson();
        this->m_id = other.getDocumentId();
        this->m_IdOwner = other.getOwnerId();
        this->m_type = other.getTypeDocument();
        this->m_when = other.getDateWhen();
    }
    return *this;
}

QDocument::~QDocument()
{

}

QDocument::DOCUMENT_TYPE QDocument::getTypeDocument() const
{
    return m_type;
}

quint64 QDocument::getFromPerson() const
{
    return m_fromPersonId;
}

QDate QDocument::getDateWhen() const
{
    return m_when;
}

quint64 QDocument::getOwnerId() const
{
    return m_IdOwner;
}

quint64 QDocument::getDocumentId() const
{
    return m_id;
}

QString QDocument::docTypeToString(DOCUMENT_TYPE type)
{
    switch(type)
    {
    case QDocument::DOCUMENT_TYPE::MED_CART:
        return "MED _CART";

    case QDocument::DOCUMENT_TYPE::PASSPORT:
        return "PASSPORT";

    case QDocument::DOCUMENT_TYPE::MED_ANALYSE:
        return "Med Analyse";
    }
    return "";
}
