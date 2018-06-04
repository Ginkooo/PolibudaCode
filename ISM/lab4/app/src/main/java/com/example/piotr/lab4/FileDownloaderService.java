package com.example.piotr.lab4;

import android.Manifest;
import android.app.IntentService;
import android.content.Context;
import android.content.Intent;
import android.os.Environment;
import android.support.annotation.Nullable;
import android.util.Log;
import android.widget.Toast;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;

public class FileDownloaderService extends IntentService {

    private static final String ACTION_TASK1 = "com.example.piotr.lab4.action.task1";
    private static final String PARAM1 = "com.example.piotr.lab4.extra.param1";
    private static Context mContext = null;
    private static int bytesFetched = 0;

    public final static String NOTIFICATION = "com.example.piotr.lab4.reciever";
    public final static String FILEINFO = "FILEINFO";

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

        int BLOCK_SIZE = 2048;;

        int count;
        try {
            URL url = new URL(url_);
            URLConnection connection = url.openConnection();
            connection.connect();

            long fileSize = connection.getContentLength();

            String name = url.getFile();
            String [] arr = name.split("/");
            name = arr[arr.length - 1];

            if ("".equals(name))
                name = "downloaded.raw";

            InputStream inputStream = new BufferedInputStream(url.openStream(), 8192);

            OutputStream outputStream = new FileOutputStream(Environment.getExternalStorageDirectory().toString() + File.separator + name);

            byte data[] = new byte[1024];

            long total = 0;

            notifyFileDownloadProgress(0, fileSize, "starting");

            while ((count = inputStream.read(data)) != -1) {
                total += count;

                notifyFileDownloadProgress(total, fileSize, "in progress");

                outputStream.write(data, 0, count);
            }

            outputStream.flush();

            notifyFileDownloadProgress(0, 0, "done");

            outputStream.close();
            inputStream.close();
        } catch (Exception e) {
            e.printStackTrace();
            notifyFileDownloadProgress(0, 0, "error");
        }
    }

    private void notifyFileDownloadProgress(long current, long size, String result) {

        ProgressInfo info = new ProgressInfo(current, size, result);

        Intent intent = new Intent(NOTIFICATION);
        intent.putExtra(FILEINFO, info);
        sendBroadcast(intent);
    }
}
