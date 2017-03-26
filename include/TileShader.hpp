#ifndef TILESHADER_HPP
#define TILESHADER_HPP

#include <PulsarShader.hpp>
#include <PulsarTexture.hpp>

typedef GLuint VAO;
typedef GLuint VBO;

namespace Pulsar
{

class TileShader : public Shader
{
public:
	TileShader();
	~TileShader();
	void render();

    VAO         vao        	= 0;
    VBO         mapCoord    = 0;
    VBO         tileCoord   = 0;
	VBO         texCoord    = 0;
    Texture*    tileTexture = NULL;
};

}

#endif
