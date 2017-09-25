#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qt_windows.h>
#include <QStorageInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dateTimeEdit->setMinimumTime(QTime(0,0,05));
    static int b;
    QString integrer = "000";
    if(integrer.toInt()==0 && (integrer.length() > 6 || integrer.length() < 4 ))
        qDebug() << "failse";
    QString l = "75,102,300,324,329,367,387,453,483,486,547,551,566,590,667,671,691,701,757,792,797,798,805,808,812,822,825,886,900,901,925,926,934,943,955,972,984,992,1003,1010,1024,1031,1041,1042,1044,1052,1056,1065,1071,1072,1075,1078,1080,1081,1085,1118";
   QStringList a = l.split(",");
   //a << "949" << "816" << "822" << "835" << "959" << "183" << "392"<< "498"<< "432"<< "385"<< "1012"<< "440"<< "822"<< "676"<< "428"<< "525"<< "579"<< "590"<< "1028"<< "422"<< "547"<< "534";//<< ""<< ""<< ""<< ""<< ""<< ""<< ""<< ""<< ""<< ""<< ""<< ""<< ""<< "";
   qDebug() << a << a.length();
   a.sort();
qDebug() << a;
    validateMedia(QString("D:/Media/MediaCheck/11_Kesar.jpg"),QString("video"));
    QFileInfoList listF = QDir::drives();
    qDebug() << listF.at(0).absoluteDir();
    qDebug() << listF.at(1).absoluteDir();
    QString d = listF.at(2).absoluteDir().canonicalPath();       // drive name E://
    QStorageInfo si(listF.at(1).absoluteDir());
    qDebug() << si.name();                                       // drive label Data
    qDebug() << listF.at(2).absoluteDir().canonicalPath();
    qDebug() << "Value of a = " << a;
    qDebug() << "Value of b = " << b;
    QMenu * menuAction = new QMenu();
    menuAction->addAction(QIcon("ImportPlaylist.png"),tr("Import Layout"))->setObjectName( "actionImportPlaylist" );
    menuAction->addAction(QIcon("ExportPlaylist.png"),tr("Export Layout"))->setObjectName( "actionExportPlaylist" );
    menuAction->addAction(QIcon("ExportDefualt.png"),tr("Export as Default Schedule"))->setObjectName( "actionExportDefault" );
    ui->toolButton->setMenu(menuAction);
    QDesktopWidget *desktop = QApplication::desktop();
    qDebug() << "Geo = " << desktop->screenGeometry(0) << this->parent();
    qDebug() << "ScreenNum = " << desktop->screenNumber(this);

    QDir dir;
    dir.setPath("S:\\");
    QStorageInfo sinfo(dir);
    qDebug() << "+++++++++++++++++++++++++++++++++ " << sinfo.rootPath();
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir.setSorting(QDir::Size | QDir::Reversed);

        QFileInfoList list = dir.entryInfoList();
      //  std::cout << "     Bytes Filename" << std::endl;
        for (int i = 0; i < list.size(); ++i) {
            QFileInfo fileInfo = list.at(i);
        //    std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
        //                                            .arg(fileInfo.fileName()));
        //    std::cout << std::endl;
        }


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent * e)
{
    qDebug() << "Close Event called";
    e->ignore();
    return;
}
/*void MainWindow::resizeEvent(QResizeEvent *e)
{
    qDebug() << "Got minimize event";
}*/

void MainWindow::on_pushButton_clicked()
{
    QFileDialog dialog(this);
        connect(&dialog, SIGNAL(directoryEntered(const QString &)), this, SLOT(onFileDialogDirectoryChanged(const QString &)));
    QString folder = dialog.getExistingDirectory(this);
}

void MainWindow::onFileDialogDirectoryChanged(const QString &)
{
    qDebug() << "Directory Entered";
}

void MainWindow::validateMedia(QString mediapath, QString mediatype)
{
    QString cmd = "MediaInfo.exe \"" + mediapath +"\"";
    qDebug() << cmd;
    QProcess qproc;
    qproc.start(cmd);
    QString mediaDuration;
    if(qproc.waitForFinished(-1))
    {
        QString outputStr = "";
        outputStr = qproc.readAll();
        QStringList list1 = outputStr.split("\n");
        for (int i = 0; i < list1.size(); ++i)
        {
            QString line = list1.at(i);
            line = line.simplified();
            QString parameterName = line.section(" : ",0,0);
            QString parameterValue = line.section(" : ",1,1);
            if(parameterName == "Overall bit rate")
            {
                parameterValue = parameterValue.left(1);
                qDebug() << parameterValue;
                if(parameterValue.toInt() > 5)
                {
                    qDebug() << "False";
                    break;
                }
            }
            else if(parameterName == "Frame rate")
            {
                parameterValue = parameterValue.section(".",0,0);
                qDebug() << parameterValue;
                if(parameterValue.toInt() > 25)
                {
                    qDebug() << "False";
                    break;
                }
            }
            else if(parameterName == "Width")
            {
                parameterValue = parameterValue.section("pixels",0,0);
                parameterValue = parameterValue.remove(" ");
                qDebug() << parameterValue;
                if(parameterValue.toInt() > 1920)
                {
                    qDebug() << "False";
                    break;
                }
            }
        }
    }
}

void MainWindow::on_toolButton_clicked()
{
     ui->toolButton->showMenu();
}
