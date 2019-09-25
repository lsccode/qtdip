#include "widgetgeometry.h"
#include "dialogMove.h"
#include "dialogZoom.h"

enum E_ACTION
{
    E_MOVE = 1,
    E_HOR,
    E_VER,
    E_TRANS,
    E_ZOOM,
    E_ROTOTE,
};

widgetGeometryTransform::widgetGeometryTransform()
{
    createAction();
}

void widgetGeometryTransform::imageProcess(QImage image, int action)
{
    QImage *pImage = nullptr;

    switch (action) {
    case E_HOR:
        imageHor(&image,&pImage);
        break;
    case E_VER:
        imageVer(&image,&pImage);
        break;
    case E_MOVE:
        imageMove(&image,&pImage);
        break;
    case E_TRANS:
        imageTrans(&image,&pImage);
        break;
    case E_ZOOM:
        imageZoomIn(&image,&pImage);
        break;
    case E_ROTOTE:
        imageRotate(&image,&pImage);
        break;
    default:
        break;
    }

    if(pImage != nullptr)
        m_pWgtRightShowAf->showImage(*pImage);

    delete pImage;
}

void widgetGeometryTransform::createAction()
{
    // 清除父类的action 动作，否则会重叠
    widgetShow::clearAction();

    //增加快速加载图片右键菜单
    createDefaultAction();

    createOneAction(tr("图像平移"),E_MOVE);
    createOneAction(tr("水平镜像"),E_HOR);
    createOneAction(tr("垂直镜像"),E_VER);
    createOneAction(tr("图像转置"),E_TRANS);
    createOneAction(tr("图像缩放"),E_ZOOM);
    createOneAction(tr("图像旋转"),E_ROTOTE);

    setContextMenuPolicy(Qt::ActionsContextMenu);
    setFocusPolicy(Qt::StrongFocus);
    setAcceptDrops(true);
}

void widgetGeometryTransform::imageMove(QImage *psrcImage, QImage **ppdstImage)
{
    static int offset_x = 0;
    static int offset_y = 0;

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

    dialogMove dlg(offset_x, offset_y);
    dlg.setWindowTitle(tr("图像平移"));
    dlg.exec();

    if(!dlg.isPushOk())
    {
        return ;
    }

    offset_x = dlg.siXoffset;
    offset_y = dlg.siyoffset;

    // 对于源图像有得像素，再使用源图像的像素
    for(int i = 0; i < siHeight; ++i){
        for(int j = 0; j < siWidth; ++j){
            int siIndex = 0;
            int sij = j + offset_x;
            int sii = i + offset_y;
            if(siFormat == QImage::Format_Indexed8){

                siIndex = psrcImage->pixelIndex(j,i);

                //当前的像素经过平移后再目标像素范围内的，就赋值给目标像素
                if(sii >= 0 && sii < siHeight && sij >= 0 && sij < siWidth){

                    pdstImage->setPixel(sij, sii, static_cast<uint>(siIndex));
                }
            }
            else {

                QColor color =  psrcImage->pixelColor(j,i);

                //当前的像素经过平移后再目标像素范围内的，就赋值给目标像素
                if(sii >= 0 && sii < siHeight && sij >= 0 && sij < siWidth)
                {
                    pdstImage->setPixelColor(sij, sii, color);
                }
            }
        }
    }

    *ppdstImage = pdstImage;

    return;
}

void widgetGeometryTransform::imageHor(QImage *psrcImage, QImage **ppdstImage)
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

    for(int i = 0; i < siHeight; ++i){
        for(int j = 0; j < siWidth; ++j){

            if(siFormat == QImage::Format_Indexed8){
                // 索引图用pixelIndex函数
                int siPix = psrcImage->pixelIndex(j,i);
                pdstImage->setPixel(siWidth - j - 1, i, static_cast<size_t>(siPix));
            }
            else {
                QRgb color = psrcImage->pixel(j,i);
                pdstImage->setPixel(siWidth - j - 1, i, color);
            }

        }
    }
    *ppdstImage = pdstImage;

    return;
}

void widgetGeometryTransform::imageVer(QImage *psrcImage, QImage **ppdstImage)
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

    for(int i = 0; i < siHeight; ++i){
        for(int j = 0; j < siWidth; ++j){
            if(siFormat == QImage::Format_Indexed8){
                int siIndex = psrcImage->pixelIndex(j,i);
                pdstImage->setPixel(j, siHeight - i - 1, static_cast<uint>(siIndex));
            }
            else {
                QColor color = psrcImage->pixelColor(j,i);
                pdstImage->setPixelColor(j, siHeight - i - 1, color);
            }
        }
    }

    *ppdstImage = pdstImage;

    return;
}

void widgetGeometryTransform::imageTrans(QImage *psrcImage, QImage **ppdstImage)
{
    int siWidth  = psrcImage->width();
    int siHeight = psrcImage->height();
    QImage::Format siFormat = psrcImage->format();

    // 此处宽高交换
    QImage *pdstImage = new QImage(siHeight, siWidth, siFormat);

    // 目的图像的宽高
    siWidth = pdstImage->width();
    siHeight = pdstImage->height();
    // 256色灰度索引图(8位索引图)，需要手动设置colorTable，然后再填充为全0
    if(siFormat == QImage::Format_Indexed8){
         pdstImage->setColorTable(psrcImage->colorTable());
         pdstImage->fill(0);
    }
    else {
        pdstImage->fill(QColor(0,0,0,0));
    }

    for(int i = 0; i < siHeight; ++i){
        for(int j = 0; j < siWidth; ++j){
            if(siFormat == QImage::Format_Indexed8){
                int siIndex = psrcImage->pixelIndex(i,j);
                pdstImage->setPixel(j, i, static_cast<uint>(siIndex));
            }
            else {
                QColor color = psrcImage->pixelColor(i,j);
                pdstImage->setPixelColor(j, i, color);
            }
        }
    }

    *ppdstImage = pdstImage;
}

void widgetGeometryTransform::imageZoomIn(QImage *psrcImage, QImage **ppdstImage)
{
    static double dbHor = 1.0;
    static double dbVer = 1.0;

    dialogZoom dlg(dbHor, dbVer);
    dlg.setWindowTitle(tr("图像缩放"));
    dlg.exec();

    if(!dlg.isPushOk())
    {
        return ;
    }

    if(dlg.dbHor < 1e-6 && dlg.dbVer < 1e-6)
    {
        return ;
    }

    dbHor = dlg.dbHor;
    dbVer = dlg.dbVer;

    int siDstWidth  = static_cast<int>(psrcImage->width()*dbHor);
    int siDstHeight = static_cast<int>(psrcImage->height()*dbVer);
    QImage::Format siFormat = psrcImage->format();

    QImage *pdstImage = new QImage(siDstWidth, siDstHeight, siFormat);

    // 256色灰度索引图(8位索引图)，需要手动设置colorTable，然后再填充为全0
    if(siFormat == QImage::Format_Indexed8){
         pdstImage->setColorTable(psrcImage->colorTable());
         pdstImage->fill(0);
    }
    else {
        pdstImage->fill(QColor(0,0,0,0));
    }

    for(int y = 0; y < siDstHeight; ++y){
        for(int x = 0; x < siDstWidth; ++x){
            int siSrcX = static_cast<int>(x/dbHor);
            int siSrcY = static_cast<int>(y/dbVer);

            if(siFormat == QImage::Format_Indexed8){
                int siIndex = psrcImage->pixelIndex(siSrcX,siSrcY);
                pdstImage->setPixel(x, y, static_cast<uint>(siIndex));
            }
            else {
                QColor color = psrcImage->pixelColor(siSrcX,siSrcY);
                pdstImage->setPixelColor(x, y, color);
            }
        }
    }

    *ppdstImage = pdstImage;
}

#define PI 3.1415926535
#define RADIAN(angle) ((angle)*PI/180.0)
#define max(a,b)            (((a) > (b)) ? (a) : (b))
void widgetGeometryTransform::imageRotate(QImage *psrcImage, QImage **ppdstImage)
{
    double       SrcX1,SrcY1,SrcX2,SrcY2;
    double       SrcX3,SrcY3,SrcX4,SrcY4;
    double       DstX1,DstY1,DstX2,DstY2;
    double       DstX3,DstY3,DstX4,DstY4;
    double       cosa,sina;
    double       num1,num2;
    double RotateAngle;
    //角度到弧度的转化
    RotateAngle=static_cast<double>(RADIAN(-90.0));
    cosa=static_cast<double>(cos(static_cast<double>(RotateAngle)));
    sina=static_cast<double>(sin(static_cast<double>(RotateAngle)));
    //原图的宽度和高度

    int siSrcWidth  = psrcImage->width();
    int siSrcHeight = psrcImage->height();
    //原图的四个角的坐标
    SrcX1=static_cast<double>(-0.5*siSrcWidth);
    SrcY1=static_cast<double>(0.5*siSrcHeight);
    SrcX2=static_cast<double>(0.5*siSrcWidth);
    SrcY2=static_cast<double>(0.5*siSrcHeight);
    SrcX3=static_cast<double>(-0.5*siSrcWidth);
    SrcY3=static_cast<double>(-0.5*siSrcHeight);
    SrcX4=static_cast<double>(0.5*siSrcWidth);
    SrcY4=static_cast<double>(-0.5*siSrcHeight);
    //新图四个角的坐标
    DstX1=cosa*SrcX1+sina*SrcY1;
    DstY1=-sina*SrcX1+cosa*SrcY1;
    DstX2=cosa*SrcX2+sina*SrcY2;
    DstY2=-sina*SrcX2+cosa*SrcY2;
    DstX3=cosa*SrcX3+sina*SrcY3;
    DstY3=-sina*SrcX3+cosa*SrcY3;
    DstX4=cosa*SrcX4+sina*SrcY4;
    DstY4=-sina*SrcX4+cosa*SrcY4;
    //计算新图的宽度，高度
    int Wnew =  static_cast<int>(max(fabs(DstX4-DstX1), fabs(DstX3-DstX2))+0.5);
    int Hnew =  static_cast<int>(max(fabs(DstY4-DstY1), fabs(DstY3-DstY2))+0.5);
    //计算矩阵(2.9)中的两个常数，这样不用以后每次都计算了
    num1=static_cast<double>( -0.5*Wnew*cosa-0.5*Hnew*sina+0.5*siSrcWidth);
    num2=static_cast<double>(0.5*Wnew*sina-0.5*Hnew*cosa+0.5*siSrcHeight);

    QImage::Format siFormat = psrcImage->format();
    QImage *pdstImage = new QImage(Wnew, Hnew, siFormat);

    int siWidth = pdstImage->width();
    int siHeight = pdstImage->height();
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
            int siSrcX = static_cast<int>(x*cosa+y*sina+num1);
            int siSrcY = static_cast<int>(-1.0*x*sina+y*cosa+num2);

            if( (siSrcX >= 0) && (siSrcX < siSrcWidth) && (siSrcY >= 0) && (siSrcY < siSrcHeight))
            {
                if(siFormat == QImage::Format_Indexed8){
                    int siIndex = psrcImage->pixelIndex(siSrcX,siSrcY);
                    pdstImage->setPixel(x, y, static_cast<uint>(siIndex));
                }
                else {
                    QColor color = psrcImage->pixelColor(siSrcX,siSrcY);
                    pdstImage->setPixelColor(x, y, color);
                }
            }
        }
    }

    *ppdstImage = pdstImage;
}
