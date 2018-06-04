package com.example.piotr.lab4;

import android.Manifest;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    private static Button fetchFileInfoButton;
    private static TextView fileSizeTextView;
    private static TextView contentTypeTextView;
    private static TextView progressTextView;
    private static ProgressBar progressBar;
    private static Button fetchFileButton;
    private static EditText urlEditText;
    private static String mUrl;
    private FileDownloadProgressReceiver receiver = new FileDownloadProgressReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            ProgressInfo info = intent.getParcelableExtra(FileDownloaderService.FILEINFO);
            System.out.println("received");
            switch (info.result) {
                case "in progress":
                    progressTextView.setText(Long.toString(info.fetched));
                    int progress = (int)((info.fetched/info.size) * 1000);
                    System.out.println(progress);
                    progressBar.setProgress(progress);
                    break;
                case "starting":
                    progressBar.setMax(1000);
                    progressBar.setVisibility(View.VISIBLE);
                    break;
                case "done":
                    Toast.makeText(getApplicationContext(), "Pobieranie zakończyło się pomyślnie!", Toast.LENGTH_SHORT).show();
                    progressBar.setVisibility(View.INVISIBLE);
                    break;
                case "error":
                    progressBar.setVisibility(View.INVISIBLE);
                    Toast.makeText(getApplicationContext(), "Podczas pobierania wystąpił błąd :<", Toast.LENGTH_SHORT).show();
                    break;
            }
        }
    };

    @Override
    protected void onResume() {
        super.onResume();
        registerReceiver(this.receiver, new IntentFilter(FileDownloaderService.NOTIFICATION));
    }

    @Override
    protected  void onPause() {
        super.onPause();
        unregisterReceiver(this.receiver);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        fetchFileButton = findViewById(R.id.fetchFileButton);
        fetchFileInfoButton = findViewById(R.id.fetchInfoButton);
        fileSizeTextView = findViewById(R.id.fileSizeTextView);
        contentTypeTextView = findViewById(R.id.fileTypeTextView);
        urlEditText = findViewById(R.id.addressEditText);
        progressTextView = findViewById(R.id.bytesFetchedTextView);
        progressBar = findViewById(R.id.fileDownloadProgressBar);

        String[] permissions = new String[] {Manifest.permission.WRITE_EXTERNAL_STORAGE};
        ActivityCompat.requestPermissions(MainActivity.this, permissions, 1);

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
