#include "app.h"
#include "log.h"
#include "ev.h"
#include "load/audio.h"
#include "render/render.h"

/*
    SOKOL is the main backend for now, propably forever.
 */
#include <sokol/app.h>

static kon_desc_t* desc = NULL;

static void
onInit(void) {
  if (!__kon_audioInit())
    return;
  __kon_renderInit(desc);

  if (desc->on_init)
    desc->on_init();
}

static void
onFrame(void) {
  float dt = (float)sapp_frame_duration();

  if (desc->on_update)
    desc->on_update(dt);
}

static void
onCleanup(void) {
  if (desc->on_deinit)
    desc->on_deinit();
  
  __kon_renderDeinit();
  __kon_audioDeinit();  
}

static void
onEvent(const sapp_event* ev) {
  /*
      Since kon_event_t maps directly, I can just cast it.
   */
  const kon_event_t* m = (kon_event_t*)ev;

  __kon_renderEvent(m);

  if (desc->on_event)
    desc->on_event(m);
}

void
__kon_run(int argc, char* argv[]) {
  desc = kon_main(argc, argv);
  
  sapp_desc d = (sapp_desc){
    .init_cb = onInit,
    .frame_cb = onFrame,
    .cleanup_cb = onCleanup,
    .event_cb = onEvent,
    .width = 640,
    .height = 480,
    .window_title = desc->title,
    .logger.func = __kon_sokol_log    
  };
  sapp_run(&d);
}

void
kon_requestQuit() {
  sapp_request_quit();
}
