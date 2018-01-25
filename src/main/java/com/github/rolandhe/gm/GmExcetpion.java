package com.github.rolandhe.gm;

/**
 * 封装GM库内部异常,由Jni库抛出, java中catch，但不会抛出该异常
 *
 * Created by hexiufeng on 2017/12/25.
 */
public class GmExcetpion extends RuntimeException {
  public GmExcetpion(String message) {
    super(message);
  }
}
