#version 330 core

// OpenGL ES 不支持 layout(location=0) ，使用 aPos 作为顶点位置的输入
in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}