//
// Wrapper around avlbst.h to make all private/protected functions public
//

#ifndef CS104_HW7_TEST_SUITE_PUBLICIFIED_AVLBST_H
#define CS104_HW7_TEST_SUITE_PUBLICIFIED_AVLBST_H

#define private public
#define protected public
#include <avlbst.h>
#undef private
#undef public

#endif //CS104_HW7_TEST_SUITE_PUBLICIFIED_AVLBST_H
