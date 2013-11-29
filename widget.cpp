#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPoint>
#include <QPen>
#include <qmath.h>
#include <QTime>
#include <QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    setWindowTitle(tr("时钟"));
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(8);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);//使用画笔
    painter.setBrush(QColor(0,0,0,100));
    painter.drawEllipse(width()/2-100,height()/2-100,200,200);

    QPen pen1;
    pen1.setWidth(1);
    QPen pen2;
    pen1.setWidth(3);
    painter.translate(width()/2,height()/2);
    for(int i=0;i<60;i++)//绘制表盘刻度
    {
        if(i%5!=0)//绘制短刻度线
        {
            painter.setPen(pen2);
            painter.drawLine(100,0,90,0);
        }
        else//绘制长刻度线
        {
            painter.setPen(pen1);
            painter.drawLine(100,0,85,0);
        }
        painter.rotate(6.0);
    }

    painter.save();
    //绘制文字
    QFont font("宋体",16,QFont::Bold);//设置字体样式
    //使用字体
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(65,8,tr("3"));
    painter.drawText(-75,8,tr("9"));
    painter.drawText(-13,-60,tr("12"));
    painter.drawText(-5,75,tr("6"));
    painter.setPen(QColor(233,195,65));
    painter.drawText(-30,-40,tr("Rolex"));

    painter.save();

    QTimer *timer=new QTimer(this);//声明一个定时器
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(1000.0);

    QTime time=QTime::currentTime();

    //根据个点坐标画针分针秒针
     QPoint hourHand[5] = {QPoint(-3,10),QPoint(3,10),QPoint(3,-45),QPoint(0,-60),QPoint(-3,-45) };

     QPoint minuteHand[2] = {QPoint(0,20),QPoint(0,-70)};

     QPoint secondHand[2] = {QPoint(0,30),QPoint(0,-90)};

    //绘制时针
    QPen penh;
    penh.setWidthF(1);
    painter.setPen(penh);
    painter.setBrush(Qt::black);
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));//坐标轴旋转的角度
    painter.drawConvexPolygon(hourHand,5);//根据三个坐标点绘图
    painter.restore();

    //绘制分针
    QPen penm;
    penm.setColor(Qt::green);
    penm.setWidthF(2);
    painter.setPen(penm);
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 2);
    painter.restore();//恢复保存前状态

    //绘制秒针
    QPen pens;
    pens.setColor(Qt::red);
    pens.setWidthF(1);
    painter.setPen(pens);
    painter.setBrush(Qt::red);
    painter.rotate(6.0*time.second());
    painter.drawConvexPolygon(secondHand,2);
    painter.restore();

    //绘制秒针上的两个红点
    painter.drawEllipse(-5,15,10,10);
    painter.drawEllipse(-3,-75,6,6);

    //绘制中心黑点
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);
    painter.drawEllipse(-6,-6,12,12);
}
