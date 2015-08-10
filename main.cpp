#include "widgetmain.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QDesktopServices>
#include <QMessageBox>
#include "global.h"
#include "tool.h"

#include "desmgr.h"
#include <windows.h>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //限制只能启动一个进程
    QSharedMemory shared_memory;
    shared_memory.setKey("85524");
    if(shared_memory.attach())
    {
        return 0;
    }

    shared_memory.create(1);

    WidgetMain w;
    if(argc > 1)
    {
        w.hide();

        QString path = "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
        QSettings reg(path, QSettings::NativeFormat);
        QString value = reg.value("dllescort").toString();
        value = value.left(value.lastIndexOf("\\dllescort.exe"));
        Global::s_strCurrentPath = value;
    }
    else
    {
        w.show();
        Global::s_strCurrentPath = QDir::currentPath();
    }

    qDebug()<<"main thread:"<<QThread::currentThreadId();

    a.setWindowIcon(QIcon(":/main/inno"));

    //初始化
     Global::initGlobalData();

    w.init();

    Global::readIni();

    return a.exec();
}
