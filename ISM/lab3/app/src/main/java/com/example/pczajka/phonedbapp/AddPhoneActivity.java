package com.example.pczajka.phonedbapp;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class AddPhoneActivity extends AppCompatActivity {

    EditText producentEditText;
    EditText modelEditText;
    EditText versionEditText;
    EditText wwwEditText;

    Button cancelButton;
    Button wwwButton;
    Button saveButton;

    private long id;

    enum Mode {ADD, EDIT}

    Mode mode = Mode.EDIT;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_add_phone);

        Bundle bundle = getIntent().getExtras();

        cancelButton = findViewById(R.id.cancel_button);
        saveButton = findViewById(R.id.save_button);
        wwwButton = findViewById(R.id.www_button);

        producentEditText = findViewById(R.id.producent_edittext);
        modelEditText = findViewById(R.id.model_edittext);
        versionEditText = findViewById(R.id.android_version_edittext);
        wwwEditText = findViewById(R.id.www_edittext);
        try {
            String producent = bundle.getString("producent");
            String model = bundle.getString("model");
            String version = bundle.getString("version");
            String www = bundle.getString("www");


            producentEditText.setText(producent);
            modelEditText.setText(model);
            versionEditText.setText(version);
            wwwEditText.setText(www);
            this.mode = Mode.EDIT;
            id = bundle.getInt("id");
        } catch (Exception e) {
            this.mode = Mode.ADD;

        }
        saveButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String producent = producentEditText.getText().toString();
                String model = modelEditText.getText().toString();
                String version = versionEditText.getText().toString();
                String www = wwwEditText.getText().toString();

                Bundle bundle = new Bundle();
                bundle.putString("producent", producent);
                bundle.putString("model", model);
                bundle.putString("version", version);
                bundle.putString("www", www);

                Intent intent = new Intent();
                intent.putExtras(bundle);
                setResult(RESULT_OK, intent);
                finish();
            }
        });

        cancelButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                setResult(RESULT_CANCELED);
                finish();
            }
        });

        wwwButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String www = wwwEditText.getText().toString();
                Intent intent = new Intent("android.intent.action.VIEW", Uri.parse(www));

                startActivity(intent);
            }
        });
    }
}
