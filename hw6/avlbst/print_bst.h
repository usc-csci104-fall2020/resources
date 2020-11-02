#include <cmath>
#include <iomanip>
#include <map>
#include <vector>
#include <cstdint>

#ifndef PRINT_BST_H
#define PRINT_BST_H

// BST pretty-print function
// Version 1.2

// maximum depth of tree to actually print.
#define PPBST_MAX_HEIGHT 6

// Returns the node's distance from the given root.
// 1 means that it is the root.
// Returns -1 (not found) if the distance is more than PPBST_MAX_HEIGHT,
// or -2 if the tree is inconsistent.
template<typename Key, typename Value>
int getNodeDepth(BinarySearchTree<Key, Value> const & tree, std::shared_ptr<Node<Key, Value>> root, std::shared_ptr<Node<Key, Value>> node)
{
    int dist = 1;

    while(node != root)
    {
        if(node == nullptr)
        {
            return -2;
        }

        ++dist;
        node = node->getParent();

        if(dist > PPBST_MAX_HEIGHT)
        {
            return -1;
        }
    }

    return dist;
}

// Returns the height of the subtree at root.
// Uses recursion, not height values, so it is bulletproof
// against incorrect heights.
// Stops recursing after PPBST_MAX_HEIGHT calls.
template<typename Key, typename Value>
int getSubtreeHeight(std::shared_ptr<Node<Key, Value>> root, int recursionDepth = 1)
{
    if(root == nullptr)
    {
        return 0;
    }

    if(recursionDepth > PPBST_MAX_HEIGHT)
    {
        // bail out to prevent infinite loops on bad trees
        return 0;
    }

    return std::max(getSubtreeHeight(root->getLeft(), recursionDepth + 1),
                    getSubtreeHeight(root->getRight(), recursionDepth + 1)) + 1;
}

/* Function to prettily print a BST out to the terminal.

   Output should look a bit like this:

   --------------------------------------------------

					 [01]
				    /    \
		 [02]                    [03]
	    /    \                  /    \
   [04]        [05]        [06]        [07]
   /  \        /  \        /  \           \
[08]  [09]  [10]  [11]  [12]  [13]  [15]  [15]

    1: Foo
    2: Bar
    3: Baz
    ....
    -------------------------------------------------

	To keep the distance between nodes down, nodes should only
	have a number inside them, and their actual value should be
	printed out at the bottom.

	This function should handle broken trees without crashing,
	and should print as much of them as it can.

    */

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot (std::shared_ptr<Node<Key, Value>> root) const
{
    // special case for empty trees:
    if(root == nullptr)
    {
        std::cout << "<empty tree>" << std::endl;
        return;
    }

#define BOX_WIDTH 4
#define PADDING 2 // distance between elements at bottom row
#define ELEMENT_WIDTH (BOX_WIDTH + PADDING)

    // save initial cout state (from https://stackoverflow.com/questions/2273330/restore-the-state-of-stdcout-after-manipulating-it)
    std::ios::fmtflags origCoutState(std::cout.flags());

    // do some initial calculations
    // ----------------------------------------------------------------------
    uint32_t printedTreeHeight = getSubtreeHeight(root);
    bool clippedFinalElements = false;

    // with the width of a standard terminal, we can only print 2^5 = 32 elements
    if(printedTreeHeight > PPBST_MAX_HEIGHT)
    {
        printedTreeHeight = PPBST_MAX_HEIGHT;
        clippedFinalElements = true;

    }

    uint16_t finalRowNumElements = (uint16_t)std::pow(2, printedTreeHeight - 1);
    uint16_t finalRowWidth = ((uint16_t)(ELEMENT_WIDTH * finalRowNumElements - PADDING));

    // get placeholders
    // ----------------------------------------------------------------------
    std::map<Key, uint8_t> valuePlaceholders;

    uint8_t nextPlaceHolderVal = 1;
    for(typename BinarySearchTree<Key, Value>::iterator treeIter = this->begin(); treeIter != this->end(); ++treeIter)
    {

        if(getNodeDepth(*this, root, treeIter.current_) != -1)
        {
            // note; the iterator will traverse in sorted order so values should get the same placeholders between
            // different calls as long as the tree is the same
            valuePlaceholders.insert(std::make_pair(treeIter->first, nextPlaceHolderVal++));
        }

    }

    // print tree
    // ----------------------------------------------------------------------

    // space in front of the first element of the previous row
    uint16_t firstElementMargin = ((uint16_t)(finalRowWidth/2 - (BOX_WIDTH/2))); // start in the middle of where the last row will be

    uint16_t elementPadding = ((uint16_t)(finalRowWidth - 2));

    std::vector<std::shared_ptr<Node<Key, Value>> > currRowNodes; // contains the 2^levelIndex nodes in this row, or nullptr to mark nonexistant nodes
    currRowNodes.push_back(root);

    for(size_t levelIndex = 0; levelIndex < printedTreeHeight; ++levelIndex)
    {
        uint16_t numElements =(uint16_t)std::pow(2, levelIndex);

        // print elements themselves
        std::cout << std::string(firstElementMargin, ' ');
        for(size_t elementIndex = 0; elementIndex < numElements; ++elementIndex)
        {
            if(currRowNodes[elementIndex] == nullptr)
            {
                std::cout << "    ";
            }
            else
            {
                uint16_t placeholder = valuePlaceholders[currRowNodes[elementIndex]->getItem().first];
                std::cout << "[" << std::setfill('0') << std::setw(2) << placeholder << "]";
            }

            if(elementIndex != ((uint16_t)(numElements - 1)))
            {
                std::cout << std::string(elementPadding, ' ');
            }
        }
        std::cout << std::endl;

        // spacing values for next row (worked out on paper)
        elementPadding = ((uint16_t)((elementPadding - BOX_WIDTH) / 2));
        firstElementMargin = ((uint16_t)(firstElementMargin - (elementPadding / 2 + 2)));

        // calculate node lists for next iteration
        // ---------------------------------------------------------------------
        std::vector<std::shared_ptr<Node<Key, Value>> > prevRowNodes = currRowNodes;
        currRowNodes.clear();
        for(typename std::vector<std::shared_ptr<Node<Key, Value>> >::iterator prevRowIter = prevRowNodes.begin(); prevRowIter != prevRowNodes.end() ; ++prevRowIter)
        {
            if(*prevRowIter == nullptr)
            {
                currRowNodes.push_back(nullptr);
                currRowNodes.push_back(nullptr);
            }
            else
            {
                currRowNodes.push_back((*prevRowIter)->getLeft());
                currRowNodes.push_back((*prevRowIter)->getRight());
            }
        }

        // print connecting lines
        // ---------------------------------------------------------------------
        if(levelIndex < printedTreeHeight - 1)
        {
            // start above middle side of first element
            std::cout << std::string(firstElementMargin + 2, ' ');

            for(size_t prevRowElementIndex = 0; prevRowElementIndex < prevRowNodes.size(); ++prevRowElementIndex)
            {
                std::shared_ptr<Node<Key, Value>> currNode = prevRowNodes[prevRowElementIndex];

                // print first branch
                if(currNode == nullptr || currNode->getLeft() == nullptr)
                {
                    std::cout << std::string(elementPadding/2 + 3, ' ');
                }
                else
                {
                    std::cout << "\u250c";

                    for(int numLines = 0; numLines < (elementPadding/2 - 1); ++numLines)
                    {
                        std::cout << u8"\u2500";
                    }

                    std::cout << "\u2518  ";
                }

                // print second branch
                if(currNode == nullptr || currNode->getRight() == nullptr)
                {
                    std::cout << std::string(elementPadding/2 + 3, ' ');
                }
                else
                {
                    std::cout << "\u2514";

                    for(int numLines = 0; numLines < (elementPadding/2 - 1); ++numLines)
                    {
                        std::cout << u8"\u2500";
                    }

                    std::cout << "\u2510  ";
                }

                std::cout << std::string(elementPadding + 2, ' ');

            }


            std::cout << std::endl;

        }
    }

    std::cout << std::endl;
    if(clippedFinalElements)
    {
        std::cout << "(deeper levels omitted due to space limitations)" << std::endl;
    }


    if(!std::is_same<Key, uint8_t>::value) // print placeholder explanations if needed:
    {
        std::cout << "Tree Placeholders:------------------" << std::endl;
        for(typename std::map<Key, uint8_t>::iterator placeholdersIter = valuePlaceholders.begin(); placeholdersIter != valuePlaceholders.end(); ++placeholdersIter)
        {
            std::cout << '[' << std::setfill('0') << std::setw(2) << ((uint16_t)placeholdersIter->second) << "] -> ";

            // print element with original cout flags
            std::cout.flags(origCoutState);
            std::cout << '(' << placeholdersIter->first << ", ";

            typename BinarySearchTree<Key, Value>::iterator elementIter = this->find(placeholdersIter->first);
            if(elementIter == this->end())
            {
                std::cout << "<error: lookup failed>";
            }
            else
            {
                std::cout << elementIter->second;
            }

            std::cout << ')' << std::endl;


        }
    }

    // restore original cout flags
    std::cout.flags(origCoutState);

}

#endif
