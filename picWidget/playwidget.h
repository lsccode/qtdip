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

private:
    QImage m_image;
signals:

public slots:

protected:
    void virtual paintEvent(QPaintEvent *event);
};

#endif // PLAYWIDGET_H
