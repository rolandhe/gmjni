#include "include/image_Composite.h"
#include "include/common.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * Class:     com_github_rolandhe_gm_Composite
 * Method:    compositeImage
 * Signature: (JIJJJ)I
 */
JNIEXPORT jboolean JNICALL Java_com_github_rolandhe_gm_Composite_compositeImage
  (JNIEnv *env, jclass cls, jlong canvasHandler, jint compositeOperator, jlong compositeHandler, jlong x, jlong y)
{
    return (jboolean)CompositeImage((Image*)canvasHandler,(int)compositeOperator,(Image*)compositeHandler,(long)x,
    (long)y);
}

/*
 * Class:     com_github_rolandhe_gm_Composite
 * Method:    appendImages
 * Signature: ([JI)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_Composite_appendImages
  (JNIEnv *env, jclass cls, jlongArray imageHandlers, jint stack)
{
    Image* imageList = convertImageHandlersToIamgeList(env,imageHandlers);
    ExceptionInfo exception;
    GetExceptionInfo(&exception);
    Image * newImagePtr = AppendImages( imageList, (unsigned int) stack, &exception);
    if(newImagePtr == (Image*)NULL)
    {
        wrap_exception(env,&exception);
        return 0;
    }
    return (jlong)newImagePtr;
}

/*
 * Class:     com_github_rolandhe_gm_Composite
 * Method:    writeImages
 * Signature: (J[JLjava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_com_github_rolandhe_gm_Composite_writeImages
   (JNIEnv *env, jclass cls, jlong imageInfoHandler, jlongArray imageHandlers, jstring fileName)
{
        ImageInfo* imageInfoPtr = (ImageInfo*) imageInfoHandler;

        const char *c_str = NULL;
        jboolean isCopy;

        c_str = (*env)->GetStringUTFChars(env, fileName, &isCopy);
        if (!isCopy)
        {
            return (jboolean)0;
        }

        Image* imageList = convertImageHandlersToIamgeList(env,imageHandlers);
        ExceptionInfo exception;
        GetExceptionInfo(&exception);

        MagickPassFail ret = WriteImages(imageInfoPtr,imageList,c_str,&exception);
        (*env)->ReleaseStringUTFChars(env, fileName, c_str);
        if(!ret)
        {
            wrap_exception(env,&exception);
        }
        return (jboolean)ret;
}

#ifdef __cplusplus
}
#endif
