#include <QColor>
#include <QMessageBox>

#include "widgetgraytransform.h"
#include "dialogThreshold.h"
#include "dialogThresholdTwo.h"
#include "dialogGrayWindow.h"
#include "dialogPiecewiseLine.h"

enum {
    E_BINARY_NOT_ZERO_SET_ONE,
    E_BINARY_THRESHOLD,
    E_BINARY_THRESHOLD_TWO,
    E_GRAY_TRANS_INVERT_COLOR,
    E_GRAY_TRANS_WINDOW,
    E_GRAY_PEICEWISE_LINT,
    E_GRAY_DISTRU_EQ,
};

widgetGrayTransform::widgetGrayTransform(QWidget *parent) : widgetShow(parent)
{
    createAction();
}

void widgetGrayTransform::imageProcess(QImage image, int action)
{
    QImage *pImage = nullptr;

    switch (action) {
    case E_BINARY_NOT_ZERO_SET_ONE:
        imageBinaryNotZeroSetOne(&image, &pImage);
        break;
    case E_BINARY_THRESHOLD:
        imageBinaryThreshold(&image, &pImage);
        break;
    case E_BINARY_THRESHOLD_TWO:
        imageBinaryTwoThreshold(&image, &pImage);
        break;
    case E_GRAY_TRANS_INVERT_COLOR:
        imageGrayInverColor(&image, &pImage);
        break;
    case E_GRAY_TRANS_WINDOW:
        imageGrayWindow(&image, &pImage);
        break;
    case E_GRAY_PEICEWISE_LINT:
        imagePiecewiseLine(&image, &pImage);
        break;
    case E_GRAY_DISTRU_EQ:
        imageDistributioneEqualization(&image, &pImage);
        break;
    default:
        break;
    }

    if(pImage)
        m_pWgtRightShowAf->showImage(*pImage);

    delete pImage;
}

void widgetGrayTransform::createAction()
{
    QList<QAction *> listActions = this->actions();

    // 清除父类的action 动作，否则会重叠
    widgetShow::clearAction();

    //增加快速加载图片右键菜单
    createDefaultAction();

    createOneAction(tr("非零值取一"), E_BINARY_NOT_ZERO_SET_ONE);
    createOneAction(tr("单阈值二值"), E_BINARY_THRESHOLD);
    createOneAction(tr("双阈值二值"), E_BINARY_THRESHOLD_TWO);

    createOneAction(tr("反色处理"), E_GRAY_TRANS_INVERT_COLOR);
    createOneAction(tr("窗口变换"), E_GRAY_TRANS_WINDOW);
    createOneAction(tr("分段线性"), E_GRAY_PEICEWISE_LINT);
    createOneAction(tr("灰度分布均衡化"), E_GRAY_DISTRU_EQ);

    setContextMenuPolicy(Qt::ActionsContextMenu);
    setFocusPolicy(Qt::StrongFocus);
    setAcceptDrops(true);
}

void widgetGrayTransform::imageBinaryNotZeroSetOne(QImage *psrcImage, QImage **ppdstImage)
{
    int siWidth  = psrcImage->width();
    int siHeight = psrcImage->height();
    QImage::Format siFormat = psrcImage->format();

    QImage *pdstImage = new QImage(siWidth, siHeight, siFormat);

    // 256色灰度索引图(8位索引图)，需要手动设置colorTable，然后再填充为全0
    if(siFormat == QImage::Format_Indexed8){
        pdstImage->setColorTable(psrcImage->colorTable());
        pdstImage->fill(0);
    }
    else {
        pdstImage->fill(QColor(0,0,0,0));
    }

    for(int y = 0; y < siHeight; ++y){
        for(int x = 0; x < siWidth; ++x){

            if(siFormat == QImage::Format_Indexed8){
                // 索引图用pixelIndex函数
                int siPix = psrcImage->pixelIndex(x,y);

                if(siPix != 0){
                    siPix = 255;
                }
                pdstImage->setPixel(x, y, static_cast<size_t>(siPix));
            }
            else {
                QColor color = psrcImage->pixelColor(x,y);

                if(color.red() != 0) color.setRed(255);
                if(color.green() != 0) color.setGreen(255);
                if(color.blue() != 0) color.setBlue(255);

                pdstImage->setPixelColor(x, y, color);
            }

        }
    }
    *ppdstImage = pdstImage;

    return;
}

void widgetGrayTransform::imageBinaryThreshold(QImage *psrcImage, QImage **ppdstImage)
{
    static int siThreshod = 100;
    int siWidth  = psrcImage->width();
    int siHeight = psrcImage->height();
    QImage::Format siFormat = psrcImage->format();

    QImage *pdstImage = new QImage(siWidth, siHeight, siFormat);

    // 256色灰度索引图(8位索引图)，需要手动设置colorTable，然后再填充为全0
    if(siFormat == QImage::Format_Indexed8){
        pdstImage->setColorTable(psrcImage->colorTable());
        pdstImage->fill(0);
    }
    else {
        pdstImage->fill(QColor(0,0,0,0));
    }

    dialogThreshold dlg(siThreshod);
    dlg.setWindowTitle(tr("阈值设置"));
    dlg.exec();

    if(!dlg.isPushOk())
    {
        return ;
    }

    siThreshod = dlg.siThreshold;

    for(int y = 0; y < siHeight; ++y){
        for(int x = 0; x < siWidth; ++x){

            if(siFormat == QImage::Format_Indexed8){
                // 索引图用pixelIndex函数
                int siPix = psrcImage->pixelIndex(x,y);

                if(siPix > siThreshod){
                    siPix = 255;
                }
                pdstImage->setPixel(x, y, static_cast<size_t>(siPix));
            }
            else {
                QColor color = psrcImage->pixelColor(x,y);

                if(color.red() > siThreshod) color.setRed(255);
                if(color.green() > siThreshod) color.setGreen(255);
                if(color.blue() > siThreshod) color.setBlue(255);

                pdstImage->setPixelColor(x, y, color);
            }

        }
    }
    *ppdstImage = pdstImage;
}

void widgetGrayTransform::imageBinaryTwoThreshold(QImage *psrcImage, QImage **ppdstImage)
{
    static int siThreshod1 = 100;
    static int siThreshod2 = 200;

    int siWidth  = psrcImage->width();
    int siHeight = psrcImage->height();
    QImage::Format siFormat = psrcImage->format();

    QImage *pdstImage = new QImage(siWidth, siHeight, siFormat);

    // 256色灰度索引图(8位索引图)，需要手动设置colorTable，然后再填充为全0
    if(siFormat == QImage::Format_Indexed8){
        pdstImage->setColorTable(psrcImage->colorTable());
        pdstImage->fill(0);
    }
    else {
        pdstImage->fill(QColor(0,0,0,0));
    }

    dialogThresholdTwo dlg(siThreshod1, siThreshod2);
    dlg.setWindowTitle(tr("阈值设置"));
    dlg.exec();

    if(!dlg.isPushOk())
    {
        return ;
    }

    siThreshod1 = dlg.siThreshold1;
    siThreshod2 = dlg.siThreshold2;

    for(int y = 0; y < siHeight; ++y){
        for(int x = 0; x < siWidth; ++x){

            if(siFormat == QImage::Format_Indexed8){
                // 索引图用pixelIndex函数
                int siPix = psrcImage->pixelIndex(x,y);

                if(siThreshod1 < siPix && siPix < siThreshod2){
                    siPix = 255;
                }
                pdstImage->setPixel(x, y, static_cast<size_t>(siPix));
            }
            else {
                QColor color = psrcImage->pixelColor(x,y);

                if(siThreshod1 < color.red() && color.red() < siThreshod2) color.setRed(255);
                if(siThreshod1 < color.green() && color.green() < siThreshod2) color.setGreen(255);
                if(siThreshod1 < color.blue() && color.blue() < siThreshod2) color.setBlue(255);

                pdstImage->setPixelColor(x, y, color);
            }

        }
    }
    *ppdstImage = pdstImage;
}

void widgetGrayTransform::imageGrayInverColor(QImage *psrcImage, QImage **ppdstImage)
{
    int siWidth  = psrcImage->width();
    int siHeight = psrcImage->height();
    QImage::Format siFormat = psrcImage->format();

    QImage *pdstImage = new QImage(siWidth, siHeight, siFormat);

    // 256色灰度索引图(8位索引图)，需要手动设置colorTable，然后再填充为全0
    if(siFormat == QImage::Format_Indexed8){
        pdstImage->setColorTable(psrcImage->colorTable());
        pdstImage->fill(0);
    }
    else {
        pdstImage->fill(QColor(0,0,0,0));
    }

    for(int y = 0; y < siHeight; ++y){
        for(int x = 0; x < siWidth; ++x){

            if(siFormat == QImage::Format_Indexed8){
                // 索引图用pixelIndex函数
                int siPix = psrcImage->pixelIndex(x,y);

                siPix = 255 - siPix;
                pdstImage->setPixel(x, y, static_cast<size_t>(siPix));
            }
            else {
                QColor color = psrcImage->pixelColor(x,y);

                color.setRed(255 - color.red());
                color.setGreen(255 - color.green());
                color.setBlue(255 - color.blue());
                pdstImage->setPixelColor(x, y, color);
            }

        }
    }
    *ppdstImage = pdstImage;
}

void widgetGrayTransform::imageGrayWindow(QImage *psrcImage, QImage **ppdstImage)
{

    static int siThres1 = 50;
    static int siThres2 = 200;

    dialogGrayWindow dlg(siThres1,siThres2);
    dlg.setWindowTitle(tr("窗口变换"));
    dlg.exec();

    if(!dlg.isPushOk()){
        return ;
    }

    siThres1 = dlg.siThreshold1;
    siThres2 = dlg.siThreshold2;

    if(siThres1 < 0 || siThres1 > 255 || siThres2 < 0 || siThres2 > 255){
        QMessageBox::information(this, "Alert ",tr("threshold must be [0, 255]"));
        return;
    }

    int siWidth  = psrcImage->width();
    int siHeight = psrcImage->height();
    QImage::Format siFormat = psrcImage->format();

    QImage *pdstImage = new QImage(siWidth, siHeight, siFormat);

    // 256色灰度索引图(8位索引图)，需要手动设置colorTable，然后再填充为全0
    if(siFormat == QImage::Format_Indexed8){
        pdstImage->setColorTable(psrcImage->colorTable());
        pdstImage->fill(0);
    }
    else {
        pdstImage->fill(QColor(0,0,0,0));
    }

    for(int y = 0; y < siHeight; ++y){
        for(int x = 0; x < siWidth; ++x){

            if(siFormat == QImage::Format_Indexed8){
                // 索引图用pixelIndex函数
                int siPix = psrcImage->pixelIndex(x,y);

                if(siPix < siThres1)
                    siPix = 0;

                if(siPix > siThres2)
                    siPix = 255;

                pdstImage->setPixel(x, y, static_cast<size_t>(siPix));
            }
            else {
                QColor color = psrcImage->pixelColor(x,y);

                if(color.red() < siThres1) color.setRed(0);
                if(color.red() > siThres2) color.setRed(255);
                if(color.green() < siThres1) color.setGreen(0);
                if(color.green() > siThres2) color.setGreen(255);
                if(color.blue() < siThres1) color.setBlue(0);
                if(color.blue() > siThres2) color.setBlue(255);

                pdstImage->setPixelColor(x, y, color);
            }

        }
    }
    *ppdstImage = pdstImage;
}

void widgetGrayTransform::createPiecewiseMap(int siX1, int siY1, int siX2, int siY2, int asimap[])
{
    for (int i = 0; i < siX1; i++){
        // 线性变换
        if(siX1 != 0){
            asimap[i] = siY1 * i / siX1;
        }
        else {
            asimap[i] = siY1;
        }
    }

    for (int i = siX1; i < siX2; i++){
        // 判断bX1是否等于bX2（防止分母为0）
        if (siX1 != siX2){
            // 线性变换
            asimap[i] = siY1 + ((siY2 - siY1) * (i - siX1) / (siX2 - siX1));
        }
        else{
            // 直接赋值为bY1
            asimap[i] = siY1;
        }
    }

    for (int i = siX2; i < 256; i++)		//(X2 —— 256)
    {
        // 判断bX2是否等于255（防止分母为0）
        if (siX2 != 255)
        {
            // 线性变换
            asimap[i] = siY2 + ((255 - siY2) * (i - siX2) / (255 - siX2));
        }
        else
        {
            // 直接赋值为255
            asimap[i] = 255;
        }
    }

    return;
}

void widgetGrayTransform::imagePiecewiseLine(QImage *psrcImage, QImage **ppdstImage)
{

    static int siX1 = 30;
    static int siY1 = 50;
    static int siX2 = 200;
    static int siY2 = 180;

    dialoPiecewiseline dlg(siX1,siY1,siX2,siY2);
    dlg.setWindowTitle(tr("窗口变换"));
    dlg.exec();

    if(!dlg.isPushOk()){
        return ;
    }

    siX1 = dlg.siX1;
    siY1 = dlg.siY1;
    siX2 = dlg.siX2;
    siY2 = dlg.siY2;

    if(siX1 < 0 || siX1 > 255) return;
    if(siY1 < 0 || siY1 > 255) return;
    if(siX2 < 0 || siX2 > 255) return;
    if(siY2 < 0 || siY2 > 255) return;


    int asimap[256] = {0};
    createPiecewiseMap(siX1,siY1,siX2,siY2,asimap);

    int siWidth  = psrcImage->width();
    int siHeight = psrcImage->height();
    QImage::Format siFormat = psrcImage->format();

    QImage *pdstImage = new QImage(siWidth, siHeight, siFormat);

    // 256色灰度索引图(8位索引图)，需要手动设置colorTable，然后再填充为全0
    if(siFormat == QImage::Format_Indexed8){
        pdstImage->setColorTable(psrcImage->colorTable());
        pdstImage->fill(0);
    }
    else {
        pdstImage->fill(QColor(0,0,0,0));
    }

    for(int y = 0; y < siHeight; ++y){
        for(int x = 0; x < siWidth; ++x){

            if(siFormat == QImage::Format_Indexed8){
                // 根据映射表转换像素值
                int siPix = psrcImage->pixelIndex(x,y);

                pdstImage->setPixel(x, y, static_cast<size_t>(asimap[siPix]));
            }
            else {
                QColor color = psrcImage->pixelColor(x,y);

                int siPix = 0 ;

                siPix = color.red();color.setRed(asimap[siPix]);
                siPix = color.green();color.setGreen(asimap[siPix]);
                siPix = color.blue();color.setBlue(asimap[siPix]);

                pdstImage->setPixelColor(x, y, color);
            }

        }
    }
    *ppdstImage = pdstImage;

    return;
}

void widgetGrayTransform::creatHist(QImage *psrcImage, double asiRedMap[256], double asiGreenMap[256], double asiBlueMap[256])
{
    int siWidth  = psrcImage->width();
    int siHeight = psrcImage->height();
    double dbTotal = siWidth*siHeight*1.0;

    QImage::Format siFormat = psrcImage->format();

    for(int y = 0; y < siHeight; ++y){
        for(int x = 0; x < siWidth; ++x){

            if(siFormat == QImage::Format_Indexed8){
                // 统计灰度直方图，8位索引图仅适用red映射就够啦
                int siPix = psrcImage->pixelIndex(x,y);
                ++asiRedMap[siPix];
            }
            else {
                QColor color = psrcImage->pixelColor(x,y);

                int siPix = 0 ;

                siPix = color.red()  ; ++asiRedMap[siPix];
                siPix = color.green(); ++asiGreenMap[siPix];
                siPix = color.blue() ; ++asiBlueMap[siPix];
            }

        }
    }

    for(int i = 0; i < 256; ++i){
        asiRedMap[i] = asiRedMap[i]/dbTotal;
        asiGreenMap[i] = asiGreenMap[i]/dbTotal;
        asiBlueMap[i] = asiBlueMap[i]/dbTotal;
    }

    return;
}

void widgetGrayTransform::creatHistAccumulative(double asiRedMap[], double asiGreenMap[], double asiBlueMap[])
{
    for(int i = 1; i < 256; i++)
    {
        asiRedMap[i] = asiRedMap[i] + asiRedMap[i-1];
        asiGreenMap[i] = asiGreenMap[i] + asiGreenMap[i-1];
        asiBlueMap[i] = asiBlueMap[i] + asiBlueMap[i-1];
    }

    return;
}

void widgetGrayTransform::createDistributionMap(QImage *psrcImage, int asiRedMap[], int asiGreenMap[], int asiBlueMap[])
{
    double adbRedMap[256] = {0.0};
    double adbGreenMap[256] = {0.0};
    double adbBlueMap[256]  = {0.0};
    // 创建直方图
    creatHist(psrcImage, adbRedMap, adbGreenMap, adbBlueMap);

    // 创建累积分布直方图
    creatHistAccumulative(adbRedMap, adbGreenMap, adbBlueMap);

    for(int i = 0; i < 256; i++){
        asiRedMap[i]   = static_cast<int>(255.0 * adbRedMap[i]);
        asiGreenMap[i] = static_cast<int>(255.0 * adbGreenMap[i]);
        asiBlueMap[i]  = static_cast<int>(255.0 * adbBlueMap[i]);
    }
}

void widgetGrayTransform::imageDistributioneEqualization(QImage *psrcImage, QImage **ppdstImage)
{
    int asiRedMap[256] = {0};
    int asiGreenMap[256] = {0};
    int asiBlueMap[256] = {0};

    createDistributionMap(psrcImage, asiRedMap, asiGreenMap, asiBlueMap);

    int siWidth  = psrcImage->width();
    int siHeight = psrcImage->height();
    QImage::Format siFormat = psrcImage->format();

    QImage *pdstImage = new QImage(siWidth, siHeight, siFormat);

    // 256色灰度索引图(8位索引图)，需要手动设置colorTable，然后再填充为全0
    if(siFormat == QImage::Format_Indexed8){
        pdstImage->setColorTable(psrcImage->colorTable());
        pdstImage->fill(0);
    }
    else {
        pdstImage->fill(QColor(0,0,0,0));
    }

    for(int y = 0; y < siHeight; ++y){
        for(int x = 0; x < siWidth; ++x){

            if(siFormat == QImage::Format_Indexed8){
                // 根据映射表转换像素值
                int siPix = psrcImage->pixelIndex(x,y);

                pdstImage->setPixel(x, y, static_cast<size_t>(asiRedMap[siPix]));
            }
            else {
                QColor color = psrcImage->pixelColor(x,y);

                int siPix = 0 ;

                siPix = color.red();color.setRed(asiRedMap[siPix]);
                siPix = color.green();color.setGreen(asiGreenMap[siPix]);
                siPix = color.blue();color.setBlue(asiBlueMap[siPix]);

                pdstImage->setPixelColor(x, y, color);
            }

        }
    }
    *ppdstImage = pdstImage;

    return;
}






