#include "playwidget.h"
#include <QPainter>

PlayWidget::PlayWidget(QWidget *parent) : QWidget(parent)
{

}

void PlayWidget::showImage(QImage image)
{
    m_image = image;
    update();
}

void PlayWidget::paintEvent(QPaintEvent *event)
{
    QPainter widgetPaint(this);
    widgetPaint.eraseRect(rect());

    int winH = 0;
    int winW = 0;
    int startX = 0;
    int startY = 0;

    if(nullptr == event)
        return;

    if(m_image.width() <= 0 || m_image.height() <= 0)
        return ;

    if(m_image.width()/m_image.height() >= width()/height())
    {
        winW = width();
        winH = width()*m_image.height()/m_image.width();
        startX = 0;
        startY = (height() - winH) / 2;
    }
    else
    {
        winW = height()*m_image.width()/m_image.height();
        winH = height();
        startX = (width()-winW)/2;
        startY = 0;
    }
    widgetPaint.setViewport(startX,startY,winW,winH);
    widgetPaint.setWindow(0, 0, m_image.width(), m_image.height());
    widgetPaint.drawImage(0,0,m_image);

    return;
}

