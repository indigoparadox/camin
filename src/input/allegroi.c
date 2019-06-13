
#define INPUT_C
#include "../input.h"

#include <allegro.h>
#include <libvcol.h>

#include "allegro/keyboard.h"

//#include "../client.h"
//#include "../server.h"
//#include "../proto.h"

extern struct CLIENT* main_client;
extern struct SERVER* main_server;

volatile bool window_closed = FALSE;

typedef struct {
   int keysym;
   void (*callback)( struct CLIENT* c, void* arg );
} INPUT_ENTRY;

static void input_close_allegro_window() {
   /* scaffold_set_client();
   proto_client_stop( main_client ); */
   window_closed = TRUE;
}

void input_init( struct INPUT* p ) {
   install_keyboard();
   set_close_button_callback( input_close_allegro_window );
}

void input_get_event( struct INPUT* input ) {
   uint16_t key_pressed;

   poll_keyboard();

   if( FALSE != window_closed ) {
      input->type = INPUT_TYPE_CLOSE;
   } else if( keypressed() ) {
      key_pressed = readkey();
      input->type = INPUT_TYPE_KEY;
      input->character = key_pressed & 0xff;
      input->scancode = input_native_to_scancode( (key_pressed & 0xff00) >> 8 );
#ifdef DEBUG_KEYS
      lg_debug( __FILE__, "Scancode: %d\n", input->scancode );
#endif /* DEBUG_KEYS */
   } else {
      input->type = INPUT_TYPE_NONE;
      input->character = 0;
      input->scancode = 0;
   }
}

void input_clear_buffer( struct INPUT* input ) {
   clear_keybuf();
}

void input_shutdown( struct INPUT* input ) {
}

int input_scancode_to_native( enum INPUT_SCANCODE code ) {
   switch( code ) {
   case INPUT_SCANCODE_ESC:
      return __allegro_KEY_ESC;

   case INPUT_SCANCODE_BACKSPACE:
      return __allegro_KEY_BACKSPACE;

   case INPUT_SCANCODE_ENTER:
      return __allegro_KEY_ENTER;

   case INPUT_SCANCODE_TAB:
      return __allegro_KEY_TAB;

   case INPUT_SCANCODE_LEFT:
      return __allegro_KEY_LEFT;

   case INPUT_SCANCODE_RIGHT:
      return __allegro_KEY_RIGHT;

   case INPUT_SCANCODE_UP:
      return __allegro_KEY_UP;

   case INPUT_SCANCODE_DOWN:
      return __allegro_KEY_DOWN;

   case INPUT_SCANCODE_NULL:
   default:
      return 0;
   }
}

enum INPUT_SCANCODE input_native_to_scancode( int code ) {
   switch( code ) {
   case __allegro_KEY_ESC:
      return INPUT_SCANCODE_ESC;

   case __allegro_KEY_BACKSPACE:
      return INPUT_SCANCODE_BACKSPACE;

   case __allegro_KEY_ENTER:
      return INPUT_SCANCODE_ENTER;

   case __allegro_KEY_TAB:
      return INPUT_SCANCODE_TAB;

   case __allegro_KEY_LEFT:
      return INPUT_SCANCODE_LEFT;

   case __allegro_KEY_RIGHT:
      return INPUT_SCANCODE_RIGHT;

   case __allegro_KEY_UP:
      return INPUT_SCANCODE_UP;

   case __allegro_KEY_DOWN:
      return INPUT_SCANCODE_DOWN;

   default:
      return 0;
   }
}
