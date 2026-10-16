#ifndef KON_RENDER_H_
#define KON_RENDER_H_

#include "../start.h"

struct kon_camera;
void kon_render(struct kon_camera* cam);

struct kon_desc;
void __kon_renderInit(struct kon_desc* desc);

void __kon_renderDeinit();

struct kon_event;
void __kon_renderEvent(const struct kon_event* ev);

#endif /* KON_RENDER_H_ */
