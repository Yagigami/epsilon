modpersonal.cpp is where my code is

there are a few more functions than those described in the header :

(funtion macro) RAND_RANGE(type, a, b) (which i don't use for now)

(static function) yasmarang(void) (which i copied from /python/src/extmod/modurandom.c since there does'nt seem to be any built-in random function)

(static funciton) seed(s) (which just sets the seed for yasmarang(void))

(static funciton) clearScreen(void)

(personal module function) modpersonal_hello_world(void) (which contains the sprite drawing little "game":
    controls:
    OnOff to stop
    Left/Right/Up/Down for img_sample to go in the respective direction
    4/6/8/2 for anim_sample to go in the respective direction)

(static function) toggleKeyCheck(key, flag, keys, toggles) (may be a bad way implementing what it is)

(function) normalizedToScreen(normalized) (converts normalized screen coordinates from [-.5;.5] left-to-right x [-.5;.5] down-to-up to actual screen coordinates [0;320]x[222;0])

(modpersonal module function) modpersonal_mesh(void) (whihc contains the rotating cube "game":
    controls:
    onOff to stop;
    0 to stop the cube from rotating
    . to not draw Edges
    4/6/8/2 to move the camera in the respective direction
    9/7 to respectively zoom/unzoom
    Left/Right/Up/Down to rotate the camera around the cube)
