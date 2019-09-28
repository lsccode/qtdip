#include <QPainter>
#include <QMessageBox>

#include "dialogPiecewiseLine.h"

WidgetPainterPiecewiseLine::WidgetPainterPiecewiseLine(QWidget *parent): QWidget(parent)
{
    setFixedSize(340, 340);
    m_x1 = 30;
    m_y1 = 50;
    m_y2 = 200;
    m_x2 = 180;
}

void WidgetPainterPiecewiseLine::setThres(int x1, int y1, int x2, int y2)
{
    this->m_x1 = x1;
	this->m_y1 = y1;
    this->m_x2 = x2;
	this->m_y2 = y2;
}

void WidgetPainterPiecewiseLine::reDraw()
{
    update();
}

void WidgetPainterPiecewiseLine::paintEvent(QPaintEvent *event)
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

    painter.translate(10,320); // 坐标原点移动到左下角
    painter.scale(1, -1);  // Y坐标变换为向上
//    painter.setWindow(-10, 2, 20, -4); // (-10, 2)    (10, -2)

    // 设置背景颜色
    painter.fillRect(-10, -10, 330, 330, Qt::darkBlue);
	
    painter.drawLine(QPointF(0, 0), QPointF(m_x1, m_y1));  
    painter.drawLine(QPointF(m_x1, m_y1), QPointF(m_x2, m_y2));    
    painter.drawLine(QPointF(m_x2, m_y2), QPointF(255, 255));     

    painter.drawLine(QPointF(0, 0), QPointF(0, 310));
    painter.drawLine(QPointF(0, 0), QPointF(310, 0));

    // 仍然以左上角为坐标原点
    QTransform transform;
    transform.translate(10,320);
    painter.setWorldTransform(transform);

    for(int i = 0; i<= 300; i += 50)//分成10份
    {
        //选取合适的坐标，绘制一段长度为4的直线，用于表示刻度
        painter.drawLine(QPointF(i, 0),QPointF(i, -10));
        painter.drawText(QPointF(i+5, 0),QString::asprintf("%d",i));
    }
    painter.drawText(QPointF(310, -10),"x");

    // 坐标系从10,370，y轴方向向下，上面painter的坐标轴已经为负，所以应该从负方向开始画
    for(int i = -50; i >= -300; i -= 50)//分成10份
    {
        //选取合适的坐标，绘制一段长度为4的直线，用于表示刻度
        painter.drawLine(QPointF(0, i),QPointF(10, i));
        painter.drawText(QPointF(0, i-5),QString::asprintf("%d",-i));
    }
    painter.drawText(QPointF(-10,-310),"y");

    painter.end();
}

dialoPiecewiseline::dialoPiecewiseline(QWidget  *parent):QDialog(parent){
    siX1 = 30;
    siY1 = 50;
    siX2 = 200;
    siY2 = 180;

    m_isPushOk = 0;
	
    initWidget();
}

dialoPiecewiseline::dialoPiecewiseline(int siX1, int siY1, int siX2, int siY2, QWidget *parent):
    QDialog(parent),siX1(siX1),siY1(siY1),siX2(siX2),siY2(siY2)
{
    m_isPushOk = 0;
    initWidget();
}

void dialoPiecewiseline::slotOK()
{
    m_isPushOk = 1;

    siX1 = m_pLeX1->text().toInt();
    siY1 = m_pLeY1->text().toInt();
    siX2 = m_pLeX2->text().toInt();
    siY2 = m_pLeY2->text().toInt();

    this->hide();
}

void dialoPiecewiseline::slotCancle()
{
    m_isPushOk = 0;
    this->hide();
}

void dialoPiecewiseline::slotThreshold1Change(QString str)
{
    int siValue = str.toInt();

    if(siValue < 0 || siValue > 255){
        QMessageBox::information(this, "Alert ",tr("threshold must be [0, 255]"));
        return;
    }

    siX1 = m_pLeX1->text().toInt();
    siY1 = m_pLeY1->text().toInt();
    siX2 = m_pLeX2->text().toInt();
    siY2 = m_pLeY2->text().toInt();

    m_pWgtPainter->setThres(siX1, siY1, siX2, siY2);
    m_pWgtPainter->reDraw();
}

dialoPiecewiseline::~dialoPiecewiseline(){
	delete m_plbX1;
	delete m_pLeX1;
	delete m_pLeY1;
    delete m_plbX2;
    delete m_pLeX2;
    delete m_pLeY2;
	delete m_pBtnOK;
	delete m_pBtnCancel;
    delete m_pGridLayoutTop;
    delete m_pHBoxLayout;
    delete m_pWgtPainter;
}

void dialoPiecewiseline::initWidget()
{
    m_pGridLayoutTop = new QGridLayout;
    m_pHBoxLayout    = new QHBoxLayout;

    m_plbX1 = new QLabel(tr("坐标1"));
    m_pLeX1  = new QLineEdit(QString::asprintf("%d",siX1));
    m_pLeY1  = new QLineEdit(QString::asprintf("%d",siY1));

    m_plbX2 = new QLabel(tr("坐标2"));
    m_pLeX2  = new QLineEdit(QString::asprintf("%d",siX2));
    m_pLeY2  = new QLineEdit(QString::asprintf("%d",siY2));

    m_pBtnOK = new QPushButton("OK");
    m_pBtnCancel = new QPushButton("Cancle");

    m_pWgtPainter = new WidgetPainterPiecewiseLine;

    m_pGridLayoutTop->addWidget(m_plbX1,0,0);
    m_pGridLayoutTop->addWidget(m_pLeX1,0,1);
    m_pGridLayoutTop->addWidget(m_pLeY1,0,2);

    m_pGridLayoutTop->addWidget(m_plbX2,1,0);
    m_pGridLayoutTop->addWidget(m_pLeX2,1,1);
    m_pGridLayoutTop->addWidget(m_pLeY2,1,2);

    m_pGridLayoutTop->addWidget(m_pBtnCancel,2,0);
    m_pGridLayoutTop->addWidget(m_pBtnOK,2,1);

    m_pHBoxLayout->addWidget(m_pWgtPainter);
    m_pHBoxLayout->addLayout(m_pGridLayoutTop);


    connect(m_pBtnOK,SIGNAL(clicked()),this,SLOT(slotOK()));
    connect(m_pBtnCancel,SIGNAL(clicked()),this,SLOT(slotCancle()));
    connect(m_pLeX1,SIGNAL(textChanged(QString)),this,SLOT(slotThreshold1Change(QString)));
    connect(m_pLeY1,SIGNAL(textChanged(QString)),this,SLOT(slotThreshold1Change(QString)));
    connect(m_pLeX2,SIGNAL(textChanged(QString)),this,SLOT(slotThreshold1Change(QString)));
    connect(m_pLeY2,SIGNAL(textChanged(QString)),this,SLOT(slotThreshold1Change(QString)));

    setLayout(m_pHBoxLayout);
}

int dialoPiecewiseline::isPushOk()
{
    return m_isPushOk;
}
