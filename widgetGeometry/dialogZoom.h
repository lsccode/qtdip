#ifndef DIALOGZOOM_H
#define DIALOGZOOM_H

#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class dialogZoom: public QDialog
{
    Q_OBJECT
public:
    dialogZoom(QWidget  *parent = nullptr);
    dialogZoom(double hor, double ver , QWidget  *parent = nullptr);
    ~dialogZoom();

    void initWidget();

    int isPushOk();

private:
    QLabel *m_plbHor;
    QLineEdit *m_pLeHor;
    QLabel *m_plbVer;
    QLineEdit *m_pLeVer;
    QPushButton *m_pBtnOK;
    QPushButton *m_pBtnCancel;
    QGridLayout *m_pGridLayoutTop;

    int m_isPushOk;

public slots:
    void slotOK();
    void slotCancle();

public:
    double dbHor;
    double dbVer;
};

#endif
