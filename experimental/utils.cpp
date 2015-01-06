#include <utils.h>


GLuint LoadShaders(std::string vertex_file,std::string fragment_file){
	return _LoadShaders(SHADER_PATH + vertex_file, SHADER_PATH + fragment_file);
}

GLuint _LoadShaders(std::string vertex_file_path,std::string fragment_file_path){
 
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
 
    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::string Line = "";
        while(getline(VertexShaderStream, Line))
            VertexShaderCode += "\n" + Line;
        VertexShaderStream.close();
    }
 
    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::string Line = "";
        while(getline(FragmentShaderStream, Line))
            FragmentShaderCode += "\n" + Line;
        FragmentShaderStream.close();
    }
 
    GLint Result = GL_FALSE;
    int InfoLogLength;
 
    // Compile Vertex Shader
    std::cout << "Compiling shader : " << vertex_file_path << "\n";
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);
 
    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
 
    // Compile Fragment Shader
    std::cout << "Compiling shader : " << fragment_file_path << "\n";
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);
 
    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
 
    // Link the program
    fprintf(stdout, "Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
 
    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> ProgramErrorMessage( std::max(InfoLogLength, int(1)) );
    glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
    fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
 
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
 
    return ProgramID;
}

GLuint loadDDS(std::string imagepath){
	return _loadDDS(IMAGES_PATH + imagepath);
}

GLuint _loadDDS(std::string imagepath){

	unsigned char header[124];

	FILE *fp;

	/* try to open the file */
	fp = fopen(imagepath.c_str(), "rb");
	if (fp == NULL)
	return 0;

	/* verify the type of file */
	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (std::strncmp(filecode, "DDS ", 4) != 0) {
	fclose(fp);
	return 0;
	}

	/* get the surface desc */
	fread(&header, 124, 1, fp); 

	unsigned int height      = *(unsigned int*)&(header[8 ]);
	unsigned int width         = *(unsigned int*)&(header[12]);
	unsigned int linearSize     = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC      = *(unsigned int*)&(header[80]);

	unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);
	/* close the file pointer */
	fclose(fp);

	//unsigned int components  = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch(fourCC)
	{
	case FOURCC_DXT1:
	format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
	break;
	case FOURCC_DXT3:
	format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
	break;
	case FOURCC_DXT5:
	format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
	break;
	default:
	free(buffer);
	return 0;
	}

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	/* load the mipmaps */
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width+3)/4)*((height+3)/4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
		0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;
	}
	free(buffer); 

	return textureID;
}

GLuint loadOBJ(std::string inputfile){

	return 0;

}

struct Entity loadModel(GLuint VertexArrayID, std::string inputfile){

	Entity result;

	glBindVertexArray(VertexArrayID);

	inputfile = "models/" + inputfile;
	std::vector<tinyobj::shape_t> shapes;

	std::string err = tinyobj::LoadObj(shapes, result.materials, inputfile.c_str(), "models/");

	if (!err.empty()) {
	  std::cerr << err << std::endl;
	  exit(1);
	}

	result.meshes.reserve(shapes.size());

	result.textures.reserve(result.materials.size());
	for (auto &material : result.materials){
		 struct Texture texture;
		 texture.diffuse = loadDDS(material.diffuse_texname);
		 texture.normal = loadDDS(material.normal_texname);
		 result.textures.push_back(texture);
	}

	for (auto &shape : shapes){
	
		tinyobj::mesh_t mesh = shape.mesh;

		struct Mesh newmesh;

		newmesh.materialId = mesh.material_ids[0];
		newmesh.indices = mesh.indices.size();
		
		// This will identify our vertex buffer
		glGenBuffers(1, &newmesh.vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, newmesh.vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, mesh.positions.size() * sizeof(float), mesh.positions.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &newmesh.uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, newmesh.uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, mesh.texcoords.size() * sizeof(float), mesh.texcoords.data(), GL_STATIC_DRAW);

		glGenBuffers(1, &newmesh.normalbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, newmesh.normalbuffer);
		glBufferData(GL_ARRAY_BUFFER, mesh.normals.size() * sizeof(float), mesh.normals.data(), GL_STATIC_DRAW);

		// Generate a buffer for the indices as well
		glGenBuffers(1, &newmesh.elementbuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newmesh.elementbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(unsigned int), mesh.indices.data() , GL_STATIC_DRAW);
		
		result.meshes.push_back(newmesh);
	}

	return result;

}
