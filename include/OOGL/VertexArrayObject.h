#ifndef OOGL_VERTEXARRAYOBJECT_H_INCLUDED
#define OOGL_VERTEXARRAYOBJECT_H_INCLUDED

#include "OOGL.h"

#include <OOBase/Table.h>

namespace OOGL
{
	class State;
	class StateFns;
	class BufferObject;

	class VertexArrayObject : public OOBase::NonCopyable, public OOBase::EnableSharedFromThis<VertexArrayObject>
	{
		friend class OOBase::AllocateNewStatic<OOBase::ThreadLocalAllocator>;
		friend class State;
		friend class StateFns;

	public:
		VertexArrayObject();
		~VertexArrayObject();

		bool valid() const;

		static OOBase::SharedPtr<VertexArrayObject> none();

		OOBase::SharedPtr<OOGL::VertexArrayObject> bind();
		OOBase::SharedPtr<OOGL::VertexArrayObject> unbind();

		void attribute_i(GLuint index, const OOBase::SharedPtr<BufferObject>& buffer, GLint components, GLenum type, GLsizei stride = 0, GLsizeiptr offset = 0);
		void attribute(GLuint index, const OOBase::SharedPtr<BufferObject>& buffer, GLint components, GLenum type, bool normalized, GLsizei stride = 0, GLsizeiptr offset = 0);

		void attribute_divisor(GLuint index, GLuint divisor);

		void enable_attribute(GLuint index, bool enable = true);
		void disable_attribute(GLuint index)
		{
			return enable_attribute(index,false);
		}

		OOBase::SharedPtr<BufferObject> element_array(const OOBase::SharedPtr<BufferObject>& buffer);
		const OOBase::SharedPtr<BufferObject>& element_array() const;

		void draw(GLenum mode, GLint first, GLsizei count);
		void multi_draw(GLenum mode, const GLint* firsts, const GLsizei* counts, GLsizei drawcount);

		void draw_instanced(GLenum mode, GLint first, GLsizei count, GLsizei instances);
		void draw_instanced(GLenum mode, GLint first, GLsizei count, GLsizei instances, GLuint baseinstance);

		void draw_elements(GLenum mode, GLsizei count, GLenum type, GLsizeiptr offset = 0);
		void draw_elements(GLenum mode, GLsizei count, GLenum type, GLsizeiptr offset, GLint basevertex);
		void draw_elements(GLenum mode, GLuint min_val, GLuint max_val, GLsizei count, GLenum type, GLsizeiptr offset = 0);
		void draw_elements(GLenum mode, GLuint min_val, GLuint max_val, GLsizei count, GLenum type, GLsizeiptr offset, GLint basevertex);
		void multi_draw_elements(GLenum mode, const GLsizei* counts, GLenum type, const GLsizeiptr* offsets, GLsizei drawcount);
		void multi_draw_elements(GLenum mode, const GLsizei* counts, GLenum type, const GLsizeiptr* offsets, GLsizei drawcount, const GLint* basevertices);

		void draw_elements_instanced(GLenum mode, GLsizei count, GLenum type, GLsizeiptr offset, GLsizei instances);
		void draw_elements_instanced(GLenum mode, GLsizei count, GLenum type, GLsizeiptr offset, GLsizei instances, GLint basevertex);
		void draw_elements_instanced(GLenum mode, GLsizei count, GLenum type, GLsizeiptr offset, GLsizei instances, GLint basevertex, GLuint baseinstance);

	private:
		State* const    m_state;
		StateFns* const m_state_fns;
		GLuint          m_array;

		OOBase::Table<GLuint,OOBase::SharedPtr<BufferObject>,OOBase::Less<GLuint>,OOBase::ThreadLocalAllocator> m_attributes;
		OOBase::SharedPtr<BufferObject> m_element_array;

		VertexArrayObject(GLuint array);
	};
}

#endif /// OOGL_VERTEXARRAYOBJECT_H_INCLUDED
