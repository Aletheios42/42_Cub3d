#ifndef DEFINES_H
#define DEFINES_H

#define DEBUG 0

// Ventana
#define WIN_HEIGHT 720
#define WIN_WIDTH 720

// Teclas
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_W 119
#define KEY_ESC 65307
#define KEY_R 82

// Angulos
#define PI 3.14169
#define FOW PI / 6
#define HALF_FOW FOW / 2

// el ancho y el alto del bloque 
// tienen que ajustarse con
// el ancho y la altura del map
// // con el ancho y la altura de la ventana
#define BLOCK_SIZE 18
#define HALF_BLOCK_SIZE (float)BLOCK_SIZE / 2.0f


// Colores
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define PINK 0xFF69B4

#endif
