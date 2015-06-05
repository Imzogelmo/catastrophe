// Permission is hereby granted, free of charge, to any person obtaining a Copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, Copy, modify, merge, publish, distribute, sublicense, and/or sell
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

#include "Catastrophe/Core/Common.h"
#include "Catastrophe/Core/Containers/Vector.h"

CE_NAMESPACE_BEGIN


class MaxRectsBinPack
{
public:
	/// Instantiates a bin of size (0,0). Call Init to create a new bin.
	MaxRectsBinPack();

	/// Instantiates a bin of the given size.
	MaxRectsBinPack(int width, int height, int initialCapacity);

	/// (Re)initializes the packer to an empty bin of width x height units. Call whenever
	/// you need to restart with a new bin.
	void Init(int width, int height, int initialCapacity);

	/// Inserts a single rectangle into the bin, possibly rotated.
	Rect Insert(int width, int height);

	/// Computes the ratio of used surface area to the total bin area.
	float Occupancy() const;

private:
	int m_binWidth;
	int m_binHeight;

	Vector<Rect> m_usedRectangles;
	Vector<Rect> m_freeRectangles;

	Rect FindPositionForNewNodeBestShortSideFit(int width, int height, int& bestShortSideFit, int& bestLongSideFit) const;

	/// @return True if the free node was split.
	bool SplitFreeNode(Rect freeNode, const Rect& usedNode);

	/// Goes through the free rectangle list and removes any redundant entries.
	void PruneFreeList();
};




CE_NAMESPACE_END

