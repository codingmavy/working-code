#include "stdint.h"
#include "gpio_regs.h"
#include "uart_kshitiz.h"

void uart_putc(char c) {
  while (!UART0_FF_THR_EMPTY);            // Wait until the FIFO holding register is empty
  UART0_DR = c;                           // Write character to transmitter register
}

void uart_puts(const char *str) {
  while (*str) {                          // Loop until value at string pointer is zero
    uart_putc(*str++);                    // Write the character and increment pointer
  }
}

void delay_long() {

    for (volatile uint64_t i = 0; i < 1000000; i++) {

        // Empty loop for delay

    }

}


// Function to create a short delay

void delay_short() {

    for (volatile uint64_t i = 0; i < 1; i++) {

        // Empty loop for delay

    }

}
uint32_t read_gpio_state() {

    return GCSR->GPIO_0; // Read the current state of GPIO_0

}
int main()
{
    UART0_FCR = UARTFCR_FFENA;              // Set the FIFO for polled operation
    uart_puts("Hello World!\n");            // Write the string to the UART
    while (1);                              // Loop forever to prevent program from ending
    {
        GCSR->GPIO_0 = 0x55;
        delay_short();
        GCSR->GPIO_0 = 0xaa;
        delay_short();

        // Read and print the state (assuming you have a way to print)

        uint32_t state = read_gpio_state();

        printf("GPIO State: 0x%X\n", state); // Print the current state
    }
}
