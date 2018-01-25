package com.github.rolandhe.gm;

/**
 * 旋转图片
 *
 * Created by hexiufeng on 2017/12/25.
 */
public class Shear extends GmBase {
  private static native long rotateImage(long image, double degree) throws GmExcetpion;

  public static Image doRotateImage(Image image, double degree) throws GmExcetpion {
    long handler = rotateImage(image.getHandler(),degree);
    return new Image(handler);
  }

}
