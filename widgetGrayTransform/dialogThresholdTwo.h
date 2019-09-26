#ifndef DIALOGThresholdTwo_H
#define DIALOGThresholdTwo_H

#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class dialogThresholdTwo: public QDialog
{
    Q_OBJECT
public:
    dialogThresholdTwo(QWidget  *parent = nullptr);
    dialogThresholdTwo(int siThreshold1, int siThreshold2 ,QWidget  *parent = nullptr);
    ~dialogThresholdTwo();

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

    int m_isPushOk;

public slots:
    void slotOK();
    void slotCancle();

public:
    int siThreshold1;
    int siThreshold2;
};

#endif
