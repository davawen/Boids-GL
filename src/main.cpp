#include <iostream>
#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "read_file.hpp"

#include "shader.hpp"
#include "shader_program.hpp"
#include "texture.hpp"

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	if(window == NULL)
	{
		std::cout << "Failed to created glfw window.\n";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if(glewInit() != GLEW_OK)
	{
		std::cout << "Failed to load GLEW\n";
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, 
		[](GLFWwindow *, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
	);

	GLfloat vertices[] = {
			// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left ;
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	// Copy data to VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	const size_t stride = sizeof(float)*8;

	// position (layout = 0)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);
	glEnableVertexAttribArray(0);

	// color (layout = 1)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void *)(sizeof(float)*3));
	glEnableVertexAttribArray(1);

	// textures (layout = 2)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void *)(sizeof(float)*6));
	glEnableVertexAttribArray(2);
	
	// Copy data to EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind VBO
	glBindVertexArray(0); // unbind VAO

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // unbind EBO after VAO

	// Set up texture
	stbi_set_flip_vertically_on_load(true);

	gl::Texture texture(gl::Texture::Target::TEXTURE_2D);

	texture.set_parameter(gl::Texture::Parameter::WRAP_S, GL_MIRRORED_REPEAT);
	texture.set_parameter(gl::Texture::Parameter::WRAP_T, GL_MIRRORED_REPEAT);

	texture.set_parameter(gl::Texture::Parameter::MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	texture.set_parameter(gl::Texture::Parameter::MAG_FILTER, GL_NEAREST);

	{
		int width, height, nrChannels;
		uint8_t *data = stbi_load("assets/container.jpg", &width, &height, &nrChannels, 0);

		if(!data)
		{
			std::cout << "Failed to load texture asset.\n";
			return -1;
		}

		texture.storage_2D(4, GL_RGBA8, width, height);
		texture.subimage_2D(0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

		texture.generate_mipmap();

		stbi_image_free(data);
	}

	gl::Texture tAwesomeFace{gl::Texture::Target::TEXTURE_2D};

	tAwesomeFace.set_parameter(gl::Texture::Parameter::WRAP_S, GL_MIRRORED_REPEAT);
	tAwesomeFace.set_parameter(gl::Texture::Parameter::WRAP_T, GL_MIRRORED_REPEAT);

	tAwesomeFace.set_parameter(gl::Texture::Parameter::MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	tAwesomeFace.set_parameter(gl::Texture::Parameter::MAG_FILTER, GL_LINEAR);

	{
		int width, height, nrChannels;
		uint8_t *data = stbi_load("assets/awesomeface.png", &width, &height, &nrChannels, 0);

		if(!data)
		{
			std::cout << "Failed to load texture asset.\n";
			return -1;
		}

		tAwesomeFace.storage_2D(4, GL_RGBA8, width, height);
		tAwesomeFace.subimage_2D(0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

		tAwesomeFace.generate_mipmap();

		stbi_image_free(data);
	}
	
	gl::ShaderProgram shader(read_file("assets/basic.vert"), read_file("assets/basic.frag"));
	shader.use(); // Use program before setting uniforms

	shader.set_int("Texture1", 0);
	shader.set_int("Texture2", 1);

	while(!glfwWindowShouldClose(window))
	{
		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
		
		// Logic


		// Rendering
		glClearColor(.2f, .3f, .3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();

		texture.bind(gl::Texture::Target::TEXTURE_2D, GL_TEXTURE0);
		tAwesomeFace.bind(gl::Texture::Target::TEXTURE_2D, GL_TEXTURE1);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(*indices), GL_UNSIGNED_INT, NULL);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();


	return 0;
}
