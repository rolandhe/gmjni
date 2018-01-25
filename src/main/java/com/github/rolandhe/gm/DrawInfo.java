package com.github.rolandhe.gm;

/**
 *
 * 封装GM DrawInfo struct，用于在图片上绘制，比如打文本水印
 *
 * Created by hexiufeng on 2018/1/2.
 */
public class DrawInfo extends GmEntity {
  public enum DecorationType{
    NoDecoration,
    UnderlineDecoration,
    OverlineDecoration,
    LineThroughDecoration;
  }
  public enum GravityType{
    ForgetGravity,
    NorthWestGravity,
    NorthGravity,
    NorthEastGravity,
    WestGravity,
    CenterGravity,
    EastGravity,
    SouthWestGravity,
    SouthGravity,
    SouthEastGravity,
    StaticGravity;
  }
  protected DrawInfo(long handler) {
    super(handler);
  }

  private static native long cloneDrawInfo(long handler);
  private  static native void destroyDrawInfo(long handler);

  // setup draw text feature
  private static native void setBoxColor(long handler,String color) throws  GmExcetpion;
  private static native void setDecorate(long handler,int decorate);
  private static native void setDensity(long handler,String density);
  private static native void setFill(long handler, String color) throws  GmExcetpion;
  private static native void setFont(long handler,String font);
  private static native void setPointsize(long handler,double size);
  private static native void setGravity(long handler, int gravity);
  private static native void setPrimitive(long handler, String primitive);
  private static native void setText(long handler, String text);


  public static DrawInfo factory() {
    return new DrawInfo(cloneDrawInfo(0));
  }
  public static DrawInfo factory(long handler) {
    if(handler == 0) {
      return factory();
    }
    return new DrawInfo(cloneDrawInfo(handler));
  }

  @Override
  protected void destroyHandler(long handler) {
    destroyDrawInfo(handler);
  }

  /**
   *
   * 设置打文本水印时的常用属性
   *
   * @param fontSize
   * @param font
   * @param textColor
   * @param primitive
   */
  public void setupTextFeature(double fontSize,String font,String textColor,String primitive) {
    setPointsize(getHandler(),fontSize);
    if(font != null) {
      setFont(getHandler(),font);
    }

    if(textColor != null) {
      setFill(getHandler(),textColor);
    }
    if(primitive != null) {
      setPrimitive(getHandler(),primitive);
    }
  }

  /**
   *
   * 设置文本水印的背景色
   *
   * @param bkColor
   */
  public void setTextBackgroudColor(String bkColor) {
    setBoxColor(getHandler(),bkColor);
  }

  /**
   * 设置文本水印的密度
   *
   * @param density
   */
  public void setTextDensity(String density) {
    setDensity(getHandler(),density);
  }

  /**
   * 设置文本水印的装饰属性
   *
   * @param decorationType
   */
  public void setTextDecorate(DecorationType decorationType) {
    setDecorate(getHandler(),decorationType.ordinal());
  }

  public void setGravity(GravityType gravityType) {
    setGravity(getHandler(),gravityType.ordinal());
  }

  /**
   *
   * 文本水印
   *
   * @param text
   */
  void setText(String text) {
    setText(getHandler(),text);
  }

}
