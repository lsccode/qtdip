#include <QPainter>
#include <QMessageBox>

#include "dialogGrayWindow.h"

WidgetPainterWindow::WidgetPainterWindow(QWidget *parent): QWidget(parent)
{
    setFixedSize(320, 320);
    m_thres1 = 50;
    m_thres2 = 200;
}

void WidgetPainterWindow::setThres(int thres1, int thres2)
{
    this->m_thres1 = thres1;
    this->m_thres2 = thres2;
}

void WidgetPainterWindow::reDraw()
{
    update();
}

void WidgetPainterWindow::paintEvent(QPaintEvent *event)
{
   if(event == nullptr)
       return;

    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen;
    pen.setColor(Qt::magenta);
    pen.setStyle(Qt::SolidLine);
    pen.setWidthF(2);
    painter.setPen(pen);

    painter.translate(10,280); // 坐标原点移动到左下角
    painter.scale(1, -1);  // Y坐标变换为向上
//    painter.setWindow(-10, 2, 20, -4); // (-10, 2)    (10, -2)

    // 设置背景颜色
    painter.fillRect(-10, -10, 300, 300, Qt::darkBlue);
    painter.drawLine(QPointF(0, 0), QPointF(m_thres1, 0));   // x
    painter.drawLine(QPointF(m_thres1, 0), QPointF(m_thres1, m_thres1));     //
    painter.drawLine(QPointF(m_thres1, m_thres1), QPointF(m_thres2, m_thres2));     //
    painter.drawLine(QPointF(m_thres2, m_thres2), QPointF(m_thres2, 255));
    painter.drawLine(QPointF(m_thres2, 255), QPointF(255, 255));

    painter.drawLine(QPointF(0, 0), QPointF(0, 260));
    painter.drawLine(QPointF(0, 0), QPointF(260, 0));

    //painter.rotate(90);
    //painter.scale(-1, -1);
    for(int i = 0; i< 280; i += 50)//分成10份
    {
        //选取合适的坐标，绘制一段长度为4的直线，用于表示刻度
        painter.drawLine(QPointF(0, i),QPointF(0, i+10));
        painter.drawText(QPointF(0, i),QString::asprintf("%d",i));
        //painter.drawText(0, i ,"10");
    }
    painter.drawText(QPointF(0, 270),"y");

    painter.scale(1, -1);
    for(int i = 0; i< 280; i += 50)//分成10份
    {
        //选取合适的坐标，绘制一段长度为4的直线，用于表示刻度
        painter.drawLine(QPointF(i, 0),QPointF(i+10, 0));
        painter.drawText(QPointF(i, 0),QString::asprintf("%d",i));
        //painter.drawText(0, i ,"10");
    }
    painter.drawText(QPointF(280, 0),"x");


    painter.end();
}

dialogGrayWindow::dialogGrayWindow(QWidget  *parent):QDialog(parent){
    siThreshold1 = 50;
    siThreshold2 = 200;

    m_isPushOk = 0;
	
    initWidget();
}

dialogGrayWindow::dialogGrayWindow(int siThreshold1, int siThreshold2, QWidget *parent):QDialog(parent),siThreshold1(siThreshold1),siThreshold2(siThreshold2)
{
    m_isPushOk = 0;
    initWidget();
}

void dialogGrayWindow::slotOK()
{
    m_isPushOk = 1;

    siThreshold1 = m_pLeX->text().toInt();
    siThreshold2 = m_pLeY->text().toInt();

    this->hide();
}

void dialogGrayWindow::slotCancle()
{
    m_isPushOk = 0;
    this->hide();
}

void dialogGrayWindow::slotThreshold1Change(QString str)
{
    int siValue = str.toInt();

    if(siValue < 0 || siValue > 255){
        QMessageBox::information(this, "Alert ",tr("threshold must be [0, 255]"));
        return;
    }

    siThreshold1 = m_pLeX->text().toInt();
    siThreshold2 = m_pLeY->text().toInt();

    m_pWgtPainter->setThres(siThreshold1,siThreshold2);
    m_pWgtPainter->reDraw();
}

dialogGrayWindow::~dialogGrayWindow(){
	delete m_plbX;
	delete m_pLeX;
	delete m_plbY;
	delete m_pLeY;
	delete m_pBtnOK;
	delete m_pBtnCancel;
    delete m_pGridLayoutTop;
    delete m_pHBoxLayout;
    delete m_pWgtPainter;
}

void dialogGrayWindow::initWidget()
{
    m_pGridLayoutTop = new QGridLayout;
    m_pHBoxLayout    = new QHBoxLayout;

    m_plbX = new QLabel(tr("阈值1"));
    m_pLeX  = new QLineEdit(QString::asprintf("%d",siThreshold1));

    m_plbY = new QLabel("阈值2");
    m_pLeY  = new QLineEdit(QString::asprintf("%d",siThreshold2));

    m_pBtnOK = new QPushButton("OK");
    m_pBtnCancel = new QPushButton("Cancle");

    m_pWgtPainter = new WidgetPainterWindow;

    m_pGridLayoutTop->addWidget(m_plbX,0,0);
    m_pGridLayoutTop->addWidget(m_pLeX,0,1);
    m_pGridLayoutTop->addWidget(m_plbY,1,0);
    m_pGridLayoutTop->addWidget(m_pLeY,1,1);
    m_pGridLayoutTop->addWidget(m_pBtnCancel,2,0);
    m_pGridLayoutTop->addWidget(m_pBtnOK,2,1);

    m_pHBoxLayout->addWidget(m_pWgtPainter);
    m_pHBoxLayout->addLayout(m_pGridLayoutTop);


    connect(m_pBtnOK,SIGNAL(clicked()),this,SLOT(slotOK()));
    connect(m_pBtnCancel,SIGNAL(clicked()),this,SLOT(slotCancle()));
    connect(m_pLeX,SIGNAL(textChanged(QString)),this,SLOT(slotThreshold1Change(QString)));
    connect(m_pLeY,SIGNAL(textChanged(QString)),this,SLOT(slotThreshold1Change(QString)));

    setLayout(m_pHBoxLayout);
}

int dialogGrayWindow::isPushOk()
{
    return m_isPushOk;
}
