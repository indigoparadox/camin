
#define INPUT_C
#include "../input.h"

#include <SDL/SDL.h>
#include <libvcol.h>

void input_init( struct INPUT* p ) {
   SDL_EnableUNICODE( 1 );
   p->event = mem_alloc( 1, SDL_Event );
}

void input_get_event( struct INPUT* input ) {
   SDL_Event* event;

   event = (SDL_Event*)(input->event);
#ifdef DEBUG
   assert( NULL != event );
#endif /* DEBUG */

   SDL_PollEvent( event );

   if( SDL_KEYDOWN == event->type ) {
      /* Detect repeats. */
      if(
         INPUT_TYPE_KEY == input->type &&
         event->key.keysym.scancode == input->scancode
      ) {
         input->repeat++;
      } else {
         input->repeat = 0;
      }

      input->type = INPUT_TYPE_KEY;
      input->character = event->key.keysym.unicode & 0x00ff;
      input->scancode = input_native_to_scancode( event->key.keysym.scancode );
#ifdef DEBUG_KEYS
      lg_debug( __FILE__, "Scancode: %d\n", input->scancode );
      lg_debug( __FILE__, "Char: %d\n", input->character );
#endif /* DEBUG_KEYS */
   } else if( SDL_QUIT == event->type ) {
      input->type = INPUT_TYPE_CLOSE;
   } else {
      input->type = INPUT_TYPE_NONE;
      input->character = 0;
      input->scancode = 0;
   }
}

void input_clear_buffer( struct INPUT* input ) {
}

void input_shutdown( struct INPUT* input ) {
   mem_free( input->event );
}

int input_scancode_to_native( enum INPUT_SCANCODE code ) {
   switch( code ) {
   case INPUT_SCANCODE_BACKSPACE:
      return 22;

   case INPUT_SCANCODE_ENTER:
      return 36;

   case INPUT_SCANCODE_ESC:
      return 9;

   case INPUT_SCANCODE_TAB:
      return 23;

   case INPUT_SCANCODE_LEFT:
      return 82;

   case INPUT_SCANCODE_RIGHT:
      return 83;

   case INPUT_SCANCODE_UP:
      return 84;

   case INPUT_SCANCODE_DOWN:
      return 85;

   case INPUT_SCANCODE_NULL:
   default:
      return 0;
   }
}

enum INPUT_SCANCODE input_native_to_scancode( int code ) {
   switch( code ) {
   case 22:
      return INPUT_SCANCODE_BACKSPACE;

   case 36:
      return INPUT_SCANCODE_ENTER;

   case 9:
      return INPUT_SCANCODE_ESC;

   case 23:
      return INPUT_SCANCODE_TAB;

   case 82:
      return INPUT_SCANCODE_LEFT;

   case 83:
      return INPUT_SCANCODE_RIGHT;

   case 84:
      return INPUT_SCANCODE_UP;

   case 85:
      return INPUT_SCANCODE_DOWN;

   default:
      return INPUT_SCANCODE_NULL;
   }
}
