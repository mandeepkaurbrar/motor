/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"

#include "pin_mux.h"
#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define APP_BOARD_TEST_LED_PORT 1U
#define APP_BOARD_TEST_LED_PIN 10U
#define APP_SW_PORT BOARD_SW1_GPIO_PORT
#define APP_SW_PIN  BOARD_SW1_GPIO_PIN



#define SWITCH1_SPEED1_PORT 1U
#define SWITCH1_SPEED1_PIN 0U
#define SWITCH2_SPEED2_PORT 1U
#define SWITCH2_SPEED2_PIN  14U
#define SWITCH3_DIRECTION1_PORT 1U
#define SWITCH3_DIRECTION1_PIN 13U
#define SWITCH4_DIRECTION2_PORT 1U
#define SWITCH4_DIRECTION2_PIN 12U


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief delay a while.
 */
void delay(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 100000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    uint32_t port_state = 0;

    uint32_t port_state_SW1 = 0;
    uint32_t port_state_SW2 = 0;
    uint32_t port_state_SW3 = 0;
    uint32_t port_state_SW4 = 0;

    /* Define the init structure for the output LED pin*/
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput, 0,
    };

    /* Board pin, clock, debug console init */
    /* attach 12 MHz clock to FLEXCOMM0 (debug console) */
    CLOCK_AttachClk(BOARD_DEBUG_UART_CLK_ATTACH);
    /* enable clock for GPIO*/
    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);

    BOARD_InitPins();
    BOARD_BootClockFROHF48M();
    BOARD_InitDebugConsole();

    /* Print a note to terminal. */
    PRINTF("\r\n GPIO Driver example\r\n");
    PRINTF("\r\n The LED is taking turns to shine.\r\n");

    /* Init SW GPIO PORT. */
    GPIO_PortInit(GPIO, APP_SW_PORT);

    GPIO_PortInit(GPIO, SPEED1_SWITCH1_PORT);

    GPIO_PortInit(GPIO, SPEED2_SWITCH2_PORT);

    GPIO_PortInit(GPIO, DIRECTION1_SWITCH3_PORT);

    GPIO_PortInit(GPIO, DIRECTION2_SWITCH4_PORT);


    /* Init output LED GPIO. */
    GPIO_PortInit(GPIO, APP_BOARD_TEST_LED_PORT);
    GPIO_PinInit(GPIO, APP_BOARD_TEST_LED_PORT, APP_BOARD_TEST_LED_PIN, &led_config);
    GPIO_PinWrite(GPIO, APP_BOARD_TEST_LED_PORT, APP_BOARD_TEST_LED_PIN, 1);

    /* Port masking */
    GPIO_PortMaskedSet(GPIO, APP_BOARD_TEST_LED_PORT, 0x0000FFFF);
    GPIO_PortMaskedWrite(GPIO, APP_BOARD_TEST_LED_PORT, 0xFFFFFFFF);

    port_state = GPIO_PortRead(GPIO, APP_SW_PORT);

    port_state_SW1 = GPIO_PortRead(GPIO, SPEED1_SWITCH1_PORT);

    port_state_SW2 = GPIO_PortRead(GPIO, SPEED2_SWITCH2_PORT);

    port_state_SW3 = GPIO_PortRead(GPIO, DIRECTION1_SWITCH3_PORT);

    port_state_SW4 = GPIO_PortRead(GPIO, DIRECTION2_SWITCH4_PORT);


    PRINTF("\r\n Standard port read: %x\r\n", port_state);

    PRINTF("\r\n Press Switch1: %x\r\n", port_state_SW1);
    PRINTF("\r\n Press Switch2: %x\r\n", port_state_SW2);
    PRINTF("\r\n Press Switch3: %x\r\n", port_state_SW3);
    PRINTF("\r\n Press Switch4: %x\r\n", port_state_SW4);

    port_state = GPIO_PortMaskedRead(GPIO, APP_SW_PORT);

    port_state_SW1 = GPIO_PortMaskedRead(GPIO, SPEED1_SWITCH1_PORT);

    port_state_SW2 = GPIO_PortMaskedRead(GPIO, SPEED2_SWITCH2_PORT);

    port_state_SW3 = GPIO_PortMaskedRead(GPIO, DIRECTION1_SWITCH3_PORT);

    port_state_SW4 = GPIO_PortMaskedRead(GPIO, DIRECTION2_SWITCH4_PORT);


    PRINTF("\r\n Masked port read: %x\r\n", port_state);

    while (1)
    {
        port_state = GPIO_PortRead(GPIO, APP_SW_PORT);

        if (!(port_state & (1 << APP_SW_PIN)))
        {
            PRINTF("\r\n Port state: %x\r\n", port_state);
            PRINTF("\n BUTTON PRESSED");
            GPIO_PortToggle(GPIO, APP_BOARD_TEST_LED_PORT, 1u << APP_BOARD_TEST_LED_PIN);
        }

        port_state_SW1 = GPIO_PortRead(GPIO, SPEED1_SWITCH1_PORT);

        if (!(port_state_SW1 & (1 << SPEED1_SWITCH1_PIN)))
        {
        	PRINTF("\n Switch1 pressed for motor1");
        	GPIO_PortToggle(GPIO, APP_BOARD_TEST_LED_PORT, 1u << APP_BOARD_TEST_LED_PIN);
        }

        port_state_SW2 = GPIO_PortRead(GPIO, SPEED2_SWITCH2_PORT);

               if (!(port_state_SW2 & (1 << SPEED2_SWITCH2_PIN)))
               {
               	PRINTF("\n Switch2 pressed for motor2");
               	GPIO_PortToggle(GPIO, APP_BOARD_TEST_LED_PORT, 1u << APP_BOARD_TEST_LED_PIN);
               }

        port_state_SW3 = GPIO_PortRead(GPIO, DIRECTION1_SWITCH3_PORT);

                if (!(port_state_SW1 & (1 << DIrECTION1_SWITCH3_PIN)))
               {
               	PRINTF("\n Switch3 pressed for motor1");
                 GPIO_PortToggle(GPIO, APP_BOARD_TEST_LED_PORT, 1u << APP_BOARD_TEST_LED_PIN);
               }

         port_state_SW4 = GPIO_PortRead(GPIO, DIRECTION2_SWITCH4_PORT);

                if (!(port_state_SW1 & (1 <<  DIRECTION2_SWITCH4_PIN)))
                {
                PRINTF("\n Switch4 pressed for motor2");
                GPIO_PortToggle(GPIO, APP_BOARD_TEST_LED_PORT, 1u << APP_BOARD_TEST_LED_PIN);
                }

        delay();
    }
}
