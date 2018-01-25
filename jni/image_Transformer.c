#include "include/image_Transformer.h"
#include "include/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Class:     com_github_rolandhe_gm_Transformer
 * Method:    cropImage
 * Signature: (JJJJJ)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_Transformer_cropImage
  (JNIEnv *env, jclass cls, jlong imageHandler, jlong columns, jlong rows, jlong x, jlong y)
  {
    if (imageHandler == 0)
    {
        return 0;
    }
    Image* imagePtr = (Image*)imageHandler;
    ExceptionInfo exception;
    GetExceptionInfo(&exception);
    RectangleInfo rect;
    rect.width = (unsigned int)columns;
    rect.height = (unsigned int)rows;
    rect.x = (int)x;
    rect.y = (int)y;
    Image* cropImage = CropImage( imagePtr, &rect, &exception );
    if(cropImage == (Image*)NULL)
    {
        wrap_exception(env,&exception);
        return 0;
    }
    return (jlong)cropImage;
  }


/*
 * Class:     com_github_rolandhe_gm_Transformer
 * Method:    chopImage
 * Signature: (JJJJJ)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_Transformer_chopImage
  (JNIEnv *env, jclass cls, jlong imageHandler, jlong columns, jlong rows, jlong x, jlong y)
  {
        if (imageHandler == 0)
        {
          return 0;
        }
        Image* imagePtr = (Image*)imageHandler;
        ExceptionInfo exception;
        GetExceptionInfo(&exception);
        RectangleInfo rect;
        rect.width = (unsigned int)columns;
        rect.height = (unsigned int)rows;
        rect.x = (int)x;
        rect.y = (int)y;
        Image* chopImage = ChopImage( imagePtr, &rect, &exception );
        if(chopImage == (Image*)NULL)
        {
          wrap_exception(env,&exception);
          return 0;
        }
        return (jlong)chopImage;
  }

/*
 * Class:     com_github_rolandhe_gm_Transformer
 * Method:    extentImage
 * Signature: (JJJJJ)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_Transformer_extentImage
  (JNIEnv *env, jclass cls, jlong imageHandler, jlong columns, jlong rows, jlong x, jlong y)
  {
        if (imageHandler == 0)
        {
            return 0;
        }
        Image* imagePtr = (Image*)imageHandler;
        ExceptionInfo exception;
        GetExceptionInfo(&exception);
        RectangleInfo rect;
        rect.width = (unsigned int)columns;
        rect.height = (unsigned int)rows;
        rect.x = (int)x;
        rect.y = (int)y;
        Image* extentImage = ExtentImage( imagePtr, &rect, &exception);
        if(extentImage == (Image*)NULL)
        {
            wrap_exception(env,&exception);
            return 0;
        }
        return (jlong)extentImage;
  }

/*
 * Class:     com_github_rolandhe_gm_Transformer
 * Method:    coalesceImages
 * Signature: ([J)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_Transformer_coalesceImages
  (JNIEnv *env, jclass cls, jlongArray imageHandlerArray)
  {
        Image* imageList = convertImageHandlersToIamgeList(env,imageHandlerArray);
        ExceptionInfo exception;
        GetExceptionInfo(&exception);
        Image*   coalesceImage = CoalesceImages(imageList,&exception);
        if(coalesceImage == (Image*)NULL)
        {
            wrap_exception(env,&exception);
            return 0;
        }
        return (jlong)coalesceImage;
  }

#ifdef __cplusplus
}
#endif
