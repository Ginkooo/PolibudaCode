package com.example.ginkooo.lab2piotrczajka;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ListView;

import java.util.ArrayList;

public class GradeActivity extends AppCompatActivity {

    static int gradeCount;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_grade);

        Bundle extras = getIntent().getExtras();
        gradeCount = extras.getInt("gradeCount");

        final ArrayList<GradeModel> grades = new ArrayList<>();
        for(int i=0; i<gradeCount; ++i) {
            String text = "ocena " + String.valueOf(i);
            grades.add(new GradeModel(text, 2));
        }
        GradeTableAdapter adapter = new GradeTableAdapter(this, grades);

        ListView listView = findViewById(R.id.grade_list_view);
        listView.setAdapter(adapter);

        final Button button = findViewById(R.id.confirm_grade_input_button);

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                int sum = 0;
                for(GradeModel g : grades) {
                    sum += g.grade;
                }
                float avg = sum / grades.size();

                Bundle bundle = new Bundle();
                bundle.putFloat("average", avg);
                Intent intent = new Intent();
                intent.putExtras(bundle);
                setResult(RESULT_OK, intent);
                finish();
            }
        });
    }
}
