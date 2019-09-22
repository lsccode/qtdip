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

    switch (action) {
    case 1:
        for(int i = 0; i < siHeight; ++i){
            for(int j = 0; j < siWidth; ++j){
                QRgb color = image.pixel(j,i);
                pImage->setPixel(siWidth - j - 1, i, color);
            }
        }
        break;
    case 2:
        for(int i = 0; i < siHeight; ++i){
            for(int j = 0; j < siWidth; ++j){
                QColor color = image.pixelColor(j,i);
                pImage->setPixelColor(j, siHeight - i - 1, color);
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

