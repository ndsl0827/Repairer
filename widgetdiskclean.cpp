#include "widgetdiskclean.h"

#include "ui_widgetdiskclean.h"

#include <QThread>

WidgetDiskClean::WidgetDiskClean(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetDiskClean)
{
    ui->setupUi(this);


    m_pObjDiskClean = new ObjDiskClean();
    m_pThread = new QThread();
    m_pObjDiskClean->moveToThread(m_pThread);
    m_pThread->start();

    connect( ui->pushButton_disk_clean, &QPushButton::clicked, m_pObjDiskClean, &ObjDiskClean::clean );
}

WidgetDiskClean::~WidgetDiskClean()
{
    delete m_pObjDiskClean;
    m_pObjDiskClean = NULL;
}
