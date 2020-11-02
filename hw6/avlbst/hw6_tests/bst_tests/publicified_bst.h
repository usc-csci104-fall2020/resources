//
// Wrapper around bst.h to make all private/protected functions public
//

#ifndef CS104_HW7_TEST_SUITE_PUBLICIFIED_BST_H
#define CS104_HW7_TEST_SUITE_PUBLICIFIED_BST_H

#define private public
#define protected public
#include <bst.h>
#undef private
#undef public

#endif //CS104_HW7_TEST_SUITE_PUBLICIFIED_BST_H
