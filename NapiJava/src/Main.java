import org.opencv.core.*;
import org.opencv.core.Point;
import org.opencv.imgcodecs.Imgcodecs;
import org.opencv.imgproc.Imgproc;
import org.opencv.objdetect.CascadeClassifier;

import javax.swing.*;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.awt.image.DataBufferByte;
import javax.swing.JFrame;
import javax.swing.SwingUtilities;
import javax.swing.border.Border;






public class Main extends JFrame{
	public static String a_result;
	
	 public Main() {
	       setTitle("Napi");
	       setSize(300, 200);
	       setLocationRelativeTo(null);
	       setDefaultCloseOperation(EXIT_ON_CLOSE);	       
	       
	       
	      
	       JTextArea textArea = new JTextArea(5, 50);
	       textArea.setLineWrap(true);
	       textArea.setWrapStyleWord(true);	       
	       textArea.append(a_result);
	       getContentPane().add(textArea);
	       pack();
	      

	       
	    }

    // Compulsory
    static{ System.loadLibrary(Core.NATIVE_LIBRARY_NAME); }


    public static void main(String[] args) {
    	
    		

        //���� ������������ ������ 90 ��������, ����� ����� ����������, ��� ������ ����������� ����, � �������� ���������� ������
        int const_pogreshnost = 90;
        int const_a = 6; //���������� �������� � ���� ������



        //colors
        int a0[] = { 0, 0, 2, 2, 3, 3, 3, 3, 4, 7, 7, 1, 3, 3, 5, 5, 0, 0, 2, 2, 3, 3, 3, 3, 4, 7, 7, 1, 3, 3, 5, 5, 2, 2, 2, 2, 3, 3, 3, 3, 4, 9, 9, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 9, 9, 6, 6, 6, 6, 6, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 6, 6, 6, 6, 6, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 6, 8, 8, 8, 8, 3, 3, 3, 3, 3, 3, 3, 3, 4, 0, 0, 6, 8, 8, 8, 8, 3, 3, 3, 3, 3, 3, 3, 3, 4, 1, 1, 6, 8, 8, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 6, 8, 8, 1, 1 };
        String a0_d = "It's colors. This photo is about sectors";
        //nature
        int a1[] = { 0, 0, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 7, 7, 8, 8, 8, 4, 4, 7, 7, 7, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 2, 0, 0, 0, 7, 0, 7, 7, 0, 0, 0, 0, 0, 0, 7, 7, 7, 7, 8, 7, 7, 7, 8, 8, 0, 0, 0, 0, 0, 7, 8, 7, 7, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0 };
        String a1_d = "�������";
        //beatles
        int a2[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4, 0, 0, 0, 0, 3, 0, 0, 0, 0, 8, 8, 8, 0, 8, 4, 4, 4, 4, 5, 4, 3, 3, 9, 0, 0, 8, 8, 8, 8, 8, 3, 3, 3, 0, 0, 3, 3, 3, 0, 0, 0, 8, 0, 0, 8, 8, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        String a2_d = "It's The Beatles. Very popular band";
        //el_capitan
        int a3[] = { 8, 8, 8, 8, 1, 1, 1, 1, 1, 1, 1, 1, 8, 1, 1, 8, 3, 3, 3, 3, 4, 3, 8, 8, 8, 8, 1, 1, 1, 1, 1, 8, 0, 3, 3, 4, 4, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 0, 3, 3, 3, 8, 8, 8, 8, 8, 1, 8, 8, 8, 8, 0, 0, 0, 8, 0, 3, 8, 8, 8, 8, 8, 8, 4, 3, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 8, 3, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 8, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        String a3_d = "����";
        //interstellar
        int a4[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 4, 4, 7, 7, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 7, 7, 4, 0, 0, 7, 7, 0, 7, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 7, 7, 7, 0, 0, 0, 0, 0, 7, 7, 7, 0, 0, 0, 0, 0, 7, 7, 2, 0, 0, 0, 0, 0, 1, 7, 7, 7, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        String a4_d = "������������. 1:24:55\n\n��� - 2014\n������ - ���, ��������������\n�������� - ��������� �����\n�������� - �������� �����, ��������� �����\n\n����� ������ �������� ������������ � ������������������ �������, ��������� �������������� � ������ \n������������ ������ �����������(������� ���������������� ��������� ������� ������������ - ������� �����\n������� ����������) � �����������, ����� ��������� ������� ����������� ��� ����������� �����������\n�������� � ���������� ������������ �� ������ �������.";
        //Avatar
        int a5[] = { 1, 1, 1, 1, 7, 1, 1, 1, 0, 0, 8, 8, 0, 1, 1, 2, 1, 1, 1, 2, 0, 7, 7, 7, 1, 8, 8, 8, 0, 1, 2, 2, 1, 1, 2, 0, 0, 8, 7, 7, 0, 2, 0, 0, 0, 2, 2, 2, 1, 1, 2, 7, 8, 8, 7, 8, 8, 7, 8, 8, 0, 2, 2, 8, 1, 1, 0, 0, 8, 8, 8, 7, 7, 7, 8, 0, 0, 0, 2, 8, 1, 1, 0, 0, 0, 8, 0, 0, 8, 8, 8, 0, 0, 0, 8, 8, 1, 1, 0, 0, 0, 0, 0, 0, 8, 8, 7, 0, 0, 0, 8, 8, 1, 1, 0, 0, 0, 8, 0, 8, 8, 8, 8, 0, 0, 8, 8, 0, 1, 1, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 8};
        String a5_d = "������. 1:07:54\n\n��� - 2009\n������ - ���, ��������������\n�������� - ������ �������\n�������� - ������ �������\n\n����� ����� � ������ ������� ���������, ����������� � ����������� ������.\n�������� �� �������� ����, ����� � ���� ��-�������� �������� ������. ��\n�������� ������� ��������� ����������� � ��������� �������� ��� � ����\n������ �� ������� �������, ��� ���������� �������� ������ �������, �������\n�������� �������� ��� ������ ����� �� ��������������� �������.";


        Mat img = Imgcodecs.imread("a.jpg");

        Imgproc.cvtColor(img, img, Imgproc.COLOR_BGR2HSV);



        //Imgcodecs.imwrite("out.jpg",img);



        int array_picture[] = new int[144];

	int a_index[] = new int[const_a];

        //�������� ������������ ������, �������� ���-�� �������� ���� ��� ����� �����
	int color_id[] = new int[10];//10 �������� ������

        //��������� �������
        for (int i = 0; i < 10; i++)
            color_id[i] = 0;

        //���������� ��� ���������� ������������� �������� �������� � ������� � ������ ����� ��������
        int max_pixels = 0;
        int max_id=-1;


        //���� �������� �� ������� arraySectors, ���������� ��������.
        //� ���� ������ ������������ �������� ���� �������, ���� �������� ���������� � ���������� �������



       /* for (int y_sector = 0; y_sector < 9; y_sector++) {
            for (int x_sector = 0; x_sector < 16; x_sector++) {

                for (int y = y_sector * 120; y < 120 + y_sector * 120; y++) {
                    for (int x = x_sector * 120; x < 120 + x_sector * 120; x++) {


                        int h = (int)img.get(x, y)[0];
                        int s = (int)img.get(x, y)[1];
                        int  v = (int)img.get(x, y)[2];

                    }
                }
            }
        }*/





       /* for (int a=0; a<1080; a++){
            for(int b=0; b<1920; b++){

               // arrayPixels[a][b]= (int)img.get(a, b)[1];


                //arrayPixels[a][b] = getColor(h,s,v);
                arrayPixels[a][b] = getColor((int)img.get(a, b)[0],(int)img.get(a, b)[1],(int)img.get(a, b)[2]);

            }
        }*/

        for (int y_sector = 0; y_sector < 9; y_sector++) {
            for (int x_sector = 0; x_sector < 16; x_sector++) {

                for (int y = y_sector * 120; y < 120 + y_sector * 120; y++) {
                    for (int x = x_sector * 120; x <120 + x_sector * 120; x++) {





                        //� ����������� �� �������� ������� ������������ +1 ���� �������� ������� c_id,
                        //����� ��������  ����� ������� ����� �����
                        //switch (ctype)
                        switch (getColor((int)img.get(y, x)[0],(int)img.get(y, x)[1],(int)img.get(y, x)[2]))
                        {
                            //���� ���� ������� ������, �� +1 � �������, �������� ���-�� �������� ������� �����
                            case 0:
                                color_id[0]++;
                                break;
                            //���� ���� ������� �����, �� +1 � �������, �������� ���-�� �������� ������ �����
                            case 1:
                                color_id[1]++;
                                break;
                            // -//-
                            case 2:
                                color_id[2]++;
                                break;
                            case 3:
                                color_id[3]++;
                                break;
                            case 4:
                                color_id[4]++;
                                break;
                            case 5:
                                color_id[5]++;
                                break;
                            case 6:
                                color_id[6]++;
                                break;
                            case 7:
                                color_id[7]++;
                                break;
                            case 8:
                                color_id[8]++;
                                break;
                            case 9:
                                color_id[9]++;
                                break;
                        }


                    }
                }

                //������ ���� ������� ���������� �������� �������� ������� c_Id � ����� ����� ��������
                for (int j = 0; j < 10; j++) {
                    if (max_pixels <= color_id[j])//��� ��������� �������� ������������� ���� �����, ��� ������ ������
                    {
                        max_pixels = color_id[j]; // ���������� ��������
                        max_id = j; //����� ����������� �������� ��������
                    }
                }

                //������ ������������� ����� max_i ������������� �������,
                //�.�. � ������ arrayP ������������, ����� ���� ����������� � ���������� �������
                //arraySectors[y_sector][x_sector] = max_id;
                array_picture[x_sector + 16 * y_sector] = max_id;



                //��������� ������� � ��������� ��� ������������ ���������� �������

                for (int i = 0; i < 10; i++)
                    color_id[i] = 0;

                max_pixels = 0;

            }
        }

        for (int pixel = 0; pixel < 144; pixel++) {
            if (array_picture[pixel] == a0[pixel]) {
                a_index[0]++;
            }
            if (array_picture[pixel] == a1[pixel]) {
                a_index[1]++;
            }
            if (array_picture[pixel] == a2[pixel]) {
                a_index[2]++;
            }
            if (array_picture[pixel] == a3[pixel]) {
                a_index[3]++;
            }
            if (array_picture[pixel] == a4[pixel]) {
                a_index[4]++;
            }
            if (array_picture[pixel] == a5[pixel]) {
                a_index[5]++;
            }

        }

        int max_index = 0; // ���������� �������
        int index_picture= -1; //����� ������� � ���������� ���������

        for (int index = 0; index < const_a; index++) {
            if ((max_index < a_index[index]) /*&& (a_index[index]>const_pogreshnost)*/) {
                max_index = a_index[index];
                index_picture = index;
            }
        }

        if (max_index > const_pogreshnost) {

            switch (index_picture)
            {
                case 0:
                	a_result = a0_d;
                    System.out.println(a0_d);
                    break;
                case 1:
                	a_result = a1_d;
                    System.out.println(a1_d);
                    break;
                case 2:
                	a_result = a2_d;
                    System.out.println(a2_d);
                    break;
                case 3:
                	a_result = a3_d;
                    System.out.println(a3_d);
                    break;
                case 4:
                	a_result = a4_d;
                    System.out.println(a4_d);
                    break;
                case 5:
                	a_result = a5_d;
                    System.out.println(a5_d);
                    break;

            }

        }
        else {
        	a_result = "����� �� ������";
            System.out.println("����� �� ������");
        }
        
        Main ex = new Main();
        ex.setVisible(true);    






       /* for (int a=0; a<1080; a++){
            for(int b=0; b<1920; b++) {
                System.out.print(arrayPixels[a][b] + " ");
            }
            System.out.println();
        }*/







        //displayImage(Mat2BufferedImage(img));




        /*System.loadLibrary(Core.NATIVE_LIBRARY_NAME);
        new DetectFaceDemo().run();*/


        /*System.out.println("Welcome to OpenCV " + Core.VERSION);
        Mat m = new Mat(5, 10, CvType.CV_8UC1, new Scalar(0));
        System.out.println("OpenCV Mat: " + m);
        Mat mr1 = m.row(1);
        mr1.setTo(new Scalar(1));
        Mat mc5 = m.col(5);
        mc5.setTo(new Scalar(5));
        System.out.println("OpenCV Mat data:\n" + m.dump());*/



    }




    static int getColor(int H, int S, int V) //� ������� ���������� ������ �� ���������� �������� H, S, V
    {
        int colorP = 0; //����������, ������������ �������� ���� (�� ��������� ������)

        // �������. � ����������� �� �������� �������� H, S, � V ����� �������� ������� ����

        if (V < 75)
            colorP = 0;
        else if (V > 190 && S < 27)
            colorP = 1;
        else if (S < 53 && V < 185)
            colorP = 2;
        else

        {
            if (H < 7)
                colorP = 3;
            else if (H < 25)
                colorP = 4;
            else if (H < 34)
                colorP = 5;
            else if (H < 73)
                colorP = 6;
            else if (H < 102)
                colorP = 7;
            else if (H < 140)
                colorP = 8;
            else if (H < 170)
                colorP = 9;
            else
                colorP = 3;
        }
        return colorP;
    }

    /*public static BufferedImage Mat2BufferedImage(Mat m){


        int type = BufferedImage.TYPE_BYTE_GRAY;
        if ( m.channels() > 1 ) {
            type = BufferedImage.TYPE_3BYTE_BGR;
        }
        int bufferSize = m.channels()*m.cols()*m.rows();
        byte [] b = new byte[bufferSize];
        m.get(0,0,b); // get all the pixels
        BufferedImage image = new BufferedImage(m.cols(),m.rows(), type);
        final byte[] targetPixels = ((DataBufferByte) image.getRaster().getDataBuffer()).getData();
        System.arraycopy(b, 0, targetPixels, 0, b.length);
        return image;

    }*/

    /*public static void displayImage(Image img2)
    {
        //BufferedImage img=ImageIO.read(new File("/HelloOpenCV/lena.png"));
        ImageIcon icon=new ImageIcon(img2);
        JFrame frame=new JFrame();
        frame.setLayout(new FlowLayout());
        frame.setSize(img2.getWidth(null)+50, img2.getHeight(null)+50);
        JLabel lbl=new JLabel();
        lbl.setIcon(icon);
        frame.add(lbl);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

    }*/


}