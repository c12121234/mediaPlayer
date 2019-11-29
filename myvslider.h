#ifndef MYVSLIDER_H
#define MYVSLIDER_H
#include <QSlider>

class MyVslider :public QSlider
{
    Q_OBJECT
public:
    MyVslider(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *ev) override;
signals:
    void MyVsliderClicked(int nVal);
};

#endif // MYVSLIDER_H
