#include "widgetgeometry.h"

enum E_ACTION
{
    E_MOVE = 1,
    E_HOR,
    E_VER,
};
int offset_x = 50;
int offset_y = 50;

widgetGeometryTransform::widgetGeometryTransform()
{
    createAction();
}

void widgetGeometryTransform::imageProcess(QImage image, int action)
{
    int siWidth = image.width();
    int siHeight = image.height();
    QImage::Format siFormat = image.format();

    QImage *pImage = new QImage(siWidth, siHeight, siFormat);

    // 以下用于填充颜色，测试用
 //   pImage->fill(QColor(255,0,0,0));

    // 256色灰度索引图，需要手动设置索引
    if(siFormat == QImage::Format_Indexed8)
    {
        pImage->setColorTable(image.colorTable());
    }

    switch (action) {
    case E_HOR:
        imageHor(&image,pImage);
        break;
    case E_VER:
        imageVer(&image,pImage);
        break;
    case E_MOVE:
        imageMove(&image,pImage);
        break;

    default:
        break;
    }

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

void widgetGeometryTransform::imageMove(QImage *psrcImage, QImage *pdstImage)
{
    int siWidth  = pdstImage->width();
    int siHeight = pdstImage->height();
    QImage::Format siFormat = psrcImage->format();

    // 首先填充目的图像
    if(siFormat == QImage::Format_Indexed8)
        pdstImage->fill(0);
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
}

void widgetGeometryTransform::imageHor(QImage *psrcImage, QImage *pdstImage)
{
    int siWidth  = psrcImage->width();
    int siHeight = psrcImage->height();
    QImage::Format siFormat = psrcImage->format();

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
}

void widgetGeometryTransform::imageVer(QImage *psrcImage, QImage *pdstImage)
{
    int siWidth  = psrcImage->width();
    int siHeight = psrcImage->height();
    QImage::Format siFormat = psrcImage->format();

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
}
