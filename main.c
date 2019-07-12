#include <time.h>

#include <math.h>

#include <stdlib.h>

#include "present.h"

#include "rngs.h"

#define MAXRANDOM 2147483647

u32 value;

void initialTest();
void testingKeyDifference();
void compareCipherFirstKeyOnly();
void compareCipherNew();
void compareCipherKeySame();
void formula();

unsigned short int x[100000];
unsigned long elements = sizeof(x) / sizeof( * x);

int main() {

  //	initialTest();
  //    testingKeyDifference();
  //    compareCipherFirstKeyOnly();
  //    compareCipherNew();
  //    compareCipherKeySame();
  formula();

  return 0;
}

void initialTest() {
  u16 key[5] = {
    0x1,
    0x2,
    0x3,
    0x4,
    0x5
  };

  u16 p[4] = {
    0x1,
    0x2,
    0x3,
    0x4
  };

  u32 i;
  u8 j;
  u16 keySize;
  u16 K[ROUNDS + 1] = {
    0x0
  };
  //  u32 ITERATION;
  //  clock_t t1;

  keySize = 80;
  keySchedule(key, K, keySize);

  pf("K: ");
  for (i = 0; i < keySize / 16; i++) {
    pf("%X ", key[i]);
  }
  pf("\n");
  pf("P: %X%X%X%X \n", p[0], p[1], p[2], p[3]);
  encrypt(K, p);
  pf("C: %X%X%X%X \n", p[0], p[1], p[2], p[3]);
  decrypt(K, p);
  pf("P: %X%X%X%X \n", p[0], p[1], p[2], p[3]);
  //
  //  // test sBoxLayer
  //  p[0] = p[1] = p[2] = p[3];
  //  sBoxlayer(p);
  //  pf("sbox: %X%X%X%X\n", p[0], p[1], p[2], p[3]);
  //
  //  // test pLayer
  //  p[0] = p[1] = p[2] = p[3] = 0x4444;
  //  pLayer(p);
  //  pf("pLayer: %X%X%X%X\n", p[0], p[1], p[2], p[3]);
  //
  //  /*
  //   * Random number initialization for random test vectors testing
  //   */
  //  SelectStream(0);
  //  PlantSeeds(-1);
  //
  //  t1 = clock();
  //  ITERATION = 0;
  //  pf("Performing %d test vectors... ", ITERATION);
  //  for (i = 0; i < ITERATION; i++) {
  //    for (j = 0; j < 4; j++) {
  //      p[j] = MAXRANDOM * Random();
  //      key[j] = MAXRANDOM * Random();
  //    }
  //    key[j] = MAXRANDOM * Random();
  //
  //    keySchedule(key, K, keySize);
  //    for (j = 0; j < 4; j++) {
  //      c[j] = p[j];
  //    }
  //    //pf("P: %04X %04X %04X %04X\n", p[0], p[1], p[2], p[3]);
  //    encrypt(K, c);
  //    //pf("C: %04X %04X %04X %04X\n", c[0], c[1], c[2], c[3]);
  //    decrypt(K, c);
  //
  //    if ((c[0] != p[0]) | (c[1] != p[1]) | (c[2] != p[2]) | (c[3] != p[3])) {
  //      pf("haha %d ", i);
  //    }
  //  }
  //  pf("Done! \n");
  //  pf("\n[%f seconds]\n", (clock() - t1) / (double) CLOCKS_PER_SEC);
  //
  //  //system("PAUSE");

}

void testingKeyDifference() {
  u16 key1[8] = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0
  };
  u16 key2[8] = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0,
    0x0
  };
  u32 i, j;
  u16 keySize;
  u16 K1[ROUNDS + 1];
  u16 K2[ROUNDS + 1];
  u16 store[100];

  keySize = 128;
  keySchedule(key1, K1, keySize);
  keySchedule(key2, K2, keySize);
  pf("\n");

  for (i = 0; i < ROUNDS + 1; i++) {
    if ((K1[i] ^ K2[i]) == 0)
      pf(".... ");
    else
      pf("%04X ", K1[i] ^ K2[i]);

    pf("\n");
  }

}

void compareCipherKeySame() {

  u16 n_choose_2[40] = {
    0,
    0,
    1,
    3,
    6,
    10,
    15,
    21,
    28,
    36,
    45,
    55,
    66,
    78,
    91,
    105,
    120,
    136,
    153,
    171,
    190,
    210,
    231,
    253,
    276,
    300,
    325,
    351,
    378,
    406,
    435,
    465,
    496,
    528,
    561,
    595,
    630,
    666,
    703,
    741
  };

  u16 key[5] = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x0
  };

  u16 p[4];
  u16 keySize;
  u16 K[ROUNDS + 1];
  u16 store[200];
  u16 same;
  u32 counter = 1;
  u32 counterCollide = 0;
  u32 total_plaintext = 0;
  u32 total_counter = 0;
  u32 total_comb = 0;

  keySize = 80;
  u16 plaintext[1] = {
    0x0
  };
  u16 keytest = {
    0x0
  };

  for (int m = 0; m < 65536; m++) {
    x[m] = plaintext[0];
    pf("", x[m]);
    for (int j = 0; j < 65536; j++) {
      //      key[3] = (keytest & 0xf) ;
      //      key[2] = ((keytest & 0xf0) >> 4);
      //      key[1] = ((keytest & 0xf00) >> 8);
      //      key[0] = ((keytest & 0xf000) >> 12);
      u16 fix = keytest;
      //      pf("fix -% 04X\n",fix);
      //      pf("key - %X %X %X %X %X\n",key[0],key[1],key[2],key[3],key[4]);
      p[0] = (x[m] & 0xF000) >> 12;
      p[1] = (x[m] & 0x0F00) >> 8;
      p[2] = (x[m] & 0x00F0) >> 4;
      p[3] = (x[m] & 0x000F);

      for (int k = 0; k <= ROUNDS; k++) {
        K[k] = fix;
        //          pf("%04X\n",K[k]);
      }

      //      keySchedule(key, K, keySize);
      encrypt(K, p);

      store[0] = ((p[0] << 12) | (p[1] << 8) | (p[2] << 4) | p[3]);
      //            pf("store[0] - %04X\n",store[0]);
      if (j == 0) {
        same = store[0];
      } else if (store[0] == same && j != 0) {
        pf("%04X :: ", keytest);
        for (int i = 0; i <= ROUNDS; i++) {
          pf("%04X ", K[i]);
        }
        pf("\n");
        counter++;
        counterCollide++;
      }
      keytest++;
    }
    plaintext[0]++;
    total_comb += n_choose_2[counter];
    if (counter > 1) {
      total_plaintext++;
      pf("P = %04X  ", x[m]);
      pf("C1 = %04X\n", same);
      pf("Counter = %d\n", counter);
      total_counter += counter;
      pf("\n");
    }
    counter = 1;
  }
  pf("DONE!\n");

  pf("\nTotal number of keys: ");
  pf("%d\n", total_counter);
  pf("\nTotal number of plaintexts: ");
  pf("%d\n", total_plaintext);
  pf("\nAverage number keys per plaintext that yield collision: ");
  pf("%f\n", total_counter * 1.0 / total_plaintext * 1.0);
  pf("\nNumber of colliding pairs: ");
  pf("%d\n", total_comb);

}

void compareCipherFirstKeyOnly() {

  u16 n_choose_2[40] = {
    0,
    0,
    1,
    3,
    6,
    10,
    15,
    21,
    28,
    36,
    45,
    55,
    66,
    78,
    91,
    105,
    120,
    136,
    153,
    171,
    190,
    210,
    231,
    253,
    276,
    300,
    325,
    351,
    378,
    406,
    435,
    465,
    496,
    528,
    561,
    595,
    630,
    666,
    703,
    741
  };

  u16 key[5] = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x0
  };

  u16 p[4];
  u16 keySize;
  u16 K[ROUNDS + 1];
  u16 store[200];
  u16 same;
  u32 counter = 1;
  u32 counterCollide = 0;
  u32 total_plaintext = 0;
  u32 total_counter = 0;
  u32 total_comb = 0;

  keySize = 80;
  u16 plaintext[1] = {
    0x0
  };
  u16 keytest = {
    0x0
  };

  for (int m = 0; m < 65536; m++) {
    x[m] = plaintext[0];
    pf("%04X\n", x[m]);
    for (int j = 0; j < 65536; j++) {
      //      key[3] = (keytest & 0xf) ;
      //      key[2] = ((keytest & 0xf0) >> 4);
      //      key[1] = ((keytest & 0xf00) >> 8);
      //      key[0] = ((keytest & 0xf000) >> 12);
      u16 fix = keytest;
      //      pf("fix -% 04X\n",fix);
      //      pf("key - %X %X %X %X %X\n",key[0],key[1],key[2],key[3],key[4]);
      p[0] = (x[m] & 0xF000) >> 12;
      p[1] = (x[m] & 0x0F00) >> 8;
      p[2] = (x[m] & 0x00F0) >> 4;
      p[3] = (x[m] & 0x000F);

      K[0] = fix;

      //      keySchedule(key, K, keySize);
      encrypt(K, p);

      store[0] = ((p[0] << 12) | (p[1] << 8) | (p[2] << 4) | p[3]);
      //            pf("store[0] - %04X\n",store[0]);
      if (j == 0) {
        same = store[0];
      } else if (store[0] == same && j != 0) {
        pf("%04X :: ", keytest);
        for (int i = 0; i <= ROUNDS; i++) {
          pf("%04X ", K[i]);
        }
        pf("\n");
        counter++;
        counterCollide++;
      }
      keytest++;
    }
    plaintext[0]++;
    total_comb += n_choose_2[counter];
    if (counter > 1) {
      total_plaintext++;
      pf("P = %04X  ", x[m]);
      pf("C1 = %04X\n", same);
      pf("Counter = %d\n", counter);
      total_counter += counter;
      pf("\n");
    }
    counter = 1;
  }
  pf("DONE!\n");

  pf("\nTotal number of keys: ");
  pf("%d\n", total_counter);
  pf("\nTotal number of plaintexts: ");
  pf("%d\n", total_plaintext);
  pf("\nAverage number keys per plaintext that yield collision: ");
  pf("%f\n", total_counter * 1.0 / total_plaintext * 1.0);
  pf("\nNumber of colliding pairs: ");
  pf("%d\n", total_comb);

}

void compareCipherNew() {

  u16 n_choose_2[40] = {
    0,
    0,
    1,
    3,
    6,
    10,
    15,
    21,
    28,
    36,
    45,
    55,
    66,
    78,
    91,
    105,
    120,
    136,
    153,
    171,
    190,
    210,
    231,
    253,
    276,
    300,
    325,
    351,
    378,
    406,
    435,
    465,
    496,
    528,
    561,
    595,
    630,
    666,
    703,
    741
  };

  u16 key[5] = {
    0x0,
    0x0,
    0x0,
    0x0,
    0x0
  };
  u16 p[4];
  u16 keySize;
  u16 K[ROUNDS + 1];
  u16 store[200];
  u16 same;
  u32 counter = 1;
  u32 counterCollide = 0;
  u32 total_plaintext = 0;
  u32 total_counter = 0;
  u32 total_comb = 0;

  keySize = 80;
  u16 plaintext[1] = {
    0x0
  };

  u16 keytest = {
    0x0
  };

  for (int m = 0; m < 65536; m++) {
    x[m] = plaintext[0];
    pf("", x[m]);
    for (int j = 0; j < 65536; j++) {
      key[3] = keytest & 0xf;
      key[2] = ((keytest & 0xf0) >> 4);
      key[1] = ((keytest & 0xf00) >> 8);
      key[0] = ((keytest & 0xf000) >> 12);
      //      pf("km - %X %X %X %X %X\n", key[0], key[1], key[2], key[3], key[4]);
      p[0] = (x[m] & 0xF000) >> 12;
      p[1] = (x[m] & 0x0F00) >> 8;
      p[2] = (x[m] & 0x00F0) >> 4;
      p[3] = (x[m] & 0x000F);

      keySchedule(key, K, keySize);
      //      for(int r=0;r <= ROUNDS; r++){
      //          pf("K0 - %04X\n", K[0]);
      //          pf("K1 - %04X\n", K[1]);
      //          pf("K2 - %04X\n", K[2]);
      //      }

      encrypt(K, p);

      store[0] = ((p[0] << 12) | (p[1] << 8) | (p[2] << 4) | p[3]);

      if (j == 0) {
        same = store[0];
      }

      if (same == store[0] && j != 0) {
        pf("%04X :: ", keytest);
        for (int i = 0; i <= ROUNDS; i++) {
          pf("%04X ", K[i]);
        }
        pf("\n");
        counter++;
        counterCollide++;
      }
      keytest++;
    }
    plaintext[0]++;
    total_comb += n_choose_2[counter];
    if (counter > 1) {
      total_plaintext++;
      pf("P = %04X  ", x[m]);
      pf("C1 = %04X\n", same);
      pf("Counter = %d\n", counter);
      total_counter += counter;
      pf("\n");
    }
    counter = 1;
  }
  pf("DONE!\n");

  pf("\nTotal number of keys: ");
  pf("%d\n", total_counter);
  pf("\nTotal number of plaintexts: ");
  pf("%d\n", total_plaintext);
  pf("\nAverage number keys per plaintext that yield collision: ");
  pf("%f\n", total_counter * 1.0 / total_plaintext * 1.0);
  pf("\nNumber of colliding pairs: ");
  pf("%d\n", total_comb);

}

void formula() {

  u16 U[16];
  u16 C[16];
  u16 Km[20];

  printf("Enter Plaintext in hexadecimal (4 bit) \n");
  do {
    scanf("%x", & value);
    if (value < 65536) {
      break;
    }
  }
  while (1);

  u16 v0 = (value & 0xf000) >> 12;
  u16 v1 = (value & 0x0f00) >> 8;
  u16 v2 = (value & 0x00f0) >> 4;
  u16 v3 = (value & 0x000f);

  printf("Enter KeyMaster in hexadecimal (5 bit) \n");
  do {
    scanf("%x", & value);
    if (value < 1048576) {
      break;
    }
  }
  while (1);

  u16 m0 = (value & 0xf0000) >> 16;
  u16 m1 = (value & 0x0f000) >> 12;
  u16 m2 = (value & 0x00f00) >> 8;
  u16 m3 = (value & 0x000f0) >> 4;
  u16 m4 = (value & 0x0000f);

  if (v0 == 0x0000) {
    U[15] = 0x0;
    U[14] = 0x0;
    U[13] = 0x0;
    U[12] = 0x0;
  } else if (v0 == 0x0001) {
    U[15] = 0x0;
    U[14] = 0x0;
    U[13] = 0x0;
    U[12] = 0x1;
  } else if (v0 == 0x0002) {
    U[15] = 0x0;
    U[14] = 0x0;
    U[13] = 0x1;
    U[12] = 0x0;
  } else if (v0 == 0x0003) {
    U[15] = 0x0;
    U[14] = 0x0;
    U[13] = 0x1;
    U[12] = 0x1;
  } else if (v0 == 0x0004) {
    U[15] = 0x0;
    U[14] = 0x1;
    U[13] = 0x0;
    U[12] = 0x0;
  } else if (v0 == 0x0005) {
    U[15] = 0x0;
    U[14] = 0x1;
    U[13] = 0x0;
    U[12] = 0x1;
  } else if (v0 == 0x0006) {
    U[15] = 0x0;
    U[14] = 0x1;
    U[13] = 0x1;
    U[12] = 0x0;
  } else if (v0 == 0x0007) {
    U[15] = 0x0;
    U[14] = 0x1;
    U[13] = 0x1;
    U[12] = 0x1;
  } else if (v0 == 0x0008) {
    U[15] = 0x1;
    U[14] = 0x0;
    U[13] = 0x0;
    U[12] = 0x0;
  } else if (v0 == 0x0009) {
    U[15] = 0x1;
    U[14] = 0x0;
    U[13] = 0x0;
    U[12] = 0x1;
  } else if (v0 == 0x000A) {
    U[15] = 0x1;
    U[14] = 0x0;
    U[13] = 0x1;
    U[12] = 0x0;
  } else if (v0 == 0x000B) {
    U[15] = 0x1;
    U[14] = 0x0;
    U[13] = 0x1;
    U[12] = 0x1;
  } else if (v0 == 0x000C) {
    U[15] = 0x1;
    U[14] = 0x1;
    U[13] = 0x0;
    U[12] = 0x0;
  } else if (v0 == 0x000D) {
    U[15] = 0x1;
    U[14] = 0x1;
    U[13] = 0x0;
    U[12] = 0x1;
  } else if (v0 == 0x000E) {
    U[15] = 0x1;
    U[14] = 0x1;
    U[13] = 0x1;
    U[12] = 0x0;
  } else if (v0 == 0x000F) {
    U[15] = 0x1;
    U[14] = 0x1;
    U[13] = 0x1;
    U[12] = 0x1;
  }
  ////////////////////////////////
  if (v1 == 0x0000) {
    U[11] = 0x0;
    U[10] = 0x0;
    U[9] = 0x0;
    U[8] = 0x0;
  } else if (v1 == 0x0001) {
    U[11] = 0x0;
    U[10] = 0x0;
    U[9] = 0x0;
    U[8] = 0x1;
  } else if (v1 == 0x0002) {
    U[11] = 0x0;
    U[10] = 0x0;
    U[9] = 0x1;
    U[8] = 0x0;
  } else if (v1 == 0x0003) {
    U[11] = 0x0;
    U[10] = 0x0;
    U[9] = 0x1;
    U[8] = 0x1;
  } else if (v1 == 0x0004) {
    U[11] = 0x0;
    U[10] = 0x1;
    U[9] = 0x0;
    U[8] = 0x0;
  } else if (v1 == 0x0005) {
    U[11] = 0x0;
    U[10] = 0x1;
    U[9] = 0x0;
    U[8] = 0x1;
  } else if (v1 == 0x0006) {
    U[11] = 0x0;
    U[10] = 0x1;
    U[9] = 0x1;
    U[8] = 0x0;
  } else if (v1 == 0x0007) {
    U[11] = 0x0;
    U[10] = 0x1;
    U[9] = 0x1;
    U[8] = 0x1;
  } else if (v1 == 0x0008) {
    U[11] = 0x1;
    U[10] = 0x0;
    U[9] = 0x0;
    U[8] = 0x0;
  } else if (v1 == 0x0009) {
    U[11] = 0x1;
    U[10] = 0x0;
    U[9] = 0x0;
    U[8] = 0x1;
  } else if (v1 == 0x000A) {
    U[11] = 0x1;
    U[10] = 0x0;
    U[9] = 0x1;
    U[8] = 0x0;
  } else if (v1 == 0x000B) {
    U[11] = 0x1;
    U[10] = 0x0;
    U[9] = 0x1;
    U[8] = 0x1;
  } else if (v1 == 0x000C) {
    U[11] = 0x1;
    U[10] = 0x1;
    U[9] = 0x0;
    U[8] = 0x0;
  } else if (v1 == 0x000D) {
    U[11] = 0x1;
    U[10] = 0x1;
    U[9] = 0x0;
    U[8] = 0x1;
  } else if (v1 == 0x000E) {
    U[11] = 0x1;
    U[10] = 0x1;
    U[9] = 0x1;
    U[8] = 0x0;
  } else if (v1 == 0x000F) {
    U[11] = 0x1;
    U[10] = 0x1;
    U[9] = 0x1;
    U[8] = 0x1;
  }
  /////////////
  if (v2 == 0x0000) {
    U[7] = 0x0;
    U[6] = 0x0;
    U[5] = 0x0;
    U[4] = 0x0;
  } else if (v2 == 0x0001) {
    U[7] = 0x0;
    U[6] = 0x0;
    U[5] = 0x0;
    U[4] = 0x1;
  } else if (v2 == 0x0002) {
    U[7] = 0x0;
    U[6] = 0x0;
    U[5] = 0x1;
    U[4] = 0x0;
  } else if (v2 == 0x0003) {
    U[7] = 0x0;
    U[6] = 0x0;
    U[5] = 0x1;
    U[4] = 0x1;
  } else if (v2 == 0x0004) {
    U[7] = 0x0;
    U[6] = 0x1;
    U[5] = 0x0;
    U[4] = 0x0;
  } else if (v2 == 0x0005) {
    U[7] = 0x0;
    U[6] = 0x1;
    U[5] = 0x0;
    U[4] = 0x1;
  } else if (v2 == 0x0006) {
    U[7] = 0x0;
    U[6] = 0x1;
    U[5] = 0x1;
    U[4] = 0x0;
  } else if (v2 == 0x0007) {
    U[7] = 0x0;
    U[6] = 0x1;
    U[5] = 0x1;
    U[4] = 0x1;
  } else if (v2 == 0x0008) {
    U[7] = 0x1;
    U[6] = 0x0;
    U[5] = 0x0;
    U[4] = 0x0;
  } else if (v2 == 0x0009) {
    U[7] = 0x1;
    U[6] = 0x0;
    U[5] = 0x0;
    U[4] = 0x1;
  } else if (v2 == 0x000A) {
    U[7] = 0x1;
    U[6] = 0x0;
    U[5] = 0x1;
    U[4] = 0x0;
  } else if (v2 == 0x000B) {
    U[7] = 0x1;
    U[6] = 0x0;
    U[5] = 0x1;
    U[4] = 0x1;
  } else if (v2 == 0x000C) {
    U[7] = 0x1;
    U[6] = 0x1;
    U[5] = 0x0;
    U[4] = 0x0;
  } else if (v2 == 0x000D) {
    U[7] = 0x1;
    U[6] = 0x1;
    U[5] = 0x0;
    U[4] = 0x1;
  } else if (v2 == 0x000E) {
    U[7] = 0x1;
    U[6] = 0x1;
    U[5] = 0x1;
    U[4] = 0x0;
  } else if (v2 == 0x000F) {
    U[7] = 0x1;
    U[6] = 0x1;
    U[5] = 0x1;
    U[4] = 0x1;
  }
  /////////
  if (v3 == 0x0000) {
    U[3] = 0x0;
    U[2] = 0x0;
    U[1] = 0x0;
    U[0] = 0x0;
  } else if (v3 == 0x0001) {
    U[3] = 0x0;
    U[2] = 0x0;
    U[1] = 0x0;
    U[0] = 0x1;
  } else if (v3 == 0x0002) {
    U[3] = 0x0;
    U[2] = 0x0;
    U[1] = 0x1;
    U[0] = 0x0;
  } else if (v3 == 0x0003) {
    U[3] = 0x0;
    U[2] = 0x0;
    U[1] = 0x1;
    U[0] = 0x1;
  } else if (v3 == 0x0004) {
    U[3] = 0x0;
    U[2] = 0x1;
    U[1] = 0x0;
    U[0] = 0x0;
  } else if (v3 == 0x0005) {
    U[3] = 0x0;
    U[2] = 0x1;
    U[1] = 0x0;
    U[0] = 0x1;
  } else if (v3 == 0x0006) {
    U[3] = 0x0;
    U[2] = 0x1;
    U[1] = 0x1;
    U[0] = 0x0;
  } else if (v3 == 0x0007) {
    U[3] = 0x0;
    U[2] = 0x1;
    U[1] = 0x1;
    U[0] = 0x1;
  } else if (v3 == 0x0008) {
    U[3] = 0x1;
    U[2] = 0x0;
    U[1] = 0x0;
    U[0] = 0x0;
  } else if (v3 == 0x0009) {
    U[3] = 0x1;
    U[2] = 0x0;
    U[1] = 0x0;
    U[0] = 0x1;
  } else if (v3 == 0x000A) {
    U[3] = 0x1;
    U[2] = 0x0;
    U[1] = 0x1;
    U[0] = 0x0;
  } else if (v3 == 0x000B) {
    U[3] = 0x1;
    U[2] = 0x0;
    U[1] = 0x1;
    U[0] = 0x1;
  } else if (v3 == 0x000C) {
    U[3] = 0x1;
    U[2] = 0x1;
    U[1] = 0x0;
    U[0] = 0x0;
  } else if (v3 == 0x000D) {
    U[3] = 0x1;
    U[2] = 0x1;
    U[1] = 0x0;
    U[0] = 0x1;
  } else if (v3 == 0x000E) {
    U[3] = 0x1;
    U[2] = 0x1;
    U[1] = 0x1;
    U[0] = 0x0;
  } else if (v3 == 0x000F) {
    U[3] = 0x1;
    U[2] = 0x1;
    U[1] = 0x1;
    U[0] = 0x1;
  }

  /////////////////////////

  if (m0 == 0x0000) {
    Km[19] = 0x0;
    Km[18] = 0x0;
    Km[17] = 0x0;
    Km[16] = 0x0;
  } else if (m0 == 0x0001) {
    Km[19] = 0x0;
    Km[18] = 0x0;
    Km[17] = 0x0;
    Km[16] = 0x1;
  } else if (m0 == 0x0002) {
    Km[19] = 0x0;
    Km[18] = 0x0;
    Km[17] = 0x1;
    Km[16] = 0x0;
  } else if (m0 == 0x0003) {
    Km[19] = 0x0;
    Km[18] = 0x0;
    Km[17] = 0x1;
    Km[16] = 0x1;
  } else if (m0 == 0x0004) {
    Km[19] = 0x0;
    Km[18] = 0x1;
    Km[17] = 0x0;
    Km[16] = 0x0;
  } else if (m0 == 0x0005) {
    Km[19] = 0x0;
    Km[18] = 0x1;
    Km[17] = 0x0;
    Km[16] = 0x1;
  } else if (m0 == 0x0006) {
    Km[19] = 0x0;
    Km[18] = 0x1;
    Km[17] = 0x1;
    Km[16] = 0x0;
  } else if (m0 == 0x0007) {
    Km[19] = 0x0;
    Km[18] = 0x1;
    Km[17] = 0x1;
    Km[16] = 0x1;
  } else if (m0 == 0x0008) {
    Km[19] = 0x1;
    Km[18] = 0x0;
    Km[17] = 0x0;
    Km[16] = 0x0;
  } else if (m0 == 0x0009) {
    Km[19] = 0x1;
    Km[18] = 0x0;
    Km[17] = 0x0;
    Km[16] = 0x1;
  } else if (m0 == 0x000A) {
    Km[19] = 0x1;
    Km[18] = 0x0;
    Km[17] = 0x1;
    Km[16] = 0x0;
  } else if (m0 == 0x000B) {
    Km[19] = 0x1;
    Km[18] = 0x0;
    Km[17] = 0x1;
    Km[16] = 0x1;
  } else if (m0 == 0x000C) {
    Km[19] = 0x1;
    Km[18] = 0x1;
    Km[17] = 0x0;
    Km[16] = 0x0;
  } else if (m0 == 0x000D) {
    Km[19] = 0x1;
    Km[18] = 0x1;
    Km[17] = 0x0;
    Km[16] = 0x1;
  } else if (m0 == 0x000E) {
    Km[19] = 0x1;
    Km[18] = 0x1;
    Km[17] = 0x1;
    Km[16] = 0x0;
  } else if (m0 == 0x000F) {
    Km[19] = 0x1;
    Km[18] = 0x1;
    Km[17] = 0x1;
    Km[16] = 0x1;
  }
  ////////////////////////////////
  if (m1 == 0x0000) {
    Km[15] = 0x0;
    Km[14] = 0x0;
    Km[13] = 0x0;
    Km[12] = 0x0;
  } else if (m1 == 0x0001) {
    Km[15] = 0x0;
    Km[14] = 0x0;
    Km[13] = 0x0;
    Km[12] = 0x1;
  } else if (m1 == 0x0002) {
    Km[15] = 0x0;
    Km[14] = 0x0;
    Km[13] = 0x1;
    Km[12] = 0x0;
  } else if (m1 == 0x0003) {
    Km[15] = 0x0;
    Km[14] = 0x0;
    Km[13] = 0x1;
    Km[12] = 0x1;
  } else if (m1 == 0x0004) {
    Km[15] = 0x0;
    Km[14] = 0x1;
    Km[13] = 0x0;
    Km[12] = 0x0;
  } else if (m1 == 0x0005) {
    Km[15] = 0x0;
    Km[14] = 0x1;
    Km[13] = 0x0;
    Km[12] = 0x1;
  } else if (m1 == 0x0006) {
    Km[15] = 0x0;
    Km[14] = 0x1;
    Km[13] = 0x1;
    Km[12] = 0x0;
  } else if (m1 == 0x0007) {
    Km[15] = 0x0;
    Km[14] = 0x1;
    Km[13] = 0x1;
    Km[12] = 0x1;
  } else if (m1 == 0x0008) {
    Km[15] = 0x1;
    Km[14] = 0x0;
    Km[13] = 0x0;
    Km[12] = 0x0;
  } else if (m1 == 0x0009) {
    Km[15] = 0x1;
    Km[14] = 0x0;
    Km[13] = 0x0;
    Km[12] = 0x1;
  } else if (m1 == 0x000A) {
    Km[15] = 0x1;
    Km[14] = 0x0;
    Km[13] = 0x1;
    Km[12] = 0x0;
  } else if (m1 == 0x000B) {
    Km[15] = 0x1;
    Km[14] = 0x0;
    Km[13] = 0x1;
    Km[12] = 0x1;
  } else if (m1 == 0x000C) {
    Km[15] = 0x1;
    Km[14] = 0x1;
    Km[13] = 0x0;
    Km[12] = 0x0;
  } else if (m1 == 0x000D) {
    Km[15] = 0x1;
    Km[14] = 0x1;
    Km[13] = 0x0;
    Km[12] = 0x1;
  } else if (m1 == 0x000E) {
    Km[15] = 0x1;
    Km[14] = 0x1;
    Km[13] = 0x1;
    Km[12] = 0x0;
  } else if (m1 == 0x000F) {
    Km[15] = 0x1;
    Km[14] = 0x1;
    Km[13] = 0x1;
    Km[12] = 0x1;
  }
  /////////////
  if (m2 == 0x0000) {
    Km[11] = 0x0;
    Km[10] = 0x0;
    Km[9] = 0x0;
    Km[8] = 0x0;
  } else if (m2 == 0x0001) {
    Km[11] = 0x0;
    Km[10] = 0x0;
    Km[9] = 0x0;
    Km[8] = 0x1;
  } else if (m2 == 0x0002) {
    Km[11] = 0x0;
    Km[10] = 0x0;
    Km[9] = 0x1;
    Km[8] = 0x0;
  } else if (m2 == 0x0003) {
    Km[11] = 0x0;
    Km[10] = 0x0;
    Km[9] = 0x1;
    Km[8] = 0x1;
  } else if (m2 == 0x0004) {
    Km[11] = 0x0;
    Km[10] = 0x1;
    Km[9] = 0x0;
    Km[8] = 0x0;
  } else if (m2 == 0x0005) {
    Km[11] = 0x0;
    Km[10] = 0x1;
    Km[9] = 0x0;
    Km[8] = 0x1;
  } else if (m2 == 0x0006) {
    Km[11] = 0x0;
    Km[10] = 0x1;
    Km[9] = 0x1;
    Km[8] = 0x0;
  } else if (m2 == 0x0007) {
    Km[11] = 0x0;
    Km[10] = 0x1;
    Km[9] = 0x1;
    Km[8] = 0x1;
  } else if (m2 == 0x0008) {
    Km[11] = 0x1;
    Km[10] = 0x0;
    Km[9] = 0x0;
    Km[8] = 0x0;
  } else if (m2 == 0x0009) {
    Km[11] = 0x1;
    Km[10] = 0x0;
    Km[9] = 0x0;
    Km[8] = 0x1;
  } else if (m2 == 0x000A) {
    Km[11] = 0x1;
    Km[10] = 0x0;
    Km[9] = 0x1;
    Km[8] = 0x0;
  } else if (m2 == 0x000B) {
    Km[11] = 0x1;
    Km[10] = 0x0;
    Km[9] = 0x1;
    Km[8] = 0x1;
  } else if (m2 == 0x000C) {
    Km[11] = 0x1;
    Km[10] = 0x1;
    Km[9] = 0x0;
    Km[8] = 0x0;
  } else if (m2 == 0x000D) {
    Km[11] = 0x1;
    Km[10] = 0x1;
    Km[9] = 0x0;
    Km[8] = 0x1;
  } else if (m2 == 0x000E) {
    Km[11] = 0x1;
    Km[10] = 0x1;
    Km[9] = 0x1;
    Km[8] = 0x0;
  } else if (m2 == 0x000F) {
    Km[11] = 0x1;
    Km[10] = 0x1;
    Km[9] = 0x1;
    Km[8] = 0x1;
  }
  /////////
  if (m3 == 0x0000) {
    Km[7] = 0x0;
    Km[6] = 0x0;
    Km[5] = 0x0;
    Km[4] = 0x0;
  } else if (m3 == 0x0001) {
    Km[7] = 0x0;
    Km[6] = 0x0;
    Km[5] = 0x0;
    Km[4] = 0x1;
  } else if (m3 == 0x0002) {
    Km[7] = 0x0;
    Km[6] = 0x0;
    Km[5] = 0x1;
    Km[4] = 0x0;
  } else if (m3 == 0x0003) {
    Km[7] = 0x0;
    Km[6] = 0x0;
    Km[5] = 0x1;
    Km[4] = 0x1;
  } else if (m3 == 0x0004) {
    Km[7] = 0x0;
    Km[6] = 0x1;
    Km[5] = 0x0;
    Km[4] = 0x0;
  } else if (m3 == 0x0005) {
    Km[7] = 0x0;
    Km[6] = 0x1;
    Km[5] = 0x0;
    Km[4] = 0x1;
  } else if (m3 == 0x0006) {
    Km[7] = 0x0;
    Km[6] = 0x1;
    Km[5] = 0x1;
    Km[4] = 0x0;
  } else if (m3 == 0x0007) {
    Km[7] = 0x0;
    Km[6] = 0x1;
    Km[5] = 0x1;
    Km[4] = 0x1;
  } else if (m3 == 0x0008) {
    Km[7] = 0x1;
    Km[6] = 0x0;
    Km[5] = 0x0;
    Km[4] = 0x0;
  } else if (m3 == 0x0009) {
    Km[7] = 0x1;
    Km[6] = 0x0;
    Km[5] = 0x0;
    Km[4] = 0x1;
  } else if (m3 == 0x000A) {
    Km[7] = 0x1;
    Km[6] = 0x0;
    Km[5] = 0x1;
    Km[4] = 0x0;
  } else if (m3 == 0x000B) {
    Km[7] = 0x1;
    Km[6] = 0x0;
    Km[5] = 0x1;
    Km[4] = 0x1;
  } else if (m3 == 0x000C) {
    Km[7] = 0x1;
    Km[6] = 0x1;
    Km[5] = 0x0;
    Km[4] = 0x0;
  } else if (m3 == 0x000D) {
    Km[7] = 0x1;
    Km[6] = 0x1;
    Km[5] = 0x0;
    Km[4] = 0x1;
  } else if (m3 == 0x000E) {
    Km[7] = 0x1;
    Km[6] = 0x1;
    Km[5] = 0x1;
    Km[4] = 0x0;
  } else if (m3 == 0x000F) {
    Km[7] = 0x1;
    Km[6] = 0x1;
    Km[5] = 0x1;
    Km[4] = 0x1;
  }
  //////////
  if (m4 == 0x0000) {
    Km[3] = 0x0;
    Km[2] = 0x0;
    Km[1] = 0x0;
    Km[0] = 0x0;
  } else if (m4 == 0x0001) {
    Km[3] = 0x0;
    Km[2] = 0x0;
    Km[1] = 0x0;
    Km[0] = 0x1;
  } else if (m4 == 0x0002) {
    Km[3] = 0x0;
    Km[2] = 0x0;
    Km[1] = 0x1;
    Km[0] = 0x0;
  } else if (m4 == 0x0003) {
    Km[3] = 0x0;
    Km[2] = 0x0;
    Km[1] = 0x1;
    Km[0] = 0x1;
  } else if (m4 == 0x0004) {
    Km[3] = 0x0;
    Km[2] = 0x1;
    Km[1] = 0x0;
    Km[0] = 0x0;
  } else if (m4 == 0x0005) {
    Km[3] = 0x0;
    Km[2] = 0x1;
    Km[1] = 0x0;
    Km[0] = 0x1;
  } else if (m4 == 0x0006) {
    Km[3] = 0x0;
    Km[2] = 0x1;
    Km[1] = 0x1;
    Km[0] = 0x0;
  } else if (m4 == 0x0007) {
    Km[3] = 0x0;
    Km[2] = 0x1;
    Km[1] = 0x1;
    Km[0] = 0x1;
  } else if (m4 == 0x0008) {
    Km[3] = 0x1;
    Km[2] = 0x0;
    Km[1] = 0x0;
    Km[0] = 0x0;
  } else if (m4 == 0x0009) {
    Km[3] = 0x1;
    Km[2] = 0x0;
    Km[1] = 0x0;
    Km[0] = 0x1;
  } else if (m4 == 0x000A) {
    Km[3] = 0x1;
    Km[2] = 0x0;
    Km[1] = 0x1;
    Km[0] = 0x0;
  } else if (m4 == 0x000B) {
    Km[3] = 0x1;
    Km[2] = 0x0;
    Km[1] = 0x1;
    Km[0] = 0x1;
  } else if (m4 == 0x000C) {
    Km[3] = 0x1;
    Km[2] = 0x1;
    Km[1] = 0x0;
    Km[0] = 0x0;
  } else if (m4 == 0x000D) {
    Km[3] = 0x1;
    Km[2] = 0x1;
    Km[1] = 0x0;
    Km[0] = 0x1;
  } else if (m4 == 0x000E) {
    Km[3] = 0x1;
    Km[2] = 0x1;
    Km[1] = 0x1;
    Km[0] = 0x0;
  } else if (m4 == 0x000F) {
    Km[3] = 0x1;
    Km[2] = 0x1;
    Km[1] = 0x1;
    Km[0] = 0x1;
  }

  //    int C[16];
  //    //U[0] --> U[15]
  //    u16 U[16] = { 0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1};
  //    u16 Km[20] = { 0x1,0x0,0x1,0x0,0x1,0x0,0x0,0x0,0x1,0x0,0x1,0x0,0x1,0x0,0x0,0x0,0x1,0x1,0x0,0x0};
  //    
  //    pf("\nP: ");
  //    for(int i = 15;i>=0;i--){
  //        if(i==3){
  //            pf(" ");
  //        }
  //        else if(i==7){
  //            pf(" ");
  //        }
  //        if(i==11){
  //            pf(" ");
  //        }
  //        
  //        pf("%X",U[i]);
  //    }
  //    pf("\n");
  //    
  //    pf("K: ");
  //    for(int i = 19;i>=0;i--){
  //        if(i==3){
  //            pf(" ");
  //        }
  //        else if(i==7){
  //            pf(" ");
  //        }
  //        if(i==11){
  //            pf(" ");
  //        }
  //        if(i==15){
  //            pf(" ");
  //        }
  //        
  //        pf("%X",Km[i]);
  //    }
  //    pf("\n");

  C[15] = ((U[12] ^ Km[16]) * (U[13] ^ Km[17]) * (U[14] ^ Km[18]) ^ (U[12] ^ Km[16]) * (U[13] ^ Km[17]) * (U[15] ^ Km[19]) ^ (U[12] ^ Km[16]) * (U[14] ^ Km[18]) * (U[15] ^ Km[19]) ^ (U[12] ^ Km[16]) ^ (U[13] ^ Km[17]) * (U[14] ^ Km[18]) ^ (U[13] ^ Km[17]) ^ (U[15] ^ Km[19]) ^ 1) ^ (Km[3] * Km[4] * Km[5] ^ Km[3] * Km[4] * Km[6] ^ Km[3] * Km[5] * Km[6] ^ Km[3] ^ Km[4] * Km[5] ^ Km[4] ^ Km[6] ^ 1);
  C[14] = ((U[8] ^ Km[12]) * (U[9] ^ Km[13]) * (U[10] ^ Km[14]) ^ (U[8] ^ Km[12]) * (U[9] ^ Km[13]) * (U[11] ^ Km[15]) ^ (U[8] ^ Km[12]) * (U[10] ^ Km[14]) * (U[11] ^ Km[15]) ^ (U[8] ^ Km[12]) ^ (U[9] ^ Km[13]) * (U[10] ^ Km[14]) ^ (U[9] ^ Km[13]) ^ (U[11] ^ Km[15]) ^ 1) ^ (Km[3] * Km[4] * Km[6] ^ Km[3] * Km[4] ^ Km[3] * Km[5] * Km[6] ^ Km[3] * Km[6] ^ Km[4] * Km[6] ^ Km[5] ^ Km[6] ^ 1);
  C[13] = ((U[4] ^ Km[8]) * (U[5] ^ Km[9]) * (U[6] ^ Km[10]) ^ (U[4] ^ Km[8]) * (U[5] ^ Km[9]) * (U[7] ^ Km[11]) ^ (U[4] ^ Km[8]) * (U[6] ^ Km[10]) * (U[7] ^ Km[11]) ^ (U[4] ^ Km[8]) ^ (U[5] ^ Km[9]) * (U[6] ^ Km[10]) ^ (U[5] ^ Km[9]) ^ (U[7] ^ Km[11]) ^ 1) ^ (Km[3] * Km[4] * Km[5] ^ Km[3] * Km[4] * Km[6] ^ Km[3] * Km[5] * Km[6] ^ Km[4] * Km[6] ^ Km[4] ^ Km[5] * Km[6] ^ Km[6]);
  C[12] = ((U[0] ^ Km[4]) * (U[1] ^ Km[5]) * (U[2] ^ Km[6]) ^ (U[0] ^ Km[4]) * (U[1] ^ Km[5]) * (U[3] ^ Km[7]) ^ (U[0] ^ Km[4]) * (U[2] ^ Km[6]) * (U[3] ^ Km[7]) ^ (U[0] ^ Km[4]) ^ (U[1] ^ Km[5]) * (U[2] ^ Km[6]) ^ (U[1] ^ Km[5]) ^ (U[3] ^ Km[7]) ^ 1) ^ (Km[3] ^ Km[4] * Km[5] ^ Km[5] ^ Km[6]);
  C[11] = ((U[12] ^ Km[16]) * (U[13] ^ Km[17]) * (U[15] ^ Km[19]) ^ (U[12] ^ Km[16]) * (U[13] ^ Km[17]) ^ (U[12] ^ Km[16]) * (U[14] ^ Km[18]) * (U[15] ^ Km[19]) ^ (U[12] ^ Km[16]) * (U[15] ^ Km[19]) ^ (U[13] ^ Km[17]) * (U[15] ^ Km[19]) ^ (U[14] ^ Km[18]) ^ (U[15] ^ Km[19]) ^ 1) ^ Km[2];
  C[10] = ((U[8] ^ Km[12]) * (U[9] ^ Km[13]) * (U[11] ^ Km[15]) ^ (U[8] ^ Km[12]) * (U[9] ^ Km[13]) ^ (U[8] ^ Km[12]) * (U[10] ^ Km[14]) * (U[11] ^ Km[15]) ^ (U[8] ^ Km[12]) * (U[11] ^ Km[15]) ^ (U[9] ^ Km[13]) * (U[11] ^ Km[15]) ^ (U[10] ^ Km[14]) ^ (U[11] ^ Km[15]) ^ 1) ^ Km[1];
  C[9] = ((U[4] ^ Km[8]) * (U[5] ^ Km[9]) * (U[7] ^ Km[11]) ^ (U[4] ^ Km[8]) * (U[5] ^ Km[9]) ^ (U[4] ^ Km[8]) * (U[6] ^ Km[10]) * (U[7] ^ Km[11]) ^ (U[4] ^ Km[8]) * (U[7] ^ Km[11]) ^ (U[5] ^ Km[9]) * (U[7] ^ Km[11]) ^ (U[6] ^ Km[10]) ^ (U[7] ^ Km[11]) ^ 1) ^ Km[0];
  C[8] = ((U[0] ^ Km[4]) * (U[1] ^ Km[5]) * (U[3] ^ Km[7]) ^ (U[0] ^ Km[4]) * (U[1] ^ Km[5]) ^ (U[0] ^ Km[4]) * (U[2] ^ Km[6]) * (U[3] ^ Km[7]) ^ (U[0] ^ Km[4]) * (U[3] ^ Km[7]) ^ (U[1] ^ Km[5]) * (U[3] ^ Km[7]) ^ (U[2] ^ Km[6]) ^ (U[3] ^ Km[7]) ^ 1) ^ Km[19];
  C[7] = ((U[12] ^ Km[16]) * (U[13] ^ Km[17]) * (U[14] ^ Km[18]) ^ (U[12] ^ Km[16]) * (U[13] ^ Km[17]) * (U[15] ^ Km[19]) ^ (U[12] ^ Km[16]) * (U[14] ^ Km[18]) * (U[15] ^ Km[19]) ^ (U[13] ^ Km[17]) * (U[15] ^ Km[19]) ^ (U[13] ^ Km[17]) ^ (U[14] ^ Km[18]) * (U[15] ^ Km[19]) ^ (U[15] ^ Km[19])) ^ Km[18];
  C[6] = ((U[8] ^ Km[12]) * (U[9] ^ Km[13]) * (U[10] ^ Km[14]) ^ (U[8] ^ Km[12]) * (U[9] ^ Km[13]) * (U[11] ^ Km[15]) ^ (U[8] ^ Km[12]) * (U[10] ^ Km[14]) * (U[11] ^ Km[15]) ^ (U[9] ^ Km[13]) * (U[11] ^ Km[15]) ^ (U[9] ^ Km[13]) ^ (U[10] ^ Km[14]) * (U[11] ^ Km[15]) ^ (U[11] ^ Km[15])) ^ Km[17];
  C[5] = ((U[4] ^ Km[8]) * (U[5] ^ Km[9]) * (U[6] ^ Km[10]) ^ (U[4] ^ Km[8]) * (U[5] ^ Km[9]) * (U[7] ^ Km[11]) ^ (U[4] ^ Km[8]) * (U[6] ^ Km[10]) * (U[7] ^ Km[11]) ^ (U[5] ^ Km[9]) * (U[7] ^ Km[11]) ^ (U[5] ^ Km[9]) ^ (U[6] ^ Km[10]) * (U[7] ^ Km[11]) ^ (U[7] ^ Km[11])) ^ Km[16];
  C[4] = ((U[0] ^ Km[4]) * (U[1] ^ Km[5]) * (U[2] ^ Km[6]) ^ (U[0] ^ Km[4]) * (U[1] ^ Km[5]) * (U[3] ^ Km[7]) ^ (U[0] ^ Km[4]) * (U[2] ^ Km[6]) * (U[3] ^ Km[7]) ^ (U[1] ^ Km[5]) * (U[3] ^ Km[7]) ^ (U[1] ^ Km[5]) ^ (U[2] ^ Km[6]) * (U[3] ^ Km[7]) ^ (U[3] ^ Km[7])) ^ Km[15];
  C[3] = ((U[12] ^ Km[16]) ^ (U[13] ^ Km[17]) * (U[14] ^ Km[18]) ^ (U[14] ^ Km[18]) ^ (U[15] ^ Km[19])) ^ Km[14];
  C[2] = ((U[8] ^ Km[12]) ^ (U[9] ^ Km[13]) * (U[10] ^ Km[14]) ^ (U[10] ^ Km[14]) ^ (U[11] ^ Km[15])) ^ Km[13];
  C[1] = ((U[4] ^ Km[8]) ^ (U[5] ^ Km[9]) * (U[6] ^ Km[10]) ^ (U[6] ^ Km[10]) ^ (U[7] ^ Km[11])) ^ Km[12];
  C[0] = ((U[0] ^ Km[4]) ^ (U[1] ^ Km[5]) * (U[2] ^ Km[6]) ^ (U[2] ^ Km[6]) ^ (U[3] ^ Km[7])) ^ Km[11];

  u16 cSegment[4];

  cSegment[0] = ((C[15] * 8) + (C[14] * 4) + (C[13] * 2) + (C[12] * 1));
  cSegment[1] = ((C[11] * 8) + (C[10] * 4) + (C[9] * 2) + (C[8] * 1));
  cSegment[2] = ((C[7] * 8) + (C[6] * 4) + (C[5] * 2) + (C[4] * 1));
  cSegment[3] = ((C[3] * 8) + (C[2] * 4) + (C[1] * 2) + (C[0] * 1));

  //    pf("\nC: ");
  //    for(int i = 15;i>=0;i--){
  //        if(i==3){
  //            pf(" ");
  //        }
  //        else if(i==7){
  //            pf(" ");
  //        }
  //        if(i==11){
  //            pf(" ");
  //        }
  //        
  //        pf("%X",C[i]);
  //    }
  //    pf("\n");

  pf("Ciphertext: ");
  for (int i = 0; i < 4; i++) {
    pf("%X", cSegment[i]);
  }
  pf("\n");

}