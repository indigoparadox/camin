
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
      input->scancode = event->key.keysym.scancode;
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