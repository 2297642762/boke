#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class mycoin : public QPushButton
{
    Q_OBJECT
public:
    explicit mycoin(QWidget *parent = nullptr);
    mycoin(QString butpth);

    int posx;
    int posy;
    bool flag;

    int min=1;
    int max=8;
    QTimer * time1;
    QTimer * time2;
    void changeflag();
    bool isanimation;
    void mousePressEvent(QMouseEvent *e);

signals:
};

#endif // MYCOIN_H
