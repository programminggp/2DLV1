#version 120
uniform mat4 WorldMatrix;
uniform float cnt;
//�t���O�����g�V�F�[�_�[�ɓn���ϐ�
varying vec3 N;//�@���x�N�g��
void main(void)
{
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
   // gl_Position.x += cnt;
    N = normalize(mat3(WorldMatrix)* gl_Normal);

        
	gl_FrontColor = gl_Color;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	//gl_TexCoord[7] = gl_MultiTexCoord7;
}
