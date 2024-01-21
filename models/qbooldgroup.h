#ifndef QBOOLDGROUP_H
#define QBOOLDGROUP_H

#include <QObject>

//Группа крови и резусь фактор

class QBooldGroup:QObject
{
    Q_OBJECT
public:
    explicit QBooldGroup(quint8 type, QString rezus,
            quint64 who_id, quint64 id=0, QObject* per=nullptr);


    QBooldGroup(const QBooldGroup& qb);
    QBooldGroup(QBooldGroup&& qb);
    QBooldGroup &operator=(const QBooldGroup& qb);

    ~QBooldGroup();

    enum class BOOLD_GROUP:quint8
    {
        O,//Первая группа крови
        A,//Второя группа крови
        B,//Третьая группа крови
        AB//Четвертая группа крови
    };

    QString getRFactor()const;
    QBooldGroup::BOOLD_GROUP getBooldGroup()const;//простое представление
    QString getBGroupRim()const;//Римское представление
    quint64 getId()const;
    quint64 getWhoBooldId()const;

private:
    BOOLD_GROUP m_group;//Группа крови
    QString m_rFactor;//Резусь фактор
    quint64 m_id;//ИД
    quint64 m_whBooldId;//Кому пренадлежить ID person

};

#endif // QBOOLDGROUP_H
