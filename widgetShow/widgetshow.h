#ifndef WIDGETSHOW_H
#define WIDGETSHOW_H

#include <QWidget>
#include <QImage>

#include "picWidget/playwidget.h"

class widgetShow : public QWidget
{
    Q_OBJECT
public:
    explicit widgetShow(QWidget *parent = nullptr);

public:
    void showImage(QImage image);
    void imageProcess(QImage image);

public:
    PlayWidget *m_pWgtLeftShowBf;
    PlayWidget *m_pWgtRightShowAf;

signals:

public slots:
};

#endif // WIDGETSHOW_H
