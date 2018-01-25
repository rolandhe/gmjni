package com.github.rolandhe.gm;

/**
 * 封装ImageInfo 结构
 *
 * Created by hexiufeng on 2017/12/21.
 */
public class ImageInfo extends GmEntity {
  public static final int MAGICK_TRUE = 1;
  public static final int MAGICK_FALSE = 0;

  private ImageInfo(long handler) {
    super(handler);
  }


  /**
   *
   * clone or create ImageInfo
   *
   * @param handler, 0 indicates create ImageInfo
   * @return
   */
  private static native long cloneImageInfo(long handler);

  private static native void destroyImageInfo(long handler);

  /**
   *
   * 设置ImageInfo.magick, 指定图片类型
   *
   * @param handler
   * @param format
   */
  private static native void setupFormat(long handler, String format);

  /**
   *
   * 设置ImageInfo.filename,一般用于指定输出文件路径
   *
   * @param handler
   * @param fileName
   */
  private static native void setupFileName(long handler, String fileName);

  /**
   *
   * 设置ImageInfo.adjoin, 用于分解GIF成多个图片
   *
   * @param handler
   * @param adjoin
   */
  private static native void setupAdjoin(long handler,int adjoin);


  public static ImageInfo factory(ImageInfo info) {
    if (info == null) {
      return new ImageInfo(cloneImageInfo(0));
    }
    return new ImageInfo(cloneImageInfo(info.getHandler()));
  }


  @Override
  protected void destroyHandler(long handler) {
    destroyImageInfo(handler);
  }

  public void confFormat(String format) {
    setupFormat(getHandler(),format);
  }
  public  void confFileName(String fileName) {
    setupFileName(getHandler(),fileName);
  }

  public void confAdjoin(int adjoin) {
    setupAdjoin(getHandler(),adjoin);
  }
}