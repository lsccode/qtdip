#ifndef WIDGETSHOW_H
#define WIDGETSHOW_H

#include <QWidget>
#include <QImage>
#include <QPoint>
#include <QMenu>

#include "picWidget/playwidget.h"

class widgetShow : public QWidget
{
    Q_OBJECT
public:
    explicit widgetShow(QWidget *parent = nullptr);

public:
    void showImage(QImage image);
    void imageProcess(QImage image);
    void createAction();

public:
    PlayWidget *m_pWgtLeftShowBf;
    PlayWidget *m_pWgtRightShowAf;
    QMenu *m_pMenu;

private:
    QImage m_image;
signals:

public slots:
    void onTaskBoxContextMenuEvent();
};

#endif // WIDGETSHOW_H
