#version 120
attribute vec4 indices;
attribute vec4 weights;
uniform mat4 Transforms[64];
//uniform mat4 WorldMatrix;

//�t���O�����g�V�F�[�_�[�ɓn���ϐ�
varying vec3 N;//�@���x�N�g��

void main(void)
{
    mat4 comb = mat4(0);
	comb += Transforms[int(indices.x)] * weights.x;
	comb += Transforms[int(indices.y)] * weights.y;
	comb += Transforms[int(indices.z)] * weights.z;
	comb += Transforms[int(indices.w)] * weights.w;
		  
	vec4 skinPosition = gl_ModelViewMatrix * comb * gl_Vertex;
    N = normalize(mat3(comb) * gl_Normal);

	gl_Position = gl_ProjectionMatrix * skinPosition;
	gl_TexCoord[0] = gl_MultiTexCoord0;

	//�f�v�X�e�N�X�`���̃e�N�X�`�����W�����߂�
	gl_TexCoord[1] = gl_TextureMatrix[1] * gl_Vertex;
}