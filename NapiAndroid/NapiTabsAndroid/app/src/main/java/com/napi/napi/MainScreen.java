package com.napi.napi;

/**
 * Created by SRoma on 08.10.2016.
 */

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.graphics.Matrix;
import android.graphics.RectF;
import android.hardware.Camera;
import android.hardware.Camera.Size;
import android.net.Uri;
import android.os.Bundle;
import android.view.Display;
import android.view.Surface;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.ViewGroup.LayoutParams;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.TextView;

import com.google.android.gms.appindexing.Action;
import com.google.android.gms.appindexing.AppIndex;
import com.google.android.gms.appindexing.Thing;
import com.google.android.gms.common.api.GoogleApiClient;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

import static android.support.v7.appcompat.R.id.info;
import static com.napi.napi.Films_Library.main;
import static com.napi.napi.RequestCode.ACTIVITY_SETTINGS;
import static com.napi.napi.RequestCode.APP_PREFERENCES_COUNT_FILMS_0;
import static com.napi.napi.RequestCode.APP_PREFERENCES_COUNT_FILMS_1;
import static com.napi.napi.RequestCode.APP_PREFERENCES_COUNT_FILMS_2;
import static com.napi.napi.RequestCode.APP_PREFERENCES_COUNT_FILMS_3;
import static com.napi.napi.RequestCode.APP_PREFERENCES_COUNT_FILMS_4;
import static com.napi.napi.RequestCode.APP_PREFERENCES_COUNT_FILMS_5;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_image_1;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_image_2;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_image_3;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_image_4;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_image_5;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_image_6;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_name_1;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_name_2;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_name_3;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_name_4;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_name_5;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_name_6;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_time_1;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_time_2;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_time_3;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_time_4;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_time_5;
import static com.napi.napi.RequestCode.APP_PREFERENCES_film_time_6;
import static com.napi.napi.RequestCode.COUNT_FILMS;
import static com.napi.napi.RequestCode.ID_FILM;
import static com.napi.napi.RequestCode.film_image_1;
import static com.napi.napi.RequestCode.film_image_2;
import static com.napi.napi.RequestCode.film_image_3;
import static com.napi.napi.RequestCode.film_image_4;
import static com.napi.napi.RequestCode.film_image_5;
import static com.napi.napi.RequestCode.film_image_6;
import static com.napi.napi.RequestCode.film_name_1;
import static com.napi.napi.RequestCode.film_name_2;
import static com.napi.napi.RequestCode.film_name_3;
import static com.napi.napi.RequestCode.film_name_4;
import static com.napi.napi.RequestCode.film_name_5;
import static com.napi.napi.RequestCode.film_name_6;
import static com.napi.napi.RequestCode.film_time_1;
import static com.napi.napi.RequestCode.film_time_2;
import static com.napi.napi.RequestCode.film_time_3;
import static com.napi.napi.RequestCode.film_time_4;
import static com.napi.napi.RequestCode.film_time_5;
import static com.napi.napi.RequestCode.film_time_6;
import static com.napi.napi.RequestCode.films;
import static com.napi.napi.RequestCode.napiHistory;


public class MainScreen extends Activity implements SurfaceHolder.Callback, View.OnClickListener, Camera.PictureCallback, Camera.PreviewCallback, Camera.AutoFocusCallback {
    private Camera camera;
    private SurfaceHolder surfaceHolder;
    private SurfaceView preview;
    private Button shotBtn;
    private TextView scanning;
    private Context mContext;



    /**
     * ATTENTION: This was auto-generated to implement the App Indexing API.
     * See https://g.co/AppIndexing/AndroidStudio for more information.
     */
    private GoogleApiClient client;


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);


        // если хотим, чтобы приложение постоянно имело портретную ориентацию
       // setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);

        // если хотим, чтобы приложение было полноэкранным
        //getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);

        // и без заголовка
        //requestWindowFeature(Window.FEATURE_NO_TITLE);

        setContentView(R.layout.camera);

        // наше SurfaceView имеет имя SurfaceView01
        preview = (SurfaceView) findViewById(R.id.SurfaceView01);
        scanning = (TextView) findViewById(R.id.TextScanning);

        scanning.setVisibility(View.INVISIBLE);

        surfaceHolder = preview.getHolder();
        surfaceHolder.addCallback(this);
        surfaceHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);

        // кнопка имеет имя Button01
        shotBtn = (Button) findViewById(R.id.Button01);
        shotBtn.setOnClickListener(this);
        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        client = new GoogleApiClient.Builder(this).addApi(AppIndex.API).build();


    }

    @Override
    protected void onResume() {
        super.onResume();
        camera = Camera.open();
        camera.setDisplayOrientation(90);

        setPreviewSize(false);



        Camera.Parameters params = camera.getParameters();

        params.setJpegQuality(100);
        Size size = camera.getParameters().getPreviewSize();

       params.setPictureSize(size.width, size.height);
       //params.setPictureSize(1920, 1920);
        try {
            camera.setParameters(params);
        } catch (Exception e) {
        }
    }





    void setPreviewSize(boolean fullScreen) {

        // получаем размеры экрана
        Display display = getWindowManager().getDefaultDisplay();
        boolean widthIsMax = display.getWidth() > display.getHeight();

        // определяем размеры превью камеры
        Size size = camera.getParameters().getPreviewSize();

        RectF rectDisplay = new RectF();
        RectF rectPreview = new RectF();

        // RectF экрана, соотвествует размерам экрана
        rectDisplay.set(0, 0, display.getWidth(), display.getHeight());

        // RectF первью
        if (widthIsMax) {
            // превью в горизонтальной ориентации
            rectPreview.set(0, 0, size.width, size.height);
        } else {
            // превью в вертикальной ориентации
            rectPreview.set(0, 0, size.height, size.width);
        }



        Matrix matrix = new Matrix();
        // подготовка матрицы преобразования
        if (!fullScreen) {
            // если превью будет "втиснут" в экран (второй вариант из урока)
            matrix.setRectToRect(rectPreview, rectDisplay,
                    Matrix.ScaleToFit.START);
        } else {
            // если экран будет "втиснут" в превью (третий вариант из урока)
            matrix.setRectToRect(rectDisplay, rectPreview,
                    Matrix.ScaleToFit.START);
            matrix.invert(matrix);
        }
        // преобразование
        matrix.mapRect(rectPreview);

        // установка размеров surface из получившегося преобразования
        preview.getLayoutParams().height = (int) (rectPreview.bottom);
        preview.getLayoutParams().width = (int) (rectPreview.right);


    }

    @Override
    protected void onPause() {
        super.onPause();

        if (camera != null) {
            camera.setPreviewCallback(null);
            camera.stopPreview();
            camera.release();
            camera = null;

        }
    }


    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {
        try {
            camera.setPreviewDisplay(holder);
            camera.setPreviewCallback(this);
        } catch (IOException e) {
            e.printStackTrace();
        }

        Size previewSize = camera.getParameters().getPreviewSize();
        float aspect = (float) previewSize.width / previewSize.height;

        int previewSurfaceWidth = preview.getWidth();
        int previewSurfaceHeight = preview.getHeight();

        LayoutParams lp = preview.getLayoutParams();

        // здесь корректируем размер отображаемого preview, чтобы не было искажений

        if (this.getResources().getConfiguration().orientation != Configuration.ORIENTATION_LANDSCAPE) {
            // портретный вид
            camera.setDisplayOrientation(90);
            lp.height = previewSurfaceHeight;
            lp.width = (int) (previewSurfaceHeight / aspect);

        } else {
            // ландшафтный
            camera.setDisplayOrientation(90);
            lp.width = previewSurfaceWidth;
            lp.height = (int) (previewSurfaceWidth / aspect);
        }

        preview.setLayoutParams(lp);
        camera.startPreview();
    }




    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {
    }

    @Override
    public void onClick(View v) {

        shotBtn.setVisibility(View.INVISIBLE);
        scanning.setVisibility(View.VISIBLE);
       tp(v);

//        try {
//            TimeUnit.SECONDS.sleep(3);
//        } catch (InterruptedException e) {
//            e.printStackTrace();
//        }
//
//        tp(v);
//
    }

    public void tp(View v){       //if (v == shotBtn) {
            // либо делаем снимок непосредственно здесь
            // 	либо включаем обработчик автофокуса

            //camera.takePicture(null, null, null, this);


            camera.autoFocus(this);



    }




    @Override
    public void onPictureTaken(byte[] paramArrayOfByte, Camera paramCamera) {
        // сохраняем полученные jpg в папке /sdcard/NapiCash/
        // имя файла - System.currentTimeMillis()

        try {
            File saveDir = new File("/sdcard/NapiCash/");

            if (!saveDir.exists()) {
                saveDir.mkdirs();
            }


            //   FileOutputStream os = new FileOutputStream(String.format("/sdcard/NapiCash/%d.jpg", System.currentTimeMillis()));
            FileOutputStream os = new FileOutputStream(String.format("/sdcard/NapiCash/a.jpg"));


            os.write(paramArrayOfByte);
            os.close();


        } catch (Exception e) {
        }

        // после того, как снимок сделан, показ превью отключается. необходимо включить его
        paramCamera.startPreview();


        if (ACTIVITY_SETTINGS != 0){
            //сдвиг элементов на 1 вниз
            for (int i = 4; i > -1; i--) {
                COUNT_FILMS[i + 1] = COUNT_FILMS[i];
            }

//первый элемент получает значение результата сканирования
            COUNT_FILMS[0] = ACTIVITY_SETTINGS;

//сдвиг значений локальных переменных
            film_name_6 = film_name_5;
            film_name_5 = film_name_4;
            film_name_4 = film_name_3;
            film_name_3 = film_name_2;
            film_name_2 = film_name_1;

            film_time_6 = film_time_5;
            film_time_5 = film_time_4;
            film_time_4 = film_time_3;
            film_time_3 = film_time_2;
            film_time_2 = film_time_1;

            film_image_6 = film_image_5;
            film_image_5 = film_image_4;
            film_image_4 = film_image_3;
            film_image_3 = film_image_2;
            film_image_2 = film_image_1;


            main();


//первый элемент получает значение, в результате сканирования
            switch (ACTIVITY_SETTINGS) {

                case 1:
                    film_name_1 = films[0][0];
                    film_time_1 = films[0][1];
                    film_image_1 = Integer.parseInt(films[0][2]);
                    break;

                case 2:
                    film_name_1 = films[1][0];
                    film_time_1 = films[1][1];
                    film_image_1 = Integer.parseInt(films[1][2]);
                    break;

                case 3:
                    film_name_1 = films[2][0];
                    film_time_1 = films[2][1];
                    film_image_1 = Integer.parseInt(films[2][2]);
                    break;
            }

            //сохранение новых значений

            saveSettings();
        }


        switch ( ACTIVITY_SETTINGS) {


            case 0:
                Intent intent0 = new Intent(this, Activity_Settings_Error.class);
                startActivity(intent0);
                break;

            default:
                ID_FILM = ACTIVITY_SETTINGS - 1;
                Intent intent = new Intent(this, Activity_Settings_Information.class);
                startActivity(intent);
                break;

        }



//            try {
//                TimeUnit.SECONDS.sleep(3);
//            } catch (InterruptedException e) {
//                e.printStackTrace();
//            }

    }

    public void saveSettings(){

        SharedPreferences.Editor editor = napiHistory.edit();

        editor.putInt(APP_PREFERENCES_COUNT_FILMS_0, COUNT_FILMS[0]);
        editor.putInt(APP_PREFERENCES_COUNT_FILMS_1, COUNT_FILMS[1]);
        editor.putInt(APP_PREFERENCES_COUNT_FILMS_2, COUNT_FILMS[2]);
        editor.putInt(APP_PREFERENCES_COUNT_FILMS_3, COUNT_FILMS[3]);
        editor.putInt(APP_PREFERENCES_COUNT_FILMS_4, COUNT_FILMS[4]);
        editor.putInt(APP_PREFERENCES_COUNT_FILMS_5, COUNT_FILMS[5]);

        editor.putInt(APP_PREFERENCES_film_image_1, film_image_1);
        editor.putInt(APP_PREFERENCES_film_image_2, film_image_2);
        editor.putInt(APP_PREFERENCES_film_image_3, film_image_3);
        editor.putInt(APP_PREFERENCES_film_image_4, film_image_4);
        editor.putInt(APP_PREFERENCES_film_image_5, film_image_5);
        editor.putInt(APP_PREFERENCES_film_image_6, film_image_6);

        editor.putString(APP_PREFERENCES_film_name_1, film_name_1);
        editor.putString(APP_PREFERENCES_film_name_2, film_name_2);
        editor.putString(APP_PREFERENCES_film_name_3, film_name_3);
        editor.putString(APP_PREFERENCES_film_name_4, film_name_4);
        editor.putString(APP_PREFERENCES_film_name_5, film_name_5);
        editor.putString(APP_PREFERENCES_film_name_6, film_name_6);

        editor.putString(APP_PREFERENCES_film_time_1, film_time_1);
        editor.putString(APP_PREFERENCES_film_time_2, film_time_2);
        editor.putString(APP_PREFERENCES_film_time_3, film_time_3);
        editor.putString(APP_PREFERENCES_film_time_4, film_time_4);
        editor.putString(APP_PREFERENCES_film_time_5, film_time_5);
        editor.putString(APP_PREFERENCES_film_time_6, film_time_6);

        editor.apply();
    }


    public void back(View v){

        Intent intent1 = new Intent(this, MainActivity.class);
        startActivity(intent1);

    }


    @Override
    public void onAutoFocus(boolean paramBoolean, Camera paramCamera) {

        //if (paramBoolean) {
            // если удалось сфокусироваться, делаем снимок

            paramCamera.takePicture(null, null, null, this);

       // }

    }


    @Override
    public void onPreviewFrame(byte[] paramArrayOfByte, Camera paramCamera) {
        // здесь можно обрабатывать изображение, показываемое в preview
    }



    public Action getIndexApiAction() {
        Thing object = new Thing.Builder()
                .setName("MainScreen Page") // TODO: Define a title for the content shown.
                // TODO: Make sure this auto-generated URL is correct.
                .setUrl(Uri.parse("http://[ENTER-YOUR-URL-HERE]"))
                .build();
        return new Action.Builder(Action.TYPE_VIEW)
                .setObject(object)
                .setActionStatus(Action.STATUS_TYPE_COMPLETED)
                .build();
    }

    @Override
    public void onStart() {
        super.onStart();

        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        client.connect();
        AppIndex.AppIndexApi.start(client, getIndexApiAction());
    }

    @Override
    public void onStop() {
        super.onStop();

        // ATTENTION: This was auto-generated to implement the App Indexing API.
        // See https://g.co/AppIndexing/AndroidStudio for more information.
        AppIndex.AppIndexApi.end(client, getIndexApiAction());
        client.disconnect();
    }
}