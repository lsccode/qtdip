#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QImage>
#include "widgetShow/widgetshow.h"
#include "widgetGrayTransform/widgetgraytransform.h"
#include "widgetGeometry/widgetgeometry.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createActions();

private slots:
    void open();
    bool loadFile(const QString &fileName);
    void saveAs();
private:
    QTabWidget *mainTabwidget;

    widgetShow *m_pWgtShow;
    widgetGeometryTransform *m_pWgtGeoTrans;
    widgetGrayTransform *m_pWgtGrayTrans;
    PlayWidget *m_wgtPlay;

    QImage m_imageFile;
    QImage m_imageRgb;
    QImage m_imageGray;

    QAction *openAsAct;
    QAction *saveAsAct;
};

#endif // MAINWINDOW_H
