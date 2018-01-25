package com.github.rolandhe;


import com.github.rolandhe.gm.Composite;
import com.github.rolandhe.gm.Image;
import com.github.rolandhe.gm.ImageProcessor;
import com.github.rolandhe.gm.Rect;
import com.github.rolandhe.gm.Resizer;
import com.github.rolandhe.gm.Shear;
import com.github.rolandhe.gm.Transformer;
import com.github.rolandhe.gm.TypeMetric;

import org.junit.Test;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.nio.file.FileSystems;
import java.nio.file.FileVisitResult;
import java.nio.file.FileVisitor;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.PathMatcher;
import java.nio.file.Paths;
import java.nio.file.SimpleFileVisitor;
import java.nio.file.Watchable;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.Map;
import java.util.Objects;
import java.util.Properties;

/**
 * Created by hexiufeng on 2017/12/26.
 */
public class TestCase {

  @Test
  public void testPlatform() throws IOException {
//    Path path = Paths.get("/Library/Fonts");
//    final PathMatcher matcher = FileSystems.getDefault()
//            .getPathMatcher("glob:/Library/Fonts/Microsoft/*" );
//
//    final int[] holder = {0};
//    Files.walkFileTree(path, new SimpleFileVisitor<Path>(){
//
//      @Override
//      public FileVisitResult visitFile(Path file, BasicFileAttributes attrs)
//              throws IOException {
////        Path name = file.getFileName();
//        if (matcher.matches(file)) {
//          System.out.println(file);
//          holder[0] += 1;
//        }
//        return FileVisitResult.CONTINUE;
//      }
//
//    });
//
//    System.out.println(holder[0]);

    Map<String,String> env = System.getenv();
    for(Map.Entry<String,String> entry : env.entrySet()) {
      System.out.printf("%s: %s\n", entry.getKey(),entry.getValue());
    }
    System.out.println("**************************************");
    Properties props = System.getProperties();
    for(Object key : props.keySet()){
      System.out.printf("%s: %s\n", key,props.getProperty(key.toString()));
    }

    System.out.println(System.mapLibraryName("GmJni"));
  }
  @Test
  public void testConvertFormat() {
    URL url = TestCase.class.getResource("/ha.png");
    String file = url.getFile();
    Image image = Image.factory(file);
    System.out.printf("%d,%d\n", image.getImageWidth(),image.getImageHeight());
    image.toFile("/Users/hexiufeng/output/ha.jpg","jpg");
    image.destory();
  }

  @Test
  public void testThumnail() {
    URL url = TestCase.class.getResource("/ha.png");
    String file = url.getFile();
    Image image = Image.factory(file);
    System.out.printf("%d,%d\n", image.getImageWidth(),image.getImageHeight());
    Image thumnail = Resizer.doThumbnailImage(image,image.getImageWidth()/2,image.getImageHeight()/2);

    thumnail.toFile("/Users/hexiufeng/output/t.png","png");
    image.destory();
    thumnail.destory();
  }

  @Test
  public void testScale() {
    URL url = TestCase.class.getResource("/ha.png");
    String file = url.getFile();
    Image image = Image.factory(file);
    System.out.printf("%d,%d\n", image.getImageWidth(),image.getImageHeight());
    Image thumnail = Resizer.doScaleImage(image,image.getImageWidth()/2,image.getImageHeight()/2) ;

    thumnail.toFile("/Users/hexiufeng/output/scale.png","png");
    image.destory();
    thumnail.destory();
  }

  @Test
  public void testDrawText() {
    URL url = TestCase.class.getResource("/ha.png");
    String file = url.getFile();
    Image image = Image.factory(file);
    System.out.printf("%d,%d\n", image.getImageWidth(),image.getImageHeight());
    boolean ok = ImageProcessor.doDrawTextOnImage(image,80,"/Library/Fonts/arial.ttf","red","hello world",100,100) ;
    System.out.println(ok);
    image.toFile("/Users/hexiufeng/output/annotate.png","png");
    image.destory();
  }

  @Test
  public void testRotate() {
    URL url = TestCase.class.getResource("/ha.png");
    String file = url.getFile();
    Image image = Image.factory(file);
    System.out.printf("%d,%d\n", image.getImageWidth(),image.getImageHeight());
    Image thumnail = Shear.doRotateImage(image,-90) ;

    thumnail.toFile("/Users/hexiufeng/output/rotate.png","png");
    image.destory();
    thumnail.destory();
  }

  @Test
  public  void testFormat() throws IOException {
    InputStream ins = TestCase.class.getResourceAsStream("/ha.png");
    byte[] buf = new byte[2048];
    int len = ins.read(buf);

    String format = Image.getMagickFileFormat(buf);

    System.out.println(format);

      ins.close();
  }

  @Test
  public void testBatchDrawText() {
    for(int i = 0; i < 4; i++) {
      batchDrawText(i);
    }
  }


  @Test
  public void testBuildGif() {
    String[] files = {
        "/Users/hexiufeng/output/annotate_0.png",
        "/Users/hexiufeng/output/annotate_1.png",
        "/Users/hexiufeng/output/annotate_2.png",
        "/Users/hexiufeng/output/annotate_3.png"
    };
    Image[] imageArray = new Image[files.length];
    int index = 0;
    for(String file :files) {
      Image image = Image.factory(file);
//      image.setDelay(100);
      imageArray[index++] = image;
    }

    boolean ok = Composite.buildGif(imageArray,"/Users/hexiufeng/output/hh.gif",120);
    System.out.println(ok);
    for(Image image:imageArray){
      image.destory();
    }
  }


  @Test
  public void testParseGif() {


    Image image = Image.factory("/Users/hexiufeng/output/hh.gif");

    boolean ok = Composite.parseGif(image,"PNG","/Users/hexiufeng/output/parse_%d.png");
    System.out.println(ok);
    image.destory();
  }


  @Test
  public void testAppend() {
    String[] files = {
            "/Users/hexiufeng/output/annotate_0.png",
            "/Users/hexiufeng/output/annotate_1.png",
            "/Users/hexiufeng/output/annotate_2.png",
            "/Users/hexiufeng/output/annotate_3.png"
    };
    Image[] imageArray = new Image[files.length];
    int index = 0;
    for(String file :files) {
      Image image = Image.factory(file);
      imageArray[index++] = image;
    }

    Image newImage = Composite.concatImages(imageArray,true);

    newImage.toFile("/Users/hexiufeng/output/append_v.png","png");
    newImage.destory();

    newImage = Composite.concatImages(imageArray,false);
    newImage.toFile("/Users/hexiufeng/output/append_h.png","png");

    newImage.destory();
    for(Image image:imageArray){
      image.destory();
    }

  }


  @Test
  public void testCropImage() {
    URL url = TestCase.class.getResource("/ha.png");
    String file = url.getFile();
    Image image = Image.factory(file);
    System.out.printf("%d,%d\n", image.getImageWidth(),image.getImageHeight());
    Image newImage = Transformer.doCropImage(image,new Rect(350,350,20,50)) ;

    newImage.toFile("/Users/hexiufeng/output/crop.png","png");
    image.destory();
    newImage.destory();
  }

  public void batchDrawText(int index) {
    URL url = TestCase.class.getResource("/ha.png");
    String file = url.getFile();
    Image image = Image.factory(file);
    String text = String.format("h_%d",index);
    TypeMetric tm = ImageProcessor.getTypeMetrics(image,60,"arial",text);
    System.out.printf("%f,%f|%f,%f\n",tm.getWidth(),tm.getHeight(),tm.getAscent(),tm.getDescent());
    tm.destory();
    boolean ok = ImageProcessor.doDrawTextOnImage(image,60,"arial","red",text,10,60) ;
    System.out.println(ok);
    String name = String.format("/Users/hexiufeng/output/annotate_%d.png",index);
    image.toFile(name,"png");
    image.destory();
  }
}
