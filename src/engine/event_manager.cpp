#include "engine/event_manager.hpp"
#include <GLFW/glfw3.h>

namespace engine
{
	EventManager::EventManager(GLFWwindow *window)
	{
		this->window = window;

		glfwSetWindowUserPointer(window, this);

		glfwSetKeyCallback(window, c_KeyCallback);
		glfwSetCursorPosCallback(window, c_CursorPosCallback);
		glfwSetCursorEnterCallback(window, c_CursorEnterCallback);
		glfwSetMouseButtonCallback(window, c_MouseButtonCallback);
	}

	// =======
	// Private Functions
	// =======
	
	void EventManager::c_KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
	{
		auto *self = static_cast<EventManager *>(glfwGetWindowUserPointer(window));

		// Forwards call to engine
		Event ev = {
			.type = action == GLFW_RELEASE ? Event::KEY_RELEASE : Event::KEY_PRESS,
			.keyboard = {
				.key = key, .scancode = scancode, .action = action, .mods = mods
			}
		};

		self->eventStack.push_back(ev);
	}

	void EventManager::c_CursorPosCallback(GLFWwindow *window, double xpos, double ypos)
	{
		auto *self = static_cast<EventManager *>(glfwGetWindowUserPointer(window));

		Event ev = {
			.type = Event::CURSOR_POS,
			.cursor = {
				.pos = { xpos, ypos }
			}
		};

		self->eventStack.push_back(ev);
	}

	void EventManager::c_CursorEnterCallback(GLFWwindow *window, int entered)
	{
		auto *self = static_cast<EventManager *>(glfwGetWindowUserPointer(window));

		Event ev = {
			.type = Event::CURSOR_ENTERED,
			.cursor = {
				.entered = !!entered // Convert to bool
			}
		};

		self->eventStack.push_back(ev);
	}

	void EventManager::c_MouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
	{
		auto *self = static_cast<EventManager *>(glfwGetWindowUserPointer(window));

		Event ev = {
			.type = action == GLFW_PRESS ? Event::MOUSE_PRESS : Event::MOUSE_RELEASE,
			.mouse = {
				.button = button,
				.action = action,
				.mods = mods
			}
		};

		self->eventStack.push_back(ev);
	}

	// =======
	// Public functions
	// =======
	bool EventManager::poll_event(Event *ev)
	{
		if(ev == NULL) return false;

		if(eventStack.empty())
		{
			ev->type = Event::EVENT_EMPTY;
			return false;
		}
		
		*ev = eventStack.back();
		eventStack.pop_back();

		return true;
	}

	const GLFWwindow *EventManager::get_window() const
	{
		return window;
	}
}
