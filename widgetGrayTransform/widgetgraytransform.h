#ifndef WIDGETGRAYTRANSFORM_H
#define WIDGETGRAYTRANSFORM_H

#include <QWidget>
#include <QImage>

#include "widgetShow/widgetshow.h"

class widgetGrayTransform : public widgetShow
{
    Q_OBJECT
public:
    explicit widgetGrayTransform(QWidget *parent = nullptr);

public:
    virtual void imageProcess(QImage image,  int action);
    virtual void createAction();

signals:

public slots:
};

#endif // WIDGETGRAYTRANSFORM_H
