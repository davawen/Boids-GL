#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/vec2.hpp>

namespace engine
{
	struct Event
	{
		enum Type
		{
			EVENT_EMPTY,
			KEY_PRESS,
			KEY_RELEASE,
			KEY_REPEAT,
			KEY_UKNOWN,
			CURSOR_POS,
			CURSOR_ENTERED,
			MOUSE_PRESS,
			MOUSE_RELEASE
		} type;

		struct
		{
			/// GLFW key code of the pressed key
			int key;
			/// Unique scan code of the pressed key
			int scancode;
			/// The action is one of `GLFW_PRESS`, `GLFW_REPEAT` or `GLFW_RELEASE`. The key will be `GLFW_KEY_UNKNOWN` if GLFW lacks a key token for it.
			int action;
			/// Modifier bits (ctrl, shift, etc...). `GLFW_MOD_*` constant;
			int mods;
		} keyboard;

		struct
		{
			/// The current position of the cursor, relative to the top-left of the window.
			glm::vec<2, double, glm::defaultp> pos;
			/// True if the cursor entered the window, false if it left the window.
			bool entered;
		} cursor;
		
		struct
		{
			/// Mouse button pressed. `GLFW_MOUSE_BUTTON_*` constant.
			int button;
			/// The action is one of `GLFW_PRESS` or `GLFW_RELEASE`.
			int action;
			/// Modifier bits. `GLFW_MOD_*` constant;
			int mods;
		} mouse;
	};
}
