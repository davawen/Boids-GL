#include <functional>
#include <stack>

#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "engine/event.hpp"

namespace engine
{
	class EventManager
	{
		private:
			GLFWwindow *window;

			std::vector<Event> eventStack;

			// GLFW callbacks
			static void c_KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
			static void c_CursorPosCallback(GLFWwindow *window, double xpos, double ypos);
			static void c_CursorEnterCallback(GLFWwindow *window, int entered);
			static void c_MouseButtonCallback(GLFWwindow *window, int button, int action, int mods);


		public:
			EventManager(GLFWwindow *window);

			/*
			 * Pops an event from the event stack and puts it in `ev`.
			 * @param[out] ev
			 * @returns True if the returned event is not empty, else false
			 */
			bool poll_event(Event *ev);

			const GLFWwindow *get_window() const;
	};
}
