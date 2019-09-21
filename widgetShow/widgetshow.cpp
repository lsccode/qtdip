#include "widgetshow.h"

#include <QGridLayout>
#include <QHBoxLayout>

widgetShow::widgetShow(QWidget *parent) : QWidget(parent)
{

    m_pWgtLeftShowBf = new PlayWidget;
    m_pWgtRightShowAf = new PlayWidget;

#if 0
    QGridLayout *layoutTop = new QGridLayout;;
    layoutTop->addWidget(m_pWgtLeftShowBf,0,0);
    layoutTop->addWidget(m_pWgtRightShowAf,0,1);
    layoutTop->setHorizontalSpacing(20);
#else
    QHBoxLayout *layoutTop = new QHBoxLayout;;
    layoutTop->addWidget(m_pWgtLeftShowBf);
    layoutTop->addSpacing(5);
    layoutTop->addWidget(m_pWgtRightShowAf);


#endif

    setLayout(layoutTop);
}

void widgetShow::showImage(QImage image)
{
    m_pWgtLeftShowBf->showImage(image);
}

void widgetShow::imageProcess(QImage image)
{
    m_pWgtRightShowAf->showImage(image);

}
