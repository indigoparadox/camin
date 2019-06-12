#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

enum INPUT_SCANCODE {
   INPUT_SCANCODE_NULL = 0,
   INPUT_SCANCODE_BACKSPACE = 1,
   INPUT_SCANCODE_ENTER = 2,
   INPUT_SCANCODE_ESC = 3,
   INPUT_SCANCODE_TAB = 4,
   INPUT_SCANCODE_LEFT = 5,
   INPUT_SCANCODE_RIGHT = 6,
   INPUT_SCANCODE_UP = 7,
   INPUT_SCANCODE_DOWN = 8
};

typedef enum INPUT_ASSIGNMENT {
   INPUT_ASSIGNMENT_ATTACK = ' ',
   INPUT_ASSIGNMENT_LEFT = 'a',
   INPUT_ASSIGNMENT_INV = 'e',
   INPUT_ASSIGNMENT_DOWN = 's',
   INPUT_ASSIGNMENT_RIGHT = 'd',
   INPUT_ASSIGNMENT_QUIT = 'q',
   INPUT_ASSIGNMENT_UP = 'w'
} INPUT_ASSIGNMENT;

typedef enum _INPUT_TYPE {
   INPUT_TYPE_NONE,
   INPUT_TYPE_KEY,
   INPUT_TYPE_MOUSE,
   INPUT_TYPE_CLOSE
} INPUT_TYPE;

struct INPUT {
   void* event;
   uint16_t character;
   enum INPUT_SCANCODE scancode;
   INPUT_TYPE type;
   uint16_t repeat;
};

//#include "scaffold.h"
//#include "client.h"

void input_init( struct INPUT* p );
void input_get_event( struct INPUT* input );
void input_clear_buffer( struct INPUT* input );
void input_shutdown( struct INPUT* input );
int input_scancode_to_native( enum INPUT_SCANCODE code );
enum INPUT_SCANCODE input_native_to_scancode( int code );

#endif /* INPUT_H */
