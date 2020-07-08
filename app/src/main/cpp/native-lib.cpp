#include <jni.h>
#include <string>
#include <sys/mman.h>
#include <fcntl.h>
#include "ALog.cpp"
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>

extern "C" JNIEXPORT jstring JNICALL
Java_com_hxjb_mmap_1step_1one_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

static int g_fd;
static const char * g_dirname;
extern "C"
JNIEXPORT jint JNICALL
Java_com_hxjb_mmap_1step_1one_MainActivity_init(JNIEnv *env, jobject thiz, jstring dir_name) {
    // TODO: implement init()
    const char * _dirName = env->GetStringUTFChars(dir_name, JNI_FALSE);
    g_dirname = _dirName;
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

extern "C"
JNIEXPORT jint JNICALL
Java_com_hxjb_mmap_1step_1one_MainActivity_writeString(JNIEnv *env, jobject thiz,
                                                       jstring str_to_write) {
    // TODO: implement writeString()
    const char* _strToWrite = env->GetStringUTFChars(str_to_write, JNI_FALSE);
    int len = env->GetStringLength(str_to_write);
    if (!_strToWrite) {
        LOGE("str to write cannot be null!");
        return -1;
    }
    if (g_fd < 0) {
        LOGE("init first!");
        return -1;
    }
    int ret = write(g_fd, _strToWrite, len);
    if (ret < 0) {
        LOGE("write error");
        return -1;
    }
    LOGE("write success len: %d", ret);
    return ret;
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_hxjb_mmap_1step_1one_MainActivity_readString(JNIEnv *env, jobject thiz) {
    // TODO: implement readString()
    if (g_fd < 0) {
        LOGE("init first!");
        return env->NewStringUTF("");
    }
    size_t fileSize = 0;
    struct stat statbuf;
    size_t flag = 0;
    flag = stat(g_dirname, &statbuf);
    if (flag != 0) {
        LOGE("Get file information error!");
    } else {
        fileSize = statbuf.st_size;
        LOGE("Get file len : %d", fileSize);
    }
    char buf[fileSize + 1];
    extern int errno;
    lseek(g_fd, 0, SEEK_SET);
    int ret = read(g_fd, buf, fileSize);
    LOGE("read errno: %d", errno);
    if (ret > 0) {
        LOGE("read file success");
        buf[fileSize] = '\0';
        return env->NewStringUTF(buf);
    } else {
        LOGE("read file error");
        return env->NewStringUTF(buf);
    }

}
