#include "TileShader.hpp"

using namespace Pulsar;

TileShader::TileShader()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &mapCoord);
    glGenBuffers(1, &tileCoord);
    glGenBuffers(1, &texCoord);

    vec2 mapCoordData[mapWidth][mapHeight][6];
    vec2 tileCoordData[mapWidth][mapHeight][6];
    vec2 texCoordData[mapWidth][mapHeight][6];

    for (int i = 0; i < mapWidth; i++)
        for (int j = 0; j < mapHeight; j++)
            for (int k = 0; k < 6; k++)
            {
                mapCoordData[i][j][k] = vec2(i, j);
                switch (k)
                {
                    case 0: tileCoordData[i][j][k] = vec2(0, 0); break;
                    case 1: tileCoordData[i][j][k] = vec2(1, 0); break;
                    case 2: tileCoordData[i][j][k] = vec2(0, 1); break;
                    case 3: tileCoordData[i][j][k] = vec2(0, 1); break;
                    case 4: tileCoordData[i][j][k] = vec2(1, 0); break;
                    case 5: tileCoordData[i][j][k] = vec2(1, 1); break;
                }
                texCoordData[i][j][k] = vec2(8, 4);
            }

    glBindBuffer(GL_ARRAY_BUFFER, mapCoord);
    glBufferData(GL_ARRAY_BUFFER, mapWidth * mapHeight * 6 * sizeof(vec2), mapCoordData, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    glBindBuffer(GL_ARRAY_BUFFER, tileCoord);
    glBufferData(GL_ARRAY_BUFFER, mapWidth * mapHeight * 6 * sizeof(vec2), tileCoordData, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    glBindBuffer(GL_ARRAY_BUFFER, texCoord);
    glBufferData(GL_ARRAY_BUFFER, mapWidth * mapHeight * 6 * sizeof(vec2), texCoordData, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    Image image;
    image.load("data/texture/simearth_2_5_ng_by_nine999jellyfish-da8n0np.png");
    tileTexture = new Texture;
    tileTexture->load(&image);
    tileTexture->enableMipmap(false);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    tileTexture->unbind();
    glBindVertexArray(0);
}

TileShader::~TileShader()
{
	if (vao)           glDeleteVertexArrays(1, &vao);
	if (mapCoord)      glDeleteBuffers(1, &mapCoord);
    if (tileCoord)     glDeleteBuffers(1, &tileCoord);
    if (texCoord)      glDeleteBuffers(1, &texCoord);
    delete tileTexture;
}

void TileShader::render()
{
    glUseProgram(program);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, mapCoord);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, tileCoord);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, texCoord);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

    tileTexture->bind();

	glDrawArrays(GL_TRIANGLES, 0, mapWidth * mapHeight * 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}
