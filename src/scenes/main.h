#include "raylib.h"

typedef struct Title {
  const char *text;
  int font_size;
  int x;
  int y;
} Title;

typedef struct PlayButton {
  const char *text;
  int font_size;
  Color color;
  int x;
  int y;
} PlayButton;

typedef struct SceneMainObject {
  Title *title;
  PlayButton *play_button;
} SceneMainObject;

SceneMainObject *scene_main_create();
void scene_main_free(SceneMainObject *object);
void scene_main_update(SceneMainObject *scene);
void scene_main_draw(SceneMainObject *scene);
