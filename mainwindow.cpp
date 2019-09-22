#include "mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QImageReader>
#include <QImageWriter>
#include <QStandardPaths>
#include <QMessageBox>
#include <QGuiApplication>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainTabwidget = new QTabWidget;

    m_pWgtShow      = new widgetShow;
    m_pWgtGrayTrans = new widgetGrayTransform;
    m_wgtPlay       = new PlayWidget;

    mainTabwidget->setIconSize(QSize(24, 24));
    mainTabwidget->setTabShape(QTabWidget::Triangular);
    mainTabwidget->addTab(m_pWgtShow,QIcon(":/images/films.png"),"预览");
    mainTabwidget->addTab(m_pWgtGrayTrans,QIcon(":/images/films.png"),"灰度变换");
    mainTabwidget->addTab(m_wgtPlay,QIcon(":/images/films.png"),"paly");

    setMinimumSize(900,480);
    setCentralWidget(mainTabwidget);
    setWindowIcon(QIcon(":/images/appMain.png"));
    setWindowTitle(tr("DIP"));

    connect(m_pWgtShow, SIGNAL(openImageFile(QString)), this, SLOT(loadFile(QString)));
    connect(m_pWgtGrayTrans, SIGNAL(openImageFile(QString)), this, SLOT(loadFile(QString)));

    createActions();
}

MainWindow::~MainWindow()
{

}

static void initializeImageFileDialog(QFileDialog &dialog, QFileDialog::AcceptMode acceptMode)
{
#if 0
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    QStringList mimeTypeFilters;
    const QByteArrayList supportedMimeTypes = acceptMode == QFileDialog::AcceptOpen
        ? QImageReader::supportedMimeTypes() : QImageWriter::supportedMimeTypes();
    foreach (const QByteArray &mimeTypeName, supportedMimeTypes)
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg image/bmp");
    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");

#else
    static bool firstDialog = true;

    if (firstDialog) {
        firstDialog = false;
        const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
        dialog.setDirectory(picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.last());
    }

    if (acceptMode == QFileDialog::AcceptSave)
        dialog.setDefaultSuffix("jpg");
#endif
}

bool MainWindow::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    image = reader.read();
    if (image.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    m_pWgtShow->showImage(image);
    m_pWgtGrayTrans->showImage(image);
    m_wgtPlay->showImage(image);

    setWindowFilePath(fileName);

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
    statusBar()->showMessage(message);
    return true;
}


void MainWindow::open()
{
    QFileDialog dialog(this, tr("Open File"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

void MainWindow::saveAs()
{
    QFileDialog dialog(this, tr("Save File As"));
    initializeImageFileDialog(dialog, QFileDialog::AcceptSave);

//    while (dialog.exec() == QDialog::Accepted && !saveFile(dialog.selectedFiles().first())) {}
}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&文件"));

    openAsAct = fileMenu->addAction(tr("&打开"), this, &MainWindow::open);
    //openAsAct->setShortcut(QKeySequence::Open);

    saveAsAct = fileMenu->addAction(tr("&另存为"), this, &MainWindow::saveAs);
    saveAsAct->setEnabled(false);
}
