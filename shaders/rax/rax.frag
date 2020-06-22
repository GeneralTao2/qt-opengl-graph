#version 440 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
//flat in float i;

uniform sampler2D ourTexture;
uniform vec3 colors[3];


void main()
{

    //int inttest = int(i);
    FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    //FragColor = texture(ourTexture, TexCoord) * vec4(inttest/10, inttest/10, inttest/10, 1.0);
    /*if(inttest == 10)
        FragColor = texture(ourTexture, TexCoord) * vec4(1, 0, 0, 1.0);
    else if (inttest == 20)
       FragColor = texture(ourTexture, TexCoord) * vec4(0, 1, 0, 1.0);
    else if (inttest == 30)
       FragColor = texture(ourTexture, TexCoord) * vec4(0, 0, 1, 1.0);*/
}
