#version 440 core
layout (points) in;
layout (triangle_strip, max_vertices = 36) out;

uniform mat4 model;

in VS_OUT {
    vec3 pos;
    vec3 color;
    mat4 proj_view;
} gs_in[]; 

out GS_OUT {
    vec2 texCoords;
    vec3 normal;
    vec3 pos;
    vec3 color;
} gs_out; 

struct QubeLayer
{
    vec3 p1;
    vec3 p2;
    vec3 p3;
    vec3 p4;
    vec3 p5;
    vec3 p6;
    vec3 normal;
    vec2 uv1;
    vec2 uv2;
    vec2 uv3;
    vec2 uv4;
    vec2 uv5;
    vec2 uv6;
    vec3 color;
};
const float r = 0.3f;
const int size = 6;
QubeLayer qybeLaers[size] = QubeLayer[size]
    (
        QubeLayer(
        vec3(-r,-r,-r),
        vec3(r, r,-r),
        vec3(r,-r,-r),
        vec3(r,r,-r),
        vec3(-r,-r,-r),
        vec3(-r,r,-r),
        vec3(0,0,-1),
        vec2(0,0),
        vec2(1,1),
        vec2(1,0),
        vec2(1,1),
        vec2(0,0),
        vec2(0,1),
        gs_in[0].color
        ),
        QubeLayer(
        vec3(-r,-r,r),
        vec3(r,-r,r),
        vec3(r,r,r),
        vec3(r,r,r),
        vec3(-r,r,r),
        vec3(-r,-r,r),
        vec3(0,0,1),
        vec2(0,0),
        vec2(1,0),
        vec2(1,1),
        vec2(1,1),
        vec2(0,1),
        vec2(0,0),
        gs_in[0].color
        ),
        QubeLayer(
        vec3(-r,r,r),
        vec3(-r,r,-r),
        vec3(-r,-r,-r),
        vec3(-r,-r,-r),
        vec3(-r,-r,r),
        vec3(-r,r,r),
        vec3(-1,0,0),
        vec2(1,0),
        vec2(1,1),
        vec2(0,1),
        vec2(0,1),
        vec2(0,0),
        vec2(1,0),
        gs_in[0].color
        ),
        QubeLayer(
        vec3(r,r,r),
        vec3(r,-r,-r),
        vec3(r,r,-r),
        vec3(r,-r,-r),
        vec3(r,r,r),
        vec3(r,-r,r),
        vec3(1,0,0),
        vec2(1,0),
        vec2(0,1),
        vec2(1,1),
        vec2(0,1),
        vec2(1,0),
        vec2(0,0),
        gs_in[0].color
        ),
        QubeLayer(
        vec3(-r,-r,-r),
        vec3(r,-r,-r),
        vec3(r,-r,r),
        vec3(r,-r,r),
        vec3(-r,-r,r),
        vec3(-r,-r,-r),
        vec3(0,-1,0),
        vec2(0,1),
        vec2(1,1),
        vec2(1,0),
        vec2(1,0),
        vec2(0,0),
        vec2(0,1),
        gs_in[0].color
        ),
        QubeLayer(
        vec3(-r,r,-r),
        vec3(r,r,r),
        vec3(r,r,-r),
        vec3(r,r,r),
        vec3(-r,r,-r),
        vec3(-r,r,r),
        vec3(0,1,0),
        vec2(0,1),
        vec2(1,0),
        vec2(1,1),
        vec2(1,0),
        vec2(0,1),
        vec2(0,0),
        gs_in[0].color
        )
    );

void main() {
    for(int i = 0; i < size; i++)
    {
        vec3 lp1 = gs_in[0].pos + qybeLaers[i].p1;
        vec3 lp2 = gs_in[0].pos + qybeLaers[i].p2;
        vec3 lp3 = gs_in[0].pos + qybeLaers[i].p3;
        vec3 lp4 = gs_in[0].pos + qybeLaers[i].p4;
        vec3 lp5 = gs_in[0].pos + qybeLaers[i].p5;
        vec3 lp6 = gs_in[0].pos + qybeLaers[i].p6;

        vec4 p1 = gs_in[0].proj_view * vec4(lp1, 1);
        vec4 p2 = gs_in[0].proj_view * vec4(lp2, 1);
        vec4 p3 = gs_in[0].proj_view * vec4(lp3, 1);
        vec4 p4 = gs_in[0].proj_view * vec4(lp4, 1);
        vec4 p5 = gs_in[0].proj_view * vec4(lp5, 1);
        vec4 p6 = gs_in[0].proj_view * vec4(lp6, 1);
        
        gs_out.normal = mat3(transpose(inverse(model))) * qybeLaers[i].normal;
        
        gl_Position  = p1;
        gs_out.pos = vec3(model * vec4(lp1, 1.0));
        gs_out.texCoords = qybeLaers[i].uv1;
        gs_out.color = qybeLaers[i].color;
        EmitVertex ();

        gl_Position  = p2;
        gs_out.pos = vec3(model * vec4(lp2, 1.0));
        gs_out.texCoords = qybeLaers[i].uv2;
        gs_out.color = qybeLaers[i].color;
        EmitVertex ();

        gl_Position  = p3;
        gs_out.pos = vec3(model * vec4(lp3, 1.0));
        gs_out.texCoords = qybeLaers[i].uv3;
        gs_out.color = qybeLaers[i].color;
        EmitVertex ();

        EndPrimitive ();

        gl_Position  = p4;
        gs_out.pos = vec3(model * vec4(lp4, 1.0));
        gs_out.texCoords = qybeLaers[i].uv4;
        gs_out.color = qybeLaers[i].color;
        EmitVertex ();

        gl_Position  = p5;
        gs_out.pos = vec3(model * vec4(lp5, 1.0));
        gs_out.texCoords = qybeLaers[i].uv5;
        gs_out.color = qybeLaers[i].color;
        EmitVertex ();

        gl_Position  = p6;
        gs_out.pos = vec3(model * vec4(lp6, 1.0));
        gs_out.texCoords = qybeLaers[i].uv6;
        gs_out.color = qybeLaers[i].color;
        EmitVertex ();

        EndPrimitive ();

    }
}
/*QubeLayer(
        vec3(-r,-r,-r),
        vec3(r,-r,-r),
        vec3(r,r,-r),
        vec3(-r,r,-r),
        vec3(0,0,-1),
        vec2(0,1),
        vec2(0,0),
        vec2(1,0),
        vec2(1,1),
        gs_in[0].color
        ),
        QubeLayer(
        vec3(-r,-r,r),
        vec3(r,-r,r),
        vec3(r,r,r),
        vec3(-r,r,r),
        vec3(0,0,1),
        vec2(0,1),
        vec2(0,0),
        vec2(1,0),
        vec2(1,1),
        gs_in[0].color
        ),
        QubeLayer(
        vec3(-r,r,r),
        vec3(-r,r,-r),
        vec3(-r,-r,-r),
        vec3(-r,-r,r),
        vec3(-1,0,0),
        vec2(0,1),
        vec2(0,0),
        vec2(1,0),
        vec2(1,1),
        gs_in[0].color
        ),
        QubeLayer(
        vec3(r,r,r),
        vec3(r,r,-r),
        vec3(r,-r,-r),
        vec3(r,-r,r),
        vec3(1,0,0),
        vec2(0,1),
        vec2(0,0),
        vec2(1,0),
        vec2(1,1),
        gs_in[0].color
        ),
        QubeLayer(
        vec3(-r,-r,-r),
        vec3(r,-r,-r),
        vec3(r,-r,r),
        vec3(-r,-r,r),
        vec3(0,-1,0),
        vec2(0,1),
        vec2(0,0),
        vec2(1,0),
        vec2(1,1),
        gs_in[0].color
        ),
        QubeLayer(
        vec3(-r,r,-r),
        vec3(r,r,-r),
        vec3(r,r,r),
        vec3(-r,r,r),
        vec3(0,1,0),
        vec2(0,1),
        vec2(0,0),
        vec2(1,0),
        vec2(1,1),
        gs_in[0].color*/