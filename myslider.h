#ifndef MYSLIDER_H
#define MYSLIDER_H
#include <QSlider>


class MySlider : public QSlider
{
    Q_OBJECT
public:
    explicit MySlider(QWidget *parent = nullptr);
protected:
    void mousePressEvent(QMouseEvent *ev) override;

signals:
    void MySliderClicked(int nVal);
};

#endif // MYSLIDER_H
