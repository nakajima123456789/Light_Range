float4x4 world;
float4x4 viewProjection;
float4x4 wvp;

static const int MAX_MATRICES = 26;
float4x3 WorldMatrixArray[MAX_MATRICES];
int NumBones;

float3 cam_pos;

float3 light_pos;
float3 light_diffuse;
float3 light_ambient;
float3 light_specular;
float3 light_attenuation;

float3 light_emission;

float3 model_diffuse;
float3 model_ambient;
float3 model_specular;

float3 model_emission;

float3 last_ambient = float3(0.01f, 0.01f, 0.01f);

float model_alpha;
float anime_alpha;

texture map;
sampler tex0 = sampler_state
{
    texture = <map>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;

    AddressU = WRAP;
    AddressV = WRAP;
};

texture modelTex;
sampler tex1 = sampler_state
{
    texture = <modelTex>;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
    MipFilter = LINEAR;

    AddressU = WRAP;
    AddressV = WRAP;
};

struct VS_INPUT
{
    float4 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD0;
};

struct ANIME_VS_INPUT
{
    float4 position : POSITION;
    float3 normal : NORMAL;
    float4 blendWeights : BLENDWEIGHT;
    float4 blendIndices : BLENDINDICES;
    float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
    float4 position : POSITION;
    float3 normal : NORMAL;
    float4 worldPos : TEXCOORD0;
    float3 eye_pos : TEXCOORD1;
    float2 uv : TEXCOORD2;
};

VS_OUTPUT MODEL_VS(VS_INPUT input)
{
    VS_OUTPUT vs_out = (VS_OUTPUT) 0;

    vs_out.position = mul(input.position, wvp);
    vs_out.worldPos = mul(input.position, world);
    
    vs_out.uv = input.uv;
    vs_out.normal = mul(input.normal, (float3x3) world);
    vs_out.eye_pos = normalize(cam_pos - vs_out.worldPos.xyz);

    return vs_out;
}

VS_OUTPUT ANIME_VS(ANIME_VS_INPUT input)
{
    VS_OUTPUT vs_out = (VS_OUTPUT) 0;
    
    int IndexArray[4] = (int[4]) input.blendIndices;
    float BlendWeightsArray[4] = (float[4]) input.blendWeights;

    float LastWeight = 0;
    
    for (int iBone = 0; iBone < NumBones - 1; iBone++)
    {
        vs_out.position.xyz += mul(input.position,
                                 WorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];
        
        vs_out.normal.xyz += mul(float4(input.normal, 1.0f),
                                 WorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];

        LastWeight += BlendWeightsArray[iBone];
    }
    
    LastWeight = 1.0f - LastWeight;
    
    // Now that we have the calculated weight, add in the final influence
    vs_out.position.xyz += (mul(input.position, WorldMatrixArray[IndexArray[NumBones - 1]])
                      * LastWeight);

    vs_out.normal += (mul(float4(input.normal, 1.0f), WorldMatrixArray[IndexArray[NumBones - 1]])
                     * LastWeight);
    
    vs_out.normal = normalize(vs_out.normal);
    
    // Transform the position into screen space
    vs_out.position.w = 1.0f;
    vs_out.worldPos = vs_out.position;
    vs_out.position = mul(vs_out.position, viewProjection);

	// Pass the texture coordinate
    vs_out.uv = input.uv;
    
    vs_out.eye_pos = normalize(cam_pos - vs_out.worldPos.xyz);
    
    return vs_out;
}

float4 PointLight(VS_OUTPUT input)
{
    float3 normal = normalize(input.normal);
    float3 Ambient = light_ambient + model_ambient;
    float3 Diffuse = light_diffuse + model_diffuse;
    float3 Specular = light_specular + model_specular;
    
    float4 color = float4(0.f, 0.f, 0.f, 1.f);
    float3 lightDir;
    float3 dir;
    float len;
    float colD;
    float colA;
    
    dir = normalize(light_pos - input.worldPos.xyz);
    
    colD = saturate(dot(normal, dir));
    
    Diffuse *= colD;
    
    float3 ref = reflect(dir, normal);
    float ER = saturate(dot(-input.eye_pos.xyz, ref));
    
    Specular = pow(ER, 10.0f) * Specular;
    
    len = length(light_pos.xyz - input.worldPos.xyz);
    
    colA = saturate(1.0f / (light_attenuation.x
                         + (light_attenuation.y * len)
                         + (light_attenuation.z * len * len)));
    
    color = float4(Diffuse + Ambient + Specular, 1);
    
    color *= colA;
    
    color += float4(last_ambient * 1, 1.f);
    
    return color;
}

float4 A_PointLight(VS_OUTPUT input)
{
    float3 normal = normalize(input.normal);
    float3 Ambient = light_ambient + model_ambient;
    float3 Diffuse = light_diffuse + model_diffuse;
    float3 Specular = light_specular + model_specular;
    
    float4 color = float4(0.f, 0.f, 0.f, 1.f);
    float3 lightDir;
    float3 dir;
    float len;
    float colD;
    float colA;
    
    dir = normalize(light_pos - input.worldPos.xyz);
    
    colD = saturate(dot(normal, dir));
    
    Diffuse *= colD;
    
    float3 ref = reflect(dir, normal);
    float ER = saturate(dot(-input.eye_pos.xyz, ref));
    
    Specular = pow(ER, 10.0f) * Specular;
    
    len = length(light_pos.xyz - input.worldPos.xyz);
    
    colA = saturate(1.0f / (light_attenuation.x
                         + (light_attenuation.y * len)
                         + (light_attenuation.z * len * len)));
    
    color = float4(Diffuse + Ambient + Specular, 1);
    
    color *= colA;
    
//    color += float4(last_ambient * 7, 1.f);
    
    return color;
}

float4 MODEL_PS(VS_OUTPUT input) : COLOR0
{
    float4 output = float4(0, 0, 0, 0);
    
    output += PointLight(input);
    
    output = saturate(output);
    
    output *= tex2D(tex0, input.uv);
    
    output.a = model_alpha;
    
  // output.r = 1.0f;
    
    return output;
}

float4 ANIME_PS(VS_OUTPUT input) : COLOR0
{
    float4 output = float4(0, 0, 0, 0);
    
    output += A_PointLight(input);
    
    output = saturate(output);
    
    output *= tex2D(tex1, input.uv);
    
    output.a = anime_alpha;
    
    output.rgb /= 2.0;
    
    return output;
}

int start = 0;
int pixel = 20;

float4 ANIME_ALPHA(VS_OUTPUT input) : COLOR0
{
    float4 output_rgb = float4(0, 0, 0, 0);
    
    output_rgb  +=  A_PointLight(input);   
    output_rgb   =  saturate(output_rgb);   
    output_rgb  *=  tex2D(tex1, input.uv); 
    output_rgb.a =  anime_alpha;
   
    output_rgb.x += sin(radians(output_rgb.y * 360 - start)) * pixel;
    
    output_rgb.rgb /= 2.0;
    
    output_rgb = float4(output_rgb.x, output_rgb.x, output_rgb.x, 1.0);
    
    return output_rgb;
}

technique MODEL
{
    pass pass0
    {
        VertexShader = compile vs_3_0 MODEL_VS();
        PixelShader = compile ps_3_0 MODEL_PS();
    }
}

technique ANIME
{
    pass pass0
    {
        VertexShader = compile vs_3_0 ANIME_VS();
        PixelShader = compile ps_3_0 ANIME_PS();
    }
}
