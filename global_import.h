extern uint8_t data_write[64];
extern uint8_t data_read[64];
extern char str[255];

extern int counter;
extern int buttonPressedKey1;
extern int buttonPressedKey2;

extern int game_end_flag;
extern int game_begin_flag;
extern int memory_error_flag;
extern int wait_memory_flag;

extern int counter_initial_value;
extern int counter_actual_value;
extern int wait_memory_counter;

extern int complete;

extern enum State {
	MENU,
	GAME_BEGIN,
	GAME_LAUNCHED, // flagLauchGame
	GAME_END_WRITE,
	GAME_END_READ,
	WAIT_MEMORY,
	GAME_END, //flagMemoryAccess
	GAME_LOST,
	MEMORY_ERROR
};

extern enum State current_state;
extern enum State previous_state;;