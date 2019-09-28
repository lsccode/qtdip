#ifndef WIDGETSMOOTHIMG_H
#define WIDGETSMOOTHIMG_H

#include <QWidget>

#include "widgetShow/widgetshow.h"

class widgetSmoothImg : public widgetShow
{
public:
    widgetSmoothImg();

public:
    virtual void imageProcess(QImage image,  int action);
    virtual void createAction();

private:
    // 对二值图像的黑白点噪声消除
    void imageNoiseReBinary(QImage *psrcImage, QImage **ppdstImage);
    //对二值图像进行消除孤立黑像素点。
    void imageSingleBlack(QImage *psrcImage, QImage **ppdstImage);
    //对二值图像进行消除孤立黑像素点。
    void imageFieldAvg3x3(QImage *psrcImage, QImage **ppdstImage);


};

#endif // WIDGETSMOOTHIMG_H
