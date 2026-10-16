#ifndef KON_AUDIO_H_
#define KON_AUDIO_H_

#include "../start.h"

#include <stddef.h>
#include <stdbool.h>

struct __kon_track_in;

/*
    @brief The sound structure
 */
typedef struct kon_track {
  struct __kon_track_in* in;

  unsigned int sample_rate;
  unsigned int channels;
  bool load;
} kon_track_t;

kon_track_t kon_loadTrackFromMemory(const void* data, size_t size);
void kon_freeTrack(kon_track_t* tk);

void kon_loopTrack(kon_track_t* tk, bool enable);

void kon_playTrack(kon_track_t* tk);

/*
    @brief Play sound tk whtk specific time frame
    @param target - In seconds
 */
void kon_seekTrack(kon_track_t* tk, double target);

void kon_pauseTrack(kon_track_t* tk);

bool __kon_audioInit();
void __kon_audioDeinit();

#endif /* KON_AUDIO_H_ */
