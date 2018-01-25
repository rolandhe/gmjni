package com.github.rolandhe.gm;

/**
 *
 * 组装图片功能
 *
 * Created by hexiufeng on 2018/1/2.
 */
public class Composite extends GmBase {
  public enum CompositeOperator {
    UndefinedCompositeOp,
    OverCompositeOp,
    InCompositeOp,
    OutCompositeOp,
    AtopCompositeOp,
    XorCompositeOp,
    PlusCompositeOp,
    MinusCompositeOp,
    AddCompositeOp,
    SubtractCompositeOp,
    DifferenceCompositeOp,
    MultiplyCompositeOp,
    BumpmapCompositeOp,
    CopyCompositeOp,
    CopyRedCompositeOp,
    CopyGreenCompositeOp,
    CopyBlueCompositeOp,
    CopyOpacityCompositeOp,
    ClearCompositeOp,
    DissolveCompositeOp,
    DisplaceCompositeOp,
    ModulateCompositeOp,
    ThresholdCompositeOp,
    NoCompositeOp,
    DarkenCompositeOp,
    LightenCompositeOp,
    HueCompositeOp,
    SaturateCompositeOp,
    ColorizeCompositeOp,
    LuminizeCompositeOp,
    ScreenCompositeOp,
    OverlayCompositeOp,
    CopyCyanCompositeOp,
    CopyMagentaCompositeOp,
    CopyYellowCompositeOp,
    CopyBlackCompositeOp,
    DivideCompositeOp,
    HardLightCompositeOp,
    ExclusionCompositeOp,
    ColorDodgeCompositeOp,
    ColorBurnCompositeOp,
    SoftLightCompositeOp,
    LinearBurnCompositeOp,
    LinearDodgeCompositeOp,
    LinearLightCompositeOp,
    VividLightCompositeOp,
    PinLightCompositeOp,
    HardMixCompositeOp;
  }

  /**
   *
   * 分层叠加图片
   *
   * @param canvasImageHandler
   * @param compose
   * @param compositeImageHandler
   * @param x
   * @param y
   * @return
   */
  private static native boolean compositeImage( long canvasImageHandler,  int compose,
                               long compositeImageHandler,  long x,long y );

  /**
   *
   * 拼接图片
   *
   * @param imageHandlers
   * @param stack
   * @return
   * @throws GmExcetpion
   */
  private static  native long appendImages( long[] imageHandlers,  int stack) throws  GmExcetpion;

  /**
   *
   * 聚合多个图片为一个组合图片，比如GIF，
   * 分解一个组合图片（GIF）成多个图片
   *
   * @param imageInfo
   * @param images
   * @param fileName
   * @return
   */
  private static  native boolean writeImages(long imageInfo,long[] images,String fileName);

  /**
   *
   * 分层叠加图片
   *
   * @param canvas
   * @param op
   * @param composite
   * @param x
   * @param y
   * @return
   */
  public static boolean doCompositeImage(Image canvas,CompositeOperator op, Image composite, long x,long y) {
    return compositeImage(canvas.getHandler(),op.ordinal(),composite.getHandler(),x,y);
  }

  /**
   *
   * 拼接多个图片
   *
   * @param images
   * @param isVertical 是否竖向拼接
   * @return
   * @throws GmExcetpion
   */
  public static  Image concatImages(Image[] images, boolean isVertical) throws GmExcetpion {
    int stack = isVertical?1:0;
    long[] imageHandlers = new long[images.length];
    for (int i = 0; i <  images.length;i++) {
      imageHandlers[i] = images[i].getHandler();
    }
    long handler = appendImages(imageHandlers,stack);
    return new Image(handler);
  }

  /**
   * 组装多个图片为一个GIF，需要预先设置Image.delay属性
   *
   * @param images
   * @param fileName
   * @return
   */
  public static boolean buildGif(Image[] images,String fileName) {
    long[] imageHandlers = new long[images.length];
    for (int i = 0; i <  images.length;i++) {
      imageHandlers[i] = images[i].getHandler();
    }
    ImageInfo info = ImageInfo.factory(null);
    info.confFormat("GIF");
    boolean ret;
    try {
      ret = writeImages(info.getHandler(), imageHandlers, fileName);
    }finally {
      info.destory();
    }

    return ret;
  }

  /**
   * 组装多个图片为一个GIF,指定统一的delay
   *
   * @param images
   * @param fileName
   * @param delay
   * @return
   */
  public static boolean buildGif(Image[] images,String fileName,int delay) {
    long[] imageHandlers = new long[images.length];
    for (int i = 0; i <  images.length;i++) {
      imageHandlers[i] = images[i].getHandler();
      images[i].setDelay(delay);
    }
    ImageInfo info = ImageInfo.factory(null);
    info.confFormat("GIF");
    boolean ret;
    try {
      ret = writeImages(info.getHandler(), imageHandlers, fileName);
    }finally {
      info.destory();
    }

    return ret;
  }

  /**
   *
   * 把GIF解析成多个图片
   *
   * @param gif
   * @param type 解析出的图片类型
   * @param fileName the file name is expected to include a printf-style formatting string for the frame number
   *                 (e.g. "image%02d.miff") so that the frames may be written
   * @return
   * @throws GmExcetpion
   */
  public  static  boolean parseGif(Image gif, String type, String fileName) throws  GmExcetpion {
    ImageInfo info = ImageInfo.factory(null);
    info.confFormat(type);
    info.confAdjoin(0);
    boolean ret;
    try {
      ret = writeImages(info.getHandler(), new long[] {gif.getHandler()}, fileName);
    }finally {
      info.destory();
    }

    return ret;
  }
}
