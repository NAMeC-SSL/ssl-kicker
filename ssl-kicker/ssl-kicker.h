/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef CATIE_SIXTRON_KICKER_H_
#define CATIE_SIXTRON_KICKER_H_

#include "mbed.h"

namespace sixtron {

class KICKER {
public:
    KICKER(PinName charge, PinName kick1, PinName kick2);

    void enable_charge();

    void disable_charge();

    void kick1(float power);

    void kick2(float power);
    
    void set_kick1_available();

    void set_kick2_available();
private:
    DigitalOut _charge;
    DigitalOut _kick1;
    DigitalOut _kick2;

    Timeout _kick1_timeout;
    Timeout _kick2_timeout;

    bool _kick1_available;
    bool _kick2_available;

    void kick1_off();

    void kick2_off();
};

} // namespace sixtron

#endif // CATIE_SIXTRON_KICKER_H_
