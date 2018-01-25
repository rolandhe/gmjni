package com.github.rolandhe.gm;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.UUID;

/**
 *
 * 封装GM的基础抽象类, 自动加载和初始化GmJni lib
 *
 * Created by hexiufeng on 2017/12/21.
 */
public abstract class GmBase {
  private static final Logger LOGGER = LoggerFactory.getLogger(GmBase.class);

  private static final String LIB_NAME = "GmJni";

  static {
    LoadLibrary();
    initGmLib();
  }

  /**
   * 封装GM库的初始化库方法
   *
   */
  private static native void initGmLib();


  private  static void LoadLibrary() {
    try {
      LOGGER.info("try to load GmJni from system path.");
      System.loadLibrary(LIB_NAME);
    }catch (UnsatisfiedLinkError e) {
      LOGGER.info("can't load GmJni from system path, and try to load from classpath/lib/.");
      extractAndLoad();
    }
  }

  /**
   *
   * Read lib from classpath:/lib/ and output temp file which name is a uuid,then load lib,because
   * System.load method just required a local file. This method uses File.deleteOnExit to
   * avoid accumulating lots of temp file.
   *
   */
  private static void extractAndLoad() {
    String libResPath = String.format("/lib/%s",System.mapLibraryName(LIB_NAME));
    String tmpPath = System.getProperty("java.io.tmpdir");
    String tmpLibName = UUID.randomUUID().toString();
    tmpLibName = System.mapLibraryName(tmpLibName);
    Path tmpLibFull = Paths.get(tmpPath,tmpLibName);
    InputStream ins =  GmBase.class.getResourceAsStream(libResPath);
    if(ins == null) {
      LOGGER.info("can't find lib from classpath: {}" , libResPath);
      throw new RuntimeException("can't find lib:" + libResPath);
    }
    try {
      LOGGER.info("read {} and output to {}.", libResPath, tmpLibFull);
      Files.copy(ins, tmpLibFull);
      LOGGER.info("load lib:{}",tmpLibFull);
      System.load(tmpLibFull.toString());
    } catch (IOException e) {
      LOGGER.info("",e);
      throw  new RuntimeException(e);
    }finally {
      try {
        ins.close();
      } catch (IOException e) {
      }
      tmpLibFull.toFile().deleteOnExit();
    }
  }

}
