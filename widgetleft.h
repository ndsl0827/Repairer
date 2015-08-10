#ifndef WIDGETLEFT_H
#define WIDGETLEFT_H

#include <QWidget>
#include <QPushButton>

class WidgetLeft : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetLeft(QWidget *parent = 0);

signals:
    void changePage( int nCurPage );

public slots:
    void changePage( QString strPage );
    void registerDlg();

private:
    void setButtonPng( int nIndex );

private:
    QPushButton* m_pBtn[4];
    QPixmap m_pixmap[4];
    QPixmap m_pixmap2[4];
    int m_nCurrentButton;

    QPushButton* m_pBtnRegister;

    QList<QPushButton*> m_lstBtn;
};

#endif // WIDGETLEFT_H
