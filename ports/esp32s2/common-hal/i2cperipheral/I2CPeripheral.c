/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 microDev
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

#include "shared-bindings/i2cperipheral/I2CPeripheral.h"

#include "py/runtime.h"

#include "common-hal/busio/I2C.h"
#include "common-hal/microcontroller/Pin.h"

void common_hal_i2cperipheral_i2c_peripheral_construct(i2cperipheral_i2c_peripheral_obj_t *self,
        const mcu_pin_obj_t *scl, const mcu_pin_obj_t *sda,
        uint8_t *addresses, unsigned int num_addresses, bool smbus) {

}

bool common_hal_i2cperipheral_i2c_peripheral_deinited(i2cperipheral_i2c_peripheral_obj_t *self) {
    return self->sda_pin == -1;
}

void common_hal_i2cperipheral_i2c_peripheral_deinit(i2cperipheral_i2c_peripheral_obj_t *self) {
    if (common_hal_i2cperipheral_i2c_peripheral_deinited(self)) {
        return;
    }

    reset_pin_number(self->sda_pin);
    reset_pin_number(self->scl_pin);
    self->sda_pin = -1;
    self->scl_pin = -1;
}

int common_hal_i2cperipheral_i2c_peripheral_is_addressed(i2cperipheral_i2c_peripheral_obj_t *self,
        uint8_t *address, bool *is_read, bool *is_restart) {

    // This should clear AMATCH, but it doesn't...
    common_hal_i2cperipheral_i2c_peripheral_ack(self, false);
    return 0;
}

int common_hal_i2cperipheral_i2c_peripheral_read_byte(i2cperipheral_i2c_peripheral_obj_t *self, uint8_t *data) {
    return 1;
}

int common_hal_i2cperipheral_i2c_peripheral_write_byte(i2cperipheral_i2c_peripheral_obj_t *self, uint8_t data) {
    return 1;
}

void common_hal_i2cperipheral_i2c_peripheral_ack(i2cperipheral_i2c_peripheral_obj_t *self, bool ack) {

}

void common_hal_i2cperipheral_i2c_peripheral_close(i2cperipheral_i2c_peripheral_obj_t *self) {

}
