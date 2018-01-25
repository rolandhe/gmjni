package com.github.rolandhe.gm;

/**
 * 图片缩放
 *
 * Created by hexiufeng on 2017/12/25.
 */
public class Resizer extends GmBase{

  /**
   * 缩略图，可能不按指定的大小，底层会按照长宽比计算出优化的大小
   *
   * @param image
   * @param columns
   * @param rows
   * @return
   * @throws GmExcetpion
   */
  private static native long thumbnailImage(long image, long columns,long rows) throws GmExcetpion;

  /**
   *
   * 严格按指定大小缩放图片
   *
   * @param image
   * @param columns
   * @param rows
   * @return
   * @throws GmExcetpion
   */
  private static native long scaleImage(long image, long columns,long rows) throws GmExcetpion;

  /**
   *
   * 严格按指定大小缩放图片,质量不高，但速度快
   *
   * @param image
   * @param columns
   * @param rows
   * @return
   * @throws GmExcetpion
   */
  private static native long sampleImage(long image, long columns,long rows) throws GmExcetpion;

  /**
   *
   * 严格控制缩放图片
   *
   * @param image
   * @param columns
   * @param rows
   * @param filterTypes
   * @param blur
   * @return
   * @throws GmExcetpion
   */
  private static native long resizeImage(long image, long columns,long rows,int filterTypes,double blur) throws GmExcetpion;


  /**
   * 缩略图，可能不按指定的大小，底层会按照长宽比计算出优化的大小
   *
   * @param image
   * @param columns
   * @param rows
   * @return
   * @throws GmExcetpion
   */
  public static Image doThumbnailImage(Image image,long columns,long rows) throws GmExcetpion {
    long handler = thumbnailImage(image.getHandler(),columns,rows);
    return new Image(handler);
  }

  /**
   * 严格按指定大小缩放图片
   *
   * @param image
   * @param columns
   * @param rows
   * @return
   * @throws GmExcetpion
   */
  public static  Image doScaleImage(Image image,long columns,long rows) throws GmExcetpion {
    long handler = scaleImage(image.getHandler(),columns,rows);
    return new Image(handler);
  }

  /**
   * 严格按指定大小缩放图片,质量不高，但速度快
   *
   * @param image
   * @param columns
   * @param rows
   * @return
   * @throws GmExcetpion
   */
  public static Image doSampleImage(Image image, long columns,long rows) throws GmExcetpion {
    long handler = sampleImage(image.getHandler(),columns,rows);
    return new Image(handler);
  }

  /**
   * 严格控制缩放图片
   *
   * @param image
   * @param columns
   * @param rows
   * @param filterTypes
   * @param blur
   * @return
   * @throws GmExcetpion
   */
  public static Image doResizeImage(Image image, long columns,long rows, FilterTypes filterTypes, double blur) throws
          GmExcetpion {
    long handler = resizeImage(image.getHandler(),columns,rows,filterTypes.ordinal(),blur);
    return new Image(handler);
  }
}
