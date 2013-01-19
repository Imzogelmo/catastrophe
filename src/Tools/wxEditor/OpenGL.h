//////////////////////////////////////////////////////////////////////////
// This program is free software: you can redistribute it and/or modify //
// it under the terms of the GNU General Public License as published by //
// the Free Software Foundation, either version 3 of the License, or    //
// (at your option) any later version.                                  //
//                                                                      //
// This program is distributed in the hope that it will be useful,      //
// but WITHOUT ANY WARRANTY; without even the implied warranty of       //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        //
// GNU General Public License for more details.                         //
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "Forward.h"


namespace OpenGL
{
	void InitOpenGL();
	bool IsOpenGLInitialized();
	void SetOrtho( const wxRect& rect );
	void ClearFrameBuffer( const Colorf& backColor = Colorf::Black(0.f) );
	void DisableBatchRendering();
	void EnableBatchRendering();

	void DrawThickOutlineRect( Primitive* primitive, 
			wxRect rect, 
			const Color& color = Color::Fuchsia(255), 
			const Color& frame = Color::Fuchsia(128) 
		);

	template<class T> inline //wxGLWindow..?
	void PrepareRenderingContext( T _this, wxGLContext *_ctx )
	{
		#ifndef __WXMOTIF__
			if (!_ctx)
				return;
		#endif

		//set shared glContext to current
		_this->SetCurrent(*_ctx);

		if( !IsOpenGLInitialized() )
			InitOpenGL();
	}


} //namespace OpenGL

