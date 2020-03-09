# Microprocessor architecture project: 0-Stop
[IMR1 - 2017] Thomas MAHERAULT - Eliott VINCENT


As part of the microprocessor architecture project, we developed the 0-Stop game. This application uses an I2C bus connected to a memory and interrupt mechanisms.


## Rules

The rules of the game are simple:
  - A counter is initialized at 10 seconds and starts to decrement...
  - When the user presses the KEY1 button, the counter stops and determines the score: the closer the score is to zero, the better it is.
  - Easy, isn't it?! But after 5 seconds, the counter will disappear and the user will have to guess the right time to be the closest to zero!

## Mechanisms used

- State machine
In order to manager the different key states of the game, we used a "state machine".
The `State` enum, declared in the `global.h` and `global_import.h` files, allows us to declare the different states of our game:
    * MENU
    * GAME_BEGIN
    * GAME_LAUNCHED
    * GAME_END_WRITE
    * GAME_END_WRITE
    * WAIT_MEMORY
    * GAME_END
    * GAME_LOST
    * MEMORY_ERROR

The handling of these states is handled by the `current_state` variable, which is of type `State`. This variable therefore changes its value at different times during the game, which allows us to identify the progress of the game.

- Interrupts
The various program interrupts are managed in the `interrupts.c` file, which contains the implementations of the various handlers:
    * Interrupts for the timer
    The timer is handled by an interrupt, which triggers the handler function `TIMER0_IRQHandler()`. This function scans the 2 buttons KEY1 and KEY2, and increments the timer.
    * Interrupts for I2C operations
    WWrite and read operations in the I2C memory are also managed by interrupt. The `i2c_eeprom_write` et `i2c_eeprom_read` functions (defined in `i2c_helpers.c`). These functions perform their respective operation, using the `IC2_MasterTransferData()` method and by specifying the `I2C_TRANSER_INTERRUPT` value of the `I2C_TRANSFER_OPT_Type` parameter, which determines the type of transfer to perform (pooling or interrupt).
    Thus, the handler function `I2C0_IRQHandler()` is triggered. In the latter, we call the `I2C_MasterHandler()` function, which will advance the transfer according to its status. Finally, we check if the transmission is complete. If it is, the `complete` flag is raised.
