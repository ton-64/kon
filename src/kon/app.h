#ifndef KON_APP_H_
#define KON_APP_H_

#include "start.h"

/* FROM: <kon/ev.h> */
struct kon_event;

typedef struct kon_app_desc {
  void (*onInit)(void);
  void (*onShutdown)(void);
  void (*onUpdate)(float);
  void (*onRender)(void);
  void (*onEvent)(struct kon_event*);

  const char* title;  
} kon_app_desc_t;

/* @brief The starter of our application that should be assigned by the cliente */
extern kon_app_desc_t* kon_passAppDesc(int argc, char* argv[]);

void __kon_app_run(int argc, char* argv[]);

/*
  Entry point of our program btw lalalal elmos worldw still W.I.P for android ahhh
 */
#if defined(KON_ENTRY) && !defined(KON_ENTRY_DONE)
int
main(int argc, char* argv[]) {
  __kon_app_run(argc, argv);
}
#define KON_ENTRY_DONE
#endif

void kon_requestQuit();

#endif /* KON_APP_H_ */
