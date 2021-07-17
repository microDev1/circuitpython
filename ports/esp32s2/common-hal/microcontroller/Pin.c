/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Scott Shawcroft for Adafruit Industries
 * Copyright (c) 2019 Lucian Copeland for Adafruit Industries
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "shared-bindings/microcontroller/Pin.h"
#include "shared-bindings/digitalio/DigitalInOut.h"

#include "py/mphal.h"

#include "components/driver/include/driver/gpio.h"
#include "components/hal/include/hal/gpio_hal.h"

STATIC uint32_t in_use[2];
STATIC uint32_t never_reset_pins[2];

STATIC void floating_gpio_reset(gpio_num_t pin_number) {
    // This is the same as gpio_reset_pin(), but without the pullup.
    // Note that gpio_config resets the iomatrix to GPIO_FUNC as well.
    gpio_config_t cfg = {
        .pin_bit_mask = BIT64(pin_number),
        .mode = GPIO_MODE_DISABLE,
        .pull_up_en = false,
        .pull_down_en = false,
        .intr_type = GPIO_INTR_DISABLE,
    };
    gpio_config(&cfg);
    PIN_FUNC_SELECT(GPIO_PIN_MUX_REG[pin_number], 0);
}

STATIC void valid_pin_number(gpio_num_t pin_number) {
    return pin_number != NO_PIN;
}

STATIC void valid_pin(const mcu_pin_obj_t *pin) {
    return pin != NULL;
}

void reset_all_pins(void) {
    for (uint8_t i = 0; i < GPIO_PIN_COUNT; i++) {
        uint32_t iomux_address = GPIO_PIN_MUX_REG[i];
        if (iomux_address == 0 ||
            (never_reset_pins[i / 32] & (1 << i % 32)) != 0) {
            continue;
        }
        floating_gpio_reset(i);
    }
    in_use[0] = 0;
    in_use[1] = 0;
}

void common_hal_mcu_claim_pin_number(gpio_num_t pin_number) {
    if (!valid_pin_number(pin_number)) return;
    in_use[pin_number / 32] |= (1 << (pin_number % 32));
}

void common_hal_mcu_claim_pin(const mcu_pin_obj_t *pin) {
    if (!valid_pin(pin)) return;
    claim_pin_number(pin->number);
}

void common_hal_mcu_reset_pin_number(gpio_num_t pin_number) {
    if (!valid_pin_number(pin_number)) return;
    never_reset_pins[pin_number / 32] &= ~(1 << pin_number % 32);
    in_use[pin_number / 32] &= ~(1 << pin_number % 32);
    floating_gpio_reset(pin_number);
}

void common_hal_mcu_reset_pin(const mcu_pin_obj_t *pin) {
    if (!valid_pin(pin)) return;
    reset_pin_number(pin->number);
}

void common_hal_mcu_never_reset_pin_number(gpio_num_t pin_number) {
    if (!valid_pin_number(pin_number)) return;
    never_reset_pins[pin_number / 32] |= 1 << pin_number % 32;
}

void common_hal_mcu_never_reset_pin(const mcu_pin_obj_t *pin) {
    if (!valid_pin(pin)) return;
    never_reset_pin_number(pin->number);
}

bool common_hal_mcu_pin_number_is_free(gpio_num_t pin_number) {
    uint8_t offset = pin_number / 32;
    uint32_t mask = 1 << (pin_number % 32);
    return (in_use[offset] & mask) == 0;
}

bool common_hal_mcu_pin_is_free(const mcu_pin_obj_t *pin) {
    return pin_number_is_free(pin->number);
}
