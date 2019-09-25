#include "widgetgraytransform.h"

#include <QColor>

widgetGrayTransform::widgetGrayTransform(QWidget *parent) : widgetShow(parent)
{
    createAction();
}

void widgetGrayTransform::imageProcess(QImage image, int action)
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
    case 1:
        for(int i = 0; i < siHeight; ++i){
            for(int j = 0; j < siWidth; ++j){

                if(siFormat == QImage::Format_Indexed8){
                    // 索引图用pixelIndex函数
                    int siPix = image.pixelIndex(j,i);
                    pImage->setPixel(siWidth - j - 1, i, static_cast<size_t>(siPix));
                }
                else {
                    QRgb color = image.pixel(j,i);
                    pImage->setPixel(siWidth - j - 1, i, color);
                }

            }
        }
        break;
    case 2:
        for(int i = 0; i < siHeight; ++i){
            for(int j = 0; j < siWidth; ++j){
                if(siFormat == QImage::Format_Indexed8){
                    int siIndex = image.pixelIndex(j,i);
                    pImage->setPixel(j, siHeight - i - 1, static_cast<uint>(siIndex));
                }
                else {
                    QColor color = image.pixelColor(j,i);
                    pImage->setPixelColor(j, siHeight - i - 1, color);
                }
            }
        }
        break;

    default:
        break;
    }

    m_pWgtRightShowAf->showImage(*pImage);

    delete pImage;
}

void widgetGrayTransform::createAction()
{
    QAction *pActionHorMir = new QAction(tr("水平镜像"), this);
    QAction *pActionVerMir = new QAction(tr("垂直镜像"), this);

    QList<QAction *> listActions = this->actions();

    // 清除父类的action 动作，否则会重叠
    widgetShow::clearAction();

    //增加快速加载图片右键菜单
    createDefaultAction();

    pActionHorMir->setData(1);
    pActionVerMir->setData(2);

    addAction(pActionHorMir);
    addAction(pActionVerMir);
    connect(pActionHorMir, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
    connect(pActionVerMir, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));

    setContextMenuPolicy(Qt::ActionsContextMenu);
    setFocusPolicy(Qt::StrongFocus);
    setAcceptDrops(true);
}

