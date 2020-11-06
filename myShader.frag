#version 440

in VertexData{
    vec4 mColor;
} VertexIn;

out vec4 FragColor;

void main(void)
{

    FragColor = VertexIn.mColor + vec4(0.4,0.4,0.4,0.4);
//FragColor =vec4(vec3(gl_FragCoord.z),1.0);
}
