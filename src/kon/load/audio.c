#include "audio.h"
#include "../log.h"

/*
    This is simply the best
 */
#include <miniaudio/miniaudio.h>

#include <stdlib.h>

#include <string.h> /* For strerror */
#include <errno.h>

static struct {
  ma_engine engine;
} state;

typedef struct __kon_track_in {
  /*
      For no dangling pointer risk
        though I hate this
   */
  void* data_copied;
  
  ma_sound sound;
  ma_decoder decoder;
} kon_in_t;

kon_track_t
kon_loadTrackFromMemory(const void* data, size_t size) {
  kon_track_t at = {0};
  kon_in_t* in = malloc(sizeof(kon_in_t));
  if (!in) {
    kon_errorLog(KON_LOG_TAG_DEFAULT, "Failed to allocate space to store track data : %s", strerror(errno));
    goto defer;
  }
  in->data_copied = malloc(size);
  if (!in->data_copied) {
    kon_errorLog(KON_LOG_TAG_DEFAULT, "Failed to allocate space to store copied data from track source : %s", strerror(errno));
    goto defer;
  }
  
  memcpy(in->data_copied, data, size);
   
  ma_result res;
  
  res = ma_decoder_init_memory(in->data_copied, size, NULL, &in->decoder);
  if (res != MA_SUCCESS) {
    kon_errorLog(KON_LOG_TAG_MINIAUDIO, "Failed to decode track data : %s", ma_result_description(res));
    free(in);
    goto defer;
  }

  res = ma_sound_init_from_data_source(&state.engine, (ma_data_source*)&in->decoder, MA_SOUND_FLAG_NO_SPATIALIZATION, NULL, &in->sound);
  if (res != MA_SUCCESS) {
    kon_errorLog(KON_LOG_TAG_MINIAUDIO, "Failed to load track : %s", ma_result_description(res));
    ma_decoder_uninit(&in->decoder);
    free(in);
    goto defer;
  }

  at.in = in;
  at.sample_rate = in->decoder.outputSampleRate;
  at.channels = in->decoder.outputChannels; 
  at.load = true;
  
  kon_infoLog(KON_LOG_TAG_MINIAUDIO, "Successfully loaded track");

defer:
  return at;
}

void
kon_freeTrack(kon_track_t* at) {
  if (!at->load)
    return;
  ma_sound_uninit(&at->in->sound);
  ma_decoder_uninit(&at->in->decoder);
  free(at->in->data_copied);
  free(at->in);

  at->load = false;
}

void
kon_loopTrack(kon_track_t* at, bool enable) {
  if (at->load)
    ma_sound_set_looping(&at->in->sound, enable ? MA_TRUE : MA_FALSE);  
}

void
kon_playTrack(kon_track_t* at) {
  if (at->load)
    ma_sound_start(&at->in->sound);
}

void
kon_pauseTrack(kon_track_t* at) {
  if (at->load)
    ma_sound_stop(&at->in->sound);
}

void
kon_seekTrack(kon_track_t* at, double target) {
  if (at->load)
    ma_sound_seek_to_pcm_frame(&at->in->sound, target);  
}

bool
__kon_audioInit() {
  ma_result res = ma_engine_init(NULL, &state.engine);
  if (res != MA_SUCCESS) {
    kon_errorLog(KON_LOG_TAG_MINIAUDIO, "Failed to init audio : %s", ma_result_description(res));
    return false;
  }
  return true;  
}

void
__kon_audioDeinit() {
  ma_engine_uninit(&state.engine);
}
