package com.github.rolandhe.gm;

/**
 * 封装GM库Image struct, Image的重要变量以java native方法暴露
 *
 * Created by hexiufeng on 2017/12/25.
 */
public class Image extends GmEntity {
  protected Image(long handler) {
    super(handler);
  }


  /**
   * 分配Image结构内存资源
   *
   * @param imageInfo GM ImageInfo struct资源
   * @return 分配的Image 句柄
   */
  private static native long alocateImage(long imageInfo);

  /**
   *
   * clone Image资源
   *
   * @param image 需要clone的Image句柄
   * @param columns
   * @param rows
   * @param orphan
   * @return
   * @throws GmExcetpion
   */
  private static native long cloneImage(long image,long columns,long rows,int orphan) throws GmExcetpion;

  /**
   *
   * 释放资源
   *
   * @param handler
   */
  private static native void destoryImage(long handler);

  /**
   * 设置Image.filename, 该属性用于指定Image需要输出的文件名称
   *
   * @param handler
   * @param outputName
   */
  private static native void setupOutputName(long handler, String outputName);

  /**
   * 设置Image.magick, 该属性用于指定图片类型，比如JPG，PNG，GIF等
   *
   * @param handler
   * @param format
   */
  private static native void setupMagick(long handler, String format);

  /**
   * 设置Image.delay, 该属性用于拼装GIF时指定图片播放的延迟时间
   *
   * @param handler
   * @param delay
   */
  private static native void setupDelay(long handler, int delay);

  /**
   *
   * 根据图片文件的头部内容，识别图片文件的类型(GIF,JPG等).
   * 一般选取2k头部内容即可
   *
   * @param buf 图片文件头部内容，一般2k即可
   * @return
   * @throws GmExcetpion
   */
  private static native String recognizeFileFormat(byte[] buf) throws GmExcetpion;

  /**
   * 把Image描述的图片输出成指定格式的图片，图片被存储到内存中。
   *
   * @param imageInfo
   * @param buf
   * @return
   * @throws GmExcetpion
   */
  private static native long blobToImage(long imageInfo,byte[] buf) throws GmExcetpion;

  /**
   * 从文件中读取图片内存并转出成Image 结构资源，文件路径由ImageInfo.filename指定
   *
   * @param imageInfo
   * @return
   * @throws GmExcetpion
   */
  private static native long readImage(long imageInfo) throws GmExcetpion;

  /**
   *
   * 输出Image描述的图片到文件，文件类型由ImageInfo.magick指定，输出文件路径由ImageInfo.filename指定。
   * 本方法可以用于转换图片类型。
   *
   * @param imageInfo
   * @param image
   * @return
   */
  private static native boolean writeImage(long imageInfo, long image);

  /**
   *
   * 输出Image描述的图片到内存。功能与writeImage类似
   *
   * @param imageInfo
   * @param image
   * @return
   * @throws GmExcetpion
   */
  private static native byte[] imageToBlob(long imageInfo, long image) throws GmExcetpion;

  /**
   *
   * 读取图片的宽度
   *
   * @param image
   * @return
   */
  private static native long getImageColumns(long image);

  /**
   *
   * 读取图片的高度
   *
   * @param image
   * @return
   */
  private static native long getImageRows(long image);

  /**
   * 图片是否是调色板图片
   *
   * @param imageHandler
   * @return
   */
  private static native boolean isPaletteImage(long imageHandler);



  /**
   * 封装alocateImage，不推荐使用，请使用{@link #factory(byte[])} 和 {@link #factory(String)}
   *
   * @param imageInfo
   * @return
   */
  public static Image factory(ImageInfo imageInfo) {
    return new Image(alocateImage(imageInfo.getHandler()));
  }

  /**
   *
   * 封装cloneImage，不推荐使用，请使用{@link #factory(byte[])} 和 {@link #factory(String)}
   *
   * @param image
   * @param columns
   * @param rows
   * @param orphan
   * @return
   * @throws GmExcetpion
   */
  public static Image factory(Image image, long columns,long rows,int orphan) throws GmExcetpion{
    long h = cloneImage(image.getHandler(),columns,rows,orphan);
    return new Image(h);
  }

  /**
   *
   * 根据图片内容分配对应的Image资源
   *
   * @param buf
   * @return
   * @throws GmExcetpion
   */
  public static Image factory(byte[] buf) throws GmExcetpion {
    String format = recognizeFileFormat(buf);
    ImageInfo imageInfo = ImageInfo.factory(null);
    imageInfo.confFormat(format);
    try{
      long h =  blobToImage(imageInfo.getHandler(),buf);
      return new Image(h);
    }finally {
      imageInfo.destory();
    }
  }

  /**
   * 根据图片文件分配对应的Image资源
   *
   * @param fileName
   * @return
   * @throws GmExcetpion
   */
  public static Image factory(String fileName) throws GmExcetpion {
    ImageInfo imageInfo = ImageInfo.factory(null);
    imageInfo.confFileName(fileName);
    try{
      long h =  readImage(imageInfo.getHandler());
      return new Image(h);
    }finally {
      imageInfo.destory();
    }
  }

  /**
   * 根据图片头部内容识别图片类型，一般2k即可
   *
   * @param buf
   * @return
   */
  public static String getMagickFileFormat(byte[] buf) {
    return recognizeFileFormat(buf);
  }

  /**
   * 存储当前Image到指定的文件，可以指定输出的图片类型
   *
   * @param outFileName
   * @param format 需要输出的图片类型
   * @throws GmExcetpion
   */
  public void toFile(String outFileName,String format) throws GmExcetpion {
    ImageInfo info = ImageInfo.factory(null);
    info.confAdjoin(ImageInfo.MAGICK_TRUE);
    if(format != null && !format.isEmpty()) {
      setupMagick(getHandler(),format);
    }
    setupOutputName(getHandler(),outFileName);
    try {
      writeImage(info.getHandler(),this.getHandler());
    }finally {
      info.destory();
    }
  }

  /**
   * 存储当前Image到内存，可以指定输出的图片类型，类似{@link #toFile(String, String)}
   *
   * @param format
   * @return
   * @throws GmExcetpion
   */
  public byte[] toBlob(String format) throws GmExcetpion {
    ImageInfo info = ImageInfo.factory(null);
    info.confAdjoin(ImageInfo.MAGICK_TRUE);
    if(format != null && !format.isEmpty()) {
      setupMagick(getHandler(),format);
    }

    try {
     return imageToBlob(info.getHandler(),this.getHandler());
    }finally {
      info.destory();
    }
  }



  public  long getImageWidth() {
    return getImageColumns(getHandler());
  }

  public long getImageHeight(){
    return getImageRows(getHandler());
  }

  public void setDelay( int delay) {
    setupDelay(getHandler(),delay);
  }

  public  boolean isPaletteImage() {
    return isPaletteImage(getHandler());
  }

  @Override
  protected void destroyHandler(long handler) {
    destoryImage(handler);
  }
}
