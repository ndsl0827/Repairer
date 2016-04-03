#ifndef OBJDISKCLEAN_H
#define OBJDISKCLEAN_H

#include <QObject>

class ObjDiskClean : public QObject
{
    Q_OBJECT
public:
    explicit ObjDiskClean(QObject *parent = 0);
    ~ObjDiskClean();

    void addSuffix(QString strSuffix);
    void removeSuffix(QString strSuffix);

private:
    void findFiles(QString strPath);
    void procFile(QString strFile);  //判断是否删除该文件

signals:

public slots:
    void clean();

private:
    QList<QString> m_lstCleanSuffix;

};

#endif // OBJDISKCLEAN_H
