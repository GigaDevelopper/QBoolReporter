#include "qdatabold.h"


QDataBold::QDataBold(const QDate &date, quint64 persId, const QString &desc, quint64 id, QObject *parent)
    :QObject(parent)
{
    this->m_date = date;
    this->m_personId = persId;
    this->m_description = desc;
    this->m_id = id;
}

QDataBold::QDataBold(const QDataBold &other)
    :QObject(other.parent())
{

    this->m_date = other.getDate();
    this->m_personId = other.getPersonId();
    this->m_description = other.getDescription();
    this->m_id = other.getId();
}

QDataBold &QDataBold::operator=(const QDataBold &other)
{
    if(this != &other)
    {

        this->m_date = other.getDate();
        this->m_personId = other.getPersonId();
        this->m_description = other.getDescription();
        this->m_id = other.getId();
    }
    return *this;
}

QDataBold::~QDataBold()
{

}

QDate QDataBold::getDate() const
{
    return m_date;
}

quint64 QDataBold::getPersonId() const
{
    return m_personId;
}

QString QDataBold::getDescription() const
{
    return m_description;
}

quint64 QDataBold::getId() const
{
    return m_id;
}
