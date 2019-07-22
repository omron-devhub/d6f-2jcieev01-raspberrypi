/*
 * MIT License
 * Copyright (c) 2019 - present OMRON Corporation
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

/* includes */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdbool.h>

/* defines */
#define D6F_ADDR 0x6C  // D6F-PH I2C client address at 7bit expression

uint8_t conv16_u8_h(int16_t a) {
    return (uint8_t)(a >> 8);
}

uint8_t conv16_u8_l(int16_t a) {
    return (uint8_t)(a & 0xFF);
}

int16_t conv8us_s16_be(uint8_t* buf) {
    return (int16_t)(((int32_t)buf[0] << 8) + (int32_t)buf[1]);
}

#define RASPBERRY_PI_I2C    "/dev/i2c-1"
#define I2CDEV              RASPBERRY_PI_I2C


/** <!-- i2c_write_reg16 {{{1 --> I2C write bytes with a 16bit register.
 */
uint32_t i2c_write_reg16(uint8_t devAddr, uint16_t regAddr,
                         uint8_t* data , uint8_t length
) {
    uint8_t buf[128];
    if (length > 127) {
        fprintf(stderr, "Byte write count (%d) > 127\n", length);
        return 11;
    }

    int fd = open(I2CDEV , O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "Failed to open device: %s\n", strerror(errno));
        return 12;
    }
    int err = 0;
    do {
        if (ioctl(fd, I2C_SLAVE, devAddr) < 0) {
            fprintf(stderr, "Failed to select device: %s\n", strerror(errno));
            err = 13; break;
        }
        buf[0] = regAddr >> 8;
        buf[1] = regAddr & 0xFF;
        if (length > 0) {
            memcpy(buf + 2, data, length);
        }
        length += 2;
        int count = write(fd, buf, length);
        if (count < 0) {
            fprintf(stderr, "Failed to write device(%d): %s\n",
                    count, strerror(errno));
            err = 14; break;
        } else if (count != length) {
            fprintf(stderr, "Short write to device, expected %d, got %d\n",
                    length, count);
            err = 15; break;
        }
    } while (false);
    close(fd);
    return err;
}


/** <!-- i2c_read_reg8 {{{1 --> I2C read function for bytes transfer.
 */
uint32_t i2c_read_reg8(uint8_t devAddr, uint8_t regAddr,
                       uint8_t* data, uint8_t length) {
    int fd = open(I2CDEV, O_RDWR);

    if (fd < 0) {
        fprintf(stderr, "Failed to open device: %s\n", strerror(errno));
        return 21;
    }
    int err = 0;
    do {
        if (ioctl(fd, I2C_SLAVE, devAddr) < 0) {
            fprintf(stderr, "Failed to select device: %s\n", strerror(errno));
            err = 22; break;
        }
        if (write(fd, &regAddr, 1) != 1) {
            fprintf(stderr, "Failed to write reg: %s\n", strerror(errno));
            err = 23; break;
        }
        int count = read(fd, data, length);
        if (count < 0) {
            fprintf(stderr, "Failed to read device(%d): %s\n",
                    count, strerror(errno));
            err = 24; break;
        } else if (count != length) {
            fprintf(stderr, "Short read  from device, expected %d, got %d\n",
                    length, count);
            err = 25; break;
        }
    } while (false);
    close(fd);
    return err;
}


/** <!-- main - Differential pressure sensor {{{1 -->
 * 1. read and convert sensor.
 * 2. output results, format is: [Pa]
 */
int main() {
    i2c_write_reg16(D6F_ADDR, 0x0B00, NULL, 0);
    delay(900);

    uint8_t send0[] = {0x40, 0x18, 0x06};
    i2c_write_reg16(D6F_ADDR, 0x00D0, send0, 3);

    delay(50);  // wait 50ms

    uint8_t send1[] = {0x51, 0x2C};
    i2c_write_reg16(D6F_ADDR, 0x00D0, send1, 2);

    uint8_t rbuf[2];
    uint32_t ret = i2c_read_reg8(D6F_ADDR, 0x07, rbuf, 2);  // read from [07h]
    if (ret) {
        return ret;
    }
    int16_t rd_flow = conv8us_s16_be(rbuf);

    float flow_rate;
    // 0-10[L/min] range
    flow_rate = ((float)rd_flow - 1024.0) * 10.0 / 60000.0 - 250.0;

    printf("sensor output: %6.2f", flow_rate);  // print converted flow rate
    printf("[L/min]\n");
    return 0;
}
// vi: ft=arduino:fdm=marker:et:sw=4:tw=80
