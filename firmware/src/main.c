/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>      // Defines NULL
#include <stdbool.h>     // Defines true
#include <stdlib.h>      // Defines EXIT_FAILURE
#include "definitions.h" // SYS function prototypes

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

void core_int(uint32_t status, uintptr_t context)
{
  GPIO_RB9_Toggle();
}

int main(void)
{
  /* Initialize all modules */
  SYS_Initialize(NULL);
  CORETIMER_CallbackSet(&core_int, 0);
  CORETIMER_Start();
  while (true)
  {
    /* Maintain state machines of all polled MPLAB Harmony modules. */
    SYS_Tasks();
    GPIO_RB10_Toggle();
    CORETIMER_DelayMs(100);
  }

  /* Execution should not come here during normal operation */

  return (EXIT_FAILURE);
}

/*******************************************************************************
 End of File
*/
