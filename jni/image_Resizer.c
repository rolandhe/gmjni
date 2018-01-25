#include "include/image_Resizer.h"
#include "include/common.h"

#ifdef __cplusplus
extern "C" {
#endif


/*
 * Class:     com_github_rolandhe_gm_Resizer
 * Method:    thumbnailImage
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_Resizer_thumbnailImage
  (JNIEnv *env, jclass cls, jlong imageHandler, jlong columns, jlong rows)
{
    if (imageHandler == 0)
    {
        return 0;
    }
    Image* imagePtr = (Image*)imageHandler;
    ExceptionInfo exception;
    GetExceptionInfo(&exception);
    Image * thumbnailImage = ThumbnailImage( imagePtr, (const unsigned long) columns,(const unsigned long)rows,&exception );

    if(thumbnailImage == (Image*)NULL)
    {
        wrap_exception(env,&exception);
        return 0;
    }
    return (jlong)thumbnailImage;
}

/*
 * Class:     com_github_rolandhe_gm_Resizer
 * Method:    scaleImage
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_Resizer_scaleImage
  (JNIEnv *env, jclass cls, jlong imageHandler, jlong columns, jlong rows)
{
    if (imageHandler == 0)
    {
        return 0;
    }
    Image* imagePtr = (Image*)imageHandler;
    ExceptionInfo exception;
    GetExceptionInfo(&exception);
    Image * scaleImage = ScaleImage(imagePtr, (const unsigned long) columns,(const unsigned long)rows,&exception);

    if(scaleImage == (Image*)NULL)
    {
        wrap_exception(env,&exception);
        return 0;
    }
    return (jlong)scaleImage;
}

/*
 * Class:     com_github_rolandhe_gm_Resizer
 * Method:    sampleImage
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_Resizer_sampleImage
  (JNIEnv *env, jclass cls, jlong imageHandler, jlong columns, jlong rows)
  {
    if (imageHandler == 0)
    {
        return 0;
    }
    Image* imagePtr = (Image*)imageHandler;
    ExceptionInfo exception;
    GetExceptionInfo(&exception);
    Image * sampleImage = SampleImage(imagePtr, (const unsigned long) columns,(const unsigned long)rows,&exception);

    if(sampleImage == (Image*)NULL)
    {
        wrap_exception(env,&exception);
        return 0;
    }
    return (jlong)sampleImage;
  }

/*
 * Class:     com_github_rolandhe_gm_Resizer
 * Method:    resizeImage
 * Signature: (JJJID)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_Resizer_resizeImage
  (JNIEnv *env, jclass cls, jlong imageHandler, jlong columns, jlong rows, jint filterTypes, jdouble blur)
  {
    if (imageHandler == 0)
    {
        return 0;
    }
    Image* imagePtr = (Image*)imageHandler;
    ExceptionInfo exception;
    GetExceptionInfo(&exception);
    Image * resizeImage = ResizeImage(imagePtr, (const unsigned long) columns,(const unsigned long)rows,
        (FilterTypes)filterTypes,(double)blur,&exception);

    if(resizeImage == (Image*)NULL)
    {
        wrap_exception(env,&exception);
        return 0;
    }
    return (jlong)resizeImage;
  }

#ifdef __cplusplus
}
#endif
