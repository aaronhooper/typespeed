#include "assets.h"
#include "config.h"
#include "dict.h"
#include "raylib.h"

#include <string.h>

static Assets _assets = {0};
static bool _is_initialized = false;

Assets *assets_get() {
  if (!_is_initialized) {
    _assets = assets_load();
    _is_initialized = true;
  }

  return &_assets;
}

Assets assets_load() {
  Assets assets = {0};
  assets.word_matched_wav = LoadWave("assets/word_matched.wav");
  assets.word_matched = LoadSoundFromWave(assets.word_matched_wav);
  assets.dict = dict_load(WORDLIST_FILE);
  return assets;
}

void assets_free(Assets *assets) {
  UnloadSound(assets->word_matched);
  UnloadWave(assets->word_matched_wav);
  dict_free(assets->dict);
  memset(assets, 0, sizeof(Assets));
}
