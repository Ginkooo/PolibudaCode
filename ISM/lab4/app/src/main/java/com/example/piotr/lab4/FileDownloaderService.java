package com.example.piotr.lab4;

import android.app.IntentService;
import android.content.Context;
import android.content.Intent;
import android.os.Environment;
import android.support.annotation.Nullable;
import android.util.Log;
import android.widget.Toast;

import java.io.DataInputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

public class FileDownloaderService extends IntentService {

    private static final String ACTION_TASK1 = "com.example.piotr.lab4.action.task1";
    private static final String PARAM1 = "com.example.piotr.lab4.extra.param1";
    private static Context mContext = null;
    private static int bytesFetched = 0;

    public FileDownloaderService() {
        super(FileDownloaderService.class.getName());
    }

    public static void startService(Context context, String url) {
        mContext = context;
        Intent intent = new Intent(context, FileDownloaderService.class);
        intent.setAction(ACTION_TASK1);
        intent.putExtra(PARAM1, url);
        context.startService(intent);
    }

    @Override
    protected void onHandleIntent(@Nullable Intent intent) {
        if (intent != null) {
            final String action = intent.getAction();
            if (ACTION_TASK1.equals(action)) {
                final String url = intent.getStringExtra(PARAM1);
                downloadAndSaveFile(url);
            } else {
                Log.d("filefetcher", "unknown action");
            }
        }
        Log.d("filefetcher","service has done it's action");
    }

    private void downloadAndSaveFile(String url_) {

        int BLOCK_SIZE = 2048;

        HttpURLConnection connection = null;
        try {
            URL url = new URL(url_);
            connection = (HttpURLConnection) url.openConnection();
            File tempFile = new File(url.getFile());
            String fName = tempFile.getName();
            if ("".equals(fName)) {
                fName = "defaultname";
            }
            File outFile = new File(
                    Environment.getExternalStorageDirectory() + File.separator + fName
            );

            outFile.exists();

            InputStream netInputStream = null;
            FileOutputStream fileOutputStream = null;

            DataInputStream reader = new DataInputStream(connection.getInputStream());
            fileOutputStream = openFileOutput(fName, MODE_PRIVATE);

            byte buffer[] = new byte[BLOCK_SIZE];

            int fetched = reader.read(buffer, 0, BLOCK_SIZE);
            while(fetched != -1) {
                fileOutputStream.write(buffer, 0, fetched);
                bytesFetched += fetched;
                Log.i("filefetcher","Pobrano " + Integer.toString(bytesFetched) + "bajtów");
                fetched = reader.read(buffer, 0, BLOCK_SIZE);
            }
            fileOutputStream.flush();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (connection != null) connection.disconnect();
        }

        Toast.makeText(mContext, "Pobrano i zapisano plik!", Toast.LENGTH_LONG).show();
    }
}
