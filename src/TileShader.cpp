#include "TileShader.hpp"

using namespace Pulsar;

TileShader::TileShader()
{
    FILE *pla;
    pla = fopen("../../SimEarth/Planets/earth.PLA","rb");  // r for read, b for binary

    char terrain[mapWidth][mapHeight][2];
    fseek(pla, 0x0080, SEEK_SET);
    fread(terrain, mapWidth * mapHeight * 2, 1, pla);

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
                switch ((terrain[i][j][0] >> 5) & 0b111)
                {
                    case 0: texCoordData[i][j][k] = vec2(38, 20); break; // No Biome
                    case 1: texCoordData[i][j][k] = vec2(37, 20); break; // Arctic
                    case 2: texCoordData[i][j][k] = vec2(12, 4); break; // Boreal
                    case 3: texCoordData[i][j][k] = vec2(7, 4); break; // Desert
                    case 4: texCoordData[i][j][k] = vec2(9, 4); break; // Grasslands
                    case 5: texCoordData[i][j][k] = vec2(10, 4); break; // Forests
                    case 6: texCoordData[i][j][k] = vec2(11, 4); break; // Jungle
                    case 7: texCoordData[i][j][k] = vec2(8, 4); break; // Swamp
                }
                switch (terrain[i][j][1] & 0x1F)
                {
                    case 0x04 ... 0x07: texCoordData[i][j][k] = vec2(0, 1); break;
                    case 0x08 ... 0x0B: texCoordData[i][j][k] = vec2(0, 2); break;
                    case 0x0C ... 0x0F: texCoordData[i][j][k] = vec2(0, 3); break;
                    case 0x10 ... 0x13: texCoordData[i][j][k] = vec2(0, 4); break;
                    case 0x14 ... 0x17: texCoordData[i][j][k] = vec2(0, 5); break;
                    case 0x18 ... 0x1B: texCoordData[i][j][k] = vec2(0, 6); break;
                    case 0x1C ... 0x1F: texCoordData[i][j][k] = vec2(0, 8); break;
                }
                switch ((terrain[i][j][1] >> 5) & 0b111)
                {
                    //case 1: case 3: case 4: case 7: texCoordData[i][j][k] = vec2(0, 0); break;
                    //  texCoordData[i][j][k] = vec2(1, 3); break;
                    // case 3: texCoordData[i][j][k] = vec2(1, 4); break;
                    // case 4: texCoordData[i][j][k] = vec2(1, 5); break;
                    // case 5: texCoordData[i][j][k] = vec2(1, 6); break;
                    // case 6: texCoordData[i][j][k] = vec2(1, 8); break;
                    // case 7: texCoordData[i][j][k] = vec2(1, 4); break;
                }
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
