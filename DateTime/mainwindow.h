#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QDebug>
#include <QPainter>
#include <QImage>
#include <QFileDialog>
#include <QProcess>
#include <QMenu>
#include <QDesktopWidget>
#include <QCloseEvent>
#include <QStorageInfo>
#include <conio.h>
#include <iostream>
#include "filedialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void validateMedia(QString, QString);
    int a;
protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButton_clicked();
    void onFileDialogDirectoryChanged(const QString &);

    void on_toolButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
