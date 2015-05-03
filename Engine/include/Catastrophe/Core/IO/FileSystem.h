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

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/Containers/String.h"

CE_NAMESPACE_BEGIN


///
/// @FileSystem
///
/// Implements platform-specific file handling and querying.
///

class CE_API FileSystem
{
public:

	/// Sets the current working directory for the current process.
	bool SetCurrentDirectory(const String& path);

	/// Gets the current working directory for the current process.
	String GetCurrentWorkingDirectory() const;

	/// Creates a new directory. Returns true if successful or if the directory already exists.
	bool CreateDirectory(const String& path) { return CreateDirectoryImpl(path); }

	/// Does a complete binary copy of a file from one location to another.
	bool CopyFile(const String& existingFileName, const String& newFileName)
	{
		return CopyFileImpl(existingFileName, newFileName);
	}

	/// Renames a file.
	bool Rename(const String& oldFileName, const String& newFileName);

	/// Hard deletes the file or directory at path.
	bool Remove(const String& path);

	/// Returns true if the path is a valid file or directory
	bool Exists(const String& path) const;

	/// Returns true if the path is a file and the file exists.
	bool IsFile(const String& path) const;

	/// Returns true if the path is a valid directory path.
	bool IsDirectory(const String& path) const;

	/// Gets whether the file is read-only.
	bool IsReadOnly(const String& path) const;

	/// Checks whether the file or directory is hidden.
	bool IsHidden(const String& path) const;

	/// Gets the filesize of a file on disk.
	u32 GetFileSize(const String& path) const;

	void ScanDirectory(StringVector& outFilenames, const String& path, const String& filter = "*.*") const;

protected:
	bool CreateDirectoryImpl(const String& path);
	bool CopyFileImpl(const String& existingFileName, const String& newFileName);

};


CE_NAMESPACE_END

