/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ssl-kicker.h"

namespace sixtron {

KICKER::KICKER(PinName charge, PinName kick1, PinName kick2):
        _charge(charge, 1), _kick1(kick1, 0), _kick2(kick2, 0)
{
}

void KICKER::enable_charge()
{
    _charge = 0;
}

void KICKER::disable_charge()
{
    _charge = 1;
}

void KICKER::kick1(float power)
{
    disable_charge();
    _kick1 = 1;

    _kick1_timeout.attach(callback(this, &KICKER::kick1_off), std::chrono::microseconds((int)(power * 10000.0)));
}

void KICKER::kick1_off()
{
    _kick1 = 0;
}

} // namespace sixtron
