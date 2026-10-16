#include "render.h"
#include "../log.h"
#include "../app.h"
#include "../ev.h"
#include "cam.h"

#include <HandmadeMath/HandmadeMath.h>

#include <nuklear/nuklear.h>

#include <sokol/app.h>
#include <sokol/gfx.h>
#include <sokol/glue.h>
#include <sokol/util/nuklear.h>

static struct {
  kon_desc_t* desc;
  
  struct nk_context* nk;
  
  sg_pass_action pass; 
} state;

void
kon_render(kon_camera_t* cam) {
  state.nk = snk_new_frame();
  
  if (state.desc->on_ui)
    state.desc->on_ui(state.nk);
   
  sg_begin_pass(&(sg_pass){
    .action = state.pass,
    .swapchain = sglue_swapchain()
  });
  
  //sg_apply_uniforms(0, &(sg_range){
  //  .ptr = kon_cameraMatrix(cam).Elements[0],
  //  .size = sizeof(HMM_Mat4)
  //});
  
  if (state.desc->on_render)
    state.desc->on_render();

  snk_render(sapp_width(), sapp_height());
    
  sg_end_pass();
  sg_commit(); 
}

void
__kon_renderInit(kon_desc_t* desc) {
  sg_setup(&(sg_desc){
    .environment = sglue_environment(),
    .logger.func = __kon_sokol_log         
  });

  snk_setup(&(snk_desc_t){
    .dpi_scale = sapp_dpi_scale()         
  });

  state.desc = desc;
  state.pass = (sg_pass_action){
    .colors[0] = {
      .load_action = SG_LOADACTION_CLEAR,
      .clear_value = { 0.0f, 0.0f, 0.0f, 0.0f }
    }
  };
}

void
__kon_renderDeinit() {
  sg_shutdown();
}

void
__kon_renderEvent(const kon_event_t* ev) {
  snk_handle_event((sapp_event*)ev);
}
