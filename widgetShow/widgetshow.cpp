#include "widgetshow.h"

#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDropEvent>
#include <QMimeData>
#include <QSplitter>

//  参考 https://blog.csdn.net/cqltbe131421/article/details/73322620

widgetShow::widgetShow(QWidget *parent) : QWidget(parent)
{

    m_pWgtLeftShowBf = new PlayWidget;
    m_pWgtRightShowAf = new PlayWidget;

#if 0
    QHBoxLayout *layoutTop = new QHBoxLayout;
    layoutTop->addWidget(m_pWgtLeftShowBf);
    layoutTop->addSpacing(5);
    layoutTop->addWidget(m_pWgtRightShowAf);

#endif

#if 0
    QGridLayout *layoutTop = new QGridLayout;

    layoutTop->addWidget(m_pWgtLeftShowBf, 0, 0);
    layoutTop->addWidget(m_pWgtRightShowAf, 0, 1);
#endif

    QHBoxLayout *layoutTop = new QHBoxLayout;
    QSplitter *splitter = new QSplitter(Qt::Horizontal);

    splitter->addWidget(m_pWgtLeftShowBf);
    splitter->addWidget(m_pWgtRightShowAf);
    splitter->setHandleWidth(2);

//    splitter->setFrameShadow(QFrame::Raised);
//    splitter->setFrameShape(QFrame::Box);
//    splitter->setLineWidth(5);
//    splitter->setStyleSheet("QSplitter::handle{background-color: blue}");


    layoutTop->addWidget(splitter);

    // 清除layout边框的空白
    layoutTop->setMargin(0);

    createAction();
    setAcceptDrops(true);
    setLayout(layoutTop);
}

void widgetShow::showImage(QImage image)
{
    m_image = image;
    int siformat = m_image.format();
    fprintf(stderr,"format is %d\n",siformat);
    m_pWgtLeftShowBf->showImage(m_image);
}

void widgetShow::imageProcess(QImage image, int i)
{
    switch (i)
    {
    case 1:
         m_pWgtRightShowAf->showImage(image);
        break;
//    case 2:
//        QMessageBox::about(this, "tip", pEven->text());
//        break;
    default:
        break;
    }

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
    setAcceptDrops(true);
}

void widgetShow::clearAction()
{
    QList<QAction *> listActions = this->actions();

    while (!listActions.isEmpty()){
        QAction * curAct = listActions.front();
        removeAction(curAct);
        listActions.pop_front();
    }
}

void widgetShow::dragEnterEvent(QDragEnterEvent *event)
{
    event->setDropAction(Qt::MoveAction);
    event->accept();
}

void widgetShow::dropEvent(QDropEvent *event)
{
    QString temp = event->mimeData()->text();

    if(temp.contains("///"))
    {
        int n = temp.indexOf("///");
        m_imagePath = temp.mid(n + 3);
    }

    emit openImageFile(m_imagePath);
}

void widgetShow::onTaskBoxContextMenuEvent()
{
    QAction *pEven = qobject_cast<QAction *>(this->sender()); //this->sender()就是发信号者 QAction

    //获取发送信息类型 1:显示 2:测试
    int iType = pEven->data().toInt();

    imageProcess(m_image, iType);
}

