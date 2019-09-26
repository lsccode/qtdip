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

private:
    // 图像二值化，非零元素取一
    void imageBinaryNotZeroSetOne(QImage *psrcImage, QImage **ppdstImage);
    // 图像二值化，设定某个阈值，超过则置为255，小于则置0，对RGB分别处理
    void imageBinaryThreshold(QImage *psrcImage, QImage **ppdstImage);
    // 图像二值化，双阈值， a < x < b,仅保留或去除这两个阈值之间的，此可以延伸到n个阈值范围
    void imageBinaryTwoThreshold(QImage *psrcImage, QImage **ppdstImage);

    // 灰度变换，反色处理
    void imageGrayInverColor(QImage *psrcImage, QImage **ppdstImage);
    //对图像进行窗口变换 x < a -> 0; x > b ->255
    void imageGrayWindow(QImage *psrcImage, QImage **ppdstImage);


signals:

public slots:
};

#endif // WIDGETGRAYTRANSFORM_H
