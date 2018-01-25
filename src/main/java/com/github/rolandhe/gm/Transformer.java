package com.github.rolandhe.gm;

/**
 * 裁剪图片
 *
 * Created by hexiufeng on 2017/12/25.
 */
public class Transformer extends GmBase {
  private static native long cropImage(long image, long columns,long rows, long x,long y) throws GmExcetpion;
  private static native long chopImage(long image, long columns,long rows, long x,long y) throws GmExcetpion;
  private static native long extentImage(long image, long columns,long rows, long x,long y) throws GmExcetpion;
  private static native long coalesceImages(long[] imageArray) throws GmExcetpion;

  /**
   * 裁剪图片
   *
   * @param image
   * @param rect
   * @return
   * @throws GmExcetpion
   */
  public static Image doCropImage(Image image, Rect rect) throws GmExcetpion {
    long handler = cropImage(image.getHandler(),rect.getWidth(), rect.getHeight(), rect.getX(),rect.getY());
    return new Image(handler);
  }

  public static Image doChopImage(Image image, Rect rect) throws GmExcetpion {
    long handler = chopImage(image.getHandler(),rect.getWidth(), rect.getHeight(), rect.getX(),rect.getY());
    return new Image(handler);
  }

  public static Image doExtentImage(Image image, Rect rect) throws GmExcetpion {
    long handler = extentImage(image.getHandler(),rect.getWidth(), rect.getHeight(), rect.getX(),rect.getY());
    return new Image(handler);
  }

  public static Image doCoalesceImages(Image[] imageArray) throws GmExcetpion {
    long[] handleArray = new long[imageArray.length];
    int index = 0;
    for(Image image : imageArray) {
      handleArray[index++] = image.getHandler();
    }
    long handler = coalesceImages(handleArray);
    return new Image(handler);
  }
}
