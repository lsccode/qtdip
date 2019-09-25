#ifndef DIALOGROTATE_H
#define DIALOGROTATE_H

#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class dialogRotate: public QDialog
{
    Q_OBJECT
public:
    dialogRotate(QWidget  *parent = nullptr);
    dialogRotate(double dbRotate, QWidget  *parent = nullptr);
    ~dialogRotate();

    void initWidget();

    int isPushOk();

private:
    QLabel *m_plbRotate;
    QLineEdit *m_pLeRotate;
    QPushButton *m_pBtnOK;
    QPushButton *m_pBtnCancel;
    QGridLayout *m_pGridLayoutTop;

    int m_isPushOk;

public slots:
    void slotOK();
    void slotCancle();

public:
    double dbRotate;
};

#endif
