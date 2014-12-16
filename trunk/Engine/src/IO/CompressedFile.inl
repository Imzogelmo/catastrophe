// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "Common.h"
#include "IO/CompressedFile.h"
#include "IO/Compression.h"

#include <cstdio>

#ifdef _MSC_VER
	#pragma warning ( push )
	#pragma warning ( disable : 4996 )
#endif

CE_NAMESPACE_BEGIN


CompressedFile::CompressedFile() :
	FileBuffer(),
	m_file()
{
}


CompressedFile::CompressedFile( const String& filename, FileMode mode ) :
	FileBuffer(),
	m_file()
{
	Open(filename, mode);
}


CompressedFile::~CompressedFile()
{
	Close();
}


bool CompressedFile::Open( const String& filename, FileMode mode )
{
	m_file.Open(filename, mode);
	if( !m_file.IsOpen() )
		return false;

	return DecompressToFileBuffer(this, &m_file);
}


void CompressedFile::Close()
{
	if( !m_file.IsOpen() || m_file.GetMode() != FileWrite )
		return;

	if( CompressFromFileBuffer(&m_file, this) )
		m_file.Close();
}


bool CompressedFile::IsOpen() const
{
	return m_file.IsOpen();
}


#ifdef _MSC_VER
	#pragma warning ( pop )
#endif

CE_NAMESPACE_END
