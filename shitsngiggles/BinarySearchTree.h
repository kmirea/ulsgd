/* 
 * File:   BinarySearchTree.h
 * Author: chris
 *
 * Created on October 5, 2010, 3:00 PM
 */

#ifndef BINARYSEARCHTREE_H
#define	BINARYSEARCHTREE_H

#include <cstdlib>
#include <vector>
#include <algorithm>
using std::vector;

template <typename T>
class BinarySearchTree
{
	class Node
	{
		Node* left;
		Node* right;
		T Data;

		friend class BinarySearchTree;
	public:
		Node( const T& data ) : left(NULL), right(NULL), Data(data) {}
		~Node()
		{
			if( left != NULL )
				delete left;
			if( right != NULL )
				delete right;
		}

		bool addNode( const T& data )	// adds a node in O(n) = n and o(n) = log(n) time
		{
			if( Data == data )
				return false;
			if( Data < data )
			{
				if( right == NULL )
				{
					right = new Node( data );
					return true;
				}
				return right->addNode( data );
			}
			if( left == NULL )
			{
				left = new Node( data );
				return true;
			}
			return left->addNode( data );
		}

		const Node* searchData( const T& data ) const	// runs a binary search in O(n) = n and o(n) = log(n)
		{
			if( Data == data )
				return const_cast<Node*>(this);

			if( Data < data )
				return (right != NULL )?right->searchData( data ):NULL;

			return (left != NULL )?left->searchData( data ):NULL;
		}
	};

	Node* RootNode;

	void getNodeList( vector<T>& List, Node* node ) const
	{
		if( node )
		{
			List.push_back( node->Data );
			if( node->left )
				getNodeList( List, node->left );
			if( node->right )
				getNodeList( List, node->right );
		}
	}
	
public:

	BinarySearchTree() : RootNode(NULL) {}
	~BinarySearchTree()
	{
		if( RootNode != NULL )
			delete RootNode;
	}

	bool addNode( const T& data )
	{
		if( RootNode == NULL )
		{
			RootNode = new Node( data );
			return true;
		}
		return RootNode->addNode( data );
	}

	const Node* searchData( const T& data ) const
	{
		return (RootNode!=NULL)?RootNode->searchData( data ):NULL;
	}

	const vector<T> getSortedNodeList() const
	{
		vector<T> List;

		getNodeList( List, RootNode );

		std::sort( List.begin(), List.end() );

		return List;
	}
};

#endif	/* BINARYSEARCHTREE_H */

