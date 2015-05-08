#ifndef SHADER_H
#define SHADER_H

class Shader {
	public:
		static GLuint loadShaders(const char *vertex_file_path, const char *fragment_file_path);
};

#endif
