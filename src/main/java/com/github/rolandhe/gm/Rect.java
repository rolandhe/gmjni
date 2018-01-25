package com.github.rolandhe.gm;

/**
 *
 * 描述一个矩形
 *
 * Created by hexiufeng on 2017/12/25.
 */
public class Rect {
  private final long width;
  private final long height;
  private final long x;
  private final long y;
  public Rect(long width,long height, long x,long y){
    this.width = width;
    this.height = height;
    this.x = x;
    this.y = y;
  }

  public long getWidth() {
    return width;
  }

  public long getHeight() {
    return height;
  }

  public long getX() {
    return x;
  }

  public long getY() {
    return y;
  }
}
