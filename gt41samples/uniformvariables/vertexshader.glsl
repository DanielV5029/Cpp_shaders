#version 330
                                       
layout (location = 0) in vec3 Position;
layout (location = 1) in vec4 Colour;

out vec4 Colour0;

uniform vec2 gOffset;
                                                                   
void main()
{  
    gl_Position = vec4(Position.x + gOffset.x, Position.y + gOffset.y, Position.z, 1.0);
	Colour0 = Colour;
}

/*
// Starting
#version 330
                                       
layout (location = 0) in vec3 Position;
layout (location = 1) in vec4 Colour;

out vec4 Colour0;

uniform float gScale;
                                                                   
void main()
{  
    gl_Position = vec4(Position.x * gScale, Position.y * gScale, Position.z * gScale, 1.0);
	Colour0 = Colour;
}*/