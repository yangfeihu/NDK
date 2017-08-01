package com.example.administrator.ndk;

/**
 * Created by Administrator on 2016/12/22 0022.
 */
public class Native {
    private final static String TAG = "Native";
    static {
        System.loadLibrary("native-lib");
    }
    public String name="Test";

    public String sayHelloFromJava(String nativeMsg){
        return  nativeMsg;
    }
    public static long getTimeFromJava(){
         return System.currentTimeMillis();
    }

    public native int add(int a,int b);
    public native String add(String a,String b);
    public native byte[] add(byte[] a);
    public native String sayHello(String msg);
    public native long getTime();
    public native void accessField();
    public native Person getPerson();
}
