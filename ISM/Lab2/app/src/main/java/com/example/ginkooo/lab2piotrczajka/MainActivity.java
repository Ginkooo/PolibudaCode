package com.example.ginkooo.lab2piotrczajka;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final EditText fnameInput = (EditText)findViewById(R.id.fnameInput);
        final EditText lnameInput = (EditText)findViewById(R.id.lnameInput);
        final EditText gradeCountInput = (EditText)findViewById(R.id.gradeCountInput);
        final Button button = (Button)findViewById(R.id.gradeButton);

        fnameInput.setOnFocusChangeListener(new View.OnFocusChangeListener() {
            @Override
            public void onFocusChange(View v, boolean hasFocus) {
                showButtonIfAllValid(button);
                if (!hasFocus) {
                    boolean valid = validateFnameInput();
                    if (valid)
                        return;
                    Toast.makeText(getApplicationContext(), "@string/fnameNotValid", Toast.LENGTH_SHORT);
                }
            }
        });

        lnameInput.setOnFocusChangeListener(new View.OnFocusChangeListener() {
            @Override
            public void onFocusChange(View v, boolean hasFocus) {
                showButtonIfAllValid(button);
                if (!hasFocus) {
                    boolean valid = validateLnameInput();
                    if (valid)
                        return;
                    Toast.makeText(getApplicationContext(), "@string/lnameNotValid", Toast.LENGTH_SHORT);
                }
            }
        });

        gradeCountInput.setOnFocusChangeListener(new View.OnFocusChangeListener() {
            @Override
            public void onFocusChange(View v, boolean hasFocus) {
                showButtonIfAllValid(button);
                if (!hasFocus) {
                    boolean valid = validateGradeCount();
                    if (valid)
                        return;
                    Toast.makeText(getApplicationContext(), "@string/gradeCountNotValid", Toast.LENGTH_SHORT);
                }
            }
        });

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(!(validateFnameInput() && validateGradeCount() && validateLnameInput()))
                    return;
                Intent intent = new Intent(MainActivity.this, GradeActivity.class);
                String text = button.getText().toString();
                int gradeCount = Integer.parseInt(text);
                intent.putExtra("gradeCount", gradeCount);
                int requestCode = 1;
                startActivityForResult(intent, requestCode);
            }
        });
    }

    public void showButtonIfAllValid(Button button) {
        if(!(validateFnameInput() && validateLnameInput() && validateGradeCount())) {
            button.setVisibility(View.INVISIBLE);
            return;
        }
        button.setVisibility(View.VISIBLE);
    }

    public boolean validateFnameInput() {
        EditText fnameInput = (EditText)findViewById(R.id.fnameInput);
        String text = fnameInput.getText().toString();
        return text.matches("[a-z][A-Z]");
    }

    public boolean validateLnameInput() {
        EditText lnameInput = (EditText)findViewById(R.id.lnameInput);
        String text = lnameInput.getText().toString();
        return text.matches("[a-z][A-Z]");
    }

    public boolean validateGradeCount() {
        EditText gradeCountInput = (EditText)findViewById(R.id.gradeCountInput);
        String text = gradeCountInput.getText().toString();
        Integer count = Integer.parseInt(text);
        if (count < 5 || count > 15)
            return false;
        return true;
    }
}
