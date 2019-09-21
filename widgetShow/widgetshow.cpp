#include "widgetshow.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>

//  参考 https://blog.csdn.net/cqltbe131421/article/details/73322620

widgetShow::widgetShow(QWidget *parent) : QWidget(parent)
{

    m_pWgtLeftShowBf = new PlayWidget;
    m_pWgtRightShowAf = new PlayWidget;

#if 0
    QGridLayout *layoutTop = new QGridLayout;;
    layoutTop->addWidget(m_pWgtLeftShowBf,0,0);
    layoutTop->addWidget(m_pWgtRightShowAf,0,1);
    layoutTop->setHorizontalSpacing(3);
#else
    QHBoxLayout *layoutTop = new QHBoxLayout;;
    layoutTop->addWidget(m_pWgtLeftShowBf);
    layoutTop->addSpacing(5);
    layoutTop->addWidget(m_pWgtRightShowAf);

#endif

    createAction();

    setLayout(layoutTop);
}

void widgetShow::showImage(QImage image)
{
    m_image = image;
    m_pWgtLeftShowBf->showImage(m_image);
}

void widgetShow::imageProcess(QImage image)
{
    m_pWgtRightShowAf->showImage(image);

}

void widgetShow::createAction()
{
    QAction *pActionShow = new QAction(tr("显示"), this);
    QAction *pActionTest = new QAction(tr("测试"), this);

    pActionShow->setData(1);
    pActionTest->setData(2);

    addAction(pActionShow);
    addAction(pActionTest);
    connect(pActionShow, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));
    connect(pActionTest, SIGNAL(triggered()), this, SLOT(onTaskBoxContextMenuEvent()));

    setContextMenuPolicy(Qt::ActionsContextMenu);
    setFocusPolicy(Qt::StrongFocus);

}

void widgetShow::onTaskBoxContextMenuEvent()
{
    QAction *pEven = qobject_cast<QAction *>(this->sender()); //this->sender()就是发信号者 QAction

    //获取发送信息类型 1:显示 2:测试
    int iType = pEven->data().toInt();

    switch (iType)
    {
    case 1:
        imageProcess(m_image);
        break;
    case 2:
        QMessageBox::about(this, "tip", pEven->text());
        break;
    default:
        break;
}
}

