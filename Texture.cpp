
#include <iostream>

#include "Texture.hpp"

Texture::Texture(GLenum textureTarget, const std::string &fileName)
:textureTarget(textureTarget), fileName(fileName), image(nullptr) {
}

bool Texture::load() {
    try {
        image = new Magick::Image(fileName);
        image->write(&blob, "RGBA");
    }
    catch(Magick::Error &error) {
        std::cout << "Error loading texture " << fileName << ": " << error.what() << '\n';
        return false;
    }

    glGenTextures(1, &textureObj); // generate 1 texture & put reference into textureObj
    glBindTexture(textureTarget, textureObj); // Binds textureObj as the currently referenced texture of type textureTarget.

    //           target (1D/2D/...)  LOD  *storage* format      width/height in texels       border  *blob* format  per channel       data
    glTexImage2D(textureTarget,      0,   GL_RGB,          image->columns(), image->rows(), 0,      GL_RGBA,       GL_UNSIGNED_BYTE, blob.data());

    //minification
    glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //magnification
    glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    return true;
}

void Texture::bind(GLenum textureUnit) { //GL_TEXTURE{0,1,whatever}
    glActiveTexture(textureUnit);
    glBindTexture(textureTarget, textureObj);
}
