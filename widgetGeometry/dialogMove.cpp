#include "dialogMove.h"

dialogMove::dialogMove(QWidget  *parent):QDialog(parent){
    siXoffset = 20;
    siyoffset = 20;

    m_isPushOk = 0;
	
    initWidget();
}

dialogMove::dialogMove(int x, int y, QWidget *parent):QDialog(parent),siXoffset(x),siyoffset(y)
{
    m_isPushOk = 0;
    initWidget();
}

void dialogMove::slotOK()
{
    m_isPushOk = 1;

    siXoffset = m_pLeX->text().toInt();
    siyoffset = m_pLeY->text().toInt();

    this->hide();
}

void dialogMove::slotCancle()
{
    m_isPushOk = 0;
    this->hide();
}

dialogMove::~dialogMove(){
	delete m_plbX;
	delete m_pLeX;
	delete m_plbY;
	delete m_pLeY;
	delete m_pBtnOK;
	delete m_pBtnCancel;
    delete m_pGridLayoutTop;
}

void dialogMove::initWidget()
{
    m_pGridLayoutTop = new QGridLayout;

    m_plbX = new QLabel("x offset");
    m_pLeX  = new QLineEdit(QString::asprintf("%d",siXoffset));

    m_plbY = new QLabel("y offset");
    m_pLeY  = new QLineEdit(QString::asprintf("%d",siyoffset));

    m_pBtnOK = new QPushButton("OK");
    m_pBtnCancel = new QPushButton("Cancle");

    m_pGridLayoutTop->addWidget(m_plbX,0,0);
    m_pGridLayoutTop->addWidget(m_pLeX,0,1);
    m_pGridLayoutTop->addWidget(m_plbY,1,0);
    m_pGridLayoutTop->addWidget(m_pLeY,1,1);
    m_pGridLayoutTop->addWidget(m_pBtnCancel,2,0);
    m_pGridLayoutTop->addWidget(m_pBtnOK,2,1);

    connect(m_pBtnOK,SIGNAL(clicked()),this,SLOT(slotOK()));
    connect(m_pBtnCancel,SIGNAL(clicked()),this,SLOT(slotCancle()));

    setLayout(m_pGridLayoutTop);
}

int dialogMove::isPushOk()
{
    return m_isPushOk;
}
