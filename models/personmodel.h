#ifndef PERSONMODEL_H
#define PERSONMODEL_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QTime>
#include <QDebug>
#include <utility>
class QString;
class QDate;
class PersonModel:public QObject
{
    Q_OBJECT
public:
    enum class QSEX:quint8{
        MAN,
        WOMAN
    };
    PersonModel();
    PersonModel(const QString& name, const QString& sur, const QString& midl,
                const QDate &brth, const QString& num,
                quint8 sx, const QString & adres,quint64 id=0);

    PersonModel(const PersonModel& p);
    PersonModel(PersonModel&& per);
    PersonModel &operator=(const PersonModel& p);
    ~PersonModel();
    quint64 getId()const;
    QString getName()const;
    QString getSurName()const;
    QString getMiddleName()const;
    QString getPhone()const;
    QString getAdress()const;
    QString getSexString()const;
    QString getBirthDay()const;
    PersonModel::QSEX getSex()const;
    quint16 getAge()const;
    QDate getBirth()const;
    friend QDebug &operator<<(QDebug dbg, const PersonModel& p);

private:
    QString m_adress;//Адрес
    quint64 m_id;
    QString m_name;//Имя
    QString m_surname;//Фамилия
    QString m_midlename;//Отчество
    QDate m_birthday;//Дата рождение
    QString m_number;//Номер телефона
    QSEX m_sx;//Поль

};
#endif // PERSONMODEL_H
