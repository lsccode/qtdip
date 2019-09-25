#include "dialogZoom.h"

dialogZoom::dialogZoom(QWidget  *parent):QDialog(parent){
    dbHor = 20;
    dbVer = 20;

    m_isPushOk = 0;
	
    initWidget();
}

dialogZoom::dialogZoom(double hor, double ver, QWidget *parent):QDialog(parent),dbHor(hor),dbVer(ver)
{
    m_isPushOk = 0;
    initWidget();
}

void dialogZoom::slotOK()
{
    m_isPushOk = 1;

    dbHor = m_pLeHor->text().toDouble();
    dbVer = m_pLeVer->text().toDouble();

    this->hide();
}

void dialogZoom::slotCancle()
{
    m_isPushOk = 0;
    this->hide();
}

dialogZoom::~dialogZoom(){
    delete m_plbHor;
    delete m_pLeHor;
    delete m_plbVer;
    delete m_pLeVer;
	delete m_pBtnOK;
	delete m_pBtnCancel;
    delete m_pGridLayoutTop;
}

void dialogZoom::initWidget()
{
    m_pGridLayoutTop = new QGridLayout;

    m_plbHor = new QLabel("x offset");
    m_pLeHor  = new QLineEdit(QString::asprintf("%f",dbHor));

    m_plbVer = new QLabel("y offset");
    m_pLeVer  = new QLineEdit(QString::asprintf("%f",dbVer));

    m_pBtnOK = new QPushButton("OK");
    m_pBtnCancel = new QPushButton("Cancle");

    m_pGridLayoutTop->addWidget(m_plbHor,0,0);
    m_pGridLayoutTop->addWidget(m_pLeHor,0,1);
    m_pGridLayoutTop->addWidget(m_plbVer,1,0);
    m_pGridLayoutTop->addWidget(m_pLeVer,1,1);
    m_pGridLayoutTop->addWidget(m_pBtnCancel,2,0);
    m_pGridLayoutTop->addWidget(m_pBtnOK,2,1);

    connect(m_pBtnOK,SIGNAL(clicked()),this,SLOT(slotOK()));
    connect(m_pBtnCancel,SIGNAL(clicked()),this,SLOT(slotCancle()));

    setLayout(m_pGridLayoutTop);
}

int dialogZoom::isPushOk()
{
    return m_isPushOk;
}
