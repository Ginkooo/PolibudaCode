package com.example.ginkooo.lab2piotrczajka;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    EditText fnameInput;
    EditText lnameInput;
    EditText gradeCountInput;
    Button button;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        final EditText fnameInput = findViewById(R.id.fnameInput);
        final EditText lnameInput = findViewById(R.id.lnameInput);
        final EditText gradeCountInput = findViewById(R.id.gradeCountInput);
        final Button button = findViewById(R.id.gradeButton);

        this.fnameInput = fnameInput;
        this.lnameInput = lnameInput;
        this.gradeCountInput = gradeCountInput;
        this.button = button;

        final int requestCode = 5;

        fnameInput.setOnFocusChangeListener(new View.OnFocusChangeListener() {
            @Override
            public void onFocusChange(View v, boolean hasFocus) {
                showButtonIfAllValid(button);
                if (!hasFocus) {
                    boolean valid = validateFnameInput();
                    if (valid)
                        return;
                    Toast.makeText(getApplicationContext(), R.string.fnameNotValid, Toast.LENGTH_SHORT).show();
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
                    Toast.makeText(getApplicationContext(), R.string.lnameNotValid, Toast.LENGTH_SHORT).show();
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
                    Toast.makeText(getApplicationContext(), R.string.gradeCountNotValid, Toast.LENGTH_SHORT).show();
                }
            }
        });

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(!(validateFnameInput() && validateGradeCount() && validateLnameInput()))
                    return;
                Intent intent = new Intent(MainActivity.this, GradeActivity.class);
                String text = gradeCountInput.getText().toString();
                int gradeCount = Integer.parseInt(text);
                intent.putExtra("gradeCount", gradeCount);
                startActivityForResult(intent, requestCode);
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (resultCode != RESULT_OK)
            return;
        Bundle bundle = data.getExtras();
        float average = bundle.getFloat("average");
        final String text;
        final String toastText;
        if (average > 3) {
            text = getResources().getString(R.string.on_result_button_text);
            toastText = getResources().getString(R.string.on_positive_result_end_toast);
        }
        else {
            text = getResources().getString(R.string.on_bad_result_button_text);
            toastText = getResources().getString(R.string.on_bad_result_end_toast);
        }

        fnameInput.setFocusable(false);
        lnameInput.setFocusable(false);
        gradeCountInput.setFocusable(false);

        button.setText(text);

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(getApplicationContext(), toastText, Toast.LENGTH_SHORT).show();
                finish();
            }
        });
    }

    public void showButtonIfAllValid(Button button) {
        if(!validateFnameInput()) {
            button.setVisibility(View.INVISIBLE);
            return;
        }
        if(!validateLnameInput()) {
            button.setVisibility(View.INVISIBLE);
            return;
        }
        if(!validateGradeCount()) {
            button.setVisibility(View.INVISIBLE);
            return;
        }
        button.setVisibility(View.VISIBLE);
    }

    public boolean validateFnameInput() {
        EditText fnameInput = findViewById(R.id.fnameInput);
        String text = fnameInput.getText().toString();
        if ("".equals(text))
            return false;
        return true;
    }

    public boolean validateLnameInput() {
        EditText lnameInput = findViewById(R.id.lnameInput);
        String text = lnameInput.getText().toString();
        if ("".equals(text))
            return false;
        return true;
    }

    public boolean validateGradeCount() {
        EditText gradeCountInput = findViewById(R.id.gradeCountInput);
        String text = gradeCountInput.getText().toString();
        Integer count;
        try {
            count = Integer.parseInt(text);
        } catch (NumberFormatException e) {
            return false;
        }
        if (count < 5 || count > 15)
            return false;
        return true;
    }
}
