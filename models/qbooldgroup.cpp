#include "qbooldgroup.h"

QBooldGroup::QBooldGroup(quint8 type, QString rezus, quint64 who_id, quint64 id, QObject *per)
    :QObject(per)
{
    this->m_group=static_cast<QBooldGroup::BOOLD_GROUP>(type);
    this->m_rFactor = rezus;
    this->m_whBooldId = who_id;
    this->m_id = id;
}

QBooldGroup::QBooldGroup(const QBooldGroup &qb)
{
    this->m_group = qb.getBooldGroup();
    this->m_id = qb.getId();
    this->m_rFactor = qb.getRFactor();
    this->m_whBooldId = qb.getWhoBooldId();
}

QBooldGroup::QBooldGroup(QBooldGroup &&qb)
{
    this->m_group = qb.getBooldGroup();
    this->m_id = qb.getId();
    this->m_rFactor = qb.getRFactor();
    this->m_whBooldId = qb.getWhoBooldId();
}

QBooldGroup &QBooldGroup::operator=(const QBooldGroup &qb)
{
    if(&qb!=this)
    {
        this->m_group = qb.getBooldGroup();
        this->m_id = qb.getId();
        this->m_rFactor = qb.getRFactor();
        this->m_whBooldId = qb.getWhoBooldId();
    }

    return *this;
}

QBooldGroup::~QBooldGroup()
{

}

QString QBooldGroup::getRFactor() const
{
    return this->m_rFactor;
}

QBooldGroup::BOOLD_GROUP QBooldGroup::getBooldGroup() const
{
    return this->m_group;
}

QString QBooldGroup::getBGroupRim() const
{
    switch(m_group)
    {
    case BOOLD_GROUP::O:
        return "I";
    case BOOLD_GROUP::A:
        return "II";
    case BOOLD_GROUP::B:
        return "III";
    case BOOLD_GROUP::AB:
        return "IV";
    }
    return "I";
}

quint64 QBooldGroup::getId() const
{
    return this->m_id;
}

quint64 QBooldGroup::getWhoBooldId() const
{
    return this->m_whBooldId;
}
