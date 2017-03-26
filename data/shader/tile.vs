uniform mat4 projection;

in vec2 mapCoord; 	// (0, 0), (0, 1), (0, 2), (0, 3), ..., (i, j)
in vec2 tileCoord; 	// (0, 0), (0, 1), (1, 0), (1, 1)
in vec2 texCoord;

out vec2 _tileCoord;
out vec2 _texCoord;

void main()
{
	_tileCoord = tileCoord;
	_texCoord = texCoord;
	gl_Position = projection * vec4(mapCoord + tileCoord, 0.0, 1.0);
}
