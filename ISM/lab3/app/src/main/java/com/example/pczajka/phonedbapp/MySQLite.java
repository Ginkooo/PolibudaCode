package com.example.pczajka.phonedbapp;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.widget.Toast;

public class MySQLite extends SQLiteOpenHelper {

    public final static int VERSION = 1;
    public final static String DB_NAME = "phone_db";
    public final static String TABLE_NAME = "phone_table";
    public final static String COLUMN_PRODUCENT = "producent";
    public final static String COLUMN_MODEL = "model";
    public final static String COLUMN_ANDROID_VERSION = "android_version";
    public final static String COLUMN_WWW = "www";
    public final static String COLUMN_ID = "_id";

    private Context context;

    public MySQLite(Context context) {
        super(context, DB_NAME, null, VERSION);
        this.context = context;
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        Toast.makeText(this.context, "DB created", Toast.LENGTH_SHORT);
    }

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {

    }
}
