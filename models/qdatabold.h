#pragma once

#include <QObject>
#include <QDate>

class QDate;

//основной класс для учета
class QDataBold:public QObject
{
    Q_OBJECT
public:
    QDataBold(const QDate& date,
              quint64 persId, const QString& desc, quint64 id = 0, QObject*parent=nullptr);

    QDataBold(const QDataBold& other);
    QDataBold &operator=(const QDataBold& other);
    ~QDataBold();
    QDate getDate()const;
    quint64 getPersonId()const;
    QString getDescription()const;
    quint64 getId()const;


private:
    QDate m_date;//
    quint64 m_personId;
    QString m_description;
    quint64 m_id;
};

