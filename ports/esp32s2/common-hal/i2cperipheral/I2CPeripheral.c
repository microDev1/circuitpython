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

#include "py/mperrno.h"
#include "py/runtime.h"

#include "common-hal/busio/I2C.h"

void common_hal_i2cperipheral_i2c_peripheral_construct(i2cperipheral_i2c_peripheral_obj_t *self,
        const mcu_pin_obj_t *scl, const mcu_pin_obj_t *sda,
        uint8_t *addresses, unsigned int num_addresses, bool smbus) {
    // Pins 45 and 46 are "strapping" pins that impact start up behavior. They usually need to
    // be pulled-down so pulling them up for I2C is a bad idea. To make this hard, we don't
    // support I2C on these pins.
    //
    // 46 is also input-only so it'll never work.
    if (scl->number == 45 || scl->number == 46 || sda->number == 45 || sda->number == 46) {
        mp_raise_ValueError(translate("Invalid pins"));
    }

    self->sda_pin = sda;
    self->scl_pin = scl;
    self->i2c_num = i2c_num_status();

    if (self->i2c_num == I2C_NUM_MAX) {
        mp_raise_ValueError(translate("All I2C peripherals are in use"));
    }

    const i2c_config_t i2c_conf = {
        .mode = I2C_MODE_SLAVE,
        .sda_io_num = self->sda_pin->number,
        .scl_io_num = self->scl_pin->number,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,  /*!< Internal GPIO pull mode for I2C sda signal*/
        .scl_pullup_en = GPIO_PULLUP_ENABLE,  /*!< Internal GPIO pull mode for I2C scl signal*/
    };

    if (!peripherals_i2c_init(self->i2c_num, &i2c_conf)) {
        mp_raise_OSError(MP_EIO);
    }

    claim_pin(sda);
    claim_pin(scl);
}

bool common_hal_i2cperipheral_i2c_peripheral_deinited(i2cperipheral_i2c_peripheral_obj_t *self) {
    return self->sda_pin == NULL;
}

void common_hal_i2cperipheral_i2c_peripheral_deinit(i2cperipheral_i2c_peripheral_obj_t *self) {
    if (common_hal_i2cperipheral_i2c_peripheral_deinited(self)) {
        return;
    }

    peripherals_i2c_deinit(self->i2c_num);

    common_hal_reset_pin(self->sda_pin);
    common_hal_reset_pin(self->scl_pin);
    self->sda_pin = NULL;
    self->scl_pin = NULL;
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
