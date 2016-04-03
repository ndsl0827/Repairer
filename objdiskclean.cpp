#include "objdiskclean.h"
#include "tool.h"
#include "global.h"
#include <QDebug>
#include <QDir>

ObjDiskClean::ObjDiskClean(QObject *parent) :
    QObject(parent)
{
}

ObjDiskClean::~ObjDiskClean()
{

}

void ObjDiskClean::clean()
{
    UINT typeDev = 0;
    wchar_t ch[4] = { 'X', ':', '\\', '\0' };
    for( wchar_t c = 'A'; c <= 'Z'; c++ )
    {
        ch[0] = c;
        typeDev = ::GetDriveType(ch);
        if( typeDev == DRIVE_FIXED )
        {
            QString strDev = QString::fromWCharArray(ch);
            qDebug()<<"分区："<<strDev<<"开始清理";

            findFiles(strDev);
        }
    }
}

void ObjDiskClean::findFiles(QString strPath)
{
    QDir dir(strPath);

    if(!dir.exists())
        return;

    dir.setFilter(QDir::Dirs|QDir::Files);

    dir.setSorting(QDir::DirsFirst);

    QFileInfoList list = dir.entryInfoList();

    int i = 0;

    bool bIsDir;

    do{
           QFileInfo fileInfo = list.at(i);

           if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
           {
                i++;
                continue;
           }

            bIsDir = fileInfo.isDir();

           if (bIsDir)
           {
               //fileInfo.size(),fileInfo.fileName(),fileInfo.path()

               findFiles(fileInfo.filePath());
           }
           else
           {
                qDebug()<<"find file:"<<fileInfo.fileName();

                QString strTmp = fileInfo.fileName();
           }
           i++;
    }
    while(i<list.size());
}

void ObjDiskClean::addSuffix(QString strSuffix)
{
    if(m_lstCleanSuffix.indexOf(strSuffix.toLower()) != -1)
    {
        m_lstCleanSuffix.push_back(strSuffix.toLower());
    }
}

void ObjDiskClean::removeSuffix(QString strSuffix)
{
    int iIndex = m_lstCleanSuffix.indexOf(strSuffix.toLower();
    if(iIndex != -1)
    {
        m_lstCleanSuffix.removeAt(iIndex);
    }
}

void ObjDiskClean::procFile(QString strFile)
{
    QString strSuffix = Tool::getFileSuffix(strFile);

    for(QList<QString>::iterator it = m_lstCleanSuffix.begin(); it == m_lstCleanSuffix.end(); it++)
    {
        if(*it == strSuffix)
        {

        }
    }
}
