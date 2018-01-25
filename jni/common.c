#include "include/common.h"
#include <stdio.h>
#include <string.h>

#define GMEXCEPTION_CLS_NAME  "com/github/rolandhe/gm/GmException"

void wrap_exception(JNIEnv *env,ExceptionInfo *exception)
{
    jclass exceptionCls = (*env)->FindClass(env,GMEXCEPTION_CLS_NAME);
    char * message = (char*)MagickMalloc(strlen(exception->reason) + 32);
    sprintf(message,"%d:%s", exception->error_number, exception->reason);
    (*env)->ThrowNew(env, exceptionCls, message);
    MagickFree((void*)message);
    (*env)->DeleteLocalRef(env, exceptionCls);
}
char * copyByteArray(JNIEnv *env,jbyteArray j_array,size_t * l)
{
    jint arr_len = (*env)->GetArrayLength(env,j_array);
    jbyte *c_array = (jbyte*)MagickMalloc((size_t)arr_len);
    memset(c_array,0,arr_len);

    (*env)->GetByteArrayRegion(env,j_array,0,arr_len,c_array);
    *l = (size_t)arr_len;
    return (char*)c_array;
}
jlong * copyLongArray(JNIEnv *env,jlongArray j_array,size_t * l)
{
    jint arr_len = (*env)->GetArrayLength(env,j_array);
    jlong *c_array = (jbyte*)MagickMalloc(sizeof(jlong) * (size_t)arr_len);
    memset(c_array,0,sizeof(jlong) * (size_t)arr_len);

    (*env)->GetLongArrayRegion(env,j_array,0,arr_len,c_array);
    *l = (size_t)arr_len;
    return c_array;
}
jbyteArray createByteArray(JNIEnv *env,char* buf,size_t  l)
{
   jbyteArray array =   (*env)->NewByteArray(env,(jsize)l);
   (*env)->SetByteArrayRegion(env,array,0,(jsize)l,(jbyte*)buf);
   return array;
}

Image * convertImageHandlersToIamgeList(JNIEnv *env,jlongArray imageHandlers)
{
        size_t size;
        jlong * c_array =  copyLongArray(env,imageHandlers,&size);

        Image* imageList = NewImageList();
        for(int i = 0; i < (int)size;i++){
            Image * p = (Image*)c_array[i];
            if (size > 1)
            {
                p->next = (Image*)NULL;
            }
            AppendImageToList(&imageList, p);
        }
        MagickFree((void*)c_array);
        return imageList;
}
