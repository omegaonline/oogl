///////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2016 Rick Taylor
//
// This file is part of OOGL, the Omega Online OpenGL library.
//
// OOGL is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// OOGL is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with OOGL.  If not, see <http://www.gnu.org/licenses/>.
//
///////////////////////////////////////////////////////////////////////////////////

#ifndef OOGL_WINDOW_H_INCLUDED
#define OOGL_WINDOW_H_INCLUDED

#include "OOGL.h"

#include <OOBase/Delegate.h>

namespace OOGL
{
	class State;
	class StateFns;
	class Framebuffer;

	class Window : public OOBase::NonCopyable
	{
		friend class State;
		friend class StateFns;

	public:
		enum Style
		{
			eWSvisible = 1,
			eWSresizable = 2,
			eWSdecorated = 4,
			eWSdebug_context = 8
		};

		Window(int width, int height, const char* title, unsigned int style = eWSdecorated, GLFWmonitor* monitor = NULL);
		~Window();

		bool valid() const;

		bool visible() const;
		void show(bool visible = true);

		bool iconified() const;
		void iconify(bool minimize);

		glm::uvec2 size() const;
		glm::vec2 dots_per_mm() const;

		glm::dvec2 cursor_pos() const;

		const OOBase::SharedPtr<Framebuffer>& default_frame_buffer() const;

		void make_current() const;
		void draw() const;

		OOBase::Delegate1<void,const Window&,OOBase::ThreadLocalAllocator> on_close(const OOBase::Delegate1<void,const Window&,OOBase::ThreadLocalAllocator>& delegate);
		OOBase::Delegate2<void,const Window&,State&,OOBase::ThreadLocalAllocator> on_draw(const OOBase::Delegate2<void,const Window&,State&,OOBase::ThreadLocalAllocator>& delegate);
		OOBase::Delegate2<void,const Window&,const glm::uvec2&,OOBase::ThreadLocalAllocator> on_sized(const OOBase::Delegate2<void,const Window&,const glm::uvec2&,OOBase::ThreadLocalAllocator>& delegate);
		OOBase::Delegate2<void,const Window&,const glm::ivec2&,OOBase::ThreadLocalAllocator> on_moved(const OOBase::Delegate2<void,const Window&,const glm::ivec2&,OOBase::ThreadLocalAllocator>& delegate);
		OOBase::Delegate3<void,const Window&,unsigned int,int,OOBase::ThreadLocalAllocator> on_character(const OOBase::Delegate3<void,const Window&,unsigned int,int,OOBase::ThreadLocalAllocator>& delegate);
		OOBase::Delegate2<void,const Window&,const glm::dvec2&,OOBase::ThreadLocalAllocator> on_cursormove(const OOBase::Delegate2<void,const Window&,const glm::dvec2&,OOBase::ThreadLocalAllocator>& delegate);
		OOBase::Delegate2<void,const Window&,bool,OOBase::ThreadLocalAllocator> on_cursorenter(const OOBase::Delegate2<void,const Window&,bool,OOBase::ThreadLocalAllocator>& delegate);
		OOBase::Delegate2<void,const Window&,bool,OOBase::ThreadLocalAllocator> on_focus(const OOBase::Delegate2<void,const Window&,bool,OOBase::ThreadLocalAllocator>& delegate);
		OOBase::Delegate2<void,const Window&,bool,OOBase::ThreadLocalAllocator> on_iconify(const OOBase::Delegate2<void,const Window&,bool,OOBase::ThreadLocalAllocator>& delegate);

		struct key_stroke_t
		{
			int key;
			int scancode;
			int action;
			int mods;
		};
		OOBase::Delegate2<void,const Window&,const key_stroke_t&,OOBase::ThreadLocalAllocator> on_keystroke(const OOBase::Delegate2<void,const Window&,const key_stroke_t&,OOBase::ThreadLocalAllocator>& delegate);

		struct mouse_click_t
		{
			unsigned int button;
			bool down;
			int mods;
		};
		OOBase::Delegate2<void,const Window&,const mouse_click_t&,OOBase::ThreadLocalAllocator> on_mousebutton(const OOBase::Delegate2<void,const Window&,const mouse_click_t&,OOBase::ThreadLocalAllocator>& delegate);

	private:
		GLFWwindow* m_glfw_window;

		OOBase::SharedPtr<Framebuffer> m_default_fb;
		OOBase::SharedPtr<State>       m_state;

		OOBase::Delegate1<void,const Window&,OOBase::ThreadLocalAllocator> m_on_close;
		OOBase::Delegate2<void,const Window&,State&,OOBase::ThreadLocalAllocator> m_on_draw;
		OOBase::Delegate2<void,const Window&,const glm::uvec2&,OOBase::ThreadLocalAllocator> m_on_sized;
		OOBase::Delegate2<void,const Window&,const glm::ivec2&,OOBase::ThreadLocalAllocator> m_on_moved;
		OOBase::Delegate3<void,const Window&,unsigned int,int,OOBase::ThreadLocalAllocator> m_on_character;
		OOBase::Delegate2<void,const Window&,const key_stroke_t&,OOBase::ThreadLocalAllocator> m_on_keystroke;
		OOBase::Delegate2<void,const Window&,const glm::dvec2&,OOBase::ThreadLocalAllocator> m_on_cursormove;
		OOBase::Delegate2<void,const Window&,bool,OOBase::ThreadLocalAllocator> m_on_cursorenter;
		OOBase::Delegate2<void,const Window&,const mouse_click_t&,OOBase::ThreadLocalAllocator> m_on_mousebutton;
		OOBase::Delegate2<void,const Window&,bool,OOBase::ThreadLocalAllocator> m_on_focus;
		OOBase::Delegate2<void,const Window&,bool,OOBase::ThreadLocalAllocator> m_on_iconify;

		GLFWmonitor* monitor() const;

		static void cb_on_move(GLFWwindow* window, int left, int top);
		static void cb_on_size(GLFWwindow* window, int width, int height);
		static void cb_on_close(GLFWwindow* window);
		static void cb_on_focus(GLFWwindow* window, int focused);
		static void cb_on_iconify(GLFWwindow* window, int iconified);
		static void cb_on_refresh(GLFWwindow* window);
		static void cb_on_character(GLFWwindow* window, unsigned int codepoint, int mods);
		static void cb_on_key(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void cb_on_mouse_wheel(GLFWwindow* window, double xoffset, double yoffset);
		static void cb_on_cursor_enter(GLFWwindow* window, int entered);
		static void cb_on_cursor_pos(GLFWwindow* window, double xpos, double ypos);
		static void cb_on_mouse_btn(GLFWwindow* window, int button, int action, int mods);

		void screen_to_fb(double& xpos, double& ypos);
	};
}

#endif // OOGL_WINDOW_H_INCLUDED
