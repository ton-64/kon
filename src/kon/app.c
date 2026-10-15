#include "app.h"
#include "ev.h"

/*
    SOKOL is the main backend for now, propably forever.
 */
#include <sokol/app.h>
#include <sokol/gfx.h>
#include <sokol/glue.h>
#include <sokol/log.h>

static kon_app_desc_t* desc = NULL;

static void
internalInitCb(void) {
  sg_setup(&(sg_desc){
      .environment = sglue_environment(),
      .logger.func = slog_func 
  });

  desc->onInit();
}

static void
internalFrameCb(void) {
  
}

static void
internalCleanupCb(void) {
  desc->onShutdown();
  
  sg_shutdown();
}

static void
internalEventCb(const sapp_event* ev) {
    
  /*
      As you can see, our event struct is directly compatible with SOKOL's event struct.
   */
  desc->onEvent((kon_event_t*)ev);
}

void
__kon_app_run(int argc, char* argv[]) {
  desc = kon_passAppDesc(argc, argv);
  
  sapp_desc d = (sapp_desc){
    .init_cb = internalInitCb,
    .frame_cb = internalFrameCb,
    .cleanup_cb = internalCleanupCb,
    .event_cb = internalEventCb,
    .width = 640,
    .height = 480,
    .window_title = desc->title,    
  };
  sapp_run(&d);
}

void
kon_requestQuit() {
  sapp_request_quit();
}
