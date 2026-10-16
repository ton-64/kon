#ifndef KON_APP_H_
#define KON_APP_H_

#include "start.h"

struct nk_context;

struct kon_event;

typedef struct kon_desc {
  void (*on_init)(void);
  void (*on_deinit)(void);
  void (*on_ui)(struct nk_context* nk); 
  void (*on_update)(float);
  void (*on_render)(void);
  void (*on_event)(const struct kon_event*);

  const char* title;  
} kon_desc_t;

/* @brief The starter of our application that should be assigned by the cliente */
extern kon_desc_t* kon_main(int argc, char* argv[]);

void __kon_run(int argc, char* argv[]);

#if defined(KON_ENTRY) && !defined(KON_ENTRY_DONE)
int
main(int argc, char* argv[]) {
  __kon_run(argc, argv);
}
#define KON_ENTRY_DONE
#endif

void kon_requestQuit();

#endif /* KON_APP_H_ */
