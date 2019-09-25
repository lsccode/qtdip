#include "dialogRotate.h"

dialogRotate::dialogRotate(QWidget  *parent):QDialog(parent){
    dbRotate = 20;

    m_isPushOk = 0;
	
    initWidget();
}

dialogRotate::dialogRotate(double dbRotate, QWidget *parent):QDialog(parent),dbRotate(dbRotate)
{
    m_isPushOk = 0;
    initWidget();
}

void dialogRotate::slotCancle()
{
    m_isPushOk = 0;
    this->hide();
}

void dialogRotate::slotOK()
{
    m_isPushOk = 1;

    dbRotate = m_pLeRotate->text().toDouble();

    this->hide();
}

dialogRotate::~dialogRotate(){
    delete m_plbRotate;
    delete m_pLeRotate;
	delete m_pBtnOK;
	delete m_pBtnCancel;
    delete m_pGridLayoutTop;
}

void dialogRotate::initWidget()
{
    m_pGridLayoutTop = new QGridLayout;

    m_plbRotate = new QLabel("旋转角度");
    m_pLeRotate  = new QLineEdit(QString::asprintf("%f",dbRotate));


    m_pBtnOK = new QPushButton("OK");
    m_pBtnCancel = new QPushButton("Cancle");

    m_pGridLayoutTop->addWidget(m_plbRotate,0,0);
    m_pGridLayoutTop->addWidget(m_pLeRotate,0,1);
    m_pGridLayoutTop->addWidget(m_pBtnCancel,1,0);
    m_pGridLayoutTop->addWidget(m_pBtnOK,1,1);

    connect(m_pBtnCancel,SIGNAL(clicked()),this,SLOT(slotCancle()));
	connect(m_pBtnOK,SIGNAL(clicked()),this,SLOT(slotOK()));

    setLayout(m_pGridLayoutTop);
}

int dialogRotate::isPushOk()
{
    return m_isPushOk;
}
