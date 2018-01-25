package com.github.rolandhe.gm;

/**
 *
 * 封装GM TypeMetric，一般用于计算输出文本的在图片上的尺寸
 *
 * Created by hexiufeng on 2018/1/2.
 */
public class TypeMetric extends GmEntity {
  protected TypeMetric(long handler) {
    super(handler);
  }

  private static native double getWidth(long handler);
  private static native double getHeight(long handler);
  private static native double getAscent(long handler);
  private static native double getDescent(long handler);
  private static native void destoryTypeMetric(long handler);

  @Override
  protected void destroyHandler(long handler) {
    destoryTypeMetric(handler);
  }

  public double getWidth() {
    return getWidth(getHandler());
  }

  public double getHeight( ) {
    return getHeight(getHandler());
  }
  public double getAscent() {
    return getAscent(getHandler());
  }
  public double getDescent() {
    return getDescent(getHandler());
  }
}
