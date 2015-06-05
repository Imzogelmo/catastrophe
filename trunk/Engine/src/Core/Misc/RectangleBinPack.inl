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
#include "Catastrophe/Core/Misc/RectangleBinPack.h"

CE_NAMESPACE_BEGIN



RectangleBinPack::RectangleBinPack() :
	m_rootNode(),
	m_binWidth(0),
	m_binHeight(0)
{
	m_rootNode.left = m_rootNode.right = null;
	m_rootNode.x = m_rootNode.y = 0;
	m_rootNode.width = m_rootNode.height = 0;
}


RectangleBinPack::~RectangleBinPack()
{
	DestroyNodes(m_rootNode->left);
	DestroyNodes(m_rootNode->right);
}


void RectangleBinPack::Init(int width, int height)
{
	DestroyNodes(m_rootNode->left);
	DestroyNodes(m_rootNode->right);

	m_binWidth = width;
	m_binHeight = height;
	m_rootNode.left = m_rootNode.right = null;
	m_rootNode.x = m_rootNode.y = 0;
	m_rootNode.width = width;
	m_rootNode.height = height;
}


float RectangleBinPack::Occupancy() const
{
	u32 totalSurfaceArea = m_binWidth * m_binHeight;
	u32 usedSurfaceArea = UsedSurfaceArea(m_rootNode);

	return (float)usedSurfaceArea/totalSurfaceArea;
}


u32 RectangleBinPack::UsedSurfaceArea(const Node &node) const
{
	if (node.left || node.right)
	{
		u32 usedSurfaceArea = node.width * node.height;
		if (node.left)
			usedSurfaceArea += UsedSurfaceArea(*node.left);
		if (node.right)
			usedSurfaceArea += UsedSurfaceArea(*node.right);

		return usedSurfaceArea;
	}

	// This is a leaf node, it doesn't constitute to the total surface area.
	return 0;
}


RectangleBinPack::Node* RectangleBinPack::Insert(RectangleBinPack::Node* node, int width, int height)
{
	// If this node is an internal node, try both leaves for possible space.
	// (The rectangle in an internal node stores used space, the leaves store free space)
	if (node->left || node->right)
	{
		if (node->left)
		{
			Node* newNode = Insert(node->left, width, height);
			if (newNode)
				return newNode;
		}
		if (node->right)
		{
			Node* newNode = Insert(node->right, width, height);
			if (newNode)
				return newNode;
		}
		return 0; // Didn't fit into either subtree!
	}

	// This node is a leaf, but can we fit the new rectangle here?
	if (width > node->width || height > node->height)
		return 0; // Too bad, no space.

	// The new cell will fit, split the remaining space along the shorter axis,
	// that is probably more optimal.
	int w = node->width - width;
	int h = node->height - height;

	node->left = AllocateNode();
	node->right = AllocateNode();

	if (w <= h) // Split the remaining space in horizontal direction.
	{
		node->left->x = node->x + width;
		node->left->y = node->y;
		node->left->width = w;
		node->left->height = height;

		node->right->x = node->x;
		node->right->y = node->y + height;
		node->right->width = node->width;
		node->right->height = h;
	}
	else // Split the remaining space in vertical direction.
	{
		node->left->x = node->x;
		node->left->y = node->y + height;
		node->left->width = width;
		node->left->height = h;

		node->right->x = node->x + width;
		node->right->y = node->y;
		node->right->width = w;
		node->right->height = node->height;
	}

	// Note that as a result of the above, it can happen that node->left or node->right
	// is now a degenerate (zero area) rectangle. No need to do anything about it,
	// like remove the nodes as "unnecessary" since they need to exist as children of
	// this node (this node can't be a leaf anymore).

	// This node is now a non-leaf, so shrink its area - it now denotes
	// *occupied* space instead of free space. Its children spawn the resulting
	// area of free space.
	node->width = width;
	node->height = height;

	return node;
}



RectangleBinPack::Node* RectangleBinPack::AllocateNode()
{
	//Node* node = m_poolAllocator.Allocate();
	//if(node == null)
	//	node = new Node;

	return new Node();
}


void RectangleBinPack::DestroyNodes(Node* node)
{
	if(node != null)
	{
		DestroyNodes(node->left);
		DestroyNodes(node->right);
		delete node;
	}
}


CE_NAMESPACE_END

