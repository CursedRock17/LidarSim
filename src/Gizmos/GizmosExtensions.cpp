#include "../../include/Gizmos_Headers/GizmosExtensions.h"

// Start of the Shader Class //
Shader::Shader(){};
Shader::~Shader(){};

void Shader::CreateShaders(const char* vertexPath, const char* fragmentPath){ 
    //Going to immediatily load in our shading files
    vertexFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try { 
	//Copying the glsl files into cpp code
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);

        std::stringstream VertexStreamString, FragmentStreamString; 
        VertexStreamString << vertexFile.rdbuf();
        FragmentStreamString << fragmentFile.rdbuf();

        vertexFile.close();
        fragmentFile.close();

        vertexBuffer = VertexStreamString.str();
        fragmentBuffer = FragmentStreamString.str();

    } catch (std::ifstream::failure& e){
        std::cout << e.what() << std::endl;
    }

    const char* vertexShaderSource = vertexBuffer.c_str();
    const char* fragmentShaderSource = fragmentBuffer.c_str();

    //Compile the vertex shader through glsl
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    
    //Checking errors in this shader
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "Vertex Shader failed to compile: " << infoLog << '\n';
    }

    //Creating the fragment shader for these shapes
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "Frag Shader failed to compile: " << infoLog << '\n';
    }

    //Creating and Linking a Shader program by adding all of the shading pieces
    shaderProgram = glCreateProgram();

    //Linking Shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
    }

    //Cleanup after the project is used
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
};

//- - - - - - End of Shader Code - - - - - -//


// End of the Shader Class //

// Start of Framebuffer Class
Framebuffer::Framebuffer(){}
Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &FBO);
}


void Framebuffer::BindFramebuffer()
{
	//Set up the Framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);
	//Need to Recall GLvewport because screen size changed
	glViewport(0, 0, 1024, 800);
}


void Framebuffer::UnbindFramebuffer()
{
	//Can Remove Everything From inside Framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::FramebufferTexture(int imageH, int imageW)
{
	// This function will allow use to take our gizmos and convert it to a texture through the framebuffef
	glGenFramebuffers(1, &FBO);
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	//Create a New Texture to Showcase
	glGenTextures(1, &RTO);
	glBindTexture(GL_TEXTURE_2D, RTO);

	//Turn our Rendered Object into our Rendered Texture (RTO)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageW, imageH, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	//Set up the actual temperary texture in the RenderTextures Function
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, RTO, 0);

	//Create Depth Testing within the texture
	glGenRenderbuffers(1, &DBO);
	glBindRenderbuffer(GL_RENDERBUFFER, DBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, imageW, imageH);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, DBO);
	
	//Error Check - See if the framebuffer works
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer is current Failing; It's not complete" << std::endl;

	UnbindFramebuffer();

	// Draw as a wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

unsigned int Framebuffer::GetFramebufferTexture()
{
	//Simple Getter Function that allows us to showcase the object we turn into a texture
	return RTO;
}

// End of Framebuffer Class
 
// Start of Instanced Objects Class
InstancedObject::InstancedObject(){}
InstancedObject::~InstancedObject(){}

void InstancedObject::PrepareObjects(std::vector<float> vertices, int objectPoints, int objectAmount )
{
	totalObjectPoints = objectPoints;
	objectCount = objectAmount;
/*	//Have to convert the vector to a pure array so we can pass as a pointer
	float verts[vertices.size()];
	for(int i = 0; i < vertices.size(); i++){
		verts[i] = vertices.at(i);		
	}

	//We can create our own VBO for this new object without a VAO because it's one continous object
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts) * objectAmount, &verts, GL_STATIC_DRAW );
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(2, 1);
*/

}


void InstancedObject::RenderingLoop()
{
//	glDrawArraysInstanced(GL_TRIANGLES, 0, totalObjectPoints, (GLsizei)objectCount);
	glColor3f(1.0f, 1.0f, 1.0f);

    // Enable the vertex array
    glEnableClientState(GL_VERTEX_ARRAY);

    // Create the vertex data for the grid
    GLfloat vertes[(21*2+21*2)*2];
    for (int i = -10; i <= 10; i++) {
        // Horizontal lines
        vertes[(i+10)*4+0] = -10.0f;
        vertes[(i+10)*4+1] = i;
        vertes[(i+10)*4+2] = 10.0f;
        vertes[(i+10)*4+3] = i;

        // Vertical lines
        vertes[(i+10)*4+4] = i;
        vertes[(i+10)*4+5] = -10.0f;
        vertes[(i+10)*4+6] = i;
        vertes[(i+10)*4+7] = 10.0f;
    }
    // Bind the vertex data
    glVertexPointer(2, GL_FLOAT, 0, vertes);

    // Draw the grid lines
    glDrawArrays(GL_LINES, 0, (21*2+21*2));

    // Disable the vertex array
    glDisableClientState(GL_VERTEX_ARRAY);
}


// End of Instanced Objects Class
