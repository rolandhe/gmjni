#include "include/image_GmBase.h"
#include "include/common.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * Class:     com_github_rolandhe_gm_GmBase
 * Method:    initGmLib
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_GmBase_initGmLib (JNIEnv *env, jclass cls)
{
    InitializeMagick(NULL);
}

#ifdef __cplusplus
}
#endif
