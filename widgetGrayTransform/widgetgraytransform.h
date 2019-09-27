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
    // 灰度变换，对图像进行窗口变换 x < a -> 0; x > b ->255
    void imageGrayWindow(QImage *psrcImage, QImage **ppdstImage);
    // 灰度变换，分段线性变换
    void imagePiecewiseLine(QImage *psrcImage, QImage **ppdstImage);
    void createPiecewiseMap(int siX1, int siY1, int siX2, int siY2, int asiMap[256]);
    // 灰度变换，灰度分布均衡化
    void imageHistDistributioneEqualization(QImage *psrcImage, QImage **ppdstImage);
    void creatHist(QImage *psrcImage, double asiRedMap[256], double asiGreenMap[256], double asiBlueMap[256]);
    void creatHistNormal(QImage *psrcImage, double asiRedMap[256], double asiGreenMap[256], double asiBlueMap[256]);
    void creatHistAccumulative(QImage *psrcImage, double asiRedMap[256], double asiGreenMap[256], double asiBlueMap[256]);
    void createDistributionMap(QImage *psrcImage, int asiRedMap[256], int asiGreenMap[256], int asiBlueMap[256]);
    // 灰度变换，直方图匹配也叫直方图规定化
    void imageHistMatch(QImage *psrcImage, QImage **ppdstImage);
    void calcHistMatchMap(double adbSrcMap[256], double adbSrcpu[64], int asiSrcMap[], int asiRedMap[], int siDstSize);
    void createHistMatchMap(QImage *psrcImage, int asiRedMap[256], int asiGreenMap[256], int asiBlueMap[256]);




signals:

public slots:
};

#endif // WIDGETGRAYTRANSFORM_H
