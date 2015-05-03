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
#include "Catastrophe/Core/Containers/Vector.h"
#include "Catastrophe/Core/IO/FileSystem.h"

#ifdef WIN32
	#define WIN32_LEAN_AND_MEAN
	#define NOMINMAX
	#define NOGDI
	#include <windows.h>
	#include <direct.h>
#endif

CE_NAMESPACE_BEGIN


bool FileSystem::SetCurrentDirectory(const String& path)
{
	bool success = _chdir(path.CString()) == 0;
	if(success)
	{
		LogDebug("Changed current directory to " + path);
	}
	else
	{
		LogError("Failed to change directory to " + path);
	}

	return success;
}


String FileSystem::GetCurrentWorkingDirectory() const
{
	char path[MAX_PATH];
	Memory::Memset(&path, 0, MAX_PATH);
	getcwd(path, MAX_PATH);
	return String(path);
}


bool FileSystem::CreateDirectoryImpl(const String& path)
{
	if(IsDirectory(path))
		return false;

#ifdef WIN32
	return CreateDirectoryA(path.CString()) == TRUE;
#else
	return _mkdir(path.CString()) == 0;
#endif
}


bool FileSystem::CopyFileImpl(const String& existingFileName, const String& newFileName)
{
#ifdef WIN32
	if(::CopyFileA(existingFileName.CString(), newFileName.CString(), FALSE) == FALSE)
	{
		LogError("Error trying to copy file \"%s\" to \"%s\". Error Code: %i.",
			existingFileName.CString(),
			newFileName.CString(),
			GetLastError()
		);
	}
#else
	File srcFile;
	File destFile;
	MemoryFile fileBuffer;

	if( !srcFile.Open(existingFileName, FileRead) )
		return false;

	if( !destFile.Open(newFileName, FileWrite) )
		return false;

	fileBuffer.Resize(srcFile.Size());
	u32 bytesRead = srcFile.Read(fileBuffer.GetData(), srcFile.Size());
	u32 bytesWritten = destFile.Write(fileBuffer.GetData(), fileBuffer.Size());

	srcFile.Close();
	destFile.Close();

	return bytesRead == bytesWritten;
#endif

	return true;
}



bool FileSystem::Rename(const String& oldFileName, const String& newFileName)
{
#ifdef WIN32
	return MoveFileA(oldFileName.CString(), newFileName.CString()) != FALSE;
#else
	return rename(oldFileName.CString(), newFileName.CString()) == 0;
#endif
}


bool FileSystem::Remove(const String& path)
{
#ifdef WIN32
	if(IsDirectory(path))
	{
		if(RemoveDirectoryA(path.CString()) == FALSE)
		{
			LogError("Error trying to delete directory \"%s\". Error Code: %i.", path.CString(), GetLastError());
			return false;
		}
	}
	else
	{
		if(DeleteFileA(path.CString()) == FALSE)
		{
			LogError("Error trying to delete file \"%s\". Error Code: %i.", path.CString(), GetLastError());
			return false;
		}
	}

	return true;
#else
	return remove(path.CString()) == 0;
#endif
}


bool FileSystem::Exists(const String& path) const
{
	String str = path;
	str.RemoveTrailingSlash();

#ifdef WIN32
	return GetFileAttributesA(str.CString()) != INVALID_FILE_ATTRIBUTES;
#else
	struct stat st;
	return stat(str.CString(), &st) == 0;
#endif
}


bool FileSystem::IsFile(const String& path) const
{
#ifdef WIN32
	DWORD attributes = GetFileAttributesA(path.CString());
	if(attributes == INVALID_FILE_ATTRIBUTES || (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
		return false;
#else
	struct stat st;
	if(stat(path.CString(), &st) == 0)
		return S_ISFILE(st.st_mode);
#endif
	return true;
}


bool FileSystem::IsDirectory(const String& path) const
{
#ifdef WIN32
	DWORD attributes = GetFileAttributesA(path.CString());
	if(attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0)
		return true;
#else
	struct stat st;
	if(stat(path.CString(), &st) == 0)
		return S_ISDIR(st.st_mode);
#endif
	return false;
}


bool FileSystem::IsReadOnly(const String& path) const
{
#ifdef WIN32
	DWORD fileAttributes = GetFileAttributesA(path.CString());
	if(fileAttributes == INVALID_FILE_ATTRIBUTES)
		return true;

	return (fileAttributes & FILE_ATTRIBUTE_READONLY) != 0;
#elif
	struct stat st;
	if(stat(path.CString(), &st) == 0)
		return (st.st_mode & S_IROTH) != 0;

	return false;
#endif
}


bool FileSystem::IsHidden(const String& path) const
{
#ifdef WIN32
	DWORD fileAttributes = GetFileAttributesA(path.CString());
	if(fileAttributes == INVALID_FILE_ATTRIBUTES)
		return true;

	return (fileAttributes & FILE_ATTRIBUTE_HIDDEN) != 0;
#endif
}


u32 FileSystem::GetFileSize(const String& path) const
{
#ifdef WIN32
	WIN32_FILE_ATTRIBUTE_DATA fileAttributeData;
	if(GetFileAttributesExA(path.CString(), GetFileExInfoStandard, &fileAttributeData) == FALSE)
	{
		LogError("Error reading file size at \"%s\". Error Code: %i.", path.CString(), GetLastError());
		return 0;
	}

	LARGE_INTEGER largeInteger;
	largeInteger.LowPart  = fileAttributeData.nFileSizeLow;
	largeInteger.HighPart = fileAttributeData.nFileSizeHigh;

	return (u32)largeInteger.QuadPart;
#else
	struct stat st;
	if(stat(path.CString(), &st) == 0)
		return (u32)st.st_size;
#endif
}


void FileSystem::ScanDirectory(StringVector& outFilenames, const String& directory, const String& filter) const
{
	String path = directory.Replaced('\\', '/');
	path.AddTrailingSlash();

#ifdef WIN32
	WIN32_FIND_DATAA findData;
	HANDLE handle = FindFirstFileA((path + filter).CString(), &findData);
	String fileName;

	if(handle != INVALID_HANDLE_VALUE)
	{
		do
		{
			fileName = findData.cFileName;
			if(!fileName.Empty())
			{
				if( (findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN) ||
					(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
					continue;

				outFilenames.Add(fileName);
			}
		}
		while(FindNextFileA(handle, &findData));

		FindClose(handle);
	}
#else
	//todo:
#endif
}


CE_NAMESPACE_END

