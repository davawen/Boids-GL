#include <vector>
#include <cmath>
#include <cstdlib>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_trigonometric.hpp>
#include <glm/fwd.hpp>
#include <glm/vector_relational.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "read_file.hpp"

#include "wrap/stb/image.hpp"

#include "wrap/gl/shader.hpp"
#include "wrap/gl/shader_program.hpp"
#include "wrap/gl/texture.hpp"
#include "wrap/gl/model.hpp"
#include "shapes.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace glm
{
	using vec2d = glm::vec<2, double, glm::defaultp>;
}

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
	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(window, 
		[](GLFWwindow *, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
	);

	GLfloat vertices[] = {
// Pos   X      Y      Z      Normals   
//       |      |      |      X     Y     Z      Texture Coordinates
//       |      |      |      |     |     |     U     V
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f
	};

	GLuint indices[] = {
		0, 1, 2,
		2, 3, 1,
		0, 4, 1,
		0, 4, 2,
		2, 4, 3,
		3, 4, 1
	};

	gl::Layout layout(sizeof(float)*8,
	{ 
		{ .index = 0, .size = 3, .type = GL_FLOAT, .offset = 0 }, // Positions (x, y, z)
		{ .index = 1, .size = 3, .type = GL_FLOAT, .offset = sizeof(float)*3 }, // Normals (x, y, z)
		{ .index = 2, .size = 2, .type = GL_FLOAT, .offset = sizeof(float)*6 }  // Textures (u, v)
	});

	gl::Model model{};

	{
		auto vertexBuffer = gl::VertexBuffer();
		vertexBuffer.set_data(vertices, sizeof(vertices), GL_STATIC_DRAW);

		model.bind();
		model.set_vbo(vertexBuffer, 36, layout);
		model.unbind();
	}

	gl::Model cone{};

	{
		std::vector<GLfloat> coneVertices;
		std::vector<GLuint> coneIndices;

		shape::generate_unit_cone(coneVertices, coneIndices, layout.stride, 0, layout[1]->offset, layout[2]->offset);

		auto vertexBuffer = gl::VertexBuffer();
		vertexBuffer.set_data(coneVertices.data(), coneVertices.size()*sizeof(GLfloat), GL_STATIC_DRAW);

		auto indexBuffer = gl::IndexBuffer();
		indexBuffer.set_data(coneIndices.data(), coneIndices.size()*sizeof(GLuint), GL_STATIC_DRAW);

		cone.bind();
		cone.set_vbo(vertexBuffer, coneVertices.size(), layout);
		cone.set_ebo(indexBuffer, coneIndices.size());
		cone.unbind();
	}


	// Set up texture
	stbi_set_flip_vertically_on_load(true);

	gl::Texture texture(gl::Texture::Target::TEXTURE_2D);

	texture.set_parameter(gl::Texture::Parameter::WRAP_S, GL_MIRRORED_REPEAT);
	texture.set_parameter(gl::Texture::Parameter::WRAP_T, GL_MIRRORED_REPEAT);

	texture.set_parameter(gl::Texture::Parameter::MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	texture.set_parameter(gl::Texture::Parameter::MAG_FILTER, GL_NEAREST);

	stb::Image image("assets/container.jpg");

	texture.storage_2D(4, GL_RGBA8, image.width, image.height);
	texture.subimage_2D(0, 0, 0, image.width, image.height, GL_RGB, GL_UNSIGNED_BYTE, image.data);

	texture.generate_mipmap();

	gl::Texture tAwesomeFace{gl::Texture::Target::TEXTURE_2D};

	tAwesomeFace.set_parameter(gl::Texture::Parameter::WRAP_S, GL_MIRRORED_REPEAT);
	tAwesomeFace.set_parameter(gl::Texture::Parameter::WRAP_T, GL_MIRRORED_REPEAT);

	tAwesomeFace.set_parameter(gl::Texture::Parameter::MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	tAwesomeFace.set_parameter(gl::Texture::Parameter::MAG_FILTER, GL_LINEAR);

	image.load("assets/awesomeface.png");

	tAwesomeFace.storage_2D(4, GL_RGBA8, image.width, image.height);
	tAwesomeFace.subimage_2D(0, 0, 0, image.width, image.height, GL_RGBA, GL_UNSIGNED_BYTE, image.data);

	tAwesomeFace.generate_mipmap();
	
	gl::ShaderProgram shader(read_file("assets/shaders/basic.vert"), read_file("assets/shaders/basic.frag"));
	shader.use(); // Use program before setting uniforms

	shader.set_uniform("Texture1", 0);
	shader.set_uniform("Texture2", 1);

	glm::vec3 cubePositions[10];
	glm::vec3 cubeSpeeds[10];
	for(size_t i = 0; i < 10; i++)
	{
		cubePositions[i] = glm::vec3(rand() / (float)RAND_MAX * 10.f - 5.f, rand() / (float)RAND_MAX * 10.f,  rand() / (float)RAND_MAX * -5.f);
		cubeSpeeds[i] = { rand() / (float)RAND_MAX - .5f, 0.f, rand() / (float)RAND_MAX - .5f };
	}

	struct Camera
	{
		glm::vec3 position = { 0.0f, 0.0f, 3.0f };
		glm::vec3 orientation = { 0.0f, 0.0f, -1.0f };
		glm::vec3 directions = { -M_PI_4, 0.0f, 0.0f };
		const glm::vec3 up = { 0.0f, 1.0f, 0.0f };
	} camera;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if(glfwRawMouseMotionSupported()) glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	glm::vec2d oldMousePos;
	glfwGetCursorPos(window, &oldMousePos.x, &oldMousePos.y);

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while(!glfwWindowShouldClose(window))
	{
		{
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
		}

		// Logic

		float cameraSpeed = 2.5f * deltaTime;

		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
		if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.position += camera.orientation * cameraSpeed;
		if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.position -= camera.orientation * cameraSpeed;
		if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.position += glm::normalize(glm::cross(camera.orientation, camera.up)) * cameraSpeed;
		if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.position -= glm::normalize(glm::cross(camera.orientation, camera.up)) * cameraSpeed;

		glm::vec2d mousePos;

		glfwGetCursorPos(window, &mousePos.x, &mousePos.y);

		//int diffx = (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) - (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS);
		glm::vec2 diff = mousePos - oldMousePos;

		if(diff.x != 0 || diff.y != 0)
		{
			camera.directions += glm::vec3(diff.x, -diff.y, 0.f) / 150.f; // world y and viewport y are inverted

			if(camera.directions.y > glm::radians(89.f)) camera.directions.y = glm::radians(89.f);
			else if(camera.directions.y < glm::radians(-89.f)) camera.directions.y = glm::radians(-89.f);

			camera.orientation.x = glm::cos(camera.directions.x) * glm::cos(camera.directions.y);
			camera.orientation.y = glm::sin(camera.directions.y);
			camera.orientation.z = glm::sin(camera.directions.x) * glm::cos(camera.directions.y);

			oldMousePos = mousePos;
		}

		


		// Rendering
		glClearColor(.2f, .3f, .3f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.use();

		//glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f), glm::vec3(0.f, 1.f, 0.0f));
		glm::mat4 view(1.0f);
		view = glm::lookAt(camera.position, camera.position + camera.orientation, camera.up);

		glm::mat4 projection = glm::perspective(glm::pi<float>()/2.f, 800.f / 600.f, 0.1f, 100.0f);

		shader.set_uniform("uView", view);
		shader.set_uniform("uProjection", projection);

		model.bind();

		texture.bind(gl::Texture::Target::TEXTURE_2D, GL_TEXTURE0);
		tAwesomeFace.bind(gl::Texture::Target::TEXTURE_2D, GL_TEXTURE1);

		for(size_t i = 0; i < 10; i++)
		{
			glm::mat4 modelMat(1.0f);
			modelMat = glm::translate(modelMat, cubePositions[i]);
			modelMat = glm::rotate(modelMat, (float)glfwGetTime() + i, glm::normalize(glm::vec3( 1.f, 0.f, 0.f )));

			shader.set_uniform("uModel", modelMat);

			model.draw(GL_TRIANGLES);
		}

		model.unbind();
		
		{
			glm::mat4 modelMat(1.0f);
			modelMat = glm::rotate(modelMat, (float)glfwGetTime(), glm::normalize(glm::vec3(1.0f, 1.0f, 0.0f)));

			shader.set_uniform("uModel", modelMat);

			cone.bind();
			cone.draw(GL_TRIANGLES);
			cone.unbind();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();


	return 0;
}
