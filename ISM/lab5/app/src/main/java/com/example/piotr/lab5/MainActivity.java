package com.example.piotr.lab5;

import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;

public class MainActivity extends AppCompatActivity {

    public static int color = Color.argb(255, 0,0,0);
    public static boolean clear = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    public void greenClicked(View view) {
        color = Color.argb(255,0, 255,0);
    }

    public void blueClicked(View view) {
        color = Color.argb(255,0, 0,255);
    }

    public void redClicked(View view) {
        color = Color.argb(255,255, 0,0);
    }

    public void blackClicked(View view) {
        color = Color.argb(255,0, 0,0);
    }

    public void clearClicked(View view) {
        clear = true;
        DrawingSurface.canvas.drawARGB(255, 255, 255, 255);
    }
}
