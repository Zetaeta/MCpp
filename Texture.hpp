
#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <string>

#include <GL/glew.h>
#include <ImageMagick-6/Magick++.h>

class Texture {
public:
    Texture(GLenum textureTarget, const std::string &fileName);

    bool load();
    void bind(GLenum textureUnit);
private:
    std::string fileName;
    GLenum textureTarget;
    GLuint textureObj;
    Magick::Image *image;
    Magick::Blob blob;
};

#endif
