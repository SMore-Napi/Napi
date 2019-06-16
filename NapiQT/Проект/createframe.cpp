#include "createframe.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "settings.h"
using namespace cv;

// получение пикселя изображения (по типу картинки и координатам)
#define PIXEL_COLOR(type,img,x,y) (((type*)((img)->imageData+(y)*(img)->widthStep))+(x)*(img)->nChannels)

// палитра из 10 цветов
int getColor10(int H, int S, int V) //в функцию передаются каждый из параметров картинки H, S, V
{
    // условия. В зависимости от диапозона значений H, S, и V будет присвоен главный цвет
    if (V < 75)
        return 0; //черный
    if (V > 190 && S < 27)
        return 1; //белый
    if (S < 53 && V < 185)
        return 2; //серый
    if (H < 7)
        return 3; //красный
    if (H < 25)
        return 4; //оранжевый
    if (H < 34)
        return 5; //желтый
    if (H < 73)
        return 6; //зеленый
    if (H < 102)
        return 7; //голубой
    if (H < 140)
        return 8; //синий
    if (H < 170)
        return 9; //фиолетовый

    return 3;  //красный

}

template <typename T>
QString toString(T val)
{
    QString s = QString::number(val);
    return s;
}

QString most_color(int *x)
{
    int key(0);

    for (int i(0); i < 10; i++)
        key += x[i] * pow(2, i);

    return  toString(key);

}

QString create_key(int a[], int n)
{

    int colors[10];
    for (int i(0); i < 10; i++)
        colors[i] = i;

    for (int i(0); i < n - 1; i++)
        for (int j(0); j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;

                temp = colors[j];
                colors[j] = colors[j + 1];
                colors[j + 1] = temp;

            }
        }

    QString str = toString(pow(2, colors[9]) + pow(2, colors[8]) + pow(2, colors[7]));

    return str;
}

CreateFrame::CreateFrame(QString path_image, bool seg)
{

    Settings stgs;

    //CreateFrame::setkey("112");
    //CreateFrame::setframe("213 1232 2432321  32q43");


    IplImage* image_a(0);
    char image_name_a[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

    for (int i(0); i < path_image.length(); i++)
        image_name_a[i] = path_image.toStdString()[i];
    image_name_a[path_image.length()] = '\0';

    char* image_file_a = image_name_a;
        image_a = cvLoadImage(image_file_a, 1);






/*
 *
    //Mat image_a;
    //Mat hsv_a;
   // image_a = imread(path_image.toStdString(), IMREAD_COLOR);
    //imshow("Hello Opencv", image_a);
    */

    // для хранения изображения
    IplImage *hsv_a(0);


    //сегменты
    int spatialRadius = 35;
    int colorRadius = 60;
    int pyramidLevels = 3;

    if(seg)
        cvPyrMeanShiftFiltering(image_a, image_a, spatialRadius, colorRadius, pyramidLevels);





    hsv_a = cvCreateImage(cvGetSize(image_a), IPL_DEPTH_8U, 3);





    // преобразуем изображение в HSV
    cvCvtColor(image_a, hsv_a, CV_BGR2HSV);


    int pixel_y = hsv_a->height / stgs.gety_sectors();
    int pixel_x = hsv_a->width / stgs.getx_sectors();
    int *key_colors_count = new int[10];
    for (int i(0); i < 10; i++)
        key_colors_count[i] = 0;
    QString fr;


    //if (stgs.otladka)
    //{
    //   cvSaveImage("segments_a.jpg", image_a);
     //  dst(image_a, hsv_a, stgs.y_sectors, stgs.x_sectors);
    // }

    //сектора
    for (int y_sector(0); y_sector < stgs.gety_sectors(); y_sector++)
    {
       for (int x_sector = 0; x_sector < stgs.getx_sectors(); x_sector++)
       {
          //создадим динамический массив, хранящий кол-во пикселей того или иного цвета в секторе
          int *color_id = new int[10];
          //обнуление массива
          for (int i = 0; i < 10; i++)
                color_id[i] = 0;


                for (int y = y_sector * pixel_y; y < pixel_y + y_sector * pixel_y; y++)
                {
                    for (int x = x_sector * pixel_x; x < pixel_x + x_sector * pixel_x; x++)
                    {
                        // получение значения HSV у пикселя
                        uchar H_a = PIXEL_COLOR(uchar, hsv_a, x, y)[0];        // значение H
                        uchar S_a = PIXEL_COLOR(uchar, hsv_a, x, y)[1];        // значение S
                        uchar V_a = PIXEL_COLOR(uchar, hsv_a, x, y)[2];        // значение V


                        int index_color_a = getColor10(H_a, S_a, V_a);
                        color_id[index_color_a] = 1;
                        key_colors_count[index_color_a]++;

                    }
                }

                //frame_int[x_sector + x_sectors * y_sector] = most_color(color_id[0]) * 100 + most_color(color_id[1]) * 10 + most_color(color_id[2]);

                fr.append(most_color(color_id));
                fr.append(" ");

                delete[] color_id;
            }
        }

    QString fkey;
    fkey.append(create_key(key_colors_count, 10));
    fkey.append("_1");


    delete[] key_colors_count;

    // освобождаем ресурсы
    cvReleaseImage(&hsv_a);
    cvReleaseImage(&image_a);

    CreateFrame::setframe(fr);
    CreateFrame::setkey(fkey);


}

CreateFrame::CreateFrame(QString path_image_a, QString path_image_b, QString path_image_c, bool seg)
{

    Settings stgs;


    IplImage* image_a(0);
    char image_name_a[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

    for (int i(0); i < path_image_a.length(); i++)
        image_name_a[i] = path_image_a.toStdString()[i];
    image_name_a[path_image_a.length()] = '\0';

    char* image_file_a = image_name_a;
        image_a = cvLoadImage(image_file_a, 1);


     IplImage* image_b(0);
     char image_name_b[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

     for (int i(0); i < path_image_b.length(); i++)
        image_name_b[i] = path_image_b.toStdString()[i];
     image_name_b[path_image_b.length()] = '\0';

     char* image_file_b = image_name_b;
         image_b = cvLoadImage(image_file_b, 1);


     IplImage* image_c(0);
     char image_name_c[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

     for (int i(0); i < path_image_c.length(); i++)
        image_name_c[i] = path_image_c.toStdString()[i];
     image_name_c[path_image_c.length()] = '\0';

     char* image_file_c = image_name_c;
         image_c = cvLoadImage(image_file_c, 1);






/*
 *
    //Mat image_a;
    //Mat hsv_a;
   // image_a = imread(path_image.toStdString(), IMREAD_COLOR);
    //imshow("Hello Opencv", image_a);
    */

    // для хранения изображения
    IplImage *hsv_a(0), *hsv_b(0), *hsv_c(0);


    //сегменты
    int spatialRadius = 35;
    int colorRadius = 60;
    int pyramidLevels = 3;

    if(seg)
    {
        cvPyrMeanShiftFiltering(image_a, image_a, spatialRadius, colorRadius, pyramidLevels);
        cvPyrMeanShiftFiltering(image_b, image_b, spatialRadius, colorRadius, pyramidLevels);
        cvPyrMeanShiftFiltering(image_c, image_c, spatialRadius, colorRadius, pyramidLevels);
    }





    hsv_a = cvCreateImage(cvGetSize(image_a), IPL_DEPTH_8U, 3);
    hsv_b = cvCreateImage(cvGetSize(image_b), IPL_DEPTH_8U, 3);
    hsv_c = cvCreateImage(cvGetSize(image_c), IPL_DEPTH_8U, 3);





    // преобразуем изображение в HSV
    cvCvtColor(image_a, hsv_a, CV_BGR2HSV);
    cvCvtColor(image_b, hsv_b, CV_BGR2HSV);
    cvCvtColor(image_c, hsv_c, CV_BGR2HSV);


    QString fr;
    int pixel_y = hsv_a->height / stgs.gety_sectors();
    int pixel_x = hsv_a->width / stgs.getx_sectors();
    int *key_colors_count = new int[10];
    for (int i(0); i < 10; i++)
        key_colors_count[i] = 0;



    //if (stgs.otladka)
    //{
    //   cvSaveImage("segments_a.jpg", image_a);
     //  dst(image_a, hsv_a, stgs.y_sectors, stgs.x_sectors);
    // }

    //сектора
    for (int y_sector(0); y_sector < stgs.gety_sectors(); y_sector++)
    {
       for (int x_sector = 0; x_sector < stgs.getx_sectors(); x_sector++)
       {
           //создадим динамический массив, хранящий кол-во пикселей того или иного цвета в секторе
           int **color_id = new int*[3];
           for (int i = 0; i < 3; i++)
                color_id[i] = new int[10];
           //обнуление массива
           for (int i = 0; i < 3; i++)
           for (int j = 0; j < 10; j++)
                color_id[i][j] = 0;


                for (int y = y_sector * pixel_y; y < pixel_y + y_sector * pixel_y; y++)
                {
                    for (int x = x_sector * pixel_x; x < pixel_x + x_sector * pixel_x; x++)
                    {
                        // получение значения HSV у пикселя
                        uchar H_a = PIXEL_COLOR(uchar, hsv_a, x, y)[0];        // значение H
                        uchar S_a = PIXEL_COLOR(uchar, hsv_a, x, y)[1];        // значение S
                        uchar V_a = PIXEL_COLOR(uchar, hsv_a, x, y)[2];        // значение V

                        uchar H_b = PIXEL_COLOR(uchar, hsv_b, x, y)[0];
                        uchar S_b = PIXEL_COLOR(uchar, hsv_b, x, y)[1];
                        uchar V_b = PIXEL_COLOR(uchar, hsv_b, x, y)[2];

                        uchar H_c = PIXEL_COLOR(uchar, hsv_c, x, y)[0];
                        uchar S_c = PIXEL_COLOR(uchar, hsv_c, x, y)[1];
                        uchar V_c = PIXEL_COLOR(uchar, hsv_c, x, y)[2];

                        int index_color_a = getColor10(H_a, S_a, V_a);


                        color_id[0][index_color_a] = 1;
                        color_id[1][getColor10(H_b, S_b, V_b)] = 1;
                        color_id[2][getColor10(H_c, S_c, V_c)] = 1;

                        key_colors_count[index_color_a]++;

                    }
                }

                //frame_int[x_sector + x_sectors * y_sector] = most_color(color_id[0]) * 100 + most_color(color_id[1]) * 10 + most_color(color_id[2]);

                fr.append(most_color(color_id[0]));
                fr.append(" ");
                fr.append(most_color(color_id[1]));
                fr.append(" ");
                fr.append(most_color(color_id[2]));
                fr.append(" ");

                for (int i = 0; i < 3; i++)
                        delete[] color_id[i];
                delete[] color_id;
            }
        }

    QString fkey;
    fkey.append(create_key(key_colors_count, 10));
    fkey.append("_3");


    delete[] key_colors_count;

    // освобождаем ресурсы
    cvReleaseImage(&hsv_a);
    cvReleaseImage(&image_a);
    cvReleaseImage(&hsv_b);
    cvReleaseImage(&image_b);
    cvReleaseImage(&hsv_c);
    cvReleaseImage(&image_c);

    CreateFrame::setframe(fr);
    CreateFrame::setkey(fkey);

}

void CreateFrame::setkey(QString x)
{
    CreateFrame::key = x;
}
void CreateFrame::setframe(QString x)
{
    CreateFrame::frame = x;
}
QString CreateFrame::getkey()
{
    return CreateFrame::key;
}
QString CreateFrame::getframe()
{
    return CreateFrame::frame;
}
