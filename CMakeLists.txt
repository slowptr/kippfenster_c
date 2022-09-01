cmake_minimum_required(VERSION 3.21)
project (kippfenster_c C)

set(CMAKE_C_STANDARD 99)
add_executable(kippfenster_c WIN32 src/main.c src/kf_wnd.h src/kf_wnd.c src/kf_wnd_ctrls.h src/kf_wnd_ctrls.c src/kf_utils.h src/kf_utils.c src/examples/example_window.h src/examples/example_window.c)
