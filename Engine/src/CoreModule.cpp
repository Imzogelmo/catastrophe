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

//#include "Core/Containers/String.h"

// Math
#include "Core/Math/Color.inl"
#include "Core/Math/Colorf.inl"
//#include "Core/Math/Frustum.inl"
#include "Core/Math/HSLColor.inl"
#include "Core/Math/HSVColor.inl"
#include "Core/Math/Math.inl"
#include "Core/Math/Matrix.inl"
#include "Core/Math/Quaternion.inl"
#include "Core/Math/Point.inl"
#include "Core/Math/Rect.inl"
#include "Core/Math/Rectf.inl"
#include "Core/Math/Vector2.inl"
#include "Core/Math/Vector3.inl"
#include "Core/Math/Vector4.inl"

// Packed
#include "Core/Math/Packed/PackedPoint.inl"
#include "Core/Math/Packed/PackedRect.inl"

// Tweening
#include "Core/Math/Easing.inl"
#include "Core/Math/Tween.inl"

// IO
#include "Core/IO/ConfigFile.inl"
#include "Core/IO/Deserializer.inl"
#include "Core/IO/File.inl"
#include "Core/IO/MemoryFile.inl"
#include "Core/IO/Log.inl"
#include "Core/IO/Serializer.inl"
#include "Core/IO/XmlDocument.inl"
#include "Core/IO/XmlElement.inl"
#include "Core/IO/XmlReader.inl"
#include "Core/IO/XmlWriter.inl"
#include "Core/IO/Compression.inl"
//#include "Core/IO/CompressedFile.inl"


// Core
#include "Core/Memory.inl"
#include "Core/Random.inl"
#include "Core/PlatformString.inl"
#include "Core/StringUtils.inl"
#include "Core/Profiler.inl"

// Allocators
#include "Core/Allocators/Allocator.inl"
#include "Core/Allocators/StackAllocator.inl"
#include "Core/Allocators/PoolAllocator.inl"


// Containers
#include "Core/Containers/String.inl"
#include "Core/Containers/FreeList.inl"

// Resource
#include "Core/Resource/ResourceGroup.inl"
#include "Core/Resource/ResourceManager.inl"

/*
// Containers
#include "Core/Containers/KeyValuePair.h"
#include "Core/Containers/HashMap.h"
#include "Core/Containers/Array.h"
#include "Core/Containers/Array2D.h"
#include "Core/Containers/StaticArray.h"
#include "Core/Containers/StaticString.h"
#include "Core/Containers/StaticVector.h"
#include "Core/Containers/Vector.h"
#include "Core/Containers/VectorMap.h"
#include "Core/Containers/VectorSet.h"
*/

// Platform Specific
// The following files may include windows.h or other namespace polluting headers.
#include "Core/Timer.inl"
#include "Core/IO/FileSystem.inl"
#include "Core/Threading/CriticalSection.inl"
#include "Core/Threading/ThreadLocalStorage.inl"
#include "Core/Threading/Thread.inl"


STATIC_ASSERT(sizeof(u8) == 1);
STATIC_ASSERT(sizeof(u16) == 2);
STATIC_ASSERT(sizeof(u32) == 4);
STATIC_ASSERT(sizeof(u64) == 8);
STATIC_ASSERT(sizeof(float) == 4);
STATIC_ASSERT(sizeof(double) == 8);
STATIC_ASSERT(sizeof(Color) == sizeof(u32));

/*
void TestStuff()
{
	HashMap<int, int, int(int)> h;
	Array<int> a;

	typedef Array2D<int> Array2;
	Array2 a2 = Array2();

	h.Add( KeyValuePair<int, int>(89, 700) );
	h.Add( KeyValuePair<const int, int>(59, 50) );
	h.Add( 2, 2 );

	VectorMap<int, int> vm;
	vm.Add(7,9);
	vm.Remove(43);
	vm.Find(0);
	vm.FindValue(9);
	vm.Clear();
	vm.Reserve(9);
	vm.Add(777);
	vm.Add(778);
	vm.Remove(777);
	vm.ShrinkToFit();
	vm = VectorMap<int, int>();
	vm.Reserve(8);
	vm.Add(KeyValuePair<int, int>(88,89));

	VectorMap<int, int, Less<int>, StaticVector<KeyValuePair<int, int>, 256 > > sm;
	sm.Add(0,0);
	sm.Add(7,9);
	sm.Remove(43);
	sm.Find(0);
	sm.FindValue(9);
	sm.Clear();
	sm.Reserve(9);
	sm.Add(777);
	sm.Add(778);
	sm.Remove(777);
	sm.ShrinkToFit();
	sm = VectorMap<int, int, Less<int>, StaticVector<KeyValuePair<int, int>, 256 > >();
	sm.Reserve(8);
	sm.Add(KeyValuePair<int, int>(88,89));

	VectorMultimap<int, int> vmm;
	vmm.Add(7,9);
	vmm.Remove(43);
	vmm.Find(0);
	vmm.FindValue(9);
	vmm.Clear();
	vmm.Reserve(9);
	vmm.Add(777);
	vmm.Add(778);
	vmm.Remove(777);
	vmm.ShrinkToFit();
	vmm = VectorMultimap<int, int>();
	vmm.Reserve(8);
	vmm.Add(KeyValuePair<int, int>(88,89));

	VectorMultimap<int, int, Less<int>, StaticVector<KeyValuePair<int, int>, 256 > > smm;
	smm.Add(0,0);
	smm.Add(7,9);
	smm.Remove(43);
	smm.Find(0);
	smm.FindValue(9);
	smm.Clear();
	smm.Reserve(9);
	smm.Add(777);
	smm.Add(778);
	smm.Remove(777);
	smm.ShrinkToFit();
	smm = VectorMultimap<int, int, Less<int>, StaticVector<KeyValuePair<int, int>, 256 > >();
	smm.Reserve(8);
	smm.Add(KeyValuePair<int, int>(88,89));



	/////////////////////////////////////////////////

	VectorSet<int> vs;
	vs.Add(7);
	vs.Remove(43);
	vs.Find(0);
	vs.Clear();
	vs.Reserve(9);
	vs.Add(777);
	vs.Add(778);
	vs.Remove(777);
	vs.ShrinkToFit();
	vs = VectorSet<int>();
	vs.Reserve(8);


	VectorMultiset<int> vms;
	vms.Add(7);
	vms.Remove(43);
	vms.Find(0);
	vms.Clear();
	vms.Reserve(9);
	vms.Add(777);
	vms.Add(778);
	vms.Remove(777);
	vms.ShrinkToFit();
	vms = VectorMultiset<int>();
	vms.Reserve(8);



	VectorSet<int, Less<int>, StaticVector<int, 32> > vss;
	vss.Add(7);
	vss.Remove(43);
	vss.Find(0);
	vss.Clear();
	vss.Reserve(9);
	vss.Add(777);
	vss.Add(778);
	vss.Remove(777);
	vss.ShrinkToFit();
	vss = VectorSet<int, Less<int>, StaticVector<int, 32> >();
	vss.Reserve(8);


	VectorMultiset<int, Less<int>, StaticVector<int, 32> > vsms;
	vsms.Add(7);
	vsms.Remove(43);
	vsms.Find(0);
	vsms.Clear();
	vsms.Reserve(9);
	vsms.Add(777);
	vsms.Add(778);
	vsms.Remove(777);
	vsms.ShrinkToFit();
	vsms = VectorMultiset<int, Less<int>, StaticVector<int, 32> >();
	vsms.Reserve(8);

}
*/

