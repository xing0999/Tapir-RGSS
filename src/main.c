#include <stdio.h>
#include <ruby.h>
#include <SDL.h>
#include "sdl_misc.h"

#ifdef RUBY_GLOBAL_SETUP
RUBY_GLOBAL_SETUP
#endif

static VALUE protected_main(VALUE data);

int main() {
  int ruby_argc = 2;
  char *ruby_argv_array[] = {
    (char*)"ruby",
    NULL
  };
  char **ruby_argv = ruby_argv_array;
  int state = 0;

  initSDL();

#ifdef RUBY_INIT_STACK
  ruby_sysinit(&ruby_argc, &ruby_argv);
  {
    RUBY_INIT_STACK;
    ruby_init();
    rb_protect(protected_main, Qnil, &state);
  }
#else
  {
    (void) ruby_argc;
    (void) ruby_argv;
    ruby_init();
    rb_protect(protected_main, Qnil, &state);
  }
#endif

  loopSDL();
  cleanupSDL();
  return state;
}

static VALUE protected_main(VALUE data) {
  (void) data;

  rb_eval_string("print \"Hello, world!\\n\"");
  rb_eval_string("p RUBY_VERSION");
  return Qnil;
}
