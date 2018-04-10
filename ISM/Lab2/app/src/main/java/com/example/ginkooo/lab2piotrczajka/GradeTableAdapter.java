package com.example.ginkooo.lab2piotrczajka;

import android.app.Activity;
import android.content.Context;
import android.provider.MediaStore;
import android.support.annotation.NonNull;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;

import org.w3c.dom.Text;

import java.util.List;

public class GradeTableAdapter extends ArrayAdapter<GradeModel> {

    List<GradeModel> grades;
    Activity context;

    public GradeTableAdapter(Activity context, List<GradeModel> grades) {
        super(context, 0, grades);
        this.grades = grades;
        this.context = context;
    }

    @Override
    public View getView(int position, View recycleView, ViewGroup parent) {
        View view = null;
        if (recycleView == null) {
            LayoutInflater inflater = context.getLayoutInflater();
            view = inflater.inflate(R.layout.grade_layout, null);

            RadioGroup group = view.findViewById(R.id.buttonGroup);
            group.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
                @Override
                public void onCheckedChanged(RadioGroup group, int checkedId) {
                    GradeModel model = (GradeModel)group.getTag();
                    RadioButton button = group.findViewById(checkedId);
                    model.grade = Integer.parseInt(button.getText().toString());
                }
            });
            group.setTag(grades.get(position));
        } else {
            view = recycleView;
            RadioGroup group = view.findViewById(R.id.buttonGroup);
            group.setTag(grades.get(position));
        }

        GradeModel grade = grades.get(position);
        TextView label = view.findViewById(R.id.label);
        label.setText(grade.name);

        RadioGroup group = view.findViewById(R.id.buttonGroup);
        for (int i=0; i<group.getChildCount(); ++i) {
            try {
                RadioButton button = (RadioButton)group.getChildAt(i);
                String text = button.getText().toString();
                if (Integer.parseInt(text) == grade.grade) {
                    button.setChecked(true);
                }
            } catch (Exception e) {
                continue;
            }
        }

        return view;
    }
}
