#include <glm/glm.hpp>

#include <wrap/gl/model.hpp>

namespace boids
{
	class Boid
	{
	private:
		const gl::Model &model;

		glm::vec3 position;
		glm::vec3 velocity;

	public:
		Boid(const gl::Model &model);

		void update(float deltatime);

		/**
		 * Doesn't need to be used if the `render()` function is called.
		 * Can be useful for instanced rendering
		 * @returns A model matrix which corresponds to this boid's position and orientation
		 */
		glm::mat4 construct_model_matrix();
		void render();
	};
}
