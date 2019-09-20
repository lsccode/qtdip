#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QImage>
#include "picWidget/playwidget.h"

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
    PlayWidget *playWidget;
    PlayWidget *playWidget1;

    QImage image;

    QAction *openAsAct;
    QAction *saveAsAct;
};

#endif // MAINWINDOW_H
