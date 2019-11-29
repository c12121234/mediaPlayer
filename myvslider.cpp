#include "myvslider.h"
#include <QMouseEvent>
MyVslider::MyVslider(QWidget *parent):
    QSlider(parent)
{

}

void MyVslider::mousePressEvent(QMouseEvent *ev)
{
    QSlider::mousePressEvent(ev);
    int nHeight = height();
    double pos =((double)nHeight-(double)ev->pos().y())/(double)nHeight;
    int nVal = pos*(maximum()-minimum())+minimum();
    setValue(nVal);
    emit MyVsliderClicked(nVal);
}
