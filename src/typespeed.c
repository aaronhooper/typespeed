#include "assets.h"
#include "config.h"
#include "raylib.h"
#include "scene.h"
#include "util.h"

int main(void) {
  InitAudioDevice();
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
  SetTargetFPS(FRAMES_PER_SEC);
  Assets *assets = assets_get();
  scene_set(SCENE_MAIN);

  while (!WindowShouldClose()) {
    scene_update();
    BeginDrawing();
    ClearBackground(LIQUORICE);
    scene_draw();
#ifdef _DEBUG
    fps_draw();
#endif
    EndDrawing();
  }

  CloseWindow();
  CloseAudioDevice();
  scene_set(SCENE_NULL);
  assets_free(assets);

  return 0;
}
