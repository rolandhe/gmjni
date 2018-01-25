#include "include/image_DrawInfo.h"
#include "include/common.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * Class:     com_github_rolandhe_gm_DrawInfo
 * Method:    cloneDrawInfo
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_DrawInfo_cloneDrawInfo
  (JNIEnv *env, jclass cls, jlong drawInfoHandler)
 {
     DrawInfo * drawInfoPtr;
     if(drawInfoHandler == 0)
     {
        drawInfoPtr = (DrawInfo*)NULL;
     }
     else
     {
        drawInfoPtr = (DrawInfo*)drawInfoHandler;
     }
     return (jlong)CloneDrawInfo((ImageInfo *) NULL,drawInfoPtr);
 }

/*
 * Class:     com_github_rolandhe_gm_DrawInfo
 * Method:    destroyDrawInfo
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_DrawInfo_destroyDrawInfo
  (JNIEnv *env, jclass cls, jlong drawInfoHandler)
  {
    DrawInfo * drawInfoPtr;
    if(drawInfoHandler == 0)
    {
      return;
    }
    else
    {
      drawInfoPtr = (DrawInfo*)drawInfoHandler;
    }
    DestroyDrawInfo(drawInfoPtr);
  }

/*
 * Class:     com_github_rolandhe_gm_DrawInfo
 * Method:    setBoxColor
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_DrawInfo_setBoxColor
  (JNIEnv *env, jclass cls, jlong drawInfoHandler, jstring color)
{
    DrawInfo * drawInfoPtr;
    if(drawInfoHandler == 0)
    {
        return;
    }
    else
    {
        drawInfoPtr = (DrawInfo*)drawInfoHandler;
    }

    const char *c_str = NULL;
    jboolean isCopy;
    c_str = (*env)->GetStringUTFChars(env, color, &isCopy);
    if (!isCopy)
    {
        return;
    }

    ExceptionInfo exception;
    GetExceptionInfo(&exception);
    if(!QueryColorDatabase(c_str,&(drawInfoPtr->undercolor),&exception))
    {
        wrap_exception(env, &exception);
    }
    (*env)->ReleaseStringUTFChars(env, color, c_str);
}

/*
 * Class:     com_github_rolandhe_gm_DrawInfo
 * Method:    setDecorate
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_DrawInfo_setDecorate
  (JNIEnv *env, jclass cls, jlong drawInfoHandler, jint decorate)
{
    DrawInfo * drawInfoPtr;
    if(drawInfoHandler == 0)
    {
      return;
    }
    else
    {
      drawInfoPtr = (DrawInfo*)drawInfoHandler;
    }
    drawInfoPtr->decorate = (int)decorate;
}

/*
 * Class:     com_github_rolandhe_gm_DrawInfo
 * Method:    setDensity
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_DrawInfo_setDensity
  (JNIEnv *env, jclass cls, jlong drawInfoHandler, jstring density)
{
    DrawInfo * drawInfoPtr;
    if(drawInfoHandler == 0)
    {
        return;
    }
    else
    {
        drawInfoPtr = (DrawInfo*)drawInfoHandler;
    }
    const char *c_str = NULL;
    jboolean isCopy;
    c_str = (*env)->GetStringUTFChars(env, density, &isCopy);
    if (!isCopy)
    {
        return;
    }

    drawInfoPtr->density =(char*)MagickMalloc(strlen(c_str) + 1);
    strcpy(drawInfoPtr->density ,c_str);
    (*env)->ReleaseStringUTFChars(env, density, c_str);
}

/*
 * Class:     com_github_rolandhe_gm_DrawInfo
 * Method:    setFill
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_DrawInfo_setFill
  (JNIEnv *env, jclass cls, jlong drawInfoHandler, jstring fill)
  {
    DrawInfo * drawInfoPtr;
    if(drawInfoHandler == 0)
    {
       return;
    }
    else
    {
       drawInfoPtr = (DrawInfo*)drawInfoHandler;
    }
    const char *c_str = NULL;
    jboolean isCopy;
    c_str = (*env)->GetStringUTFChars(env, fill, &isCopy);
    if (!isCopy)
    {
       return;
    }

    ExceptionInfo exception;
    GetExceptionInfo(&exception);
    if(!QueryColorDatabase(c_str,&(drawInfoPtr->fill),&exception))
    {
        wrap_exception(env, &exception);
    }
    (*env)->ReleaseStringUTFChars(env, fill, c_str);
  }

/*
 * Class:     com_github_rolandhe_gm_DrawInfo
 * Method:    setFont
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_DrawInfo_setFont
  (JNIEnv *env, jclass cls, jlong drawInfoHandler, jstring font)
{
    DrawInfo * drawInfoPtr;
    if(drawInfoHandler == 0)
    {
       return;
    }
    else
    {
       drawInfoPtr = (DrawInfo*)drawInfoHandler;
    }
    const char *c_str = NULL;
    jboolean isCopy;
    c_str = (*env)->GetStringUTFChars(env, font, &isCopy);
    if (!isCopy)
    {
       return;
    }

    drawInfoPtr->font =(char*)MagickMalloc(strlen(c_str) + 1);
    strcpy(drawInfoPtr->font ,c_str);
    (*env)->ReleaseStringUTFChars(env, font, c_str);
}

/*
 * Class:     com_github_rolandhe_gm_DrawInfo
 * Method:    setPointsize
 * Signature: (JD)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_DrawInfo_setPointsize
  (JNIEnv * env, jclass cls, jlong drawInfoHandler, jdouble pointSize)
  {
      DrawInfo * drawInfoPtr;
      if(drawInfoHandler == 0)
      {
         return;
      }
      else
      {
         drawInfoPtr = (DrawInfo*)drawInfoHandler;
      }
      drawInfoPtr->pointsize = pointSize;
  }

/*
 * Class:     com_github_rolandhe_gm_DrawInfo
 * Method:    setGravity
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_DrawInfo_setGravity
  (JNIEnv * env, jclass cls, jlong drawInfoHandler, jint gravity)
{
      DrawInfo * drawInfoPtr;
      if(drawInfoHandler == 0)
      {
         return;
      }
      else
      {
         drawInfoPtr = (DrawInfo*)drawInfoHandler;
      }
      drawInfoPtr->gravity = (int)gravity;
}

/*
 * Class:     com_github_rolandhe_gm_DrawInfo
 * Method:    setPrimitive
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_DrawInfo_setPrimitive
  (JNIEnv *env, jclass cls, jlong drawInfoHandler, jstring primitive)
{
    DrawInfo * drawInfoPtr;
    if(drawInfoHandler == 0)
    {
       return;
    }
    else
    {
       drawInfoPtr = (DrawInfo*)drawInfoHandler;
    }
    const char *c_str = NULL;
    jboolean isCopy;
    c_str = (*env)->GetStringUTFChars(env, primitive, &isCopy);
    if (!isCopy)
    {
       return;
    }

    drawInfoPtr->primitive =(char*)MagickMalloc(strlen(c_str) + 1);
    strcpy(drawInfoPtr->primitive ,c_str);
    (*env)->ReleaseStringUTFChars(env, primitive, c_str);
}


/*
 * Class:     com_github_rolandhe_gm_DrawInfo
 * Method:    setText
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_DrawInfo_setText
   (JNIEnv *env, jclass cls, jlong drawInfoHandler, jstring text)
  {
      DrawInfo * drawInfoPtr;
      if(drawInfoHandler == 0)
      {
         return;
      }
      else
      {
         drawInfoPtr = (DrawInfo*)drawInfoHandler;
      }
      const char *c_str = NULL;
      jboolean isCopy;
      c_str = (*env)->GetStringUTFChars(env, text, &isCopy);
      if (!isCopy)
      {
         return;
      }

      drawInfoPtr->text =(char*)MagickMalloc(strlen(c_str) + 1);
      strcpy(drawInfoPtr->text ,c_str);
      (*env)->ReleaseStringUTFChars(env, text, c_str);
  }

#ifdef __cplusplus
}
#endif