// catastrophe rpg engine
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.


#include <Catastrophe/Graphics/Vertex.h>
#include <Catastrophe/Graphics/GraphicsDevice.h>

#include "Script/MonoEngineBinding.h"


//(PrimitiveType primitiveType, ref T[] vertices, int first, int count, int stride, VertexElement[] elements);
void MonoEngineBinding::VertexArray_Render(
	int primitiveType,
	void* vertices,
	int first,
	int count,
	int stride,
	void* elements
)
{
	GraphicsDevice* graphicsDevice = GraphicsDevice::GetInstance();
	void* data = (void*)mono_array_addr_with_size((MonoArray*)vertices, 0, 0);
	int numElements = mono_array_length((MonoArray*)elements);
	const VertexElement* elementPtr = (VertexElement*)mono_array_addr_with_size((MonoArray*)elements, 0, 0);

	VertexFormat vertexFormat(elementPtr, numElements, stride);
	graphicsDevice->DrawVertices(primitiveType, data, first, count, vertexFormat);
}


void MonoEngineBinding::BindVertexArray()
{
	mono_add_internal_call("CatastropheEngine.Graphics.VARenderer::VertexArray_Render", VertexArray_Render);
	//mono_add_internal_call("CatastropheEngine.Graphics.VertexArray::Test<T>", Test);
}

