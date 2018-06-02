package com.example.piotr.lab4;

import android.os.AsyncTask;
import android.widget.TextView;

import org.w3c.dom.Text;

import java.net.HttpURLConnection;
import java.net.URL;

public class FileInfoFetcher extends AsyncTask<String, Integer, FileInformation> {

    private TextView fileSizeTextView;
    private TextView contentTypeTextView;

    public FileInfoFetcher(TextView fileSizeTextView, TextView contentTypeTextView) {
        super();
        this.fileSizeTextView = fileSizeTextView;
        this.contentTypeTextView = contentTypeTextView;
    }

    @Override
    protected FileInformation doInBackground(String... strings) {
        String url_ = strings[0];

        FileInformation ret = new FileInformation();
        ret.contentType = "nieznany";
        ret.size = -1;

        HttpURLConnection connection = null;
        try {
            URL url = new URL(url_);
            connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("GET");
            connection.setDoOutput(true);

            int size = connection.getContentLength();
            String type = connection.getContentType();
            ret.size = size;
            ret.contentType = type;

        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if(connection != null) connection.disconnect();
        }
        return ret;
    }

    @Override
    protected void onPostExecute(FileInformation result) {
        if(result.size == -1)
            FlagRegister.isFileReadyForDownload = false;
        else
            FlagRegister.isFileReadyForDownload = true;
        fileSizeTextView.setText(Integer.toString(result.size));
        contentTypeTextView.setText(result.contentType);
    }
}
