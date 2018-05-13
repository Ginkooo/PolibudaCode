package com.example.pczajka.phonedbapp;

import android.content.ContentUris;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.ActionMode;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;

public class MainActivity extends AppCompatActivity {

    private SQLiteDatabase dbHandler;
    Menu menu;
    private ListView phoneList;
    private Context context;
    SimpleCursorAdapter dbAdapter;

    enum RequestCode {ADD, EDIT}

    private void recreateTable() {
        //this.dbHandler.execSQL("drop table phone_table");
        try {
            this.dbHandler.execSQL(String.format("CREATE TABLE %s (" +
                            "%s integer primary key," +
                            "%s text not null," +
                            "%s text not null," +
                            "%s text not null," +
                            "%s text);",
                    MySQLite.TABLE_NAME,
                    MySQLite.COLUMN_ID,
                    MySQLite.COLUMN_PRODUCENT,
                    MySQLite.COLUMN_MODEL,
                    MySQLite.COLUMN_ANDROID_VERSION,
                    MySQLite.COLUMN_WWW));
        } catch(Exception e) {

        }

        this.dbHandler.execSQL("insert into phone_table (producent, model, android_version) values('asdf','sdfsdf','34')");
        this.dbHandler.execSQL("insert into phone_table (producent, model, android_version) values('sgg','asfgr','54')");
        this.dbHandler.execSQL("insert into phone_table (producent, model, android_version) values('trw4et','ergerg','23')");
    }

    private void removeSelected() {

        long selected[] = this.phoneList.getCheckedItemIds();
        for(int i=0; i<selected.length; ++i) {
            long id = selected[i];

            this.dbHandler.execSQL("delete from phone_table where _id=" + id); //this might work
        }

    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);

        this.context = getApplicationContext();

        MySQLite mySQLite = new MySQLite(this);
        this.dbHandler = mySQLite.getWritableDatabase();
        recreateTable();
        Cursor cursor = this.dbHandler.query(true, MySQLite.TABLE_NAME,
                                             new String[]{MySQLite.COLUMN_ID,
                                                     MySQLite.COLUMN_PRODUCENT,
                                                     MySQLite.COLUMN_MODEL}, null, null, null, null, null, null);

        String[] mapFrom = new String[] {MySQLite.COLUMN_PRODUCENT, MySQLite.COLUMN_MODEL };
        int[] mapTo = new int[] {R.id.producent, R.id.model};

        dbAdapter = new SimpleCursorAdapter(this, R.layout.phone_layout, cursor, mapFrom, mapTo);

        phoneList = this.findViewById(R.id.phone_list);

        phoneList.setChoiceMode(ListView.CHOICE_MODE_MULTIPLE_MODAL);

        phoneList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Intent intent = new Intent(MainActivity.this, AddPhoneActivity.class);

                Bundle bundle = new Bundle();

                Cursor cursor = dbHandler.query(MySQLite.TABLE_NAME,
                        new String[]{MySQLite.COLUMN_ID, MySQLite.COLUMN_PRODUCENT, MySQLite.COLUMN_MODEL, MySQLite.COLUMN_ANDROID_VERSION, MySQLite.COLUMN_WWW},
                        MySQLite.COLUMN_ID +"="+id, null, null, null, null);

                boolean exists = cursor.moveToFirst();

                if (!exists)
                    throw new RuntimeException();

                int id_ = (int)cursor.getLong(0);
                String producent = cursor.getString(1);
                String model = cursor.getString(2);
                String version = cursor.getString(3);
                String www = cursor.getString(4);

                bundle.putInt("id", id_);
                bundle.putString("producent", producent);
                bundle.putString("model", model);
                bundle.putString("version", version);
                bundle.putString("www", www);

                intent.putExtras(bundle);

                startActivityForResult(intent, RequestCode.EDIT.ordinal());
            }
        });

        phoneList.setMultiChoiceModeListener(new AbsListView.MultiChoiceModeListener() {
            @Override
            public void onItemCheckedStateChanged(ActionMode mode, int position, long id, boolean checked) {

            }

            @Override
            public boolean onCreateActionMode(ActionMode mode, Menu menu) {
                MenuInflater inflater = mode.getMenuInflater();

                inflater.inflate(R.menu.menu, menu);

                MenuItem item = menu.findItem(R.id.menu_action_button);

                item.setTitle("Remove selected");

                return true;
            }

            @Override
            public boolean onPrepareActionMode(ActionMode mode, Menu menu) {
                return false;
            }

            @Override
            public boolean onActionItemClicked(ActionMode mode, MenuItem item) {
                switch (item.getItemId()) {
                    case R.id.menu_action_button:
                        removeSelected();
                        return true;
                }
                return false;
            }

            @Override
            public void onDestroyActionMode(ActionMode mode) {
            }
        });

        phoneList.setAdapter(dbAdapter);

    }

    @Override
    public boolean onPrepareOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();

        inflater.inflate(R.menu.menu, menu);

        this.menu = menu;

        MenuItem item = menu.findItem(R.id.menu_action_button);

        item.setOnMenuItemClickListener(new MenuItem.OnMenuItemClickListener() {
            @Override
            public boolean onMenuItemClick(MenuItem item) {
                showAddItemView();
                return true;
            }
        });

        return true;
    }

    private void showAddItemView() {
        Intent intent = new Intent(MainActivity.this, AddPhoneActivity.class);

        startActivityForResult(intent, RequestCode.ADD.ordinal());
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (resultCode != RESULT_OK)
            return;

        Bundle bundle = data.getExtras();

        if (requestCode == RequestCode.ADD.ordinal()) {
            String producent = bundle.getString("producent");
            String model = bundle.getString("model");
            String version = bundle.getString("version");
            String www = bundle.getString("www");

            dbHandler.execSQL(String.format("insert into phone_table(%s, %s, %s, %s) values('%s', '%s', '%s', '%s')",
                    MySQLite.COLUMN_PRODUCENT,
                    MySQLite.COLUMN_MODEL,
                    MySQLite.COLUMN_ANDROID_VERSION,
                    MySQLite.COLUMN_WWW,
                    producent,
                    model,
                    version,
                    www));
        }
        if (requestCode == RequestCode.EDIT.ordinal()) {

            int id = bundle.getInt("id");
            String producent = bundle.getString("producent");
            String model = bundle.getString("model");
            String version = bundle.getString("version");
            String www = bundle.getString("www");

            dbHandler.execSQL(String.format("update phone_table set %s='%s', %s='%s', %s='%s', %s='%s' where %s=%s",
                    MySQLite.COLUMN_PRODUCENT,
                    producent,
                    MySQLite.COLUMN_MODEL,
                    model,
                    MySQLite.COLUMN_ANDROID_VERSION,
                    version,
                    MySQLite.COLUMN_WWW,
                    www,
                    MySQLite.COLUMN_ID,
                    String.valueOf(id)));
        }
    }
}
