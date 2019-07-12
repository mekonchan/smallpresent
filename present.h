
#include <stdio.h>
#define pf printf
#define fpf fprintf
#define u32 unsigned int           // holds 32-bit values
#define u16 unsigned short int     // holds 16-bit values
#define u8 unsigned char           // holds 8-bit values
#define s8 signed char
#define ROUNDS 1

void keySchedule(u16 *key, u16 K[], u16 keySize);

void keyScheduleInit(u16 *key, u16 K[], u16 keySize);

void encrypt(u16 K[], u16 *B);

void decrypt(u16 K[], u16 *B);

void Round(u16 *key, u16 *B);

void RoundInv(u16 *key, u16 *B);

void addRoundKey(u16 *key, u16 *X);

void addRoundKeyInv(u16 *key, u16 *X);

void sBoxlayer(u16 *X);

void sBoxlayerInv(u16 *X);

void pLayer(u16 *X);

void pLayerInv(u16 *X);

