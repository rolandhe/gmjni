package com.github.rolandhe.gm;

/**
 *
 * 封装GM实体类的基类, 封装GM库句柄以及控制资源释放.GM实体指的是一些struct:Image,ImageInfo等.
 * 所谓句柄指的是c的指针,在java中用long表示.
 *
 * Created by hexiufeng on 2017/12/25.
 */
public abstract class GmEntity extends GmBase {
  private final long handler;
  private boolean destoried;
  public long getHandler() {
    return handler;
  }
  protected GmEntity(long handler) {
    this.handler = handler;
  }

  /**
   * 释放GM库底层资源
   */
  public void destory() {
    if(!destoried) {
      destroyHandler(getHandler());
    }
    destoried = true;
  }

  /**
   * 释放有GM库分配的资源
   *
   * @param handler 需要释放的资源句柄
   */
  protected abstract void destroyHandler(long handler);
}
