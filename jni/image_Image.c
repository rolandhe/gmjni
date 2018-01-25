#include "include/image_Image.h"
#include "include/common.h"

#ifdef __cplusplus
extern "C" {
#endif



/*
 * Class:     com_github_rolandhe_gm_Image
 * Method:    alocateImage
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_Image_alocateImage
  (JNIEnv *env, jclass cls, jlong hanlder)
{
    if (hanlder == 0)
    {
        return 0;
    }
    Image * imagePtr = AllocateImage( (const ImageInfo *)hanlder );
    return (jlong)imagePtr;
}

/*
 * Class:     com_github_rolandhe_gm_Image
 * Method:    cloneImage
 * Signature: (JJJI)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_Image_cloneImage
  (JNIEnv *env, jclass cls, jlong handler, jlong columns, jlong rows, jint orphan)
{
    if (handler == 0)
    {
        return 0;
    }
    Image * imagePtr = (Image*)handler;
    ExceptionInfo exception;
    GetExceptionInfo(&exception);
    Image * clonePtr = CloneImage( imagePtr, (const unsigned long) columns,
               (const unsigned long) rows, (const unsigned int) orphan,
              &exception);
    if (clonePtr == (Image*)NULL)
    {
        wrap_exception(env,&exception);
        return 0;
    }
    return (jlong)clonePtr;

}

/*
 * Class:     com_github_rolandhe_gm_Image
 * Method:    destoryImage
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_Image_destoryImage
  (JNIEnv *env, jclass cls, jlong handler)
  {
    if (handler == 0)
    {
        return;
    }
    DestroyImage((Image*)handler);
  }

/*
 * Class:     com_github_rolandhe_gm_Image
 * Method:    setupOutputName
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_Image_setupOutputName
  (JNIEnv * env, jclass cls, jlong imageHandler, jstring fileName)
  {
    if (imageHandler == 0)
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

    Image * imagePtr = (Image *)imageHandler;
    strcpy(imagePtr->filename,c_str);
    (*env)->ReleaseStringUTFChars(env, fileName, c_str);
  }
  /*
   * Class:     com_github_rolandhe_gm_Image
   * Method:    setupMagick
   * Signature: (JLjava/lang/String;)V
   */
  JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_Image_setupMagick
    (JNIEnv * env, jclass cls, jlong imageHandler, jstring format)
    {
    if (imageHandler == 0)
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

        Image * imagePtr = (Image *)imageHandler;
        strcpy(imagePtr->magick,c_str);
        (*env)->ReleaseStringUTFChars(env, format, c_str);
    }


/*
 * Class:     com_github_rolandhe_gm_Image
 * Method:    setupDelay
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_com_github_rolandhe_gm_Image_setupDelay
  (JNIEnv *env, jclass cls, jlong imageHandler, jint delay)
{
    if (imageHandler == 0)
    {
        return;
    }

    Image * imagePtr = (Image *)imageHandler;
    imagePtr->delay = (unsigned int)delay;

}

/*
 * Class:     com_github_rolandhe_gm_Image
 * Method:    recognizeFileFormat
 * Signature: ([B)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_github_rolandhe_gm_Image_recognizeFileFormat
  (JNIEnv *env, jclass cls, jbyteArray buf)
{
    size_t l;
    char* content = copyByteArray(env,buf,&l);
    char format[128];
    ExceptionInfo exception;
    GetExceptionInfo(&exception);
    MagickPassFail fail = GetMagickFileFormat((unsigned char*)content,l,format,128,&exception);
    MagickFree((void*)content);
    if (!fail)
    {
        wrap_exception(env,&exception);
        return NULL;
    }
    return (*env)->NewStringUTF(env,format);
}


/*
 * Class:     com_github_rolandhe_gm_Image
 * Method:    blobToImage
 * Signature: (J[B)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_Image_blobToImage
  (JNIEnv *env, jclass cls, jlong imageInfoHandler, jbyteArray buf)
{
    if (imageInfoHandler == 0)
    {
        return 0;
    }
    ImageInfo *imageInfoPtr = (ImageInfo*)imageInfoHandler;
    size_t l;
    char* content = copyByteArray(env,buf,&l);
    ExceptionInfo exception;
    GetExceptionInfo(&exception);
    Image *imagePtr = BlobToImage(imageInfoPtr, content, l, &exception);
    MagickFree((void*)content);
    if(imagePtr == (Image*)NULL)
    {
        wrap_exception(env,&exception);
        return 0;
    }
    return (jlong)imagePtr;

}

/*
 * Class:     com_github_rolandhe_gm_Image
 * Method:    readImage
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_Image_readImage
  (JNIEnv *env, jclass cls, jlong imageInfoHandler)
{
    if (imageInfoHandler == 0)
    {
        return 0;
    }
    ImageInfo *imageInfoPtr = (ImageInfo*)imageInfoHandler;
    ExceptionInfo exception;
    GetExceptionInfo(&exception);
    Image * imagePtr = ReadImage(imageInfoPtr, &exception);
    if (imagePtr == (Image *) NULL)
    {
        wrap_exception(env,&exception);
        return 0;
    }
    return (jlong)imagePtr;
}

/*
 * Class:     com_github_rolandhe_gm_Image
 * Method:    writeImage
 * Signature: (JJ)J
 */
JNIEXPORT jboolean JNICALL Java_com_github_rolandhe_gm_Image_writeImage
  (JNIEnv *env, jclass cls, jlong imageInfoHandler, jlong imageHandler)
  {
    if (imageInfoHandler == 0 || imageHandler == 0)
    {
        return (jboolean)0;
    }
    ImageInfo* imageInfoPtr =(ImageInfo*)imageInfoHandler;
    Image * imagePtr = (Image*)imageHandler;
    if (!WriteImage (imageInfoPtr,imagePtr)){
        return (jboolean)0;
    }
    return (jboolean)1;
  }

/*
 * Class:     com_github_rolandhe_gm_Image
 * Method:    imageToBlob
 * Signature: (JJ)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_github_rolandhe_gm_Image_imageToBlob
  (JNIEnv *env, jclass cls, jlong imageInfoHandler, jlong imageHandler)
{
    if (imageInfoHandler == 0 || imageHandler == 0)
    {
        return NULL;
    }
    ImageInfo* imageInfoPtr =(ImageInfo*)imageInfoHandler;
    Image * imagePtr = (Image*)imageHandler;
    ExceptionInfo exception;
    GetExceptionInfo(&exception);
    size_t l;
    char * blob = (char*)ImageToBlob( imageInfoPtr, imagePtr, &l,&exception);
    if (blob == NULL)
    {
        wrap_exception(env,&exception);
        return NULL;
    }

    jbyteArray result =  createByteArray(env,blob,l);
    MagickFree((void*)blob);
    return result;
}


/*
 * Class:     com_github_rolandhe_gm_Image
 * Method:    getImageColumns
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_Image_getImageColumns
  (JNIEnv *env, jclass cls, jlong imageHandler)
{
    if (imageHandler == 0)
    {
        return 0;
    }
    Image* imagePtr = (Image*)imageHandler;
    return (jlong)(imagePtr->columns);
}

/*
 * Class:     com_github_rolandhe_gm_Image
 * Method:    getImageRows
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_github_rolandhe_gm_Image_getImageRows
  (JNIEnv *env, jclass cls, jlong imageHandler)
{
    if (imageHandler == 0)
    {
        return 0;
    }
    Image* imagePtr = (Image*)imageHandler;
    return (jlong)(imagePtr->rows);
}

/*
 * Class:     com_github_rolandhe_gm_Image
 * Method:    isPaletteImage
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_com_github_rolandhe_gm_Image_isPaletteImage
  (JNIEnv *env, jclass cls, jlong imageHandler)
  {
      if (imageHandler == 0)
      {
          return (jboolean)0;
      }
      Image* imagePtr = (Image*)imageHandler;
      ExceptionInfo exception;
      GetExceptionInfo(&exception);
      MagickBool isPaletteImage =  IsPaletteImage(imagePtr,&exception);

      if(exception.reason != (char*)NULL)
      {
            wrap_exception(env,&exception);
            return (jboolean)0;
      }

      return (jboolean)isPaletteImage;
  }

#ifdef __cplusplus
}
#endif
