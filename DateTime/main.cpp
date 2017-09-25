#include "mainwindow.h"
#include <QApplication>
#include <stdio.h>
int cnt;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//float value;
//value = 2.8;
//printf("value= %d\n",value);


    qDebug() << "Value = " <<cnt;

    MainWindow w;
    w.show();

    return a.exec();
}



/*#include<stdio.h>

main()
{
float value;
value = 2.8;
printf("value= %d\n",value);
}*/
