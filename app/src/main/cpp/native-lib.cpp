#include "string"
#include "../jni/com_example_administrator_ndk_Native.h"
#include <iostream>
using namespace std;

//传递普通的类型
jint JNICALL Java_com_example_administrator_ndk_Native_add
        (JNIEnv *, jobject, jint j, jint k)
{
    return j+k;
}

//传递字符串，返回字符串
jstring JNICALL Java_com_example_administrator_ndk_Native_add__Ljava_lang_String_2Ljava_lang_String_2
        (JNIEnv *env, jobject obj, jstring a, jstring b)
{
    const char* strA = env->GetStringUTFChars(a,false);
    const char* strB = env->GetStringUTFChars(b,false);
    char* c = (char*)malloc(strlen(strA)+strlen(strB)+1);
    strcpy(c,strA);
    strcat(c,strB);
    env->ReleaseStringUTFChars(a,strA);
    env->ReleaseStringUTFChars(b,strB);
    return env->NewStringUTF(c);
}

//传递数组，返回数组
jbyteArray JNICALL Java_com_example_administrator_ndk_Native_add___3B
        (JNIEnv *env, jobject, jbyteArray arrayA)
{
    jsize length = env->GetArrayLength(arrayA);
    jbyte* array = env->GetByteArrayElements(arrayA, false);
    jbyteArray arrayResult = env->NewByteArray(length);
    jint i = 0;
    for(i = 0;i<length;i++)
    {
        array[i] = array[i]*2;
    }
    env->SetByteArrayRegion(arrayResult,0,length,array);
    env->ReleaseByteArrayElements(arrayA,array,0);
    return arrayResult;
}
//回调Java中的普通方法
jstring JNICALL Java_com_example_administrator_ndk_Native_sayHello
        (JNIEnv *env, jobject, jstring msg){
    jstring str = NULL;
    //得到类
    jclass clz = env->FindClass("com/example/administrator/ndk/Native");
    //得到构造函数
    jmethodID ctor = env->GetMethodID(clz,"<init>","()V");
    //创建一个对象
    jobject nativeObj = env->NewObject(clz, ctor);
    //得到方法ID
    jmethodID mid = env->GetMethodID(clz, "sayHelloFromJava", "(Ljava/lang/String;)Ljava/lang/String;");
    //回调java中的方法
    if (mid) {
        str = (jstring)env->CallObjectMethod(nativeObj, mid, msg);
    }
    return str;
}

//回调Java中的静态方法
jlong JNICALL Java_com_example_administrator_ndk_Native_getTime
        (JNIEnv *env, jobject jobj){
    jlong  time = 0;
    //得到类
    //jclass  clz = env->GetObjectClass(jobj);
    jclass clz = env->FindClass("com/example/administrator/ndk/Native");
    jmethodID mid = env->GetStaticMethodID(clz,"getTimeFromJava","()J");
    if (mid) {
        time = env->CallStaticLongMethod(clz,mid);
    }
    return time;
}

//访问字段
void JNICALL Java_com_example_administrator_ndk_Native_accessField
        (JNIEnv *env, jobject obj){

    jclass  cls = env->GetObjectClass(obj);
    //得到属性ID()
    jfieldID nameId = env->GetFieldID(cls,"name","Ljava/lang/String;");
    //得到属
    jobject name = env->GetObjectField(cls,nameId);
    //设置属性的值
    env->SetObjectField(obj,nameId,env->NewStringUTF("from c++"));
}

//返回对象
jobject JNICALL Java_com_example_administrator_ndk_Native_getPerson
        (JNIEnv *env, jobject){
    //得到类
    jclass clz = env->FindClass("com/example/administrator/ndk/Person");
    //得到构造函数
    jmethodID ctor = env->GetMethodID(clz,"<init>","()V");
   //创建一个对象
    jobject nativeObj = env->NewObject(clz, ctor);
    //得到方法ID
    jmethodID setNameId = env->GetMethodID(clz, "setName", "(Ljava/lang/String;)V");
    jmethodID setAgeId = env->GetMethodID(clz, "setAge", "(I)V");

    if(setNameId){
        env->CallVoidMethod(nativeObj,setNameId,env->NewStringUTF("yangfeihu"));
    }
    if(setAgeId){
        env->CallVoidMethod(nativeObj,setAgeId,100);
    }
    return nativeObj;
}



