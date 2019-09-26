#include "dialogThreshold.h"

dialogThreshold::dialogThreshold(QWidget  *parent):QDialog(parent){
    siThreshold = 100;

    m_isPushOk = 0;
	
    initWidget();
}

dialogThreshold::dialogThreshold(int siThreshold, QWidget *parent):QDialog(parent),siThreshold(siThreshold)
{
    m_isPushOk = 0;
    initWidget();
}

void dialogThreshold::slotCancle()
{
    m_isPushOk = 0;
    this->hide();
}

void dialogThreshold::slotOK()
{
    m_isPushOk = 1;

    siThreshold = m_pLeThreshold->text().toInt();

    this->hide();
}

dialogThreshold::~dialogThreshold(){
    delete m_plbThreshold;
    delete m_pLeThreshold;
	delete m_pBtnOK;
	delete m_pBtnCancel;
    delete m_pGridLayoutTop;
}

void dialogThreshold::initWidget()
{
    m_pGridLayoutTop = new QGridLayout;

    m_plbThreshold = new QLabel("阈值");
    m_pLeThreshold  = new QLineEdit(QString::asprintf("%d",siThreshold));


    m_pBtnOK = new QPushButton("OK");
    m_pBtnCancel = new QPushButton("Cancle");

    m_pGridLayoutTop->addWidget(m_plbThreshold,0,0);
    m_pGridLayoutTop->addWidget(m_pLeThreshold,0,1);
    m_pGridLayoutTop->addWidget(m_pBtnCancel,1,0);
    m_pGridLayoutTop->addWidget(m_pBtnOK,1,1);

    connect(m_pBtnCancel,SIGNAL(clicked()),this,SLOT(slotCancle()));
	connect(m_pBtnOK,SIGNAL(clicked()),this,SLOT(slotOK()));

    setLayout(m_pGridLayoutTop);
}

int dialogThreshold::isPushOk()
{
    return m_isPushOk;
}
