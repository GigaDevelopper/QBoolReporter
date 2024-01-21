#include "personmodel.h"

PersonModel::PersonModel()
{
    this->m_birthday=QDate::currentDate();
    this->m_name="";
    this->m_surname ="";
    this->m_id = 0;
    this->m_number ="+77777777";
    this->m_sx=PersonModel::QSEX::MAN;
    this->m_midlename = "";
    this->m_adress ="Moscow";
}


PersonModel::PersonModel(const QString &name, const QString &sur, const QString &midl,
                         const QDate &brth, const QString &num, quint8 sx, const QString &adres,quint64 id)

{
    this->m_name = name;
    this->m_surname = sur;
    this->m_midlename = midl;
    this->m_number = num;
    this->m_adress = adres;
    this->m_birthday = brth;
    this->m_id=id;
    this->m_sx=static_cast<QSEX>(sx);
}

PersonModel::PersonModel(const PersonModel &p)
{
    this->m_adress=p.getAdress();
    this->m_birthday=p.getBirth();
    this->m_id=p.getId();
    this->m_midlename=p.getMiddleName();
    this->m_name=p.getName();
    this->m_surname = p.getSurName();
    this->m_number=p.getPhone();
    this->m_sx = p.getSex();
}

PersonModel::PersonModel(PersonModel &&per)
{

    this->m_adress=std::move(per.m_adress);
    this->m_birthday=std::move(per.m_birthday);
    this->m_id=per.getId();
    this->m_midlename=per.m_midlename;
    this->m_name=per.m_name;
    this->m_surname =per.m_surname;
    this->m_number=std::move(per.m_number);
    this->m_sx = per.getSex();
}

PersonModel &PersonModel::operator=(const PersonModel &p)
{
    if(this != &p)
    {
        this->m_adress=p.getAdress();
        this->m_birthday=p.getBirth();
        this->m_id=p.getId();
        this->m_midlename=p.getMiddleName();
        this->m_name=p.getName();
        this->m_surname = p.getSurName();
        this->m_number=p.getPhone();
        this->m_sx = p.getSex();
    }
    return *this;
}

PersonModel::~PersonModel()
{
    qDebug()<<"Deleted Object Person Model";
}


quint64 PersonModel::getId() const
{
    return m_id;
}

QString PersonModel::getName() const
{
    return this->m_name;
}

QString PersonModel::getSurName() const
{
   return this->m_surname;
}

QString PersonModel::getMiddleName() const
{
   return m_midlename;
}

QString PersonModel::getPhone() const
{
   return m_number;
}

QString PersonModel::getAdress() const
{
   return m_adress;
}

QString PersonModel::getSexString() const
{
   switch (m_sx)
   {
   case PersonModel::QSEX::MAN:
       return "Мужчина";
   case PersonModel::QSEX::WOMAN:
       return "Женьшина";
   }
   return "";
}

QString PersonModel::getBirthDay() const
{
   return m_birthday.toString("yyyy-MM-dd");
}

PersonModel::QSEX PersonModel::getSex() const
{
   return this->m_sx;
}

quint16 PersonModel::getAge() const
{
   auto cur = QDate::currentDate();
   return cur.year() - this->m_birthday.year();
}

QDate PersonModel::getBirth() const
{
   return m_birthday;
}

QDebug &operator<<(QDebug dbg, const PersonModel& p)
{
   dbg<<p.getId()<<" "<<p.getName()<<" "<<p.getSurName()<<" "<<p.getSexString();
   dbg<<"  "<<p.getAdress()<<" "<<p.getPhone()<<p.getBirthDay();
   return dbg;
}
