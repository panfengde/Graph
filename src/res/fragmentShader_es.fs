#ifdef GL_ES
#version 300 es
precision mediump float; // 在 OpenGL ES 中设置精度
#else
#version 330 core
#endif

out vec4 FragColor;
void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}