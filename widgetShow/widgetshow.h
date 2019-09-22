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
    virtual void imageProcess(QImage image, int i);
    virtual void createAction();
    virtual void clearAction();

protected:
    // 以下两个动作支持拖动，必须同时存在
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

protected:
    PlayWidget *m_pWgtLeftShowBf;
    PlayWidget *m_pWgtRightShowAf;
    QImage m_image;
    QString m_imagePath;

signals:
    void openImageFile(QString str);

public slots:
    void onTaskBoxContextMenuEvent();
};

#endif // WIDGETSHOW_H
