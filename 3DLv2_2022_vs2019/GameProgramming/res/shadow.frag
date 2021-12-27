#version 120
uniform vec3 lightVec;
uniform vec3 lightAmbientColor;
uniform vec3 lightDiffuseColor;
uniform vec3 eyeVec;
uniform vec4 Ambient;
uniform vec4 Diffuse;
uniform vec3 Specular;
uniform vec3 Emissive;
uniform float Pow;
uniform sampler2D Sampler;	//テクスチャ
uniform int TextureFlg;

//頂点シェーダーから受け取る変数
varying vec3 N;//法線ベクトル

uniform sampler2DShadow DepthTexture;	//デプステクスチャ

void main(void)
{

	float NL = dot(N, lightVec); 
	vec3 Reflect = normalize(2 * NL * N - lightVec);
	float specular = pow(clamp(dot(Reflect, eyeVec),0,1.0), Pow);

	vec4 texColor;
	if(TextureFlg == -1)
	{
		texColor = vec4(1.0,1.0,1.0,1.0);
	}
	else
	{
		texColor = texture2D(Sampler, gl_TexCoord[0].st);
	}

	//デプステクスチャの値を取得
	float shd = shadow2DProj(DepthTexture, gl_TexCoord[1]).r;
	//値が0は影にする
	if(shd < 0.5) {
		texColor = texColor * 0.5;
	}
   
	gl_FragColor= texColor * (Diffuse * clamp(NL,0,1.0)* vec4(lightDiffuseColor,1.0)+ Ambient * vec4(lightAmbientColor,1.0) + vec4(specular*Specular + Emissive,1.0));
}
