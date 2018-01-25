#include "include/image_ImageInfo.h"
#include "include/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_github_rolandhe_gm_ImageInfo
 * Method:    cloneImageInfo
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_ImageInfo_cloneImageInfo
  (JNIEnv *env, jclass cls, jlong imageInfoHandler)
{
    if(imageInfoHandler == 0) {
        return (jlong)(CloneImageInfo(0));
    }

    return (jlong)(CloneImageInfo((ImageInfo*)imageInfoHandler));
}

/*
 * Class:     com_github_rolandhe_gm_ImageInfo
 * Method:    destroyImageInfo
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_ImageInfo_destroyImageInfo
  (JNIEnv *env, jclass cls, jlong hanlder)
{
    if (hanlder == 0)
    {
        return;
    }
    ImageInfo * imageInfoPtr = (ImageInfo *)hanlder;
    DestroyImageInfo(imageInfoPtr);
}

/*
 * Class:     com_github_rolandhe_gm_ImageInfo
 * Method:    setupFormat
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_ImageInfo_setupFormat
  (JNIEnv *env, jclass cls, jlong hanlder, jstring format)
{
    if (hanlder == 0)
    {
        return;
    }
    const char *c_str = NULL;
    jboolean isCopy;
    c_str = (*env)->GetStringUTFChars(env, format, &isCopy);
    if (!isCopy)
    {
        return;
    }

    ImageInfo * imageInfoPtr = (ImageInfo *)hanlder;
    strcpy(imageInfoPtr->magick,c_str);
    (*env)->ReleaseStringUTFChars(env, format, c_str);
}

/*
 * Class:     com_github_rolandhe_gm_ImageInfo
 * Method:    setupFileName
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_ImageInfo_setupFileName
  (JNIEnv *env, jclass cls, jlong hanlder, jstring fileName)
{
    if (hanlder == 0)
    {
        return;
    }
    const char *c_str = NULL;
    jboolean isCopy;
    c_str = (*env)->GetStringUTFChars(env, fileName, &isCopy);
    if (!isCopy)
    {
        return;
    }

    ImageInfo * imageInfoPtr = (ImageInfo *)hanlder;
    strcpy(imageInfoPtr->filename,c_str);
    (*env)->ReleaseStringUTFChars(env, fileName, c_str);
}

/*
 * Class:     com_github_rolandhe_gm_ImageInfo
 * Method:    setupAdjoin
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_ImageInfo_setupAdjoin
  (JNIEnv *env, jclass cls, jlong hanlder, jint adjoin)
{
    if (hanlder == 0)
    {
        return;
    }
    ImageInfo * imageInfoPtr = (ImageInfo *)hanlder;
    imageInfoPtr->adjoin = (MagickBool)adjoin;
}


#ifdef __cplusplus
}
#endif
