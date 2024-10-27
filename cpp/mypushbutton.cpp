#include "mypushbutton.h"
#include<QDebug>
#include <QPropertyAnimation>
mypushbutton::mypushbutton(QWidget *parent)
    : QPushButton{parent}
{

}
mypushbutton::mypushbutton(QString normalimgpath,QString pressimgpath)
{
    Normalimgpath=normalimgpath;
    Pressimgpath=pressimgpath;
    QPixmap pix;
    bool ret=pix.load(normalimgpath);
    if(!ret)
    {
        qDebug()<<normalimgpath<<"加载图片失败1";
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet(" QPushButton { border:0px; }");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));


}
void mypushbutton::zoom1()
{
    QPropertyAnimation * animation1 = new QPropertyAnimation(this,"geometry");
    //设置时间间隔，单位毫秒
    animation1->setDuration(200);
    //创建起始位置
    animation1->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //创建结束位置
    animation1->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置缓和曲线，QEasingCurve::OutBounce 为弹跳效果
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation1->start();


}//下跳
void mypushbutton::zoom2()
{
    QPropertyAnimation * animation1 = new QPropertyAnimation(this,"geometry");
    animation1->setDuration(300);
    animation1->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation1->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation1->setEasingCurve(QEasingCurve::OutBounce);
    animation1->start();
}
// void mypushbutton::mousePressEvent(QMouseEvent *e)
// {

//     if(this->Pressimgpath != "") //选中路径不为空，显示选中图片
//     {
//         QPixmap pixmap;
//         bool ret = pixmap.load(this->Pressimgpath);
//         if(!ret)
//         {
//             qDebug() << Pressimgpath << "加载图片失败2!";
//         }

//         this->setFixedSize( pixmap.width(), pixmap.height() );
//         this->setStyleSheet("QPushButton{border:0px;}");
//         this->setIcon(pixmap);
//         this->setIconSize(QSize(pixmap.width(),pixmap.height()));
//     }
//     //交给父类执行按下事件
//     return QPushButton::mousePressEvent(e);

// }
// void mypushbutton::mouseReleaseEvent(QMouseEvent *e)
// {
//     QPixmap pix;
//     bool ret=pix.load(Normalimgpath);
//     if(!ret)
//     {
//         qDebug()<<Normalimgpath<<"加载图片失败3";
//     }

//     this->setFixedSize(pix.width(),pix.height());
//     this->setStyleSheet("QPushButton{border:0px;}");
//     this->setIcon(pix);
//     this->setIconSize(QSize(pix.width(),pix.height()));

//     return QPushButton::mouseReleaseEvent(e);
// }
