#include "dict.h"
#include "raylib.h"

typedef struct Assets {
  Sound word_matched;
  Wave word_matched_wav;
  Dict dict;
} Assets;

Assets *assets_get();
Assets assets_load();
void assets_free(Assets *assets);
