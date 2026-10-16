#define KON_ENTRY
#include <kon.h>
#include <nuklear/nuklear.h>

static kon_track_t goob;

void on_init() {
  kon_toExecDir();

  size_t size;
  char* data = kon_loadFile("a.mp3", &size);
  if (data == NULL) {
    return;
  }

  goob = kon_loadTrackFromMemory(data, size);
  if (goob.load == false) {
    kon_errorLog(0, "Ha");
    kon_requestQuit();
    return;
  }

  free(data);
}

void on_deinit() {
  kon_freeTrack(&goob);
}

void on_update(float dt) {
  kon_camera_t cam = kon_cameraInit(500, 500);
  kon_render(&cam);  
}

void on_ui(struct nk_context* nk) {
  if (nk_begin(nk, "Basic", nk_rect(50, 50, 100, 200), NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE)) {
    nk_layout_row_dynamic(nk, 30, 1);

    if (nk_button_label(nk, "Test") == nk_true) {
      kon_playTrack(&goob);
    }
  }
  nk_end(nk);
}

void on_render() {
  
}

kon_desc_t* kon_main(int argc, char* argv[]) {
  static kon_desc_t desc = (kon_desc_t){
    .on_init = on_init,
    .on_deinit = on_deinit,
    .on_update = on_update,
    .on_ui = on_ui,
    .on_render = on_render,
    .title = "Hello"
  };
  return &desc;
}
