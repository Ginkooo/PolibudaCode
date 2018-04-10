package com.example.ginkooo.lab2piotrczajka;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class GradeActivity extends AppCompatActivity {

    static int gradeCount;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_grade);

        Bundle extras = getIntent().getExtras();
        gradeCount = extras.getInt("gradeCount");
    }
}
