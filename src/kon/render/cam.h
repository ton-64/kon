/*
    Basic orthographic camera
 */
#ifndef KON_CAM_H_
#define KON_CAM_H_

#include "../start.h"

#include <HandmadeMath/HandmadeMath.h>

typedef struct kon_camera {
  float x, y;
  float zoom;
  float width;
  float height;
} kon_camera_t;

static inline kon_camera_t
kon_cameraInit(float width, float height) {
  return (kon_camera_t){
    .x = 0,
    .y = 0,
    .zoom = 0,
    .width = width,
    .height = height 
  };
}

static inline HMM_Mat4
kon_cameraMatrix(kon_camera_t* cam) {
  float h_w = (cam->width / 2.0f) * cam->zoom;
  float h_h = (cam->height / 2.0f) * cam->zoom;
  
  float left = cam->x - h_w;
  float right = cam->x + h_w;
  float bottom = cam->y - h_h;
  float top = cam->y + h_h;

  return 
#if defined(KON_GLCORE) || defined(KON_GLES3)
  HMM_Orthographic_RH_NO(left, right, bottom, top, -1.0f, 1.0f);
#elif defined(KON_D3D11) || defined(KON_METAL) || defined(KON_WGPU)
  HMM_Orthographic_LH_ZO(left, right, bottom, top, -1.0f, 1.0f);
#else
  HMM_Orthographic_RH_ZO(left, right, bottom, top, -1.0f, 1.0f);
#endif   
};

#endif /* CAMERA_H_ */
