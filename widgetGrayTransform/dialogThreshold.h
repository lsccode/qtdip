#ifndef DIALOGTHRESHOLD_H
#define DIALOGTHRESHOLD_H

#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class dialogThreshold: public QDialog
{
    Q_OBJECT
public:
    dialogThreshold(QWidget  *parent = nullptr);
    dialogThreshold(int siThreshold, QWidget  *parent = nullptr);
    ~dialogThreshold();

    void initWidget();

    int isPushOk();

private:
    QLabel *m_plbThreshold;
    QLineEdit *m_pLeThreshold;
    QPushButton *m_pBtnOK;
    QPushButton *m_pBtnCancel;
    QGridLayout *m_pGridLayoutTop;

    int m_isPushOk;

public slots:
    void slotOK();
    void slotCancle();

public:
    int siThreshold;
};

#endif
