#include "playscene.h"
#include<QMenuBar>
#include<QPainter>
#include<mypushbutton.h>
#include<QTimer>
#include<QLabel>
#include<QTextFormat>
#include<dataconfig.h>
#include<QPropertyAnimation>
#include<QSoundEffect>
playscene::playscene(QWidget *parent)
    : QMainWindow{parent}
{

}
playscene::playscene(int index)
{

    this->levalindex=index;


    this->setFixedSize(320,588);
    QPixmap icon(":/res/Coin0001.png");
    if (icon.isNull()) {
        qDebug() << "Icon loading failed!";
    } else {
        this->setWindowIcon(icon);
    }
    this->setWindowTitle(QString("第,%1,关--薯条翻金币").arg(QString::number(index)));

    //返回音效
    QSoundEffect * backsound = new QSoundEffect(this);
    backsound ->setSource(QUrl::fromLocalFile(":/res/:/res/BackButtonSound.wav"));
    //翻金币
    QSoundEffect * flipsound = new QSoundEffect(this);
    flipsound->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));
    //胜利
    QSoundEffect * winsound = new QSoundEffect(this);
    winsound->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));


    QMenuBar * bar=this->menuBar();
    this->setMenuBar(bar);
    QMenu * starmenu = bar->addMenu("开始");
    QAction * quiteaction = starmenu->addAction("退出");
    connect(quiteaction,&QAction::triggered,[=](){
        this->close();
    });
    //返回


    mypushbutton * closebtn= new mypushbutton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    closebtn->setParent(this);
    closebtn->move(this->width()-closebtn->width(),this->height()-closebtn->height());

    //信号
    connect(closebtn,&QPushButton::clicked,[=](){
        backsound->play();
        if(closebtn->Pressimgpath!= "") //选中路径不为空，显示选中图片
        {
            QPixmap pixmap;
            bool ret = pixmap.load(closebtn->Pressimgpath);
            if(!ret)
            {
                qDebug() << closebtn->Pressimgpath << "加载图片失败2!";
            }

            closebtn->setFixedSize( pixmap.width(), pixmap.height() );
            closebtn->setStyleSheet("QPushButton{border:0px;}");
            closebtn->setIcon(pixmap);
            closebtn->setIconSize(QSize(pixmap.width(),pixmap.height()));

        };
        QTimer::singleShot(300, this,[=](){
            QPixmap pixmap;
            bool ret = pixmap.load(closebtn->Normalimgpath);
            if(!ret)
            {
                qDebug() << closebtn->Normalimgpath << "加载图片失败2!";
            }

            closebtn->setFixedSize( pixmap.width(), pixmap.height() );
            closebtn->setStyleSheet("QPushButton{border:0px;}");
            closebtn->setIcon(pixmap);
            closebtn->setIconSize(QSize(pixmap.width(),pixmap.height()));
        });

        QTimer::singleShot(500, this,[=](){
            this->hide();
            //触发自定义信号，关闭自身
            emit this->playSceneBack();
        });

    });

    //初始化二维数组
    dataConfig config;
    for(int i = 0 ; i < 4;i++){
        for(int j = 0 ; j < 4; j++)
        {
            gamearray[i][j] = config.mData[this->levalindex][i][j];
        }
    }

    //胜利
    QLabel *label = new QLabel(this);
    QPixmap pix;
    pix.load(":/res/LevelCompletedDialogBg.png");
    label->setGeometry(0,0,pix.width(),pix.height());
    label->setPixmap(pix);
    label->setParent(this);
    label->move(this->width()*0.5-pix.width()*0.5,-pix.height());



    QLabel * label1 = new QLabel;
    label1->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label1->setFont(font);
    QString str=QString("第%1关").arg(QString::number(this->levalindex));
    label1->setText(str);
    label1->setTextFormat(Qt::RichText);
    label1->setGeometry(QRect(15, this->height() - 50,170, 50));
    // label->setStyleSheet("QLabel{background-color:rgb(200,101,102);}");
    //金币背景
    for(int i =0;i<4;i++)
    {
        for(int j = 0;j<4;j++)
        {
            QLabel * labels = new QLabel;
            labels->setParent(this);
            labels->setGeometry(0,0,50,50);
            labels->setPixmap(QPixmap(":/res/BoardNode(1).png"));
            labels->move(70 + i*50,200+j*50);

            // mycoin * coin = new mycoin(":/res/Coin0001.png");
            // coin->setParent(this);
            // coin->move(72 + i*50,204+j*50);

            QString img;
            if(gamearray[i][j]==1)
            {
                img=":/res/Coin0001.png";
            }
            else
            {
                img = ":/res/Coin0008.png";
            }

            mycoin * coin = new mycoin(img);
            coin->setParent(this);
            coin->move(72 + i*50,204+j*50);
            coin->posx = i; //记录x坐标
            coin->posy = j; //记录y坐标
            coin->flag =gamearray[i][j]; //记录正反标志

            coinbtn[i][j]=coin;
            connect(coin,&mycoin::clicked,[=](){
                flipsound->play();

                //qDebug() << "点击的位置： x = " <<  coin->posX << " y = " << coin->posY ;
                coin->changeflag();
                gamearray[i][j] = gamearray[i][j] == 0 ? 1 : 0; //数组内部记录的标志同步修改

                //翻转周围金币
                QTimer::singleShot(300,this,[=](){
                    if(coin->posx+1<=3)
                    {
                        coinbtn[coin->posx+1][coin->posy]->changeflag();
                        gamearray[coin->posx+1][coin->posy]=gamearray[coin->posx+1][coin->posy]== 0 ? 1 : 0;
                    }
                    if(coin->posx-1>=0)
                    {
                        coinbtn[coin->posx-1][coin->posy]->changeflag();
                        gamearray[coin->posx-1][coin->posy]=gamearray[coin->posx-1][coin->posy]== 0 ? 1 : 0;
                    }
                    if(coin->posy+1<=3)
                    {
                        coinbtn[coin->posx][coin->posy+1]->changeflag();
                        gamearray[coin->posx][coin->posy+1]=gamearray[coin->posx][coin->posy+1]== 0 ? 1 : 0;
                    }
                    if(coin->posy-1>=0)
                    {
                        coinbtn[coin->posx][coin->posy-1]->changeflag();
                        gamearray[coin->posx][coin->posy-1]=gamearray[coin->posx][coin->posy-1]== 0 ? 1 : 0;
                    }

                    this->iswin=true;
                    for(int i = 0;i < 4;i++)
                    {
                        for(int j = 0 ; j<4;j++)
                        {
                            if(coinbtn[i][j]->flag==false)
                            {
                                this->iswin=false;
                                break;
                            }
                        }
                    }


                    if(this->iswin)
                    {
                        winsound->play();
                        qDebug() << "胜利";
                        QPropertyAnimation * animation1 =  new QPropertyAnimation(label,"geometry");
                        animation1->setDuration(1000);
                        animation1->setStartValue(QRect(label->x(),label->y(),label->width(),label->height()));
                        animation1->setEndValue(QRect(label->x(),label->y()+170,label->width(),label->height()));
                        animation1->setEasingCurve(QEasingCurve::OutBounce);
                        animation1->start();


                    }



                });





            });

        }
    }



}

void playscene::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);






}
