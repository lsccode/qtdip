#ifndef WIDGETGEOMETRY_H
#define WIDGETGEOMETRY_H

#include <QWidget>
#include "widgetShow/widgetshow.h"

class widgetGeometryTransform : public widgetShow
{
public:
    widgetGeometryTransform();

public:
    virtual void imageProcess(QImage image,  int action);
    virtual void createAction();
    virtual void createOneAction(QString str, int action);
private:
    void imageMove(QImage *psrcImage, QImage *pdstImage);
    void imageHor(QImage *psrcImage, QImage *pdstImage);
    void imageVer(QImage *psrcImage, QImage *pdstImage);


};

#endif // WIDGETGEOMETRY_H
