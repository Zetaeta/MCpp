#!/bin/bash
g++ main.cpp Transformer.cpp Matrix.cpp Vector.cpp Camera.cpp Quaternion.cpp Texture.cpp -lGLEW -lglut -lGL -lMagick++-6.Q16 -g -O0 -std=c++11 -I/usr/include/ImageMagick-6
