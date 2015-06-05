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
#include "Catastrophe/Core/Misc/MaxRectsBinPack.h"

CE_NAMESPACE_BEGIN



MaxRectsBinPack::MaxRectsBinPack() :
	m_binWidth(0),
	m_binHeight(0)
{
}


MaxRectsBinPack::MaxRectsBinPack(int width, int height, int initialCapacity) :
	m_binWidth(0),
	m_binHeight(0)
{
	Init(width, height, initialCapacity);
}


void MaxRectsBinPack::Init(int width, int height, int initialCapacity)
{
	m_binWidth = width;
	m_binHeight = height;

	m_usedRectangles.Clear();
	m_freeRectangles.Clear();

	m_usedRectangles.Reserve(initialCapacity);
	m_freeRectangles.Reserve(initialCapacity);

	m_freeRectangles.Add(Rect(0, 0, width, height));
}


Rect MaxRectsBinPack::Insert(int width, int height)
{
	Rect newNode;
	int score1; // Unused in this function. We don't need to know the score after finding the position.
	int score2;

	newNode = FindPositionForNewNodeBestShortSideFit(width, height, score1, score2);

	if(newNode.height == 0)
		return newNode;

	u32 numRectanglesToProcess = m_freeRectangles.Size();
	for(u32 i = 0; i < numRectanglesToProcess; ++i)
	{
		if(SplitFreeNode(m_freeRectangles[i], newNode))
		{
			m_freeRectangles.Erase(m_freeRectangles.begin() + i);
			--i;
			--numRectanglesToProcess;
		}
	}

	PruneFreeList();
	m_usedRectangles.Add(newNode);

	return newNode;
}


float MaxRectsBinPack::Occupancy() const
{
	u32 usedSurfaceArea = 0;
	for(u32 i = 0; i < m_usedRectangles.Size(); ++i)
		usedSurfaceArea += m_usedRectangles[i].width * m_usedRectangles[i].height;

	return (float)usedSurfaceArea / (m_binWidth * m_binHeight);
}


Rect MaxRectsBinPack::FindPositionForNewNodeBestShortSideFit(int width, int height, int& bestShortSideFit, int& bestLongSideFit) const
{
	Rect bestNode = Rect::Zero;
	bestShortSideFit = INT_MAX;

	for(u32 i = 0; i < m_freeRectangles.Size(); ++i)
	{
		// Try to place the rectangle in upright (non-flipped) orientation.
		if(m_freeRectangles[i].width >= width && m_freeRectangles[i].height >= height)
		{
			int leftoverHoriz = abs(m_freeRectangles[i].width - width);
			int leftoverVert = abs(m_freeRectangles[i].height - height);
			int shortSideFit = Min(leftoverHoriz, leftoverVert);
			int longSideFit = Max(leftoverHoriz, leftoverVert);

			if(shortSideFit < bestShortSideFit || (shortSideFit == bestShortSideFit && longSideFit < bestLongSideFit))
			{
				bestNode.x = m_freeRectangles[i].x;
				bestNode.y = m_freeRectangles[i].y;
				bestNode.width = width;
				bestNode.height = height;
				bestShortSideFit = shortSideFit;
				bestLongSideFit = longSideFit;
			}
		}

		if(m_freeRectangles[i].width >= height && m_freeRectangles[i].height >= width)
		{
			int flippedLeftoverHoriz = abs(m_freeRectangles[i].width - height);
			int flippedLeftoverVert = abs(m_freeRectangles[i].height - width);
			int flippedShortSideFit = Min(flippedLeftoverHoriz, flippedLeftoverVert);
			int flippedLongSideFit = Max(flippedLeftoverHoriz, flippedLeftoverVert);

			if(flippedShortSideFit < bestShortSideFit || (flippedShortSideFit == bestShortSideFit && flippedLongSideFit < bestLongSideFit))
			{
				bestNode.x = m_freeRectangles[i].x;
				bestNode.y = m_freeRectangles[i].y;
				bestNode.width = height;
				bestNode.height = width;
				bestShortSideFit = flippedShortSideFit;
				bestLongSideFit = flippedLongSideFit;
			}
		}
	}

	return bestNode;
}


bool MaxRectsBinPack::SplitFreeNode(Rect freeNode, const Rect& usedNode)
{
	// Test with SAT if the rectangles even intersect.
	if(usedNode.x >= freeNode.x + freeNode.width || usedNode.x + usedNode.width <= freeNode.x ||
		usedNode.y >= freeNode.y + freeNode.height || usedNode.y + usedNode.height <= freeNode.y)
		return false;

	if(usedNode.x < freeNode.x + freeNode.width && usedNode.x + usedNode.width > freeNode.x)
	{
		// New node at the top side of the used node.
		if(usedNode.y > freeNode.y && usedNode.y < freeNode.y + freeNode.height)
		{
			Rect newNode = freeNode;
			newNode.height = usedNode.y - newNode.y;
			m_freeRectangles.Add(newNode);
		}

		// New node at the bottom side of the used node.
		if(usedNode.y + usedNode.height < freeNode.y + freeNode.height)
		{
			Rect newNode = freeNode;
			newNode.y = usedNode.y + usedNode.height;
			newNode.height = freeNode.y + freeNode.height - (usedNode.y + usedNode.height);
			m_freeRectangles.Add(newNode);
		}
	}

	if(usedNode.y < freeNode.y + freeNode.height && usedNode.y + usedNode.height > freeNode.y)
	{
		// New node at the left side of the used node.
		if(usedNode.x > freeNode.x && usedNode.x < freeNode.x + freeNode.width)
		{
			Rect newNode = freeNode;
			newNode.width = usedNode.x - newNode.x;
			m_freeRectangles.Add(newNode);
		}

		// New node at the right side of the used node.
		if(usedNode.x + usedNode.width < freeNode.x + freeNode.width)
		{
			Rect newNode = freeNode;
			newNode.x = usedNode.x + usedNode.width;
			newNode.width = freeNode.x + freeNode.width - (usedNode.x + usedNode.width);
			m_freeRectangles.Add(newNode);
		}
	}

	return true;
}


void MaxRectsBinPack::PruneFreeList()
{
	/// Go through each pair and remove any rectangle that is redundant.
	for(u32 i = 0; i < m_freeRectangles.Size(); ++i)
	{
		for(u32 j = i+1; j < m_freeRectangles.Size(); ++j)
		{
			if(m_freeRectangles[j].Contains(m_freeRectangles[i]))
			{
				m_freeRectangles.EraseAt(i);
				--i;
				break;
			}
			if(m_freeRectangles[i].Contains(m_freeRectangles[j]))
			{
				m_freeRectangles.EraseAt(j);
				--j;
			}
		}
	}
}




CE_NAMESPACE_END

