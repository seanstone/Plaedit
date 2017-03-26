uniform sampler2D tileTexture;
uniform vec2 tileStrobe;

in vec2 _tileCoord;
in vec2 _texCoord;

void main()
{
	vec2 uv = tileStrobe * (_texCoord + _tileCoord);
	gl_FragColor = texture(tileTexture, uv);
}
