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

#ifndef OOGL_FRAMEBUFFER_H_INCLUDED
#define OOGL_FRAMEBUFFER_H_INCLUDED

#include "OOGL.h"

namespace OOGL
{
	class State;

	class Framebuffer : public OOBase::NonCopyable
	{
		friend class OOBase::AllocateNewStatic<OOBase::ThreadLocalAllocator>;
		friend class Window;
		friend class State;

	public:
		Framebuffer();
		~Framebuffer();

		bool valid() const;

		GLenum check() const;

	private:
		GLuint       m_id;
		bool         m_default;

		Framebuffer(GLuint id);
		static OOBase::SharedPtr<Framebuffer> get_default();
	};
}

#endif // OOGL_FRAMEBUFFER_H_INCLUDED
