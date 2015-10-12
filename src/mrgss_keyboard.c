#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <mruby.h>
#include <mruby/class.h>
#include <mrgss/mrgss.h>
#include <mrgss/mrgss_keyboard.h>

/**
 *  buffers
 */
static char press[512];
static char trigger[512];
static char release[512];
static char repeat[512];
static mrb_int time[512];

/*
 * Update
 */
static mrb_value
input_update(mrb_state *mrb, mrb_int capa) {
    const Uint8* currentKeyStates;
    currentKeyStates = SDL_GetKeyboardState(NULL);
    for (int i = 0; i < 512; ++i) {
        trigger[i] = !press[i] && currentKeyStates[i];
        release[i] = press[i] && !currentKeyStates[i];
        press[i] = currentKeyStates[i];
        time[i] = press[i] ? time[i] + 1 : 0;
        repeat[i] = time[i] % 2 == 0;
    }
    return mrb_nil_value();
}

/*
 * trigger
 */
static mrb_value
input_trigger (mrb_state *mrb, mrb_int capa)
{
  mrb_int key;
  mrb_get_args (mrb, "i", &key);
  return trigger[key] == TRUE ? mrb_true_value () : mrb_false_value ();

}

/*
 * press
 */
static mrb_value
input_press (mrb_state *mrb, mrb_int capa)
{
  mrb_int key;
  mrb_get_args (mrb, "i", &key);
  return press[key] == TRUE ? mrb_true_value () : mrb_false_value ();
}

/*
 * release
 */
static mrb_value
input_release (mrb_state *mrb, mrb_int capa)
{
  mrb_int key;
  mrb_get_args (mrb, "i", &key);
  return release[key] == TRUE ? mrb_true_value () : mrb_false_value ();
}

/*
 * repeat
 */
static mrb_value
input_repeat (mrb_state *mrb, mrb_int capa)
{
  mrb_int key;
  mrb_get_args (mrb, "i", &key);
  return repeat[key] == TRUE ? mrb_true_value () : mrb_false_value ();
}

/*
 * time
 */
static mrb_value
input_time (mrb_state *mrb, mrb_int capa)
{
  mrb_int key;
  mrb_get_args (mrb, "i", &key);
  return mrb_fixnum_value (time[key]);
}

/**
 * Initialize mruby class
 */
void mrgss_keyboard_init(mrb_state *mrb) {
    struct RClass *hw = mrb_define_module_under(mrb, mrgss_module(),"Keyboard");
    mrb_define_class_method(mrb, hw, "update", (mrb_func_t) input_update, MRB_ARGS_NONE());
    mrb_define_class_method(mrb, hw, "trigger?", (mrb_func_t) input_trigger, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, hw, "press?", (mrb_func_t) input_press, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, hw, "release?", (mrb_func_t) input_release, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, hw, "repeat?", (mrb_func_t) input_repeat, MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb, hw, "press_time", (mrb_func_t) input_time, MRB_ARGS_REQ(1));
}
