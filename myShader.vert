#version 440


uniform mat4 osg_ModelViewProjectionMatrix; 

layout(location = 0) in vec3 osg_Vertex;
layout(location = 1) in vec3 osg_Normal;
layout(location = 2) in vec4 osg_Color; 

out VertexData{
    vec4 mColor;

} VertexOut;

void main(void)
{
    vec4 red = vec4(osg_Normal,1.0);
    //VertexOut.mColor = red*(dot(osg_Normal,vec3(0.0,0.0,1.0)));
    //VertexOut.mVertex = vec4(osg_Vertex,1);
VertexOut.mColor = red;
    gl_Position = osg_ModelViewProjectionMatrix * vec4(osg_Vertex,1);
}  
