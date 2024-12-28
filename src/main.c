#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/kernel.h>


#define CAPSENSE2_I2C_ADDR 0x28 // CAP1114 I2C address

#define I2C0_NODE DT_NODELABEL(capsense2)

const struct device *i2c_dev;

static const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(I2C0_NODE);

int main(void)
{
    printf("Hello, Zephyr!\n");

   int ret;
    uint8_t touch_status;

    uint8_t dev_addr;

    i2c_dev = DEVICE_DT_GET(DT_NODELABEL(i2c0));
    if (!device_is_ready(dev_i2c.bus)) {
        printf("I2C device not ready");
        return 1;
    }

 while (1) {
        // Read touch status register (example register address 0x03)
        ret = i2c_reg_read_byte(i2c_dev, CAPSENSE2_I2C_ADDR, 0x03, &touch_status);
        if (ret == 0) {
            printf("Touch Status: 0x%02X \n", touch_status);
        } else {
            printf("Failed to read touch status (err: %d)", ret);
        }

        k_sleep(K_MSEC(500));
    }


    return 0;
}
