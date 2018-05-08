#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring

JNICALL
Java_group_peterzheng_trainticketbookingsystem_feature_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Welcome to Train Ticket Booking System!";
    return env->NewStringUTF(hello.c_str());
}
