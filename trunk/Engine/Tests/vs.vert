

uniform float angle;
uniform float radius;


void main()
{
	//vec4 v = vec4(gl_Vertex);		
	//v.x = v.x + cos(angle) * radius;
	//v.y = v.y + sin(angle) * radius;

	//gl_FrontColor = gl_Color;
	//gl_Position = gl_ModelViewProjectionMatrix * v;

	gl_FrontColor = gl_Color;
	gl_Position = ftransform();

}


/*
void main()
{
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = ftransform();
} 
*/
