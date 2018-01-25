#include "include/image_TypeMetric.h"
#include "include/common.h"



#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_github_rolandhe_gm_TypeMetric
 * Method:    getWidth
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_com_github_rolandhe_gm_TypeMetric_getWidth
  (JNIEnv *env, jclass cls, jlong handler)
{
    if(handler == 0)
    {
        return 0.0;
    }
    TypeMetric* typeMetricPtr = (TypeMetric*)handler;

    return typeMetricPtr->width;
}

/*
 * Class:     com_github_rolandhe_gm_TypeMetric
 * Method:    getHeight
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_com_github_rolandhe_gm_TypeMetric_getHeight
  (JNIEnv *env, jclass cls, jlong handler)
{
    if(handler == 0)
    {
        return 0.0;
    }
    TypeMetric* typeMetricPtr = (TypeMetric*)handler;

    return typeMetricPtr->height;
}

/*
 * Class:     com_github_rolandhe_gm_TypeMetric
 * Method:    getAscent
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_com_github_rolandhe_gm_TypeMetric_getAscent
  (JNIEnv *env, jclass cls, jlong handler)
{
    if(handler == 0)
    {
        return 0.0;
    }
    TypeMetric* typeMetricPtr = (TypeMetric*)handler;

    return typeMetricPtr->ascent;
}
/*
 * Class:     com_github_rolandhe_gm_TypeMetric
 * Method:    getDescent
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_com_github_rolandhe_gm_TypeMetric_getDescent
  (JNIEnv *env, jclass cls, jlong handler)
{
    if(handler == 0)
    {
        return 0.0;
    }
    TypeMetric* typeMetricPtr = (TypeMetric*)handler;

    return typeMetricPtr->descent;
}
/*
 * Class:     com_github_rolandhe_gm_TypeMetric
 * Method:    destoryTypeMetric
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_TypeMetric_destoryTypeMetric
  (JNIEnv *env, jclass cls, jlong handler)
{
    if(handler == 0)
    {
        return;
    }
    MagickFree((void*)handler);
}

#ifdef __cplusplus
}
#endif
