#include "dialogThresholdTwo.h"

dialogThresholdTwo::dialogThresholdTwo(QWidget  *parent):QDialog(parent){
    siThreshold1 = 20;
    siThreshold2 = 20;

    m_isPushOk = 0;
	
    initWidget();
}

dialogThresholdTwo::dialogThresholdTwo(int siThreshold1, int siThreshold2, QWidget *parent):QDialog(parent),siThreshold1(siThreshold1),siThreshold2(siThreshold2)
{
    m_isPushOk = 0;
    initWidget();
}

void dialogThresholdTwo::slotOK()
{
    m_isPushOk = 1;

    siThreshold1 = m_pLeX->text().toInt();
    siThreshold2 = m_pLeY->text().toInt();

    this->hide();
}

void dialogThresholdTwo::slotCancle()
{
    m_isPushOk = 0;
    this->hide();
}

dialogThresholdTwo::~dialogThresholdTwo(){
	delete m_plbX;
	delete m_pLeX;
	delete m_plbY;
	delete m_pLeY;
	delete m_pBtnOK;
	delete m_pBtnCancel;
    delete m_pGridLayoutTop;
}

void dialogThresholdTwo::initWidget()
{
    m_pGridLayoutTop = new QGridLayout;

    m_plbX = new QLabel("слох1");
    m_pLeX  = new QLineEdit(QString::asprintf("%d",siThreshold1));

    m_plbY = new QLabel("слох2");
    m_pLeY  = new QLineEdit(QString::asprintf("%d",siThreshold2));

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

int dialogThresholdTwo::isPushOk()
{
    return m_isPushOk;
}
