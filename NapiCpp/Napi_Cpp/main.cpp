#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <ctime>


// получение пикселя изображения (по типу картинки и координатам)
#define PIXEL_COLOR(type,img,x,y) (((type*)((img)->imageData+(y)*(img)->widthStep))+(x)*(img)->nChannels)

uchar cCTHue[10] =    {0,       0,      0,     0,     20,      30,      60,    85,   120,    138  };
uchar cCTSat[10] =    {0,       0,      0,    255,   255,     255,     255,   255,   255,    255  };
uchar cCTVal[10] =    {0,      255,    120,   255,   255,     255,     255,   255,   255,    255  };

typedef unsigned int uint;

using namespace std;

struct im
{
	string frame;
	string key;
};

struct settings
{
	bool otladka;
	bool seg;
	int	kadrov;
	int	y_sectors; //количество секторов по оси Y 
	int	x_sectors; //количество секторов по оси X	
	string file_type;
	string name_frame_a;
	string name_frame_b;
	string name_frame_c;
	string path_library;
	string path_films;
};

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

//палитра из 5 цветов
int getColor5(int H, int S, int V)
{
	int color = 0;

	if (V < 75)
		color = 6; //черный
	else if (V > 190 && S < 27)
			color = 1; //белый
	else if (S < 53 && V < 185)
			color = 2; //серый
	else if (H < 7)
			color = 3; //красный
	else if (H < 25)
			color = 3; //оранжевый
	else if (H < 34)
			color = 3; //желтый
	else if (H < 73)
			color = 6; //зеленый
	else if (H < 102)
			color = 1; //голубой
	else if (H < 140)
			color = 1; //синий
	else if (H < 170)
			color = 9; //фиолетовый
	else    
		color = 3;   //красный
        
	return color;
}


int getColorMy(int H, int S, int V)
{
	
	
	if (H <= 18)
		return 0;
	else if (H <= 36)
		return 1;
	else if (H <= 54)
		return 2;
	else if (H <= 72)
		return 3;
	else if (H <= 90)
		return 4;
	else if (H <= 108)
		return 5;
	else if (H <= 126)
		return 6;
	else if (H <= 144)
		return 7;
	else if (H <= 162)
		return 8;

	return 9;
}

int sum_color(int x)
{
	switch (x)
	{
	//Если цвет пикселя чёрный, то +1 в элемент, хранящий кол-во пикселей чёрного цвета
	case 0:
		return 0;		
	//Если цвет пикселя белый, то +1 в элемент, хранящий кол-во пикселей белого цвета
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 3;
	case 4:
		return 4;
	case 5:
		return 5;
	case 6:
		return 6;
	case 7:
		return 7;
	case 8:
		return 8;
	case 9:
		return 9;
	}

	return 0;
}


template <typename T>
string toString(T val)
{
    ostringstream oss;
    oss<< val;
    return oss.str();
}

string most_color(int *x)
{
	int key(0);

	for (int i(0); i < 10; i++)	
		key += x[i] * pow(2, i);

	return  toString(key);
}

string create_key(int a[], int n)
{

	int colors[10];
	for (int i(0); i < 10; i++)
		colors[i] = i;

	for (int i(0); i < n - 1; i++)
		for (int j(0); j < n - i - 1; j++)
		{
			if(a[j] > a[j+1])
			{
				int temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;

				temp = colors[j];
				colors[j] = colors[j+1];
				colors[j+1] = temp;

			}
		}	

	string str = toString(pow(2, colors[9]) + pow(2, colors[8]) + pow(2, colors[7]));
	
	return str;
}


int compare_frame(string frame, string x, int lenght, string &temp_name)
{
	int sum(0);

	int x_frame(0);
	int x_x(0);

	for (int j(0); j < lenght; j++)
	{
		int frame_number(0);
		while(frame[x_frame] != ' ')
		{			
			frame_number = frame_number*10 + (frame[x_frame] - '0');
			x_frame++;
		}
		x_frame++;

		int x_number(0);
		while(x[x_x] != ' ')
		{			
			x_number = x_number*10 + (x[x_x] - '0');
			x_x++;
		}
		x_x++;

		if(frame_number == x_number)
			sum++;		

	}	

	temp_name = x.erase(0, x_x);		

	return sum;
}

string convert_time(int time, int quantity)
{
	
	int h, m, s, ms;
	
	ms = time % quantity;
	time /= quantity;

	s = time % quantity;
	time /= quantity;

	m = time % quantity;
	time /= quantity;

	h = time % quantity;
	time /= quantity;

	string str;

	str.append(toString(h));
	str.append(":");
	str.append(toString(m));
	str.append(":");
	str.append(toString(s));
	str.append(":");
	str.append(toString(ms));

	return str;

}

void show_res(int max_rang, int lenght, string name, bool pr, settings stgs)
{		
	
	int h(0), time(0), quantity(0);
	while(name[h] != ' ')
	{
		time = time * 10 + name[h] - '0';
		h++;

	}
	name.erase(0, h+1);

	h = 0;
	while(name[h] != ' ')
	{
		quantity = quantity * 10 + name[h] - '0';
		h++;

	}
	name.erase(0, h+1);

	if(pr)
		cout << max_rang * 100 / lenght << "%"  << endl;

	cout << "Время кадра: " << convert_time(time, quantity) << ". Кадр: " << time << endl << endl;	
	
		
	string film_path = stgs.path_films;
	film_path.append("\\");
	film_path.append(name);
	film_path.append(".txt");

	ifstream fin_des(film_path);
	if(!fin_des)
	{
		cout << name << endl;
		cout << "Описание отсутствует." << endl;
	}
	else
	{
		string des;
		getline(fin_des, des);					

		while(des != ".")
		{
			cout << des << endl;
			getline(fin_des, des);

		}

		fin_des.close();
	}

}

void scan_library(string key, string frame, int lenght, int kadrov, settings stgs)
{
	ifstream fin(key);

	if(!fin)
	{
		cout << "Фильм не найден" << endl;
	} 
	else
	{
		int max_rang(0);
		string name, temp_name;

		while(1)
		{
			string x;
			getline(fin, x);
			if(x.empty())
			{
				
				if (max_rang >= 100*kadrov)
				{
					//если обнаружился					
					system("cls");
					show_res(max_rang, lenght*kadrov, name, true, stgs);
				} 
				else 				
					cout << "Фильм не найден" << endl;
				
				break;
			}


			int rang = compare_frame(frame, x, lenght*kadrov, temp_name);				

			if (rang >= 135*kadrov)
			{
				//если обнаружился
				name = temp_name;
				system("cls");
				show_res(rang, lenght*kadrov, name, false, stgs);
				break;
			}
			else if (rang > max_rang)
			{
				max_rang = rang;
				name = temp_name;
				
			}
		}		

	}
	
	fin.close();
}

int count_color(int *x)
{
	int max_pixels(0);
	int max_id;

	//данный цикл находит наибольшее значение элемента массива c_Id и номер этого элемента
	for (int j(0); j < 10; j++) 
	{					
		if (max_pixels <= x[j])//при равенстве значение присваивается того цвета, чей индекс больше
		{
			max_pixels = x[j]; // наибольшее значение
			max_id = j; //номер наибольшего значения элемента
		}
	}	

	return max_id;
}


//создание универсального dst для демонстрации
void dst(IplImage* image_a, IplImage* hsv_a, int y_sectors, int x_sectors)
{

	int pixel_y = hsv_a->height / y_sectors;
	int pixel_x = hsv_a->width / x_sectors;

	IplImage *dst(0);
	dst = cvCreateImage( cvGetSize(image_a), IPL_DEPTH_8U, 3 );

		


		//преобразование
		for (int y(0); y < hsv_a->height; y++) 
		{
              for (int x(0); x < hsv_a->width; x++)
			  {                      
                 uchar H = PIXEL_COLOR(uchar, hsv_a, x, y)[0];       
                 uchar S = PIXEL_COLOR(uchar, hsv_a, x, y)[1];     
                 uchar V = PIXEL_COLOR(uchar, hsv_a, x, y)[2]; 				 
				 				 			 

                 PIXEL_COLOR(uchar, dst, x, y)[0] = cCTHue[getColor10(H, S, V)];  
                 PIXEL_COLOR(uchar, dst, x, y)[1] = cCTSat[getColor10(H, S, V)]; 
                 PIXEL_COLOR(uchar, dst, x, y)[2] = cCTVal[getColor10(H, S, V)];
				
              }			  
		}

		cvCvtColor( dst, dst, CV_HSV2BGR );
		cvSaveImage("a_colors10.jpg", dst);



		//сектора
		for (int y_sector(0); y_sector < y_sectors; y_sector++) 
		{
			for (int x_sector = 0; x_sector < x_sectors; x_sector++) 
			{
				//создадим динамический массив, хранящий кол-во пикселей того или иного цвета в секторе
				int *color_id = new int[10];//10 основных цветов
				//обнуление массива
				for (int i = 0; i < 10; i++)
					color_id[i] = 0;


				for (int y = y_sector * pixel_y; y < pixel_y + y_sector * pixel_y; y++) 
				{
					for (int x = x_sector * pixel_x; x < pixel_x + x_sector * pixel_x; x++)
					{
					
						// получение значения HSV у пикселя
						uchar H = PIXEL_COLOR(uchar, hsv_a, x, y)[0];        // значение H
						uchar S = PIXEL_COLOR(uchar, hsv_a, x, y)[1];        // значение S
						uchar V = PIXEL_COLOR(uchar, hsv_a, x, y)[2];        // значение V 

						color_id[sum_color(getColor10(H, S, V))]++;

					}
				}

				int max_id = count_color(color_id);	

				for (int y = y_sector * pixel_y; y < pixel_y + y_sector * pixel_y; y++) 
				{
					for (int x = x_sector * pixel_x; x < pixel_x + x_sector * pixel_x; x++)
					{
						PIXEL_COLOR(uchar, dst, x, y)[0] = cCTHue[max_id];  
						PIXEL_COLOR(uchar, dst, x, y)[1] = cCTSat[max_id]; 
						PIXEL_COLOR(uchar, dst, x, y)[2] = cCTVal[max_id];

					}
				}					

				delete[] color_id;
			}			
		}
		 
		cvCvtColor( dst, dst, CV_HSV2BGR );
		cvSaveImage("a_sectors.jpg", dst);
		cvReleaseImage(&dst);


}
//кодирует последовательность 3 кадров
im create_frame_3(int argc, char* argv[], IplImage* image_a, IplImage* image_b, IplImage* image_c, settings stgs)
{
	// для хранения изображения
	  IplImage *hsv_a(0), *hsv_b(0), *hsv_c(0);
	 // загрузка изображения 
     

		//сегменты
				
		int spatialRadius = 35;
		int colorRadius = 60;
		int pyramidLevels = 3;

		if (stgs.seg)
		{
			cvPyrMeanShiftFiltering(image_a, image_a, spatialRadius, colorRadius, pyramidLevels);
			cvPyrMeanShiftFiltering(image_b, image_b, spatialRadius, colorRadius, pyramidLevels);
			cvPyrMeanShiftFiltering(image_c, image_c, spatialRadius, colorRadius, pyramidLevels);

		}
		

		

        hsv_a = cvCreateImage( cvGetSize(image_a), IPL_DEPTH_8U, 3 );
		hsv_b = cvCreateImage( cvGetSize(image_b), IPL_DEPTH_8U, 3 );
		hsv_c = cvCreateImage( cvGetSize(image_c), IPL_DEPTH_8U, 3 );

		 // преобразуем изображение в HSV  
        cvCvtColor( image_a, hsv_a, CV_BGR2HSV );
		cvCvtColor( image_b, hsv_b, CV_BGR2HSV );	
		cvCvtColor( image_c, hsv_c, CV_BGR2HSV );

		im fr;			
		int pixel_y = hsv_a->height / stgs.y_sectors;
		int pixel_x = hsv_a->width / stgs.x_sectors;
		int *key_colors_count = new int[10];		
		for (int i(0); i < 10; i++)
			key_colors_count[i] = 0;	
		

		


		if (stgs.otladka)
		{
			cvSaveImage("segments_a.jpg", image_a);
			cvSaveImage("segments_b.jpg", image_b);
			cvSaveImage("segments_c.jpg", image_c);

			dst(image_a, hsv_a, stgs.y_sectors, stgs.x_sectors);

		}				

		//сектора
		for (int y_sector(0); y_sector < stgs.y_sectors; y_sector++) 
		{
			for (int x_sector = 0; x_sector < stgs.x_sectors; x_sector++) 
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
				fr.frame.append(most_color(color_id[0]));
				fr.frame.append(" ");
				fr.frame.append(most_color(color_id[1]));
				fr.frame.append(" ");
				fr.frame.append(most_color(color_id[2]));
				fr.frame.append(" ");	

				for (int i = 0; i < 3; i++) 
					delete [] color_id[i];
				delete [] color_id;
			}			
		}		

		fr.key = stgs.path_library;
		fr.key.append("\\");
		fr.key.append(create_key(key_colors_count, 10));	
		fr.key.append("_3.txt");	
		
		

		delete [] key_colors_count;


	// освобождаем ресурсы
	cvReleaseImage(&hsv_a);	
	cvReleaseImage(&hsv_b);
	cvReleaseImage(&hsv_c);	

	return fr;

}
//кодирует 1 кадр
im create_frame(int argc, char* argv[], IplImage* image_a, settings stgs)
{
	// для хранения изображения
	  IplImage *hsv_a(0);

		//сегменты
				
		int spatialRadius = 35;
		int colorRadius = 60;
		int pyramidLevels = 3;

		if (stgs.seg)
			cvPyrMeanShiftFiltering(image_a, image_a, spatialRadius, colorRadius, pyramidLevels);		

        hsv_a = cvCreateImage( cvGetSize(image_a), IPL_DEPTH_8U, 3 );

		 // преобразуем изображение в HSV  
        cvCvtColor( image_a, hsv_a, CV_BGR2HSV );

		im fr;			
		int pixel_y = hsv_a->height / stgs.y_sectors;
		int pixel_x = hsv_a->width / stgs.x_sectors;
		int *key_colors_count = new int[10];		
		for (int i(0); i < 10; i++)
			key_colors_count[i] = 0;	
		

		


		if (stgs.otladka)
		{
			cvSaveImage("segments_a.jpg", image_a);
			dst(image_a, hsv_a, stgs.y_sectors, stgs.x_sectors);
		}

		

		//сектора
		for (int y_sector(0); y_sector < stgs.y_sectors; y_sector++) 
		{
			for (int x_sector = 0; x_sector < stgs.x_sectors; x_sector++) 
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
				fr.frame.append(most_color(color_id));
				fr.frame.append(" ");	
				
				delete [] color_id;
			}			
		}		

		
		fr.key = stgs.path_library;
		fr.key.append("\\");
		fr.key.append(create_key(key_colors_count, 10));
		fr.key.append("_1.txt");	
		

		delete [] key_colors_count;


	// освобождаем ресурсы	
	cvReleaseImage(&hsv_a);	

	return fr;

}

void scan_frame(int argc, char* argv[], settings stgs)
{
	stgs.name_frame_a.append(stgs.file_type);
	IplImage* image_a(0);
    char image_name_a[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	  for (int i(0); i < stgs.name_frame_a.size(); i++)	  
		  image_name_a[i] = stgs.name_frame_a[i];
	image_name_a[stgs.name_frame_a.size()] = '\0';



      
    char* image_file_a = argc >= 2 ? argv[1] : image_name_a;	       
    image_a = cvLoadImage(image_file_a, 1);
    if(!image_a)
	{
		cout << "Error. Can't find an image" << endl;                
        system("pause");			
    }

	im frame;

	if(stgs.kadrov == 3)
	{
		stgs.name_frame_b.append(stgs.file_type);
		stgs.name_frame_c.append(stgs.file_type);
		IplImage* image_b(0), *image_c(0);
		char image_name_b[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
		char image_name_c[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
		for (int i(0); i < stgs.name_frame_b.size(); i++)	  
			image_name_b[i] = stgs.name_frame_b[i];
		for (int i(0); i < stgs.name_frame_c.size(); i++)	  
			image_name_c[i] = stgs.name_frame_c[i];
		image_name_b[stgs.name_frame_b.size()] = '\0';
		image_name_c[stgs.name_frame_c.size()] = '\0';


		char* image_file_b = argc >= 2 ? argv[1] : image_name_b;
		char* image_file_c = argc >= 2 ? argv[1] : image_name_c;
		image_b = cvLoadImage(image_file_b, 1);
		image_c = cvLoadImage(image_file_c, 1);

		frame = create_frame_3(argc, argv, image_a, image_b, image_c, stgs);
		cvReleaseImage(&image_a);
		cvReleaseImage(&image_b);	
		cvReleaseImage(&image_c);	

	}
	else
	{
		frame = create_frame(argc, argv, image_a, stgs);
		cvReleaseImage(&image_a);	
	}

	
	if(stgs.otladka)
	{
		ofstream fout("frame.txt");			
		fout << frame.frame << endl << frame.key << endl;	
		fout.close();

	}	
	
	scan_library(frame.key, frame.frame, stgs.y_sectors*stgs.x_sectors, stgs.kadrov, stgs);
}

void add_library(int argc, char* argv[], string name_file, string name, int number, int size, int quantity, settings stgs)
{
		
	  IplImage* image_a(0);
      char image_name_a[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

	  for (int i(0); i < size; i++)	  
		  image_name_a[i] = name_file[i];	  
	  
	image_name_a[size] = '\0';

		  
		char* image_file_a = argc >= 2 ? argv[1] : image_name_a;		  
      image_a = cvLoadImage(image_file_a, 1);
      if(!image_a)
		{
			cout << "Error. Can't find an image" << endl;                
            system("pause");			
        }

	im frame = create_frame(argc, argv, image_a, stgs);
	cvReleaseImage(&image_a);


	ofstream fout(frame.key, std::ios_base::in | std::ios_base::app);				
	fout << frame.frame << number << " " << quantity << " " << name << endl;	
	fout.close();

}

void add_library_3(int argc, char* argv[], string name_file, string name, int number, int size, int quantity, string name_file_2, string name_file_3, settings stgs)	
{
		
	  IplImage* image_a(0), * image_b(0), * image_c(0);
      char image_name_a[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	  char image_name_b[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
	  char image_name_c[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";

	  for (int i(0); i < size; i++)	
	  {
		  image_name_a[i] = name_file[i];
		  image_name_b[i] = name_file_2[i];	
		  image_name_c[i] = name_file_3[i];	
	  }
		    
	  
	image_name_a[size] = '\0';
	image_name_b[size] = '\0';
	image_name_c[size] = '\0';

		  
		char* image_file_a = argc >= 2 ? argv[1] : image_name_a;	
		char* image_file_b = argc >= 2 ? argv[1] : image_name_b;	
		char* image_file_c = argc >= 2 ? argv[1] : image_name_c;	
      image_a = cvLoadImage(image_file_a, 1);
	  image_b = cvLoadImage(image_file_b, 1);
	  image_c = cvLoadImage(image_file_c, 1);
      if( (!image_a) || (!image_b) ||(!image_c))
		{
			cout << "Error. Can't find an image" << endl;                
            system("pause");			
        }

	im frame = create_frame_3(argc, argv, image_a, image_b, image_c, stgs);
	cvReleaseImage(&image_a);
	cvReleaseImage(&image_b);
	cvReleaseImage(&image_c);


	ofstream fout(frame.key, std::ios_base::in | std::ios_base::app);				
	fout << frame.frame << number << " " << quantity << " " << name << endl;	
	fout.close();

}

void add_to_library(int argc, char* argv[], settings stgs)
{
	string name, a, directory;
	int first, last, lenght, quantity;

	cout << "Введите название фильма: " << endl;	
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	
	getline(cin, name);	

	cout << "Введите путь к кадрам фильма: " << endl;	
	getline(cin, directory);

	cout << "[имя]_[номер]: " << endl;
	cout << "Введите имя кадров: " << endl;		
	getline(cin, a);
	cout << "Введите номер первого кадра: " << endl;
	cin >> first;
	cout << "Введите номер последнего кадра: " << endl;
	cin >> last;
	cout << "Введите длину названия: " << endl;
	cin >> lenght;

	cout << "Введите количество кадров в секунду: " << endl;
	cin >> quantity;
	system("cls");

	unsigned long long  t1, t2;

	if (stgs.kadrov == 3)
	{
		
		t1 = clock();
	
		for (int i(first); i <= last-2; i++)
		{
			system("cls");
			cout << (i * 100) / (last-2) << "%" <<endl;
			string name_file;
			name_file.append(directory);		
			name_file.append("\\");
			name_file.append(a);
			name_file.append("_");
			string name_file_2 = name_file;
			string name_file_3 = name_file;

			for(int j(lenght-1); j >= 0; j--)
			{
				int k = i / pow(10, j);
				k = k % 10;
				name_file.append(toString(k));

				k = (i+1) / pow(10, j);
				k = k % 10;
				name_file_2.append(toString(k));

				k = (i+2) / pow(10, j);
				k = k % 10;
				name_file_3.append(toString(k));
			}
			name_file.append(stgs.file_type);			
			name_file_2.append(stgs.file_type);
			name_file_3.append(stgs.file_type);


			add_library_3(argc, argv, name_file, name, i, name_file.size(), quantity, name_file_2, name_file_3, stgs);
			
		}

		t2 = clock();
	}
	else
	{
		t1= clock();
	
		for (int i(first); i <= last; i++)
		{
			system("cls");
			cout << (i * 100) / (last-2) << "%" <<endl;
			string name_file;
			name_file.append(directory);		
			name_file.append("\\");
			name_file.append(a);
			name_file.append("_");

			for(int j(lenght-1); j >= 0; j--)
			{
				int k = i / pow(10, j);
				k = k % 10;
				name_file.append(toString(k));
			}
			name_file.append(stgs.file_type);
			add_library(argc, argv, name_file, name, i, name_file.size(), quantity, stgs);
			
		}

		t2 = clock();
	}
	

	system("cls");
	cout << "Добавлено" << endl;
	cout << endl;
	cout << "Время добавления: " << (t2-t1)/1000.0 << endl;	
	
}

void load_settings(settings &stg)
{
	ifstream fin("settings.txt");

	if(fin)
	{
		fin >> stg.otladka;
		fin >> stg.seg;
		fin >> stg.kadrov;
		fin >> stg.y_sectors;
		fin >> stg.x_sectors;
		fin >> stg.file_type;
		fin >> stg.name_frame_a;
		fin >> stg.name_frame_b;
		fin >> stg.name_frame_c;
		fin >> stg.path_library;
		fin >> stg.path_films;
	}

	fin.close();
}

void save_settings(settings stgs)
{
	ofstream fout("settings.txt");
	
	fout << stgs.otladka << endl;
	fout << stgs.seg << endl;
	fout << stgs.kadrov << endl;
	fout << stgs.y_sectors << endl;
	fout << stgs.x_sectors << endl;
	fout << stgs.file_type << endl;
	fout << stgs.name_frame_a << endl;
	fout << stgs.name_frame_b << endl;
	fout << stgs.name_frame_c << endl;
	fout << stgs.path_library << endl;
	fout << stgs.path_films << endl;

	fout.close();
}
void edit_settings(settings &stgs)
{
	cout << "(1) otladka = " << stgs.otladka << endl;
	cout << "(2) seg = " << stgs.seg << endl;
	cout << "(3) kadrov = " << stgs.kadrov << endl;
	cout << "(4) y_sectors = " << stgs.y_sectors << endl;
	cout << "(5) x_sectors = " << stgs.x_sectors << endl;
	cout << "(6) file_type = " << stgs.file_type << endl;
	cout << "(7) name_frame_a = " << stgs.name_frame_a << endl;
	cout << "(8) name_frame_b = " << stgs.name_frame_b << endl;
	cout << "(9) name_frame_c = " << stgs.name_frame_c << endl;
	cout << "(10) path_library = " << stgs.path_library << endl;
	cout << "(11) path_films = " << stgs.path_films << endl;
	cout << "(12) выход"<< endl << endl;
	
	int keyboard;
	int key;
	string ke;
	cin >> keyboard;	

	switch(keyboard)
	{
	case 1:
		cin >> key;
		stgs.otladka = key;
		break;
	case 2:
		cin >> key;
		stgs.seg = key;
		break;
	case 3:
		cin >> key;
		stgs.kadrov = key;
		break;
	case 4:
		cin >> key;
		stgs.y_sectors = key;
		break;
	case 5:
		cin >> key;
		stgs.x_sectors = key;
		break;
	case 6:
		cin >> ke;
		stgs.file_type = ke;
		break;
	case 7:
		cin >> ke;
		stgs.name_frame_a = ke;
		break;
	case 8:
		cin >> ke;
		stgs.name_frame_b = ke;
		break;
	case 9:
		cin >> ke;
		stgs.name_frame_c = ke;
		break;
	case 10:
		cin >> ke;
		stgs.path_library = ke;
		break;
	case 11:
		cin >> ke;
		stgs.path_films = ke;
		break;
	default:
		break;

	}

	save_settings(stgs);

	system("cls");

}
void default_settings(settings &stgs)
{
	stgs.otladka = false;
	stgs.seg = false;
	stgs.kadrov = 1;
	stgs.y_sectors = 9; //количество секторов по оси Y 
	stgs.x_sectors = 16; //количество секторов по оси X	
	stgs.file_type = ".jpeg";
	stgs.name_frame_a = "a";
	stgs.name_frame_b = "b";
	stgs.name_frame_c = "c";
	stgs.path_library = "";
	stgs.path_films = "";
}
int main(int argc, char* argv[])
{
	setlocale(LC_CTYPE, "Russian");

	settings stgs;
	default_settings(stgs);
	load_settings(stgs);
		

	while(1)
	{
		cout << "1 - сканировать, 2 - добавить в библиотеку, 3 - изменить настройки, 4 - выйти" << endl;
		char keyboard;		
		cin >> keyboard;
		cout << endl;		

		switch (keyboard)
		{
		case '1':
			system("cls");	
			unsigned long long t1, t2;
			t1 = clock();
			scan_frame(argc, argv, stgs);
			t2 = clock();
			cout << endl;
			cout << "Время сканирования: " << (t2-t1)/10000.0 << endl;
			break;
		case '2':
			system("cls");			
			add_to_library(argc, argv, stgs);			
			break;	
		case '3':
			system("cls");			
			edit_settings(stgs);		
			break;	
		case '4':
			system("cls");	
			system("pause");			
			return 0;
			break;
		default:
			system("cls");
			break;
		}

	}	
	

	system("pause");
	return 0;
}


