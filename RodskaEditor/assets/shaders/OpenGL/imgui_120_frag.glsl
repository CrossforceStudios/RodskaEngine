#ifdef GL_ES
    precision mediump float;
#endif
uniform sampler2D Texture;
varying vec2 Frag_UV;
varying vec4 Frag_Color;
out vec4 Out_Color;
void main()
{
     gl_FragColor = Frag_Color * texture(Texture, Frag_UV.st);
}