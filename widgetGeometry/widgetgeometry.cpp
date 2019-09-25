#include "widgetgeometry.h"

enum E_ACTION
{
    E_MOVE = 1,
    E_HOR,
    E_VER,
    E_TRANS,
    E_ZOOM
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

    createOneAction(tr("图像平移"),E_MOVE);
    createOneAction(tr("水平镜像"),E_HOR);
    createOneAction(tr("垂直镜像"),E_VER);
    createOneAction(tr("图像转置"),E_TRANS);
    createOneAction(tr("图像缩放"),E_ZOOM);

    setContextMenuPolicy(Qt::ActionsContextMenu);
    setFocusPolicy(Qt::StrongFocus);
    setAcceptDrops(true);
}

void widgetGeometryTransform::createOneAction(QString str, int action)
{
    QAction *pAction = new QAction(str, this);

    pAction->setData(action);
    addAction(pAction);
    connect(pAction, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
}

static int offset_x = 50;
static int offset_y = 50;
void widgetGeometryTransform::imageMove(QImage *psrcImage, QImage **ppdstImage)
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

    // 对于源图像有得像素，再使用源图像的像素
    for(int i = 0; i < siHeight; ++i){
        for(int j = 0; j < siWidth; ++j){
            int siIndex = 0;
            int sij = j + offset_y;
            int sii = i + offset_x;
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

static float dbHor = 2.0;
static float dbVer = 1.0;

void widgetGeometryTransform::imageZoomIn(QImage *psrcImage, QImage **ppdstImage)
{
    int siWidth  = static_cast<int>(psrcImage->width()*dbHor);
    int siHeight = static_cast<int>(psrcImage->height()*dbVer);
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
            int siSrcX = static_cast<int>(x/dbHor);
            int siSrcY = static_cast<int>(y/dbHor);

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
