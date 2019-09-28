#include "widgetsmoothimg.h"

enum {
    E_NOISE_BINAY_IMG,
    E_NOISE_SINGLE_BLACK,
    E_FIELD_AVERAGE_3x3,
};

widgetSmoothImg::widgetSmoothImg()
{
    createAction();
}

void widgetSmoothImg::imageProcess(QImage image, int action)
{
    QImage *pImage = nullptr;

    switch (action) {
    case E_NOISE_BINAY_IMG:
        imageNoiseReBinary(&image, &pImage);
        break;
    case E_NOISE_SINGLE_BLACK:
        imageSingleBlack(&image, &pImage);
        break;
    default:
        break;
    }

    if(pImage)
        m_pWgtRightShowAf->showImage(*pImage);

    delete pImage;
}

void widgetSmoothImg::createAction()
{

    widgetShow::clearAction();

    //增加快速加载图片右键菜单
    createDefaultAction();

    createOneAction(tr("二值噪声消除"), E_NOISE_BINAY_IMG);
    createOneAction(tr("单点黑色"), E_NOISE_SINGLE_BLACK);

    setContextMenuPolicy(Qt::ActionsContextMenu);
    setFocusPolicy(Qt::StrongFocus);
    setAcceptDrops(true);
}

#define M_MAX_DIFFERENCE (150)
void widgetSmoothImg::imageNoiseReBinary(QImage *psrcImage, QImage **ppdstImage)
{
    int siWidth = psrcImage->width();
    int siHeight = psrcImage->height();
    QImage::Format siFormat = psrcImage->format();

    QImage *pdstImage = new QImage(siWidth, siHeight, siFormat);

    QImage temp = psrcImage->copy(0, 0, siWidth, siHeight);

    for(int y = 0; y < siHeight; ++y){
        for(int x = 0; x < siWidth; ++x){
            if(siFormat == QImage::Format_Indexed8){
                // 索引图用pixelIndex函数
                int siPix = psrcImage->pixelIndex(x,y);

                siPix = (siPix > 100 ? 255 : 0);
                temp.setPixel(x,y, static_cast<size_t>(siPix));

            }
            else {
                int siPix = 0;
                QColor color = psrcImage->pixelColor(x,y);

                siPix = color.red();siPix = (siPix > 100 ? 255 : 0);color.setRed(siPix);
                siPix = color.green();siPix = (siPix > 100 ? 255 : 0);color.setGreen(siPix);
                siPix = color.blue();siPix = (siPix > 100 ? 255 : 0);color.setBlue(siPix);

                temp.setPixelColor(x, y, color);
            }

        }
    }

    for(int y = 1; y < siHeight - 1; y++)
    {
        for(int x = 1; x < siWidth - 1; x++)
        {
            int averg=0;
            int siPix = 0;

            if(siFormat == QImage::Format_Indexed8){
                // 索引图用pixelIndex函数
                siPix = psrcImage->pixelIndex(x, y);
                //求周围8近邻均值
                averg = temp.pixelIndex(x-1, y-1) + temp.pixelIndex(x, y-1) + temp.pixelIndex(x+1, y-1) +
                        temp.pixelIndex(x-1, y) +     0                     + temp.pixelIndex(x+1, y) +
                        temp.pixelIndex(x-1, y+1) + temp.pixelIndex(x , y+1) + temp.pixelIndex(x+1, y+1) ;
                averg /= 8;

                if(abs(averg - siPix) > M_MAX_DIFFERENCE)
                    siPix = averg;

                pdstImage->setPixel(x, y, static_cast<size_t>(siPix));
            }
            else {
                QColor color = psrcImage->pixelColor(x,y);

                averg = 0;
                siPix = color.red();
                averg = temp.pixelColor(x-1, y-1).red() + temp.pixelColor(x, y-1).red() + temp.pixelColor(x+1, y-1).red() +
                        temp.pixelColor(x-1, y).red() +     0                     + temp.pixelColor(x+1, y).red() +
                        temp.pixelColor(x-1, y+1).red() + temp.pixelColor(x , y+1).red() + temp.pixelColor(x+1, y+1).red() ;
                averg /= 8;
                if(abs(averg- siPix) > M_MAX_DIFFERENCE)
                    siPix = averg;
                color.setRed(siPix);

                averg = 0;
                siPix = color.green();
                averg = temp.pixelColor(x-1, y-1).green() + temp.pixelColor(x, y-1).green() + temp.pixelColor(x+1, y-1).green() +
                        temp.pixelColor(x-1, y).green() +     0                     + temp.pixelColor(x+1, y).green() +
                        temp.pixelColor(x-1, y+1).green() + temp.pixelColor(x , y+1).green() + temp.pixelColor(x+1, y+1).green() ;
                averg /= 8;
                if(abs(averg- siPix) > M_MAX_DIFFERENCE)
                    siPix = averg;
                color.setGreen(siPix);

                averg = 0;
                siPix = color.blue();
                averg = temp.pixelColor(x-1, y-1).blue() + temp.pixelColor(x, y-1).blue() + temp.pixelColor(x+1, y-1).blue() +
                        temp.pixelColor(x-1, y).blue() +     0                     + temp.pixelColor(x+1, y).blue() +
                        temp.pixelColor(x-1, y+1).blue() + temp.pixelColor(x , y+1).blue() + temp.pixelColor(x+1, y+1).blue() ;
                averg /= 8;
                if(abs(averg- siPix) > M_MAX_DIFFERENCE)
                    siPix = averg;
                color.setBlue(siPix);

                pdstImage->setPixelColor(x, y, color);
            }
        }
    }

    *ppdstImage = pdstImage;

    return;

}

void widgetSmoothImg::imageSingleBlack(QImage *psrcImage, QImage **ppdstImage)
{

}
