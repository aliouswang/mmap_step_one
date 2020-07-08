package com.hxjb.mmap_step_one;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String dirName = getFilesDir() + "/mmkv_test.txt";
        int fd = init(dirName);

//        Log.e("mmkv", "fd:" + fd);

        String str = "Hello NDK";
        writeString(str);

        String temp = readString();
        Log.e("mmkv", temp);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native int init(String dirName);

    public native int writeString(String strToWrite);

    public native String readString();
}
