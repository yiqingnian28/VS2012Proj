/******************************************************************************
*
*
******************************************************************************/

#ifndef TREE_NODE_ITERATOR_LH
#define TREE_NODE_ITERATOR_LH


#include <stddef.h> //for ptrdiff_t

struct TreeNodeBase{
	typedef TreeNodeBase* BasePointer;
	BasePointer parent_;
	BasePointer left_;
	BasePointer right_;
};

template<typename Value>
struct TreeNode:public TreeNode{
	typedef TreeNode<Value>* LinkType;
	Value valueField_;
};

struct TreeBaseIterator{
	typedef TreeNodeBase::BasePointer BasePointer;
	typedef ptrdiff_t DifferenceType;

	BasePointer pNode_;

};



#endif // TREE_NODE_ITERATOR_LH
