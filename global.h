uint8_t data_write[64];
uint8_t data_read[64];
char str[255];

int counter = 0;

int buttonPressedKey1 = 0;
int buttonPressedKey2 = 0;

int game_end_flag = 0;
int game_begin_flag = 0;
int memory_error_flag = 0;
int wait_memory_flag = 0;

int complete;


int counter_actual_value;
int wait_memory_counter;


enum State {
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

enum State current_state;
enum State previous_state;