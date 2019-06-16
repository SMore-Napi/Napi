package com.napi.napi;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.ScrollView;
import android.widget.TextView;

import static com.napi.napi.R.layout.tab_2;
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

import static com.napi.napi.RequestCode.napiHistory;


public class Tab2 extends Fragment {

    RelativeLayout result1;
    RelativeLayout result2;
    RelativeLayout result3;
    RelativeLayout result4;
    RelativeLayout result5;
    RelativeLayout result6;

    ImageView imageFilm1;
    ImageView imageFilm2;
    ImageView imageFilm3;
    ImageView imageFilm4;
    ImageView imageFilm5;
    ImageView imageFilm6;

    TextView textName1;
    TextView textName2;
    TextView textName3;
    TextView textName4;
    TextView textName5;
    TextView textName6;

    TextView textTime1;
    TextView textTime2;
    TextView textTime3;
    TextView textTime4;
    TextView textTime5;
    TextView textTime6;

    Button buttonDelete1;
    Button buttonDelete2;
    Button buttonDelete3;
    Button buttonDelete4;
    Button buttonDelete5;
    Button buttonDelete6;

    Button buttonInformation1;
    Button buttonInformation2;
    Button buttonInformation3;
    Button buttonInformation4;
    Button buttonInformation5;
    Button buttonInformation6;

    ScrollView scrollView_Tab2;

    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {

        View v = inflater.inflate(tab_2, container, false);

        napiHistory = getActivity().getPreferences(0);

        ACTIVITY_SETTINGS = 0;

        //инициализация переменных
        imageFilm1 = (ImageView) v.findViewById(R.id.imageFilm1);
        imageFilm2 = (ImageView) v.findViewById(R.id.imageFilm2);
        imageFilm3 = (ImageView) v.findViewById(R.id.imageFilm3);
        imageFilm4 = (ImageView) v.findViewById(R.id.imageFilm4);
        imageFilm5 = (ImageView) v.findViewById(R.id.imageFilm5);
        imageFilm6 = (ImageView) v.findViewById(R.id.imageFilm6);

        textName1 = (TextView) v.findViewById(R.id.textName1);
        textName2 = (TextView) v.findViewById(R.id.textName2);
        textName3 = (TextView) v.findViewById(R.id.textName3);
        textName4 = (TextView) v.findViewById(R.id.textName4);
        textName5 = (TextView) v.findViewById(R.id.textName5);
        textName6 = (TextView) v.findViewById(R.id.textName6);

        textTime1 = (TextView) v.findViewById(R.id.textTime1);
        textTime2 = (TextView) v.findViewById(R.id.textTime2);
        textTime3 = (TextView) v.findViewById(R.id.textTime3);
        textTime4 = (TextView) v.findViewById(R.id.textTime4);
        textTime5 = (TextView) v.findViewById(R.id.textTime5);
        textTime6 = (TextView) v.findViewById(R.id.textTime6);

        result1 = (RelativeLayout) v.findViewById(R.id.result1);
        result2 = (RelativeLayout) v.findViewById(R.id.result2);
        result3 = (RelativeLayout) v.findViewById(R.id.result3);
        result4 = (RelativeLayout) v.findViewById(R.id.result4);
        result5 = (RelativeLayout) v.findViewById(R.id.result5);
        result6 = (RelativeLayout) v.findViewById(R.id.result6);

        buttonDelete1 = (Button) v.findViewById(R.id.buttonDelete1);
        buttonDelete2 = (Button) v.findViewById(R.id.buttonDelete2);
        buttonDelete3 = (Button) v.findViewById(R.id.buttonDelete3);
        buttonDelete4 = (Button) v.findViewById(R.id.buttonDelete4);
        buttonDelete5 = (Button) v.findViewById(R.id.buttonDelete5);
        buttonDelete6 = (Button) v.findViewById(R.id.buttonDelete6);

        buttonInformation1 = (Button) v.findViewById(R.id.buttonInformation1);
        buttonInformation2 = (Button) v.findViewById(R.id.buttonInformation2);
        buttonInformation3 = (Button) v.findViewById(R.id.buttonInformation3);
        buttonInformation4 = (Button) v.findViewById(R.id.buttonInformation4);
        buttonInformation5 = (Button) v.findViewById(R.id.buttonInformation5);
        buttonInformation6 = (Button) v.findViewById(R.id.buttonInformation6);

        scrollView_Tab2 = (ScrollView) v.findViewById(R.id.scrollView_Tab2);

        buttonDelete1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                remove(v);
            }
        });

        buttonDelete2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                remove(v);
            }
        });

        buttonDelete3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                remove(v);
            }
        });

        buttonDelete4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                remove(v);
            }
        });

        buttonDelete5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                remove(v);
            }
        });

        buttonDelete6.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                remove(v);
            }
        });

        buttonInformation1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonInformation_Click(v);
            }
        });

        buttonInformation2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonInformation_Click(v);
            }
        });

        buttonInformation3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonInformation_Click(v);
            }
        });

        buttonInformation4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonInformation_Click(v);
            }
        });

        buttonInformation5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonInformation_Click(v);
            }
        });

        buttonInformation6.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonInformation_Click(v);
            }
        });

        scrollView_Tab2.setVisibility(View.VISIBLE);

        // Получаем значения из сохранения
        getterForO();

        //присвоение значений
        if (COUNT_FILMS[0] == 0)
            scrollView_Tab2.setVisibility(View.INVISIBLE);
        else {
            scrollView_Tab2.setVisibility(View.VISIBLE);
            setterForO();
            refresh();
        }

        return v;
    }

    public void getterForO(){

        if (napiHistory.contains(APP_PREFERENCES_COUNT_FILMS_0))
            COUNT_FILMS[0] = napiHistory.getInt(APP_PREFERENCES_COUNT_FILMS_0, 0);

        if (napiHistory.contains(APP_PREFERENCES_COUNT_FILMS_1))
            COUNT_FILMS[1] = napiHistory.getInt(APP_PREFERENCES_COUNT_FILMS_1, 0);

        if (napiHistory.contains(APP_PREFERENCES_COUNT_FILMS_2))
            COUNT_FILMS[2] = napiHistory.getInt(APP_PREFERENCES_COUNT_FILMS_2, 0);

        if (napiHistory.contains(APP_PREFERENCES_COUNT_FILMS_3))
            COUNT_FILMS[3] = napiHistory.getInt(APP_PREFERENCES_COUNT_FILMS_3, 0);

        if (napiHistory.contains(APP_PREFERENCES_COUNT_FILMS_4))
            COUNT_FILMS[4] = napiHistory.getInt(APP_PREFERENCES_COUNT_FILMS_4, 0);

        if (napiHistory.contains(APP_PREFERENCES_COUNT_FILMS_5))
            COUNT_FILMS[5] = napiHistory.getInt(APP_PREFERENCES_COUNT_FILMS_5, 0);


        if (napiHistory.contains(APP_PREFERENCES_film_image_2))
            film_image_1 = napiHistory.getInt(APP_PREFERENCES_film_image_1, 0);

        if (napiHistory.contains(APP_PREFERENCES_film_image_2))
            film_image_2 = napiHistory.getInt(APP_PREFERENCES_film_image_2, 0);

        if (napiHistory.contains(APP_PREFERENCES_film_image_3))
            film_image_3 = napiHistory.getInt(APP_PREFERENCES_film_image_3, 0);

        if (napiHistory.contains(APP_PREFERENCES_film_image_4))
            film_image_4 = napiHistory.getInt(APP_PREFERENCES_film_image_4, 0);

        if (napiHistory.contains(APP_PREFERENCES_film_image_5))
            film_image_5 = napiHistory.getInt(APP_PREFERENCES_film_image_5, 0);

        if (napiHistory.contains(APP_PREFERENCES_film_image_6))
            film_image_6 = napiHistory.getInt(APP_PREFERENCES_film_image_6, 0);


        if (napiHistory.contains(APP_PREFERENCES_film_name_1))
            film_name_1 = napiHistory.getString(APP_PREFERENCES_film_name_1, "");

        if (napiHistory.contains(APP_PREFERENCES_film_name_2))
            film_name_2 = napiHistory.getString(APP_PREFERENCES_film_name_2, "");

        if (napiHistory.contains(APP_PREFERENCES_film_name_3))
            film_name_3 = napiHistory.getString(APP_PREFERENCES_film_name_3, "");

        if (napiHistory.contains(APP_PREFERENCES_film_name_4))
            film_name_4 = napiHistory.getString(APP_PREFERENCES_film_name_4, "");

        if (napiHistory.contains(APP_PREFERENCES_film_name_5))
            film_name_5 = napiHistory.getString(APP_PREFERENCES_film_name_5, "");

        if (napiHistory.contains(APP_PREFERENCES_film_name_6))
            film_name_6 = napiHistory.getString(APP_PREFERENCES_film_name_6, "");


        if (napiHistory.contains(APP_PREFERENCES_film_time_1))
            film_time_1 = napiHistory.getString(APP_PREFERENCES_film_time_1, "");

        if (napiHistory.contains(APP_PREFERENCES_film_time_2))
            film_time_2 = napiHistory.getString(APP_PREFERENCES_film_time_2, "");

        if (napiHistory.contains(APP_PREFERENCES_film_time_3))
            film_time_3 = napiHistory.getString(APP_PREFERENCES_film_time_3, "");

        if (napiHistory.contains(APP_PREFERENCES_film_time_4))
            film_time_4 = napiHistory.getString(APP_PREFERENCES_film_time_4, "");

        if (napiHistory.contains(APP_PREFERENCES_film_time_5))
            film_time_5 = napiHistory.getString(APP_PREFERENCES_film_time_5, "");

        if (napiHistory.contains(APP_PREFERENCES_film_time_6))
            film_time_6 = napiHistory.getString(APP_PREFERENCES_film_time_6, "");
    }

    public void setterForO(){

        textName1.setText(film_name_1);
        textName2.setText(film_name_2);
        textName3.setText(film_name_3);
        textName4.setText(film_name_4);
        textName5.setText(film_name_5);
        textName6.setText(film_name_6);

        textTime1.setText(film_time_1);
        textTime2.setText(film_time_2);
        textTime3.setText(film_time_3);
        textTime4.setText(film_time_4);
        textTime5.setText(film_time_5);
        textTime6.setText(film_time_6);

        imageFilm1.setImageResource(film_image_1);
        imageFilm2.setImageResource(film_image_2);
        imageFilm3.setImageResource(film_image_3);
        imageFilm4.setImageResource(film_image_4);
        imageFilm5.setImageResource(film_image_5);
        imageFilm6.setImageResource(film_image_6);
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

    public void refresh(){

        for (int j = 1; j < 7; j++) {

            switch (j) {

                case 1:
                    switch (COUNT_FILMS[0]) {
                        case 0:
                            result1.setVisibility(View.INVISIBLE);
                            break;

                        default:
                            result1.setVisibility(View.VISIBLE);
                            break;
                    }
                    break;

                case 2:
                    switch (COUNT_FILMS[1]) {
                        case 0:
                            result2.setVisibility(View.INVISIBLE);
                            break;

                        default:
                            result2.setVisibility(View.VISIBLE);
                            break;
                    }
                    break;

                case 3:
                    switch (COUNT_FILMS[2]) {
                        case 0:
                            result3.setVisibility(View.INVISIBLE);
                            break;

                        default:
                            result3.setVisibility(View.VISIBLE);
                            break;
                    }
                    break;

                case 4:
                    switch (COUNT_FILMS[3]) {
                        case 0:
                            result4.setVisibility(View.INVISIBLE);
                            break;

                        default:
                            result4.setVisibility(View.VISIBLE);
                            break;
                    }
                    break;

                case 5:
                    switch (COUNT_FILMS[4]) {
                        case 0:
                            result5.setVisibility(View.INVISIBLE);
                            break;

                        default:
                            result5.setVisibility(View.VISIBLE);
                            break;
                    }
                    break;

                case 6:
                    switch (COUNT_FILMS[5]) {
                        case 0:
                            result6.setVisibility(View.INVISIBLE);
                            break;

                        default:
                            result6.setVisibility(View.VISIBLE);
                            break;
                    }
                    break;
            }
        }
    }

    public void remove(View view) {

        int k=0;

        switch (view.getId()) {
            case R.id.buttonDelete1:

                k = 0;

                film_name_1 = film_name_2;
                film_name_2 = film_name_3;
                film_name_3 = film_name_4;
                film_name_4 = film_name_5;

                film_time_1 = film_time_2;
                film_time_2 = film_time_3;
                film_time_3 = film_time_4;
                film_time_4 = film_time_5;

                film_image_1 = film_image_2;
                film_image_2 = film_image_3;
                film_image_3 = film_image_4;
                film_image_4 = film_image_5;

                break;

            case R.id.buttonDelete2:

                k = 1;

                film_name_2 = film_name_3;
                film_name_3 = film_name_4;
                film_name_4 = film_name_5;

                film_time_2 = film_time_3;
                film_time_3 = film_time_4;
                film_time_4 = film_time_5;

                film_image_2 = film_image_3;
                film_image_3 = film_image_4;
                film_image_4 = film_image_5;

                break;

            case R.id.buttonDelete3:

                k = 2;

                film_name_3 = film_name_4;
                film_name_4 = film_name_5;

                film_time_3 = film_time_4;
                film_time_4 = film_time_5;

                film_image_3 = film_image_4;
                film_image_4 = film_image_5;

                break;

            case R.id.buttonDelete4:

                k = 3;

                film_name_4 = film_name_5;
                film_time_4 = film_time_5;
                film_image_4 = film_image_5;
                break;

            case R.id.buttonDelete5:
                k = 4;
                break;
        }

        film_name_5 = film_name_6;
        film_time_5 = film_time_6;
        film_image_5 = film_image_6;


        for (int i = k; i < 5; i++) {
            COUNT_FILMS[i] = COUNT_FILMS[i + 1];
        }

        COUNT_FILMS[5] = 0;
        saveSettings();
        setterForO();

        if (COUNT_FILMS[0] == 0) {
            scrollView_Tab2.setVisibility(View.INVISIBLE);
        } else {
            refresh();
        }
    }



    public void buttonInformation_Click(View view){

        switch (view.getId()){
            case R.id.buttonInformation1:
                ID_FILM = COUNT_FILMS[0]-1;
                break;
            case R.id.buttonInformation2:
                ID_FILM = COUNT_FILMS[1]-1;
                break;
            case R.id.buttonInformation3:
                ID_FILM = COUNT_FILMS[2]-1;
                break;
            case R.id.buttonInformation4:
                ID_FILM = COUNT_FILMS[3]-1;
                break;
            case R.id.buttonInformation5:
                ID_FILM = COUNT_FILMS[4]-1;
                break;
            case R.id.buttonInformation6:
                ID_FILM = COUNT_FILMS[5]-1;
                break;
        }

        //переход к information.xml
        Intent intent = new Intent(getActivity().getApplicationContext(), Activity_Settings_Information.class);
        startActivity(intent);

    }

}
