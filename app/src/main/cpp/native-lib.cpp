#include <jni.h>
#include <string>
#include <sys/mman.h>
#include <fcntl.h>
#include "ALog.cpp"
#include <errno.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_hxjb_mmap_1step_1one_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

static int g_fd;

extern "C"
JNIEXPORT jint JNICALL
Java_com_hxjb_mmap_1step_1one_MainActivity_init(JNIEnv *env, jobject thiz, jstring dir_name) {
    // TODO: implement init()
    const char * _dirName = env->GetStringUTFChars(dir_name, JNI_FALSE);
    if (!_dirName) {
        return -1;
    }
    extern int errno;
    int fd = open(_dirName, O_RDWR | O_CREAT | O_CLOEXEC, S_IRWXU);
    if (fd < 0) {
        LOGE("open fd failed: %d", errno);
        return -1;
    }
    LOGE("open fd success: %d", g_fd);
    g_fd = fd;
    return fd;
}
