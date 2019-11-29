#include "myslider.h"
#include <QMouseEvent>

MySlider::MySlider(QWidget *parent) : QSlider(parent)
{

}

void MySlider::mousePressEvent(QMouseEvent *ev)
{
    QSlider::mousePressEvent(ev);
    double pos = (double)ev->pos().x()/(double)width();
    int nVal = pos*(maximum()-minimum())+minimum();
    setValue(nVal);
    emit MySliderClicked(nVal);
}
