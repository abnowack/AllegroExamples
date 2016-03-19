cmake_minimum_required(VERSION 3.4)
project(AllegroExamples C)

include_directories("C:/msys64/home/Aaron/.local/include")
link_directories("C:/msys64/home/Aaron/.local/lib")

add_executable(SimpleDisplay simple_display.c)
target_link_libraries(SimpleDisplay allegro)

add_executable(SimpleEvent simple_event.c)
target_link_libraries(SimpleEvent allegro)

add_executable(SimpleTimer simple_timer.c)
target_link_libraries(SimpleTimer allegro)

add_executable(SimpleBitmap simple_bitmap.c)
target_link_libraries(SimpleBitmap allegro)

add_executable(SimpleImage simple_image.c)
target_link_libraries(SimpleImage allegro allegro_image)

add_executable(SimpleMouse simple_mouse.c)
target_link_libraries(SimpleMouse allegro)

add_executable(SimpleKeyboard simple_keyboard.c)
target_link_libraries(SimpleKeyboard allegro)

add_executable(SimpleFont simple_font.c)
target_link_libraries(SimpleFont allegro allegro_font allegro_ttf)

add_executable(SimpleSprite sprite_engine/simple_sprite.c)
target_link_libraries(SimpleSprite allegro allegro_image)

add_executable(TilesetDisplay tileset_display.c)
target_link_libraries(TilesetDisplay allegro allegro_image)

file(COPY share DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY sprite_engine/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})