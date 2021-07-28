g++ -g `pkg-config --cflags gtk+-3.0` -o main main.cpp SIGL/src/FrameBuffer.cpp SIGL/src/SoftwareGraphics.cpp SurfaceTest.cpp SIGL/src/ColorProfile.cpp SIGL/src/Surface.cpp SIGL/src/Font.cpp SIGL/src/Sprite.cpp SIGL/src/Engine3D.cpp -ISIGL/include -DSOFTWARE_RENDERING `pkg-config --libs gtk+-3.0`
./main
