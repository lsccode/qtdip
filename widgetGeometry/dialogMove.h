#ifndef DIALOGMOVE_H
#define DIALOGMOVE_H

#include <QLabel>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>

class dialogMove: public QDialog
{
    Q_OBJECT
public:
    dialogMove(QWidget  *parent = nullptr);
    dialogMove(int x, int y ,QWidget  *parent = nullptr);
    ~dialogMove();

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
    int siXoffset;
    int siyoffset;
};

#endif
