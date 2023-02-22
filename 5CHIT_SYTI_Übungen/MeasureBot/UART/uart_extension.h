/*
 * uart_extension.h
 *
 * Created: 18.01.2023 19:11:59
 *  Author: manue
 */ 

#define C_BEGIN "<"
#define C_ESC   ">"
#define C_TYPE_DELIMITER ";"
#define C_DEVICE_DATA_DELIMITER ":"
#define C_DEVICE_DELIMITER "|"
#define BUFFER_SIZE 50
typedef enum RxState {WAIT, ACCEPT, ESCAPE, ERROR} rxStatus;

void uart_put_string(char *string);
int handle_uart_values();
int uart_check_for_value(uint8_t *value);
void write_char_to_buffer(uint8_t *value);
void read_buffer(char *output);