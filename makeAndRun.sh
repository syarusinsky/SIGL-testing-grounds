g++ -std=c++17 -Ofast -g `pkg-config --cflags gtk+-3.0` -funroll-loops -fomit-frame-pointer -finline -fopenmp -fno-exceptions -march=x86-64 -mtune=generic -mno-vzeroupper -o main main.cpp SIGL/src/FrameBuffer.cpp SIGL/src/SoftwareGraphics.cpp SurfaceTest.cpp SIGL/src/ColorProfile.cpp SIGL/src/Surface.cpp SIGL/src/Font.cpp SIGL/src/Sprite.cpp SIGL/src/Engine3D.cpp SIGL/src/Texture.cpp -ISIGL/include -DSOFTWARE_RENDERING `pkg-config --libs gtk+-3.0`
# -fopt-info-vec-missed 
# 2>&1 | grep SoftwareGraphics.hpp
./main
