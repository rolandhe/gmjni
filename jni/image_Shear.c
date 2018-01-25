#include "include/image_Shear.h"
#include "include/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_github_rolandhe_gm_Shear
 * Method:    rotateImage
 * Signature: (JD)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_Shear_rotateImage
  (JNIEnv * env, jclass cls, jlong imageHandler, jdouble degree)
{
    if (imageHandler == 0)
    {
        return 0;
    }
    Image* imagePtr = (Image*)imageHandler;
    ExceptionInfo exception;
    GetExceptionInfo(&exception);
    Image * rotateImage = RotateImage(imagePtr,degree,&exception);
    if(rotateImage == (Image*)NULL)
    {
        wrap_exception(env,&exception);
        return 0;
    }
    return (jlong)rotateImage;
}


#ifdef __cplusplus
}
#endif
