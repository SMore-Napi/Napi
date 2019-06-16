#ifndef CREATEFRAME_H
#define CREATEFRAME_H

#include <QDialog>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

class CreateFrame
{
private:
    QString frame;
    QString key;
public:
    CreateFrame(QString image, bool seg);
    CreateFrame(QString image_a, QString image_b, QString image_c, bool seg);
    void setkey(QString x);
    void setframe(QString x);
    QString getkey();
    QString getframe();
};

#endif // CREATEFRAME_H
