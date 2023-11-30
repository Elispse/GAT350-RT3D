#version 430

#define INVERT_MASK     (1 << 0)
#define GRAYSCALE_MASK  (1 << 1)
#define COLORTINT_MASK  (1 << 2)
#define GRAIN_MASK      (1 << 3)
#define SCANLINE_MASK   (1 << 4) 
#define BLUR_MASK       (1 << 5)

in layout(location = 0) vec2 ftexcoord;
out layout(location = 0) vec4 ocolor;

uniform uint params = 0;
uniform float time = 0;
uniform float intensity = 1.0;
uniform vec3 tint = vec3(1);

layout(binding = 0) uniform sampler2D screenTexture;

float random(vec2 st) 
{
	return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

vec4 invert(in vec4 color)
{
	return vec4(vec3(1, 1, 1) - vec3(color), color.a);
}

vec4 grayscale(in vec4 color)
{
	return vec4(vec3(0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b), color.a);
}

vec4 colortint(in vec4 color)
{
	return color * vec4(tint, 1);
}

vec4 grain(in vec4 color)
{
	return color * random(gl_FragCoord.xy + time);
}

vec4 scanline(in vec4 color)
{
	return (int(gl_FragCoord.y) % 2 != 0) ? vec4(0, 0, 0, 1) : color;
}

vec4 blur()
{
	// get texture size and calculate size of a pizel in uv coordinates (step_size = uv pixel)
	ivec2 texture_size = textureSize(screenTexture, 0);
	vec2 step_size = 1.0 / texture_size;

	//pixels to sample (o = center pixel)
	// x x x
	// x o x
	// x x x 
	vec2 offsets[9] = vec2[](
		vec2(-step_size.x, -step_size.y),
		vec2( 0.0f,        -step_size.y),
		vec2( step_size.x, -step_size.y),
		vec2(-step_size.x,  0.0f),
		vec2( 0.0f,         0.0f),
		vec2( step_size.x,  0.0f),
		vec2(-step_size.x, +step_size.y),
		vec2( 0.0f,        +step_size.y),
		vec2( step_size.x,  step_size.y)
	);

	//outline operation to perform on pixels
	float kernel[9] = float[](
		1,  1,  1,
		1, -8,  1,
		1,  1,  1
	);

	/*
	//sharpen operation to perform on pixels
	float kernel[9] = float[](
		-1, -1, -1,
		-1,  9, -1,
		-1, -1, -1
	);
	
	/*
	// blur operation to perform on pixels
	float kernel[9] = float[](
		1 / 16.0, 2 / 16.0, 1 / 16.0,
		2 / 16.0, 4 / 16.0, 2 / 16.0,
		1 / 16.0, 2 / 16.0, 1 / 16.0
	);
	*/
	vec4 color = vec4(0.0);
	for(int i = 0; i < 9; i++)
	{
		color += texture(screenTexture, ftexcoord + offsets[i]) * kernel[i];
	}

	color.a = 1.0;

	return color;
}

void main()
{
	vec4 basecolor = texture(screenTexture, ftexcoord);
	vec4 postprocess = basecolor;

	if (bool(params & INVERT_MASK)) postprocess = invert(postprocess);
	if (bool(params & GRAYSCALE_MASK)) postprocess = grayscale(postprocess);
	if (bool(params & COLORTINT_MASK)) postprocess = colortint(postprocess);
	if (bool(params & GRAIN_MASK)) postprocess = grain(postprocess);
	if (bool(params & SCANLINE_MASK)) postprocess = scanline(postprocess);
	if (bool(params & BLUR_MASK)) postprocess = blur();

	ocolor = mix(basecolor, postprocess, intensity);
}
