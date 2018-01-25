#include "include/image_ImageProcessor.h"
#include "include/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_github_rolandhe_gm_ImageProcessor
 * Method:    obtainTypeMetrics
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_ImageProcessor_obtainTypeMetrics
  (JNIEnv *env, jclass cls, jlong imageHandler, jlong drawInfoHandler)
{
    Image *image = (Image*)imageHandler;
    DrawInfo * drawInfo = (DrawInfo*)drawInfoHandler;
    TypeMetric * typeMetricPtr = (TypeMetric*) MagickMalloc(sizeof(TypeMetric));
    MagickPassFail ret =  GetTypeMetrics(image, drawInfo,typeMetricPtr);
    if(!ret)
    {
        MagickFree(typeMetricPtr);
        return 0;
    }
    return (jlong)typeMetricPtr;
}

/*
 * Class:     com_github_rolandhe_gm_ImageProcessor
 * Method:    annotateImage
 * Signature: (JJ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_github_rolandhe_gm_ImageProcessor_annotateImage
  (JNIEnv *env, jclass cls, jlong imageHandler, jlong drawInfoHandler)
  {
    Image *image = (Image*)imageHandler;
      DrawInfo * drawInfo = (DrawInfo*)drawInfoHandler;
    MagickPassFail ret =  AnnotateImage(image,drawInfo);

    return (jboolean)ret;
  }

/*
 * Class:     com_github_rolandhe_gm_ImageProcessor
 * Method:    transparentImage
 * Signature: (JLjava/lang/String;J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_github_rolandhe_gm_ImageProcessor_transparentImage
  (JNIEnv *env, jclass cls, jlong imageHandler, jstring color, jlong opacity)
{
    Image * imagePtr = (Image*)imageHandler;
    PixelPacket target;
    const char *c_str = NULL;
    jboolean isCopy;
    c_str = (*env)->GetStringUTFChars(env, color, &isCopy);
    if (!isCopy)
    {
        return (jboolean)0;
    }

    ExceptionInfo exception;
    GetExceptionInfo(&exception);
   MagickPassFail ret =  QueryColorDatabase(c_str,&target,&exception);
   (*env)->ReleaseStringUTFChars(env, color, c_str);
   if(!ret)
    {
        wrap_exception(env, &exception);
        return (jboolean)0;
    }
   ret =  TransparentImage( imagePtr, target,(unsigned int)opacity);
   return (jboolean)ret;
}

/*
 * Class:     com_github_rolandhe_gm_ImageProcessor
 * Method:    drawTextOnImage
 * Signature: (JJ)Z
 */
JNIEXPORT jboolean JNICALL Java_com_github_rolandhe_gm_ImageProcessor_drawTextOnImage
  (JNIEnv *env, jclass cls, jlong imageHandler, jlong drawInfoHandler)
{
    Image *image = (Image*)imageHandler;
    DrawInfo * drawInfo = (DrawInfo*)drawInfoHandler;
    MagickPassFail ret =  DrawImage(image,drawInfo);

    return (jboolean)ret;
}
#ifdef __cplusplus
}
#endif
