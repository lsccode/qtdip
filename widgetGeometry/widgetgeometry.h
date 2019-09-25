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
    // 图像平移
    void imageMove(QImage *psrcImage, QImage **ppdstImage);
    // 水平镜像
    void imageHor(QImage *psrcImage, QImage **ppdstImage);
    // 垂直镜像
    void imageVer(QImage *psrcImage, QImage **ppdstImage);
    // 图像转置
    void imageTrans(QImage *psrcImage, QImage **ppdstImage);
    // 图像放大
    void imageZoomIn(QImage *psrcImage, QImage **ppdstImage);


};

#endif // WIDGETGEOMETRY_H
