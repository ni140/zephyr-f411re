/*
 * Copyright (c) 2025 Maciej
 *
 * SPDX-License-Identifier: MIT
 */

// Source:
// https://gist.github.com/disposedtrolley/f0edbef0e65dbd7b56207e4ffc35c8d1
// https://github.com/HexabitzPlatform/STM32-Zephyr/tree/main

// I2C:
// zephyr\samples\boards\st\i2c_timing\src\main.c

// Modules:
// https://www.youtube.com/watch?v=NlRM2IfODTs&list=PLEQVp_6G_y4iFfemAbFsKw6tsGABarTwp&index=3

#include <stdio.h>
#include <string.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/kernel.h>

#define SLEEP_TIME_MS 100

// static uint8_t rx_data;

const struct device *uart = DEVICE_DT_GET(DT_NODELABEL(usart1));

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

char uart_buffer[] = "hello world!\n";

void print_uart(char *buf, uint8_t msg_len) {
  for (int i = 0; i < msg_len; i++) {
    uart_poll_out(uart, buf[i]);
  }
}

int main(void) {
  int ret = 0;

  if (!gpio_is_ready_dt(&led)) {
    return 0;
  }

  ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
  if (ret < 0) {
    return 0;
  }

  if (!device_is_ready(uart)) {
    return 0;
  }

  while (1) {
    gpio_pin_toggle_dt(&led);

    // ret = uart_poll_in(uart, &rx_data);
    // if (ret == 0) {
    //   uart_poll_out(uart, rx_data);
    //   // printk("Received data: %c\n", rx_data);
    // }

    print_uart(uart_buffer, strlen(uart_buffer));

    k_msleep(SLEEP_TIME_MS);
  }
  return 0;
}
