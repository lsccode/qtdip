#ifndef DIALOPIECEWISELINE_H
#define DIALOPIECEWISELINE_H

#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>

class WidgetPainterPiecewiseLine : public QWidget
{
    Q_OBJECT

public:
    WidgetPainterPiecewiseLine(QWidget *parent = nullptr);
    void setThres(int x1, int y1, int x2, int y2);
    void reDraw();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    int m_x1;
	int m_y1;
    int m_x2;
	int m_y2;

};


class dialoPiecewiseline: public QDialog
{
    Q_OBJECT
public:
    dialoPiecewiseline(QWidget  *parent = nullptr);
    dialoPiecewiseline(int siX1, int siY1, int siX2, int siY2, QWidget  *parent = nullptr);
    ~dialoPiecewiseline();

    void initWidget();

    int isPushOk();

private:
    QLabel *m_plbX1;
    QLineEdit *m_pLeX1;
    QLineEdit *m_pLeY1;

    QLabel *m_plbX2;
    QLineEdit *m_pLeX2;
    QLineEdit *m_pLeY2;

    QPushButton *m_pBtnOK;
    QPushButton *m_pBtnCancel;
    QGridLayout *m_pGridLayoutTop;
    QHBoxLayout *m_pHBoxLayout;

    WidgetPainterPiecewiseLine *m_pWgtPainter;

    int m_isPushOk;

public slots:
    void slotOK();
    void slotCancle();
    void slotThreshold1Change(QString str);

public:
    int siX1;
    int siY1;
    int siX2;
    int siY2;
};

#endif
