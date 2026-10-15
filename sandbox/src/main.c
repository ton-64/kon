#include <kon/log.h>
#include <kon/fs.h>

#define KON_ENTRY
#include <kon/app.h>

#include <kon/ev.h>

#include <stdlib.h>
#include <string.h>

kon_log_level_t kon_min_log_level = KON_LOG_LEVEL_INFO;

static void
onInit() {
  char* data = kon_loadFile("a.txt", NULL);
  kon_infoLog(0, "%s", data);
  free(data);
}

static void
onShutdown() {
  kon_saveFile("a.txt", "Hello World", 11);
}

static void
onUpdate(float dt) {
  
}

static void
onEvent(kon_event_t* ev) {
  switch (ev->kind) {
    case KON_EVENTKIND_KEY_DOWN:
      if (ev->keycode == KON_KEYCODE_Q)
        kon_requestQuit();    
    default:
      break;
  } 
}

kon_app_desc_t*
kon_passAppDesc(int argc, char* argv[]) {
  static kon_app_desc_t desc = (kon_app_desc_t){
    .onInit = onInit,
    .onShutdown = onShutdown,
    .onUpdate = onUpdate,
    .onEvent = onEvent,

    .title = "Kon sandbox"
  };
  return &desc;
}
