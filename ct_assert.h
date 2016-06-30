#ifndef __CT_ASSERT_H__
#define __CT_ASSERT_H__

#define CONCAT(a, b) a##b

#define ct_assert(e) enum { CONCAT(ct_assert_l_, __LINE__) = 1/(!!(e)) }

#endif
