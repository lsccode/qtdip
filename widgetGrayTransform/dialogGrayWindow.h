#ifndef DIALOGGRAYWINDOW_H
#define DIALOGGRAYWINDOW_H

#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

class WidgetPainterWindow : public QWidget
{
    Q_OBJECT

public:
    WidgetPainterWindow(QWidget *parent = nullptr);
    void setThres(int thres1, int thres2);
    void reDraw();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_thres1;
    int m_thres2;

};


class dialogGrayWindow: public QDialog
{
    Q_OBJECT
public:
    dialogGrayWindow(QWidget  *parent = nullptr);
    dialogGrayWindow(int siThreshold1, int siThreshold2 ,QWidget  *parent = nullptr);
    ~dialogGrayWindow();

    void initWidget();

    int isPushOk();

private:
    QLabel *m_plbX;
    QLineEdit *m_pLeX;
    QLabel *m_plbY;
    QLineEdit *m_pLeY;
    QPushButton *m_pBtnOK;
    QPushButton *m_pBtnCancel;
    QGridLayout *m_pGridLayoutTop;
    QHBoxLayout *m_pHBoxLayout;

    WidgetPainterWindow *m_pWgtPainter;

    int m_isPushOk;

public slots:
    void slotOK();
    void slotCancle();
    void slotThreshold1Change(QString str);

public:
    int siThreshold1;
    int siThreshold2;
};

#endif
