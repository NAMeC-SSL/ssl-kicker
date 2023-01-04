/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ssl-kicker.h"

namespace sixtron {

KICKER::KICKER(PinName charge, PinName kick1, PinName kick2):
        _charge(charge, 1),
        _kick1(kick1, 0),
        _kick2(kick2, 0),
        _kick1_available(true),
        _kick2_available(true)
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
    if (!_kick1_available) {
        return;
    }
    _kick1 = 1;
    _kick1_available = false;

    _kick1_timeout.attach(
            callback(this, &KICKER::kick1_off), std::chrono::microseconds((int)(power * 10000.0)));
}

void KICKER::kick1_off()
{
    _kick1 = 0;

    _kick1_timeout.attach(callback(this, &KICKER::set_kick1_available), 1s);
}

void KICKER::kick2(float power)
{
    disable_charge();
    if (!_kick2_available) {
        return;
    }
    _kick2 = 1;
    _kick2_available = false;

    _kick2_timeout.attach(
            callback(this, &KICKER::kick2_off), std::chrono::microseconds((int)(power * 10000.0)));
}

void KICKER::kick2_off()
{
    _kick2 = 0;

    _kick2_timeout.attach(callback(this, &KICKER::set_kick2_available), 1s);
}

void KICKER::set_kick1_available()
{
    _kick1_available = true;
}

void KICKER::set_kick2_available()
{
    _kick2_available = true;
}

} // namespace sixtron
