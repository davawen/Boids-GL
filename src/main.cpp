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
	
	glfwSetKeyCallback(window,
		[](GLFWwindow *window, int key, int, int action, int)
		{
			if(key == GLFW_KEY_C && action == GLFW_PRESS) glfwSetInputMode(window, GLFW_CURSOR, glfwGetInputMode(window, GLFW_CURSOR) == GLFW_CURSOR_DISABLED ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED );
		}
	);

	gl::VertexDescriptor layout;

	layout.append_attribute("position", { .index = 0, .size = 3, .type = GL_FLOAT, .offset = 0 }); // Positions (x, y, z)
	layout.append_attribute("normal", { .index = 1, .size = 3, .type = GL_FLOAT, .offset = sizeof(float)*3 }); // Normals (x, y, z)
	layout.append_attribute("texCoord", { .index = 2, .size = 2, .type = GL_FLOAT, .offset = sizeof(float)*6 });  // Textures (u, v)

	gl::Model cube;
	gl::Model lightCube;

	auto cubeVertexBuffer = gl::VertexBuffer();

	{
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

		cubeVertexBuffer.set_data(vertices, sizeof(vertices), GL_STATIC_DRAW);

		cube.bind();
		cube.set_vbo(&cubeVertexBuffer, 36, layout);
		cube.unbind();

		lightCube.bind();
		lightCube.set_vbo(&cubeVertexBuffer, 36, layout);
		lightCube.unbind();
	}

	gl::Model cone;

	auto coneVertexBuffer = gl::VertexBuffer();
	auto coneIndexBuffer = gl::IndexBuffer();

	{
		auto [coneVertices, coneIndices] = shape::generate_unit_cone(layout);

		coneVertexBuffer.set_data(coneVertices.data(), coneVertices.size()*sizeof(GLfloat), GL_STATIC_DRAW);

		coneIndexBuffer.set_data(coneIndices.data(), coneIndices.size()*sizeof(GLuint), GL_STATIC_DRAW);

		cone.bind();
		cone.set_vbo(&coneVertexBuffer, coneVertices.size(), layout);
		cone.set_ebo(&coneIndexBuffer, coneIndices.size());
		cone.unbind();
	}

	// Set up texture parameters and contents
	stbi_set_flip_vertically_on_load(true);

	gl::Texture texture(gl::Texture::Target::TEXTURE_2D);

	{
		texture.set_parameter(gl::Texture::Parameter::WRAP_S, GL_MIRRORED_REPEAT);
		texture.set_parameter(gl::Texture::Parameter::WRAP_T, GL_MIRRORED_REPEAT);

		texture.set_parameter(gl::Texture::Parameter::MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		texture.set_parameter(gl::Texture::Parameter::MAG_FILTER, GL_NEAREST);

		stb::Image image("assets/container.jpg");

		texture.storage_2D(4, GL_RGBA8, image.width, image.height);
		texture.subimage_2D(0, 0, 0, image.width, image.height, GL_RGB, GL_UNSIGNED_BYTE, image.data);

		texture.generate_mipmap();
	}

	gl::Texture tAwesomeFace{gl::Texture::Target::TEXTURE_2D};

	{
		tAwesomeFace.set_parameter(gl::Texture::Parameter::WRAP_S, GL_MIRRORED_REPEAT);
		tAwesomeFace.set_parameter(gl::Texture::Parameter::WRAP_T, GL_MIRRORED_REPEAT);

		tAwesomeFace.set_parameter(gl::Texture::Parameter::MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		tAwesomeFace.set_parameter(gl::Texture::Parameter::MAG_FILTER, GL_LINEAR);

		stb::Image image("assets/awesomeface.png");

		tAwesomeFace.storage_2D(4, GL_RGBA8, image.width, image.height);
		tAwesomeFace.subimage_2D(0, 0, 0, image.width, image.height, GL_RGBA, GL_UNSIGNED_BYTE, image.data);

		tAwesomeFace.generate_mipmap();
	}
	
	gl::ShaderProgram shader(read_file("assets/shaders/basic.vert"), read_file("assets/shaders/basic.frag"));
	shader.use(); // Use program before setting uniforms

	shader.set_uniform("Texture1", 0);
	shader.set_uniform("Texture2", 1);

	gl::ShaderProgram lightingShader(read_file("assets/shaders/light.vert"), read_file("assets/shaders/light.frag"));

	lightingShader.use();

	lightingShader.set_uniform("uObjectColor", glm::vec3(1.0f, 0.5f, 0.31f));
	lightingShader.set_uniform("uLightColor", glm::vec3(1.0f, 1.0f, 1.0f));

	gl::ShaderProgram lightSourceShader(read_file("assets/shaders/light.vert"), read_file("assets/shaders/white.frag"));

	struct Camera
	{
		glm::vec3 position = { 0.0f, 0.0f, 3.0f };
		glm::vec3 orientation = { 0.0f, 0.0f, -1.0f };
		glm::vec3 directions = { -M_PI_4, 0.0f, 0.0f };
		const glm::vec3 up = { 0.0f, 1.0f, 0.0f };
	} camera;


	if(glfwRawMouseMotionSupported()) glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	glm::vec2d oldMousePos;
	glfwGetCursorPos(window, &oldMousePos.x, &oldMousePos.y);

	{
		int xpos, ypos;
		glfwGetWindowPos(window, &xpos, &ypos);

		oldMousePos.x += xpos;
		oldMousePos.y += ypos;
	}

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

		{
			int xpos, ypos;
			glfwGetWindowPos(window, &xpos, &ypos);

			mousePos.x += xpos;
			mousePos.y += ypos;
		}

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

		//glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f), glm::vec3(0.f, 1.f, 0.0f));
		glm::mat4 view(1.0f);
		view = glm::lookAt(camera.position, camera.position + camera.orientation, camera.up);

		glm::mat4 projection = glm::perspective(glm::pi<float>()/2.f, 800.f / 600.f, 0.1f, 100.0f);

		// shader.use();
		// shader.set_uniform("uView", view);
		// shader.set_uniform("uProjection", projection);

		const glm::vec3 lightPos(1.5f, 1.0f, 2.0f);

		lightingShader.use();
		lightingShader.set_uniform("uView", view);
		lightingShader.set_uniform("uProjection", projection);
		lightingShader.set_uniform("uLightPos", lightPos);

		texture.bind(gl::Texture::Target::TEXTURE_2D, GL_TEXTURE0);
		tAwesomeFace.bind(gl::Texture::Target::TEXTURE_2D, GL_TEXTURE1);

		{
			glm::mat4 modelMat(1.0f);
			//modelMat = glm::translate(modelMat, glm::vec3(3.0f, 0.f, -3.0f));
			modelMat = glm::rotate(modelMat, (float)glfwGetTime(), glm::vec3(0.f, 1.f, 0.f));

			lightingShader.set_uniform("uModel", modelMat);
			lightingShader.set_uniform("uNormal", glm::transpose(glm::inverse(modelMat)));

			cube.bind();
			cube.draw(GL_TRIANGLES);
			cube.unbind();
		}

		{
			glm::mat4 modelMat(1.0f);

			modelMat = glm::translate(modelMat, glm::vec3(3.0f, 0.f, 0.f));
			modelMat = glm::rotate(modelMat, (float)glfwGetTime(), glm::vec3(1.f, 0.f, 0.f));

			lightingShader.set_uniform("uModel", modelMat);
			lightingShader.set_uniform("uNormal", glm::transpose(glm::inverse(modelMat)));

			cone.bind();
			cone.draw(GL_TRIANGLES);
			cone.unbind();
		}

		lightSourceShader.use();
		lightSourceShader.set_uniform("uView", view);
		lightSourceShader.set_uniform("uProjection", projection);
		
		{
			glm::mat4 modelMat(1.0f);
			modelMat = glm::translate(modelMat, lightPos);
			modelMat = glm::scale(modelMat, glm::vec3(0.2f));

			lightSourceShader.set_uniform("uModel", modelMat);
			lightSourceShader.set_uniform("uNormal", glm::transpose(glm::inverse(modelMat)));

			lightCube.bind();
			lightCube.draw(GL_TRIANGLES);
			lightCube.unbind();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();


	return 0;
}
