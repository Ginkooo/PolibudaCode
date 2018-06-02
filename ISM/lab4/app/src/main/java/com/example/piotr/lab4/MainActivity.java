package com.example.piotr.lab4;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    private static Button fetchFileInfoButton;
    private static TextView fileSizeTextView;
    private static TextView contentTypeTextView;
    private static Button fetchFileButton;
    private static EditText urlEditText;
    private static String mUrl;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        fetchFileButton = findViewById(R.id.fetchFileButton);
        fetchFileInfoButton = findViewById(R.id.fetchInfoButton);
        fileSizeTextView = findViewById(R.id.fileSizeTextView);
        contentTypeTextView = findViewById(R.id.fileTypeTextView);
        urlEditText = findViewById(R.id.addressEditText);

        fetchFileInfoButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String url = urlEditText.getText().toString();
                mUrl = url;

                String[] arr = new String[1];
                arr[0] = url;

                FileInfoFetcher fetcher = new FileInfoFetcher(fileSizeTextView, contentTypeTextView);
                fetcher.execute(arr);
            }
        });

        fetchFileButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!FlagRegister.isFileReadyForDownload) {
                    Toast.makeText(getApplicationContext(), "Ło paaaanie, toż to plik nie gotowy", Toast.LENGTH_SHORT).show();
                    return;
                }

                FileDownloaderService.startService(MainActivity.this, mUrl);
            }
        });


    }
}
