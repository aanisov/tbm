#ifndef _TESTSUITE_VEXPRESS_TEST_ENTRY_H
#define _TESTSUITE_VEXPRESS_TEST_ENTRY_H

#include "gic.h"
#include "handler.h"

struct test_info {
    struct gic_info gic;
    const struct handler_action* actions;
    const struct handler_action* maintenance_irq_actions;
    struct timer_info timers[4];
    bool virt_mode;
};

void gic_test(const char * test_name, const struct test_info *info);

#define GIC_TEST(info) gic_test(__func__, info)

#endif
