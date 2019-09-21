#ifndef PLAYWIDGET_H
#define PLAYWIDGET_H

#include <QWidget>
#include <QImage>

class PlayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayWidget(QWidget *parent = nullptr);

public:
    void showImage(QImage image);

protected:
    void virtual paintEvent(QPaintEvent *event);

private:
    QImage m_image;
signals:

public slots:


};

#endif // PLAYWIDGET_H
