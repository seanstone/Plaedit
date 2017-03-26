uniform sampler2D tileTexture;
vec2 textureSize = vec2(1200, 516);
vec2 tileOffset = vec2(3, 3);
vec2 tileSize 	= vec2(16, 16);
vec2 tileStrobe = vec2(19, 19);

in vec2 _tileCoord;
in vec2 _texCoord;

void main()
{
	vec2 uv = (tileOffset + tileStrobe * _texCoord + tileSize * _tileCoord) / textureSize;
	gl_FragColor = texture(tileTexture, uv);
}
