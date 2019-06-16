package com.napi.smore.napi;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import static com.napi.smore.napi.Films_Library.main;
import static com.napi.smore.napi.RequestCode.ID_FILM;
import static com.napi.smore.napi.RequestCode.films;


public class Activity_Settings_Information extends Activity {

    ImageView imageFilm;
    TextView textName;
    TextView textTime;

    TextView textInformationMore_1;
    TextView textInformationMore_2;
    TextView textInformationMore_3;
    TextView textInformationMore_4;
    TextView textInformationMore_5;
    TextView textInformationMore_6;
    TextView textInformationMore_7;
    TextView textInformationMore_8;
    TextView textInformationMore_9;
    TextView textInformationMore_10;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings_information);

        imageFilm = (ImageView) findViewById(R.id.activity_settings_imageFilm);
        textName = (TextView) findViewById(R.id.activity_settings_textName);
        textTime = (TextView) findViewById(R.id.activity_settings_textTime);

        textInformationMore_1 = (TextView) findViewById(R.id.textInformationMore_1b);
        textInformationMore_2 = (TextView) findViewById(R.id.textInformationMore_2b);
        textInformationMore_3 = (TextView) findViewById(R.id.textInformationMore_3b);
        textInformationMore_4 = (TextView) findViewById(R.id.textInformationMore_4b);
        textInformationMore_5 = (TextView) findViewById(R.id.textInformationMore_5b);
        textInformationMore_6 = (TextView) findViewById(R.id.textInformationMore_6b);
        textInformationMore_7 = (TextView) findViewById(R.id.textInformationMore_7b);
        textInformationMore_8 = (TextView) findViewById(R.id.textInformationMore_8b);
        textInformationMore_9 = (TextView) findViewById(R.id.textInformationMore_9b);
        textInformationMore_10 = (TextView) findViewById(R.id.textInformationMore_1_6a);




        main();

        textName.setText(films[ID_FILM][0]);
        textTime.setText(films[ID_FILM][1]);
        imageFilm.setImageResource(Integer.parseInt(films[ID_FILM][2]));
        textInformationMore_1.setText(films[ID_FILM][3]);
        textInformationMore_2.setText(films[ID_FILM][4]);
        textInformationMore_3.setText(films[ID_FILM][5]);
        textInformationMore_4.setText(films[ID_FILM][6]);
        textInformationMore_5.setText(films[ID_FILM][7]);
        textInformationMore_10.setText(films[ID_FILM][8]);
        textInformationMore_6.setText(films[ID_FILM][9]);
        textInformationMore_7.setText(films[ID_FILM][10]);
        textInformationMore_8.setText(films[ID_FILM][11]);
        textInformationMore_9.setText(films[ID_FILM][12]);

    }

    public void back_MainActivity (View view){
        Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);

    }


}