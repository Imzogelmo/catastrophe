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
#include "Catastrophe/Core/Containers/FreeList.h"
#include "Catastrophe/Core/Allocators/Allocator.h"

CE_NAMESPACE_BEGIN


class RectangleBinPack
{
public:
	/** A node of a binary tree. Each node represents a rectangular area of the texture
	    we surface. Internal nodes store rectangles of used data, whereas leaf nodes track 
	    rectangles of free space. All the rectangles stored in the tree are disjoint.
	*/
	struct Node
	{
		// Left and right child. We don't really distinguish which is which, so these could
		// as well be child1 and child2.
		Node* left;
		Node* right;

		// The top-left coordinate of the rectangle.
		int x;
		int y;

		// The dimension of the rectangle.
		int width;
		int height;
	};

	RectangleBinPack();
	~RectangleBinPack();

	/// Starts a new packing process to a bin of the given dimension.
	void Init(int width, int height);

	/// Inserts a new rectangle of the given size into the bin.
	/** Running time is linear to the number of rectangles that have been already packed.
		@return A pointer to the node that stores the newly added rectangle, or 0 if it didn't fit.
	*/
	Node* Insert(int width, int height)
	{
		return Insert(&m_rootNode, width, height);
	}

	/// Computes the ratio of used surface area.
	float Occupancy() const;

private:
	Node m_rootNode;

	// The total size of the bin we started with.
	int m_binWidth;
	int m_binHeight;

	//FreeList m_freeMemoryList;
	//PoolAllocator<Node> m_poolAllocator;

	/// @return The surface area used by the subtree rooted at node.
	u32 UsedSurfaceArea(const Node &node) const;

	/// Inserts a new rectangle in the subtree rooted at the given node.
	Node* Insert(Node* node, int width, int height);

	Node* AllocateNode();

	void DestroyNodes(Node* node);
};




CE_NAMESPACE_END

