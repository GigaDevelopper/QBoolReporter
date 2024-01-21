#pragma once

#include <QWidget>
#include <personmodel.h>
#include "qbooldgroup.h"

namespace Ui {
class QDataVoew;
}

class QDataVoew : public QWidget
{
    Q_OBJECT

public:
    explicit QDataVoew(QWidget *parent = nullptr);
    ~QDataVoew();
public slots:

    void setPerson(const PersonModel &per);
    void setBold(const QBooldGroup &bold);
    void setDescription(const QString &desc);
    QSize sizeHint()const override;

private:
    Ui::QDataVoew *ui;
};

