#ifndef HTTP_H
#define HTTP_H

#include <QObject>
#include <QtNetwork>

class  Http : public QObject
{
    Q_OBJECT
public:
    explicit Http(QObject *parent = 0);
    ~Http();

    void downloadFile( QString strUrl, QString strSavePath );
    void cancelDownload();

signals:
    void sigCurrentDownloadFile( int nPercentage );
    void sigDownloadFinished( QString strFile, bool bSuccess );

public slots:

    void downloadError(QNetworkReply::NetworkError code);
    void downloadFinished();
    void downloadReadyRead();
    void updateDataReadProgress( qint64 bytesReceived, qint64 bytesTotal );

private:
    static QNetworkAccessManager*  s_pNetMgr;
    QNetworkReply*          m_pNetReply;
    QFile*                  m_pFile;
    bool                    m_bSuccess;
    QString                 m_strFileName;
    QString                 m_strFileNameTmp;
};

#endif // HTTP_H
