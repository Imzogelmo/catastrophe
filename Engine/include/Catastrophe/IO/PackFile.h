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

#include <fc/vector_map.h>

#include "Deserializer.h"
#include "Serializer.h"

CE_NAMESPACE_BEGIN


struct PackFileEntry
{
	u32 offset;
	u32 compressedSize;
	u32 uncompressedSize;
}


class CE_API PackFile
{
public:
	typedef fc::map<String, PackFileEntry> map_type;

	PackFile();
	PackFile(const String& filename, u32 startOffset = 0);

	virtual ~PackFile();

	bool Open(const String& filename, u32 startOffset = 0);
	bool EntryExists(const String& filename) const;

	const PackFileEntry* GetEntry(const String& filename) const;
	const map_type& GetEntries() const { return m_fileEntries; }
	const String& GetFileName() const { return m_filename; }

	u32 GetNumFiles() const { return m_fileEntries.size(); }
	u32 GetTotalSize() const { return m_totalSize; }

	bool IsCompressed() const { return m_isCompressed; }

protected:
	String		m_filename;
	map_type	m_fileEntries;
	u32			m_totalSize;
	bool		m_isCompressed;

};


CE_NAMESPACE_END
