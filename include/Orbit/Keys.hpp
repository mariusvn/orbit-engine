/*
 * Project: Orbit Engine
 * File: Keys.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_KEYS_HPP
#define ORBITENGINE_KEYS_HPP


/* Printable keys */
#define ORBIT_KEY_SPACE              32
#define ORBIT_KEY_APOSTROPHE         39  /* ' */
#define ORBIT_KEY_COMMA              44  /* , */
#define ORBIT_KEY_MINUS              45  /* - */
#define ORBIT_KEY_PERIOD             46  /* . */
#define ORBIT_KEY_SLASH              47  /* / */
#define ORBIT_KEY_0                  48
#define ORBIT_KEY_1                  49
#define ORBIT_KEY_2                  50
#define ORBIT_KEY_3                  51
#define ORBIT_KEY_4                  52
#define ORBIT_KEY_5                  53
#define ORBIT_KEY_6                  54
#define ORBIT_KEY_7                  55
#define ORBIT_KEY_8                  56
#define ORBIT_KEY_9                  57
#define ORBIT_KEY_SEMICOLON          59  /* ; */
#define ORBIT_KEY_EQUAL              61  /* = */
#define ORBIT_KEY_A                  65
#define ORBIT_KEY_B                  66
#define ORBIT_KEY_C                  67
#define ORBIT_KEY_D                  68
#define ORBIT_KEY_E                  69
#define ORBIT_KEY_F                  70
#define ORBIT_KEY_G                  71
#define ORBIT_KEY_H                  72
#define ORBIT_KEY_I                  73
#define ORBIT_KEY_J                  74
#define ORBIT_KEY_K                  75
#define ORBIT_KEY_L                  76
#define ORBIT_KEY_M                  77
#define ORBIT_KEY_N                  78
#define ORBIT_KEY_O                  79
#define ORBIT_KEY_P                  80
#define ORBIT_KEY_Q                  81
#define ORBIT_KEY_R                  82
#define ORBIT_KEY_S                  83
#define ORBIT_KEY_T                  84
#define ORBIT_KEY_U                  85
#define ORBIT_KEY_V                  86
#define ORBIT_KEY_W                  87
#define ORBIT_KEY_X                  88
#define ORBIT_KEY_Y                  89
#define ORBIT_KEY_Z                  90
#define ORBIT_KEY_LEFT_BRACKET       91  /* [ */
#define ORBIT_KEY_BACKSLASH          92  /* \ */
#define ORBIT_KEY_RIGHT_BRACKET      93  /* ] */
#define ORBIT_KEY_GRAVE_ACCENT       96  /* ` */
#define ORBIT_KEY_WORLD_1            161 /* non-US #1 */
#define ORBIT_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define ORBIT_KEY_ESCAPE             256
#define ORBIT_KEY_ENTER              257
#define ORBIT_KEY_TAB                258
#define ORBIT_KEY_BACKSPACE          259
#define ORBIT_KEY_INSERT             260
#define ORBIT_KEY_DELETE             261
#define ORBIT_KEY_RIGHT              262
#define ORBIT_KEY_LEFT               263
#define ORBIT_KEY_DOWN               264
#define ORBIT_KEY_UP                 265
#define ORBIT_KEY_PAGE_UP            266
#define ORBIT_KEY_PAGE_DOWN          267
#define ORBIT_KEY_HOME               268
#define ORBIT_KEY_END                269
#define ORBIT_KEY_CAPS_LOCK          280
#define ORBIT_KEY_SCROLL_LOCK        281
#define ORBIT_KEY_NUM_LOCK           282
#define ORBIT_KEY_PRINT_SCREEN       283
#define ORBIT_KEY_PAUSE              284
#define ORBIT_KEY_F1                 290
#define ORBIT_KEY_F2                 291
#define ORBIT_KEY_F3                 292
#define ORBIT_KEY_F4                 293
#define ORBIT_KEY_F5                 294
#define ORBIT_KEY_F6                 295
#define ORBIT_KEY_F7                 296
#define ORBIT_KEY_F8                 297
#define ORBIT_KEY_F9                 298
#define ORBIT_KEY_F10                299
#define ORBIT_KEY_F11                300
#define ORBIT_KEY_F12                301
#define ORBIT_KEY_F13                302
#define ORBIT_KEY_F14                303
#define ORBIT_KEY_F15                304
#define ORBIT_KEY_F16                305
#define ORBIT_KEY_F17                306
#define ORBIT_KEY_F18                307
#define ORBIT_KEY_F19                308
#define ORBIT_KEY_F20                309
#define ORBIT_KEY_F21                310
#define ORBIT_KEY_F22                311
#define ORBIT_KEY_F23                312
#define ORBIT_KEY_F24                313
#define ORBIT_KEY_F25                314
#define ORBIT_KEY_KP_0               320
#define ORBIT_KEY_KP_1               321
#define ORBIT_KEY_KP_2               322
#define ORBIT_KEY_KP_3               323
#define ORBIT_KEY_KP_4               324
#define ORBIT_KEY_KP_5               325
#define ORBIT_KEY_KP_6               326
#define ORBIT_KEY_KP_7               327
#define ORBIT_KEY_KP_8               328
#define ORBIT_KEY_KP_9               329
#define ORBIT_KEY_KP_DECIMAL         330
#define ORBIT_KEY_KP_DIVIDE          331
#define ORBIT_KEY_KP_MULTIPLY        332
#define ORBIT_KEY_KP_SUBTRACT        333
#define ORBIT_KEY_KP_ADD             334
#define ORBIT_KEY_KP_ENTER           335
#define ORBIT_KEY_KP_EQUAL           336
#define ORBIT_KEY_LEFT_SHIFT         340
#define ORBIT_KEY_LEFT_CONTROL       341
#define ORBIT_KEY_LEFT_ALT           342
#define ORBIT_KEY_LEFT_SUPER         343
#define ORBIT_KEY_RIGHT_SHIFT        344
#define ORBIT_KEY_RIGHT_CONTROL      345
#define ORBIT_KEY_RIGHT_ALT          346
#define ORBIT_KEY_RIGHT_SUPER        347
#define ORBIT_KEY_MENU               348

#define ORBIT_KEY_LAST               ORBIT_KEY_MENU

#define ORBIT_MOD_SHIFT           0x0001

#define ORBIT_MOD_CONTROL         0x0002

#define ORBIT_MOD_ALT             0x0004

#define ORBIT_MOD_SUPER           0x0008

#define ORBIT_MOD_CAPS_LOCK       0x0010

#define ORBIT_MOD_NUM_LOCK        0x0020

#define ORBIT_MOUSE_BUTTON_1         0
#define ORBIT_MOUSE_BUTTON_2         1
#define ORBIT_MOUSE_BUTTON_3         2
#define ORBIT_MOUSE_BUTTON_4         3
#define ORBIT_MOUSE_BUTTON_5         4
#define ORBIT_MOUSE_BUTTON_6         5
#define ORBIT_MOUSE_BUTTON_7         6
#define ORBIT_MOUSE_BUTTON_8         7
#define ORBIT_MOUSE_BUTTON_LAST      ORBIT_MOUSE_BUTTON_8
#define ORBIT_MOUSE_BUTTON_LEFT      ORBIT_MOUSE_BUTTON_1
#define ORBIT_MOUSE_BUTTON_RIGHT     ORBIT_MOUSE_BUTTON_2
#define ORBIT_MOUSE_BUTTON_MIDDLE    ORBIT_MOUSE_BUTTON_3

#endif //ORBITENGINE_KEYS_HPP
