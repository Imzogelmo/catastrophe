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

#pragma once

#include "PackFile.h"


CE_NAMESPACE_BEGIN


PackFile::PackFile() :
	m_filename(),
	m_fileEntries(),
	m_totalSize(0),
	m_isCompressed(false),
{
}


PackFile::PackFile(const String& filename, u32 startOffset) :
	m_filename(),
	m_fileEntries(),
	m_totalSize(0),
	m_isCompressed(false),
{
	Open(filename, startOffset);
}


PackFile::~PackFile()
{
}


bool PackFile::Open(const String& filename, u32 startOffset)
{
	File f(filename);

	if( !f.IsOpen() )
		return false;

	String id;
	id.Resize(4);
	f.Read(id.data(), 4);
	if( id != "UPAK" )
		return false;

	f.Seek(startOffset);
	m_totalSize = f.GetSize();
	u32 numFiles = f.ReadUInt();

	for (u32 i = 0; i < numFiles; ++i)
	{
		String name = f.ReadString();

		PackFileEntry entry;
		entry.offset = f.ReadUInt() + startOffset;
		entry.compressedSize = f.ReadUInt();
		entry.uncompressedSize = f.ReadUInt();

		if( offset > m_totalSize )
			return false;

		m_fileEntries[name] = entry;
	}

	return true;
}


bool PackFile::EntryExists(const String& filename) const
{
	return m_fileEntries.contains(filename);
}


const PackFileEntry* PackFile::GetEntry(const String& filename) const
{
	map_type::const_iterator it = m_fileEntries.find(filename);
	if( it != m_fileEntries.end() )
		return &it.second;

	return 0;
}





CE_NAMESPACE_END

