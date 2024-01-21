#ifndef PERSONCONTROLLER_H
#define PERSONCONTROLLER_H

#include <QObject>
#include <memory>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "personmodel.h"
#include <vector>

using std::shared_ptr;
using std::vector;

class PersonController:QObject
{
    Q_OBJECT
public:
    explicit PersonController(shared_ptr<QSqlDatabase>_dBase);
    bool createPersonTable();//Добавление таблицы
    bool addPerson(const PersonModel& mdl);//Добавление персона
    bool dropPerson(quint64 id);//Удаление  персона
    std::vector<PersonModel> getAllPerson()const;//Получение всех
    PersonModel getPersonById(quint64 id);

    quint64 getIdByPhone(const QString &phone);
    ~PersonController();


private:
    shared_ptr<QSqlDatabase>m_base;
};

#endif // PERSONCONTROLLER_H
