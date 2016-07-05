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

#include "../include/OOGL/VertexArrayObject.h"
#include "../include/OOGL/State.h"
#include "../include/OOGL/BufferObject.h"
#include "../include/OOGL/StateFns.h"

OOGL::VertexArrayObject::VertexArrayObject() :
		m_state(State::get_current().get()),
		m_state_fns(StateFns::get_current().get()),
		m_array(0)
{
	m_state_fns->glGenVertexArrays(1,&m_array);
}

OOGL::VertexArrayObject::VertexArrayObject(GLuint array) :
		m_state(State::get_current().get()),
		m_state_fns(StateFns::get_current().get()),
		m_array(array)
{
}

OOBase::SharedPtr<OOGL::VertexArrayObject> OOGL::VertexArrayObject::none()
{
	return OOBase::allocate_shared<VertexArrayObject,OOBase::ThreadLocalAllocator>(0);
}

OOGL::VertexArrayObject::~VertexArrayObject()
{
	if (m_array)
		m_state_fns->glDeleteVertexArrays(1,&m_array);
}

bool OOGL::VertexArrayObject::valid() const
{
	return (m_array != 0);
}

OOBase::SharedPtr<OOGL::VertexArrayObject> OOGL::VertexArrayObject::bind()
{
	return m_state->bind(shared_from_this());
}

OOBase::SharedPtr<OOGL::VertexArrayObject> OOGL::VertexArrayObject::unbind()
{
	return m_state->bind(OOBase::SharedPtr<OOGL::VertexArrayObject>());
}

void OOGL::VertexArrayObject::attribute_i(GLuint index, const OOBase::SharedPtr<BufferObject>& buffer, GLint components, GLenum type, GLsizei stride, GLsizeiptr offset)
{
	m_state->bind(shared_from_this());

	assert(buffer->target() == GL_ARRAY_BUFFER);
	m_state->bind(buffer);

	m_state_fns->glVertexAttribIPointer(index,components,type,stride,reinterpret_cast<const GLvoid*>(offset));

	OOBase::Table<GLuint,OOBase::SharedPtr<BufferObject>,OOBase::Less<GLuint>,OOBase::ThreadLocalAllocator>::iterator i = m_attributes.find(index);
	if (i)
		i->second = buffer;
	else
		m_attributes.insert(index,buffer);
}

void OOGL::VertexArrayObject::attribute(GLuint index, const OOBase::SharedPtr<BufferObject>& buffer, GLint components, GLenum type, bool normalized, GLsizei stride, GLsizeiptr offset)
{
	m_state->bind(shared_from_this());

	assert(buffer->target() == GL_ARRAY_BUFFER);
	m_state->bind(buffer);

	m_state_fns->glVertexAttribPointer(index,components,type,normalized ? GL_TRUE : GL_FALSE,stride,reinterpret_cast<const GLvoid*>(offset));

	OOBase::Table<GLuint,OOBase::SharedPtr<BufferObject>,OOBase::Less<GLuint>,OOBase::ThreadLocalAllocator>::iterator i = m_attributes.find(index);
	if (i)
		i->second = buffer;
	else
		m_attributes.insert(index,buffer);
}

void OOGL::VertexArrayObject::enable_attribute(GLuint index, bool enable)
{
	if (enable)
		m_state_fns->glEnableVertexArrayAttrib(shared_from_this(),index);
	else
		m_state_fns->glDisableVertexArrayAttrib(shared_from_this(),index);
}

OOBase::SharedPtr<OOGL::BufferObject> OOGL::VertexArrayObject::element_array(const OOBase::SharedPtr<BufferObject>& buffer)
{
	OOBase::SharedPtr<OOGL::BufferObject> prev = m_element_array;
	if (buffer != m_element_array)
	{
		bind();

		prev = m_element_array;
		m_element_array = buffer;

		m_state->bind(buffer);
	}
	return prev;
}

const OOBase::SharedPtr<OOGL::BufferObject>& OOGL::VertexArrayObject::element_array() const
{
	return m_element_array;
}

void OOGL::VertexArrayObject::draw(GLenum mode, GLint first, GLsizei count)
{
	m_state->bind(shared_from_this());
	glDrawArrays(mode,first,count);

	OOGL_CHECK("glDrawArrays");
}

void OOGL::VertexArrayObject::draw_instanced(GLenum mode, GLint first, GLsizei count, GLsizei instances)
{
	m_state->bind(shared_from_this());
	m_state_fns->glDrawArraysInstanced(mode,first,count,instances);
}

void OOGL::VertexArrayObject::draw_instanced(GLenum mode, GLint first, GLsizei count, GLsizei instances, GLuint baseinstance)
{
	m_state->bind(shared_from_this());
	if (baseinstance)
		m_state_fns->glDrawArraysInstancedBaseInstance(mode,first,count,instances,baseinstance);
	else
		m_state_fns->glDrawArraysInstanced(mode,first,count,instances);
}

void OOGL::VertexArrayObject::multi_draw(GLenum mode, const GLint* firsts, const GLsizei* counts, GLsizei drawcount)
{
	m_state->bind(shared_from_this());
	m_state_fns->glMultiDrawArrays(mode,firsts,counts,drawcount);
}

void OOGL::VertexArrayObject::draw_elements(GLenum mode, GLsizei count, GLenum type, GLsizeiptr offset)
{
	m_state->bind(shared_from_this());
	glDrawElements(mode,count,type,(const void*)offset);

	OOGL_CHECK("glDrawElements");
}

void OOGL::VertexArrayObject::draw_elements(GLenum mode, GLsizei count, GLenum type, GLsizeiptr offset, GLint basevertex)
{
	m_state->bind(shared_from_this());
	if (basevertex)
		m_state_fns->glDrawElementsBaseVertex(mode,count,type,offset,basevertex);
	else
	{
		glDrawElements(mode,count,type,(const void*)offset);
		OOGL_CHECK("glDrawElements");
	}
}

void OOGL::VertexArrayObject::draw_elements(GLenum mode, GLuint min_val, GLuint max_val, GLsizei count, GLenum type, GLsizeiptr offset)
{
	m_state->bind(shared_from_this());
	m_state_fns->glDrawRangeElements(mode,min_val,max_val,count,type,offset);
}

void OOGL::VertexArrayObject::draw_elements(GLenum mode, GLuint min_val, GLuint max_val, GLsizei count, GLenum type, GLsizeiptr offset, GLint basevertex)
{
	m_state->bind(shared_from_this());
	if (!basevertex)
		m_state_fns->glDrawRangeElements(mode,min_val,max_val,count,type,offset);
	else
		m_state_fns->glDrawRangeElementsBaseVertex(mode,min_val,max_val,count,type,offset,basevertex);
}

void OOGL::VertexArrayObject::multi_draw_elements(GLenum mode, const GLsizei* counts, GLenum type, const GLsizeiptr* offsets, GLsizei drawcount)
{
	m_state->bind(shared_from_this());
	m_state_fns->glMultiDrawElements(mode,counts,type,offsets,drawcount);
}

void OOGL::VertexArrayObject::multi_draw_elements(GLenum mode, const GLsizei* counts, GLenum type, const GLsizeiptr* offsets, GLsizei drawcount, const GLint* basevertices)
{
	m_state->bind(shared_from_this());
	if (!basevertices)
		m_state_fns->glMultiDrawElements(mode,counts,type,offsets,drawcount);
	else
		m_state_fns->glMultiDrawElementsBaseVertex(mode,counts,type,offsets,drawcount,basevertices);
}

void OOGL::VertexArrayObject::draw_elements_instanced(GLenum mode, GLsizei count, GLenum type, GLsizeiptr offset, GLsizei instances)
{
	m_state->bind(shared_from_this());
	m_state_fns->glDrawElementsInstanced(mode,count,type,offset,instances);
}

void OOGL::VertexArrayObject::draw_elements_instanced(GLenum mode, GLsizei count, GLenum type, GLsizeiptr offset, GLsizei instances, GLint basevertex)
{
	m_state->bind(shared_from_this());
	if (!basevertex)
		m_state_fns->glDrawElementsInstanced(mode,count,type,offset,instances);
	else
		m_state_fns->glDrawElementsInstancedBaseVertex(mode,count,type,offset,instances,basevertex);
}

void OOGL::VertexArrayObject::draw_elements_instanced(GLenum mode, GLsizei count, GLenum type, GLsizeiptr offset, GLsizei instances, GLint basevertex, GLuint baseinstance)
{
	m_state->bind(shared_from_this());
	if (!basevertex)
	{
		if (!baseinstance)
			m_state_fns->glDrawElementsInstanced(mode,count,type,offset,instances);
		else
			m_state_fns->glDrawElementsInstancedBaseInstance(mode,count,type,offset,instances,baseinstance);
	}
	else
	{
		if (!baseinstance)
			m_state_fns->glDrawElementsInstancedBaseVertex(mode,count,type,offset,instances,basevertex);
		else
			m_state_fns->glDrawElementsInstancedBaseVertexBaseInstance(mode,count,type,offset,instances,basevertex,baseinstance);
	}
}
