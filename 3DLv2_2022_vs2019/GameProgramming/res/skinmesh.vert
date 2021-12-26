#version 120
attribute vec4 indices;
attribute vec4 weights;
uniform mat4 Transforms[128];
//uniform mat4 WorldMatrix;
uniform float cnt;
//フラグメントシェーダーに渡す変数
varying vec3 N;//法線ベクトル
void main(void)
{
    mat4 comb = mat4(0);
	comb += Transforms[int(indices.x)] * weights.x;
	comb += Transforms[int(indices.y)] * weights.y;
	comb += Transforms[int(indices.z)] * weights.z;
	comb += Transforms[int(indices.w)] * weights.w;
		  
	vec4 skinPosition = gl_ModelViewMatrix * comb * gl_Vertex;
    gl_Position = gl_ProjectionMatrix * skinPosition;
//    N = normalize(mat3(WorldMatrix* comb) * gl_Normal);
    N = normalize(mat3(comb) * gl_Normal);
    
	gl_FrontColor = gl_Color;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}
