#include <jni.h>
#include <magick/api.h>

#ifndef JNI_COMMON_H
#define JNI_COMMON_H

void wrap_exception(JNIEnv *env,ExceptionInfo *exception);
char * copyByteArray(JNIEnv *env,jbyteArray buf,size_t * l);
jlong * copyLongArray(JNIEnv *env,jlongArray buf,size_t * l);
jbyteArray createByteArray(JNIEnv *env,char* buf,size_t  l);
Image * convertImageHandlersToIamgeList(JNIEnv *env,jlongArray imageHandlers);

#endif
