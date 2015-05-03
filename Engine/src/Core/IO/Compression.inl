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

#include "lz4/lz4.c"
#include "lz4/lz4hc.c"

#include "Catastrophe/Core/Memory.h"
#include "Catastrophe/Core/IO/Compression.h"
#include "Catastrophe/Core/IO/File.h"
#include "Catastrophe/Core/IO/Log.h"

CE_NAMESPACE_BEGIN


u32 GetCompressionBounds( u32 inputSize )
{
	return (u32)LZ4_compressBound(inputSize);
}


u32 CompressData( void* dest, const void* source, u32 sourceSize )
{
	CE_ASSERT(dest != null);
	CE_ASSERT(source != null);

	return (u32)LZ4_compressHC((const char*)source, (char*)dest, (int)sourceSize);
}


u32 DecompressData( void* dest, const void* source, u32 destSize )
{
	CE_ASSERT(dest != null);
	CE_ASSERT(source != null);

	return (u32)LZ4_decompress_fast( (const char*)source, (char*)dest, (int)destSize );
}


bool CompressFile( Serializer* dest, Deserializer* source )
{
	CE_ASSERT(dest != null);
	CE_ASSERT(source != null);

	u32 bufferSize = source->Size() - source->Position();

	MemoryFile fileBuffer;
	fileBuffer.Resize(bufferSize);
	if( source->Read(fileBuffer.GetData(), bufferSize) != bufferSize )
		return false;

	return CompressFromMemoryFile(dest, &fileBuffer);
}


bool DecompressFile( Serializer* dest, Deserializer* source )
{
	CE_ASSERT(dest != null);
	CE_ASSERT(source != null);

	MemoryFile fileBuffer;
	if( !DecompressToMemoryFile(&fileBuffer, source) )
		return false;

	return dest->Write(fileBuffer.GetData(), fileBuffer.Size()) == fileBuffer.Size();
}


bool CompressFromMemoryFile( Serializer* dest, MemoryFile* fileBuffer )
{
	CE_ASSERT(dest != null);
	CE_ASSERT(fileBuffer != null);

	bool ret = false;
	u32 uncompressedSize = fileBuffer->Size();

	if( uncompressedSize == 0 )
	{
		dest->WriteInt(0);
		dest->WriteInt(0);
	}
	else
	{
		u32 compressedSize = 0;
		u32 compressionBounds = GetCompressionBounds(uncompressedSize);
		u8* pDest = (u8*)Memory::AllocateTemporary(compressionBounds);

		// Compress the entire buffer regardless of position.
		compressedSize = CompressData(pDest, fileBuffer->GetData(), uncompressedSize);

		dest->WriteInt(uncompressedSize);
		dest->WriteInt(compressedSize);
		if( dest->Write(pDest, compressedSize) == compressedSize )
			ret = true;

		Memory::DeallocateTemporary(pDest);
	}

	return ret;
}


bool DecompressToMemoryFile( MemoryFile* fileBuffer, Deserializer* source )
{
	CE_ASSERT(fileBuffer != null);
	CE_ASSERT(source != null);

	bool ret = false;
	u32 uncompressedSize = 0;
	u32 compressedSize = 0;

	if( source->Read(&uncompressedSize, 4) && source->Read(&compressedSize, 4) )
	{
		fileBuffer->Resize(uncompressedSize);

		u8* pSource = (u8*)Memory::AllocateTemporary(compressedSize);

		source->Read(pSource, compressedSize);
		if( DecompressData(fileBuffer->GetData(), pSource, uncompressedSize) == compressedSize )
			ret = true;

		Memory::DeallocateTemporary(pSource);
	}

	if( !ret )
		Log("Error: Could not decompress file. ");

	return ret;
}


CE_NAMESPACE_END

