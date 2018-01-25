package com.github.rolandhe.gm;

/**
 *
 * 修改图片功能
 *
 * Created by hexiufeng on 2018/1/2.
 */
public class ImageProcessor extends GmBase {

  /**
   * 获取文本水印的尺寸
   *
   * @param imageHandler
   * @param drawInfo
   * @return
   */
  private static native long obtainTypeMetrics(long imageHandler,long drawInfo);

  /**
   * 封装AnnotateIamge, 一般不用，打文本水印使用{@link #drawTextOnImage(long, long)}
   *
   * @param imageHandler
   * @param drawInfo
   * @return
   */
  private static native boolean annotateImage(long imageHandler,long drawInfo);

  /**
   * 透明化指定的颜色
   *
   * @param imageHandler
   * @param color
   * @param opacity
   * @return
   */
  private static native boolean transparentImage(long imageHandler,String color,long opacity);

  /**
   * 打文本水印
   *
   * @param imageHandler
   * @param drawInfo
   * @return
   */
  private static native boolean drawTextOnImage(long imageHandler,long drawInfo);

  public static TypeMetric getTypeMetrics(Image image, DrawInfo drawInfo) {
    long tmHandler = obtainTypeMetrics(image.getHandler(), drawInfo.getHandler());
    if (tmHandler == 0) {
      return null;
    }
    return new TypeMetric(tmHandler);
  }

  /**
   * 获取文本水印的尺寸
   *
   * @param image
   * @param fontSize
   * @param font
   * @param text
   * @return
   */
  public static TypeMetric getTypeMetrics(Image image,double fontSize,String font,String text) {
    DrawInfo drawInfo = create(fontSize,font,null,null);
    drawInfo.setText(text);
    try {
      return getTypeMetrics(image, drawInfo);
    }finally {
      drawInfo.destory();
    }
  }

  /**
   * 封装AnnotateIamge, 一般不用，打文本水印使用{@link #doDrawTextOnImage(Image, double, String, String, String, long, long)}
   *
   * @param image
   * @param drawInfo
   * @return
   */
  public static boolean doAnnotateImage(Image image, DrawInfo drawInfo) {
    return annotateImage(image.getHandler(),drawInfo.getHandler());
  }


  public static boolean doAnnotateImage(Image image,double fontSize,String font,String textColor,String text,long x,long y) {
    String primitive = String.format("text %d,%d '%s'",x,y,text);
    DrawInfo drawInfo = create(fontSize,font,textColor,primitive);
    try {
      return doAnnotateImage(image, drawInfo);
    }finally {
      drawInfo.destory();
    }
  }

  /**
   * 打文本水印
   *
   * @param image
   * @param drawInfo
   * @return
   */
  public static boolean doDrawTextOnImage(Image image, DrawInfo drawInfo) {
    return drawTextOnImage(image.getHandler(),drawInfo.getHandler());
  }

  /**
   *
   * 打文本水印
   *
   * @param image
   * @param fontSize
   * @param font
   * @param textColor
   * @param text
   * @param x
   * @param y
   * @return
   */
  public static boolean doDrawTextOnImage(Image image,double fontSize,String font,String textColor,String text,long x,long y) {
    String primitive = String.format("text %d,%d '%s'",x,y,text);
    DrawInfo drawInfo = create(fontSize,font,textColor,primitive);
    try {
      return doDrawTextOnImage(image, drawInfo);
    }finally {
      drawInfo.destory();
    }
  }

  /**
   * 透明化指定的颜色
   *
   * @param image
   * @param color
   * @param opacity
   * @return
   */
  public  static boolean doTransparentImage(Image image,String color, long opacity){
    return transparentImage(image.getHandler(),color,opacity);
  }

  private static DrawInfo create(double fontSize,String font,String textColor,String primitive) {
    DrawInfo info = DrawInfo.factory();
    info.setupTextFeature(fontSize, font, textColor,primitive);
    return info;
  }
}
