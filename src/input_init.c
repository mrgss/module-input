#include <mruby.h>
#include <mruby/compile.h>
#include <mrgss/mrgss_keyboard.h>
#include <mrgss/mrgss_mouse.h>


void
mrb_mrgss_input_gem_init(mrb_state *mrb) {
    mrgss_keyboard_init(mrb);
    mrgss_mouse_init(mrb);
}

void
mrb_mrgss_input_gem_final(mrb_state* mrb) {
    
}

