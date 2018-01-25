cmake_minimum_required (VERSION 3.7)
project (GmJni)

include_directories (/usr/include /usr/local/include /usr/local/include/GraphicsMagick)
link_directories(/usr/lib /usr/local/lib)
add_library(GmJni SHARED common.c image_DrawInfo.c image_Image.c image_ImageProcessor.c image_Shear.c image_TypeMetric.c image_Composite.c image_GmBase.c image_ImageInfo.c image_Resizer.c image_Transformer.c) 
target_link_libraries(GmJni GraphicsMagick)

