// GLSL shader autogenerated by cg2glsl.py.
#if defined(VERTEX)

#if __VERSION__ >= 130
#define COMPAT_VARYING out
#define COMPAT_ATTRIBUTE in
#define COMPAT_TEXTURE texture
#else
#define COMPAT_VARYING varying
#define COMPAT_ATTRIBUTE attribute
#define COMPAT_TEXTURE texture2D
#endif

#ifdef GL_ES
#define COMPAT_PRECISION mediump
#else
#define COMPAT_PRECISION
#endif
COMPAT_VARYING     float _frame_rotation;
COMPAT_VARYING     vec4 _color1;
struct output_dummy {
    vec4 _color1;
};
struct input_dummy {
    vec2 _video_size;
    vec2 _texture_size;
    vec2 _output_dummy_size;
    float _frame_count;
    float _frame_direction;
    float _frame_rotation;
};
vec4 _oPosition1;
vec4 _r0005;
COMPAT_ATTRIBUTE vec4 gl_Vertex;
COMPAT_ATTRIBUTE vec4 COLOR;
COMPAT_ATTRIBUTE vec4 gl_MultiTexCoord0;
COMPAT_VARYING vec4 COL0;
COMPAT_VARYING vec4 TEX0;
 
uniform int FrameDirection;
uniform int FrameCount;
uniform COMPAT_PRECISION vec2 OutputSize;
uniform COMPAT_PRECISION vec2 TextureSize;
uniform COMPAT_PRECISION vec2 InputSize;
void main()
{
    vec4 _oColor;
    vec2 _otexCoord;
    _r0005 = gl_Vertex.x*gl_ModelViewProjectionMatrix[0];
    _r0005 = _r0005 + gl_Vertex.y*gl_ModelViewProjectionMatrix[1];
    _r0005 = _r0005 + gl_Vertex.z*gl_ModelViewProjectionMatrix[2];
    _r0005 = _r0005 + gl_Vertex.w*gl_ModelViewProjectionMatrix[3];
    _oPosition1 = _r0005;
    _oColor = COLOR;
    _otexCoord = gl_MultiTexCoord0.xy;
    gl_Position = _r0005;
    COL0 = COLOR;
    TEX0.xy = gl_MultiTexCoord0.xy;
} 
#elif defined(FRAGMENT)

#if __VERSION__ >= 130
#define COMPAT_VARYING in
#define COMPAT_TEXTURE texture
out vec4 FragColor;
#else
#define COMPAT_VARYING varying
#define FragColor gl_FragColor
#define COMPAT_TEXTURE texture2D
#endif

#ifdef GL_ES
#ifdef GL_FRAGMENT_PRECISION_HIGH
precision highp float;
#else
precision mediump float;
#endif
#define COMPAT_PRECISION mediump
#else
#define COMPAT_PRECISION
#endif
COMPAT_VARYING     float _frame_rotation;
COMPAT_VARYING     vec4 _color;
struct output_dummy {
    vec4 _color;
};
struct input_dummy {
    vec2 _video_size;
    vec2 _texture_size;
    vec2 _output_dummy_size;
    float _frame_count;
    float _frame_direction;
    float _frame_rotation;
};
vec3 _TMP3;
vec3 _TMP2;
vec3 _TMP1;
vec3 _TMP0;
vec3 _TMP10;
vec3 _TMP9;
vec3 _TMP8;
vec4 _TMP14;
float _TMP13;
float _TMP12;
input_dummy _IN1;
uniform sampler2D Texture;
vec2 _x0019;
float _x0021;
float _TMP22;
float _ax0023;
float _x0023;
float _TMP26;
float _ax0027;
float _x0027;
float _TMP30;
float _ax0031;
float _TMP34;
float _ax0035;
float _x0035;
float _x0039;
float _TMP40;
float _ax0041;
float _x0041;
float _TMP44;
float _ax0045;
float _x0045;
float _TMP48;
float _ax0049;
float _TMP52;
float _ax0053;
float _x0053;
vec2 _c0061;
vec2 _c0065;
vec2 _c0069;
vec2 _c0073;
float _ypos0075;
vec2 _c0079;
vec2 _c0083;
vec2 _c0087;
vec2 _c0091;
float _ypos0093;
vec2 _c0097;
vec2 _c0101;
vec2 _c0105;
vec2 _c0109;
float _ypos0111;
vec2 _c0115;
vec2 _c0119;
vec2 _c0123;
vec2 _c0127;
COMPAT_VARYING vec4 TEX0;
 
uniform int FrameDirection;
uniform int FrameCount;
uniform COMPAT_PRECISION vec2 OutputSize;
uniform COMPAT_PRECISION vec2 TextureSize;
uniform COMPAT_PRECISION vec2 InputSize;
void main()
{
    vec2 _stepxy;
    vec2 _pos;
    vec2 _f;
    vec4 _linetaps1;
    vec4 _columntaps;
    vec2 _xystart;
    vec4 _xpos2;
    output_dummy _OUT;
    vec3 _TMP17;
    _stepxy = vec2(1.00000000E+00/TextureSize.x, 1.00000000E+00/TextureSize.y);
    _pos = TEX0.xy + _stepxy*5.00000000E-01;
    _x0019 = _pos/_stepxy;
    _f = fract(_x0019);
    _x0021 = 1.00000000E+00 - _f.x;
    _x0023 = _x0021 - 2.00000000E+00;
    _ax0023 = abs(_x0023);
    if (_ax0023 < 1.00000000E+00) { 
        _TMP12 = _x0023*_x0023;
        _TMP22 = (_TMP12*(7.50000000E+00*_ax0023 + -1.35000000E+01) + 6.00000000E+00)/6.00000000E+00;
    } else {
        if (_ax0023 >= 1.00000000E+00 && _ax0023 < 2.00000000E+00) { 
            _TMP13 = _x0023*_x0023;
            _TMP22 = (_TMP13*(-4.50000000E+00*_ax0023 + 2.25000000E+01) + -3.60000000E+01*_ax0023 + 1.80000000E+01)/6.00000000E+00;
        } else {
            _TMP22 = 0.00000000E+00;
        } 
    } 
    _x0027 = _x0021 - 1.00000000E+00;
    _ax0027 = abs(_x0027);
    if (_ax0027 < 1.00000000E+00) { 
        _TMP12 = _x0027*_x0027;
        _TMP26 = (_TMP12*(7.50000000E+00*_ax0027 + -1.35000000E+01) + 6.00000000E+00)/6.00000000E+00;
    } else {
        if (_ax0027 >= 1.00000000E+00 && _ax0027 < 2.00000000E+00) { 
            _TMP13 = _x0027*_x0027;
            _TMP26 = (_TMP13*(-4.50000000E+00*_ax0027 + 2.25000000E+01) + -3.60000000E+01*_ax0027 + 1.80000000E+01)/6.00000000E+00;
        } else {
            _TMP26 = 0.00000000E+00;
        } 
    } 
    _ax0031 = abs(_x0021);
    if (_ax0031 < 1.00000000E+00) { 
        _TMP12 = _x0021*_x0021;
        _TMP30 = (_TMP12*(7.50000000E+00*_ax0031 + -1.35000000E+01) + 6.00000000E+00)/6.00000000E+00;
    } else {
        if (_ax0031 >= 1.00000000E+00 && _ax0031 < 2.00000000E+00) { 
            _TMP13 = _x0021*_x0021;
            _TMP30 = (_TMP13*(-4.50000000E+00*_ax0031 + 2.25000000E+01) + -3.60000000E+01*_ax0031 + 1.80000000E+01)/6.00000000E+00;
        } else {
            _TMP30 = 0.00000000E+00;
        } 
    } 
    _x0035 = _x0021 + 1.00000000E+00;
    _ax0035 = abs(_x0035);
    if (_ax0035 < 1.00000000E+00) { 
        _TMP12 = _x0035*_x0035;
        _TMP34 = (_TMP12*(7.50000000E+00*_ax0035 + -1.35000000E+01) + 6.00000000E+00)/6.00000000E+00;
    } else {
        if (_ax0035 >= 1.00000000E+00 && _ax0035 < 2.00000000E+00) { 
            _TMP13 = _x0035*_x0035;
            _TMP34 = (_TMP13*(-4.50000000E+00*_ax0035 + 2.25000000E+01) + -3.60000000E+01*_ax0035 + 1.80000000E+01)/6.00000000E+00;
        } else {
            _TMP34 = 0.00000000E+00;
        } 
    } 
    _linetaps1 = vec4(_TMP22, _TMP26, _TMP30, _TMP34);
    _x0039 = 1.00000000E+00 - _f.y;
    _x0041 = _x0039 - 2.00000000E+00;
    _ax0041 = abs(_x0041);
    if (_ax0041 < 1.00000000E+00) { 
        _TMP12 = _x0041*_x0041;
        _TMP40 = (_TMP12*(7.50000000E+00*_ax0041 + -1.35000000E+01) + 6.00000000E+00)/6.00000000E+00;
    } else {
        if (_ax0041 >= 1.00000000E+00 && _ax0041 < 2.00000000E+00) { 
            _TMP13 = _x0041*_x0041;
            _TMP40 = (_TMP13*(-4.50000000E+00*_ax0041 + 2.25000000E+01) + -3.60000000E+01*_ax0041 + 1.80000000E+01)/6.00000000E+00;
        } else {
            _TMP40 = 0.00000000E+00;
        } 
    } 
    _x0045 = _x0039 - 1.00000000E+00;
    _ax0045 = abs(_x0045);
    if (_ax0045 < 1.00000000E+00) { 
        _TMP12 = _x0045*_x0045;
        _TMP44 = (_TMP12*(7.50000000E+00*_ax0045 + -1.35000000E+01) + 6.00000000E+00)/6.00000000E+00;
    } else {
        if (_ax0045 >= 1.00000000E+00 && _ax0045 < 2.00000000E+00) { 
            _TMP13 = _x0045*_x0045;
            _TMP44 = (_TMP13*(-4.50000000E+00*_ax0045 + 2.25000000E+01) + -3.60000000E+01*_ax0045 + 1.80000000E+01)/6.00000000E+00;
        } else {
            _TMP44 = 0.00000000E+00;
        } 
    } 
    _ax0049 = abs(_x0039);
    if (_ax0049 < 1.00000000E+00) { 
        _TMP12 = _x0039*_x0039;
        _TMP48 = (_TMP12*(7.50000000E+00*_ax0049 + -1.35000000E+01) + 6.00000000E+00)/6.00000000E+00;
    } else {
        if (_ax0049 >= 1.00000000E+00 && _ax0049 < 2.00000000E+00) { 
            _TMP13 = _x0039*_x0039;
            _TMP48 = (_TMP13*(-4.50000000E+00*_ax0049 + 2.25000000E+01) + -3.60000000E+01*_ax0049 + 1.80000000E+01)/6.00000000E+00;
        } else {
            _TMP48 = 0.00000000E+00;
        } 
    } 
    _x0053 = _x0039 + 1.00000000E+00;
    _ax0053 = abs(_x0053);
    if (_ax0053 < 1.00000000E+00) { 
        _TMP12 = _x0053*_x0053;
        _TMP52 = (_TMP12*(7.50000000E+00*_ax0053 + -1.35000000E+01) + 6.00000000E+00)/6.00000000E+00;
    } else {
        if (_ax0053 >= 1.00000000E+00 && _ax0053 < 2.00000000E+00) { 
            _TMP13 = _x0053*_x0053;
            _TMP52 = (_TMP13*(-4.50000000E+00*_ax0053 + 2.25000000E+01) + -3.60000000E+01*_ax0053 + 1.80000000E+01)/6.00000000E+00;
        } else {
            _TMP52 = 0.00000000E+00;
        } 
    } 
    _columntaps = vec4(_TMP40, _TMP44, _TMP48, _TMP52);
    _linetaps1 = _linetaps1/(_linetaps1.x + _linetaps1.y + _linetaps1.z + _linetaps1.w);
    _columntaps = _columntaps/(_columntaps.x + _columntaps.y + _columntaps.z + _columntaps.w);
    _xystart = (-1.50000000E+00 - _f)*_stepxy + _pos;
    _xpos2 = vec4(_xystart.x, _xystart.x + _stepxy.x, _xystart.x + _stepxy.x*2.00000000E+00, _xystart.x + _stepxy.x*3.00000000E+00);
    _c0061 = vec2(_xpos2.x, _xystart.y);
    _TMP14 = COMPAT_TEXTURE(Texture, _c0061);
    _TMP8 = _TMP14.xyz;
    _c0065 = vec2(_xpos2.y, _xystart.y);
    _TMP14 = COMPAT_TEXTURE(Texture, _c0065);
    _TMP9 = _TMP14.xyz;
    _c0069 = vec2(_xpos2.z, _xystart.y);
    _TMP14 = COMPAT_TEXTURE(Texture, _c0069);
    _TMP10 = _TMP14.xyz;
    _c0073 = vec2(_xpos2.w, _xystart.y);
    _TMP14 = COMPAT_TEXTURE(Texture, _c0073);
    _TMP0 = _TMP8*_linetaps1.x + _TMP9*_linetaps1.y + _TMP10*_linetaps1.z + _TMP14.xyz*_linetaps1.w;
    _ypos0075 = _xystart.y + _stepxy.y;
    _c0079 = vec2(_xpos2.x, _ypos0075);
    _TMP14 = COMPAT_TEXTURE(Texture, _c0079);
    _TMP8 = _TMP14.xyz;
    _c0083 = vec2(_xpos2.y, _ypos0075);
    _TMP14 = COMPAT_TEXTURE(Texture, _c0083);
    _TMP9 = _TMP14.xyz;
    _c0087 = vec2(_xpos2.z, _ypos0075);
    _TMP14 = COMPAT_TEXTURE(Texture, _c0087);
    _TMP10 = _TMP14.xyz;
    _c0091 = vec2(_xpos2.w, _ypos0075);
    _TMP14 = COMPAT_TEXTURE(Texture, _c0091);
    _TMP1 = _TMP8*_linetaps1.x + _TMP9*_linetaps1.y + _TMP10*_linetaps1.z + _TMP14.xyz*_linetaps1.w;
    _ypos0093 = _xystart.y + _stepxy.y*2.00000000E+00;
    _c0097 = vec2(_xpos2.x, _ypos0093);
    _TMP14 = COMPAT_TEXTURE(Texture, _c0097);
    _TMP8 = _TMP14.xyz;
    _c0101 = vec2(_xpos2.y, _ypos0093);
    _TMP14 = COMPAT_TEXTURE(Texture, _c0101);
    _TMP9 = _TMP14.xyz;
    _c0105 = vec2(_xpos2.z, _ypos0093);
    _TMP14 = COMPAT_TEXTURE(Texture, _c0105);
    _TMP10 = _TMP14.xyz;
    _c0109 = vec2(_xpos2.w, _ypos0093);
    _TMP14 = COMPAT_TEXTURE(Texture, _c0109);
    _TMP2 = _TMP8*_linetaps1.x + _TMP9*_linetaps1.y + _TMP10*_linetaps1.z + _TMP14.xyz*_linetaps1.w;
    _ypos0111 = _xystart.y + _stepxy.y*3.00000000E+00;
    _c0115 = vec2(_xpos2.x, _ypos0111);
    _TMP14 = COMPAT_TEXTURE(Texture, _c0115);
    _TMP8 = _TMP14.xyz;
    _c0119 = vec2(_xpos2.y, _ypos0111);
    _TMP14 = COMPAT_TEXTURE(Texture, _c0119);
    _TMP9 = _TMP14.xyz;
    _c0123 = vec2(_xpos2.z, _ypos0111);
    _TMP14 = COMPAT_TEXTURE(Texture, _c0123);
    _TMP10 = _TMP14.xyz;
    _c0127 = vec2(_xpos2.w, _ypos0111);
    _TMP14 = COMPAT_TEXTURE(Texture, _c0127);
    _TMP3 = _TMP8*_linetaps1.x + _TMP9*_linetaps1.y + _TMP10*_linetaps1.z + _TMP14.xyz*_linetaps1.w;
    _TMP17 = _TMP0*_columntaps.x + _TMP1*_columntaps.y + _TMP2*_columntaps.z + _TMP3*_columntaps.w;
    _OUT._color = vec4(_TMP17.x, _TMP17.y, _TMP17.z, 1.00000000E+00);
    FragColor = _OUT._color;
    return;
} 
#endif
