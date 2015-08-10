#include "http.h"
#include "tool.h"

QNetworkAccessManager* Http::s_pNetMgr;

Http::Http(QObject *parent) :
    QObject(parent)
{
    Http::s_pNetMgr = NULL;
    m_bSuccess = false;
}

Http::~Http()
{
//    if(m_pFile)
//    {
//        m_pFile->remove();
//    }

    if(!m_strFileNameTmp.isEmpty())
    {
        if(m_pFile)
        {

        }
        Tool::deleteFile(m_strFileNameTmp);
    }
}

void Http::downloadFile( QString strUrl, QString strSavePath )
{
    qDebug()<<"Http::downloadFile() thread:"<<QThread::currentThreadId();

    if(!Http::s_pNetMgr)
    {
        Http::s_pNetMgr = new QNetworkAccessManager();
    }

    QUrl url = strUrl;

//    QFileInfo info(url.path());
//    QString strFileName(info.fileName());

//    //获取文件名
//    if(strFileName.isEmpty())
//    {
//        return;
//    }

    Tool::createDirectory( strSavePath, true );
    m_strFileNameTmp = strSavePath + ".tmp";
    m_strFileName = strSavePath;
    m_pFile = new QFile(m_strFileNameTmp);
    if(!m_pFile->open(QIODevice::WriteOnly))
    {
        //如果打开文件失败，则删除file，并使file指针为0，然后返回
        qDebug() << "file open error"<<strSavePath;

        delete m_pFile;
        m_pFile = NULL;

        return;
    }

    //测试
//    {
//    QSettings settings("option.ini", QSettings::IniFormat); // 当前目录的INI文件
//    settings.beginGroup("Option");
//    settings.setValue("downloadFile strUrl", strUrl );
//    settings.endGroup();
//    }

    m_bSuccess = true;
    m_pNetReply = Http::s_pNetMgr->get(QNetworkRequest(url));

    //下载完成后
    connect( m_pNetReply, SIGNAL(finished()), this, SLOT(downloadFinished()) );
    //有可用数据时
    connect( m_pNetReply, SIGNAL(readyRead()), this, SLOT(downloadReadyRead()) );
    //更新进度时
    connect( m_pNetReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(updateDataReadProgress(qint64,qint64)) );

    //connect( m_pNetReply, SIGNAL(error(QNetworkReply::NetworkError code)), this, SLOT(downloadError(QNetworkReply::NetworkError code)) );
}

void Http::updateDataReadProgress( qint64 bytesReceived, qint64 bytesTotal )
{
    if( -1 == bytesTotal )
    {
        //m_bSuccess = false;
        return;
    }

    //qDebug()<<bytesReceived<<bytesTotal;
    float fTmp = (float)bytesReceived/(float)bytesTotal;
    int nPercentage = fTmp*100;
    emit(sigCurrentDownloadFile(nPercentage));
}

void Http::downloadFinished()
{
    QNetworkReply::NetworkError err = m_pNetReply->error();
    QString strError = m_pNetReply->errorString();
    if( 0 != err )
    {
        m_bSuccess = false;
    }

    if(m_pFile == NULL)
    {
        return;
    }

    QString strFile = m_pFile->fileName();
    strFile.replace( "/", "\\" );

    m_pFile->flush();
    m_pFile->close();
    m_pNetReply->deleteLater();
    m_pNetReply = NULL;



    if(m_bSuccess )
    {
        m_pFile->rename( m_strFileNameTmp, m_strFileName );

        emit sigDownloadFinished( m_strFileName, m_bSuccess );
    }
    else
    {
        Tool::deleteFile(m_strFileNameTmp);


        int n1 = strError.indexOf("http");
        int n2 = strError.lastIndexOf("/");
        QString tmp = strError.mid( n1, n2-n1+1 );
        strError.remove(tmp);

        emit sigDownloadFinished( strError, m_bSuccess );
    }



    m_strFileName.clear();
    m_strFileNameTmp.clear();

    m_pFile->deleteLater();
    m_pFile = NULL;
}

void Http::downloadReadyRead()
{
    if(m_pFile)
    {
        m_pFile->write(m_pNetReply->readAll());
    }
}

void Http::cancelDownload()
{
    if(m_pNetReply)
    {
        m_bSuccess = false;
        m_pNetReply->abort();
    }
}

void Http::downloadError(QNetworkReply::NetworkError code)
{
    int n = 0;
}

