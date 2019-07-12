#include "present.h"

#include <string.h>

u8 S[16] = {
  0xC,
  0x5,
  0x6,
  0xB,
  0x9,
  0x0,
  0xA,
  0xD,
  0x3,
  0xE,
  0xF,
  0x8,
  0x4,
  0x7,
  0x1,
  0x2
};

u16 Bin[16] = {
  0x0000,
  0x0001,
  0x0010,
  0x0011,
  0x0100,
  0x0101,
  0x0110,
  0x0111,
  0x1000,
  0x1001,
  0x1010,
  0x1011,
  0x1100,
  0x1101,
  0x1110,
  0x1111
};

u8 SInv[16] = {
  0x5,
  0xE,
  0xF,
  0x8,
  0xC,
  0x1,
  0x2,
  0xD,
  0xB,
  0x4,
  0x6,
  0x3,
  0x0,
  0x7,
  0x9,
  0xA
};

/*
 * Key schedule
 */
void keySchedule(u16 * key, u16 K[], u16 keySize) {
  u16 keyReg[8]; // support for 128-bit key
  u16 temp[8];
  u16 x, y, z, m;
  int i, j;
  
  for (i = 0; i < 8; i++) {
    keyReg[i] = key[i];
    //      pf("%X\n",keyReg[i]);
  }

  K[0] = keyReg[0] << 12 | keyReg[1] << 8 | keyReg[2] << 4 | keyReg[3];

     pf("K 1: %04X \n", K[0]);

  for (i = 2; i <= ROUNDS + 1; i++) {

    //temp[0] = temp[1] = temp[2] = temp[3] = temp[4] = 0;

    // rotating 61 bits to the left
    temp[0] = (((keyReg[3] & 0x0007) << 1) | (keyReg[4] >> 3)) & 0xf;
    temp[1] = (((keyReg[4] & 0x0007) << 1) | (keyReg[0] >> 3)) & 0xf;
    temp[2] = (((keyReg[0] & 0x0007) << 1) | (keyReg[1] >> 3)) & 0xf;
    temp[3] = (((keyReg[1] & 0x0007) << 1) | (keyReg[2] >> 3)) & 0xf;
    temp[4] = (((keyReg[2] & 0x0007) << 1) | (keyReg[3] >> 3)) & 0xf;

    for (j = 0; j < 5; j++) {
      keyReg[j] = temp[j];
    }
          pf("  Rotate: %X %X %X %X %X\n", keyReg[0], keyReg[1], keyReg[2], \
    keyReg[3], keyReg[4]);

  // sbox
  //      s = S[keyReg[0] >> 12];
  //      keyReg[0] &= 0x0FFF;
  //      keyReg[0] |= (s << 12);
  keyReg[0] = S[keyReg[0]];

        pf("  Sbox:   %X %X %X %X %X\n", keyReg[0], keyReg[1], keyReg[2], \
  keyReg[3], keyReg[4]);

// XOR with round counter i
      pf("  Round counter: %04X\n", i - 1);
z = (Bin[keyReg[4]]);
y = Bin[keyReg[3]];
//      pf("%04X",y);
//      pf("%04X\n",z);
m = Bin[i - 1];
//      pf("%05X\n",m);
z = (Bin[keyReg[4]] ^ ((m) << 12));
y = Bin[keyReg[3]] ^ (m >> 4);

if (z == 0x0000) {
  keyReg[4] = 0x0000;
} else if (z == 0x0001) {
  keyReg[4] = 0x0001;
} else if (z == 0x0010) {
  keyReg[4] = 0x0002;
} else if (z == 0x0011) {
  keyReg[4] = 0x0003;
} else if (z == 0x0100) {
  keyReg[4] = 0x0004;
} else if (z == 0x0101) {
  keyReg[4] = 0x0005;
} else if (z == 0x0110) {
  keyReg[4] = 0x0006;
} else if (z == 0x0111) {
  keyReg[4] = 0x0007;
} else if (z == 0x1000) {
  keyReg[4] = 0x0008;
} else if (z == 0x1001) {
  keyReg[4] = 0x0009;
} else if (z == 0x1010) {
  keyReg[4] = 0x000A;
} else if (z == 0x1011) {
  keyReg[4] = 0x000B;
} else if (z == 0x1100) {
  keyReg[4] = 0x000C;
} else if (z == 0x1101) {
  keyReg[4] = 0x000D;
} else if (z == 0x1110) {
  keyReg[4] = 0x000E;
} else if (z == 0x1111) {
  keyReg[4] = 0x000F;
}

if (y == 0x0000) {
  keyReg[3] = 0x0000;
} else if (y == 0x0001) {
  keyReg[3] = 0x0001;
} else if (y == 0x0010) {
  keyReg[3] = 0x0002;
} else if (y == 0x0011) {
  keyReg[3] = 0x0003;
} else if (y == 0x0100) {
  keyReg[3] = 0x0004;
} else if (y == 0x0101) {
  keyReg[3] = 0x0005;
} else if (y == 0x0110) {
  keyReg[3] = 0x0006;
} else if (y == 0x0111) {
  keyReg[3] = 0x0007;
} else if (y == 0x1000) {
  keyReg[3] = 0x0008;
} else if (y == 0x1001) {
  keyReg[3] = 0x0009;
} else if (y == 0x1010) {
  keyReg[3] = 0x000A;
} else if (y == 0x1011) {
  keyReg[3] = 0x000B;
} else if (y == 0x1100) {
  keyReg[3] = 0x000C;
} else if (y == 0x1101) {
  keyReg[3] = 0x000D;
} else if (y == 0x1110) {
  keyReg[3] = 0x000E;
} else if (y == 0x1111) {
  keyReg[3] = 0x000F;
}

      pf("  XOR:    %X %X %X %X %X\n\n", keyReg[0], keyReg[1], keyReg[2], \
keyReg[3], keyReg[4]);

K[i - 1] = keyReg[0] << 12 | keyReg[1] << 8 | keyReg[2] << 4 | keyReg[3];

      pf("K%2d: %X\n", i, K[i-1]);
}

   pf("Encryption keys: \n");
   for (i = 0; i <= ROUNDS; i++) {
      pf("%04X\n", K[i]);
   }

/*
pf("Decryption keys: \n");
for (i = 0; i < 33; i++) {
    pf("%8X %8X %8X %8X\n", K->Dec[i][0], K->Dec[i][1], K->Dec[i][2], \
        K->Dec[i][3]);
}
*/
}

void keyScheduleInit(u16 * key, u16 K[], u16 keySize) {
  u16 keyReg[8]; // support for 128-bit key
  u16 temp[8];
  u8 i, j, s;
  for (i = 0; i < 5; i++) {
    keyReg[i] = key[i];
  }

  K[0] = keyReg[0];

  pf("K 1: %04X \n", keyReg[0]);

  for (i = 1; i <= ROUNDS; i++) {

    //temp[0] = temp[1] = temp[2] = temp[3] = temp[4] = 0;

    // rotating 61 bits to the left
    temp[0] = ((keyReg[3] & 0x0007) << 13) | (keyReg[4] >> 3);
    temp[1] = ((keyReg[4] & 0x0007) << 13) | (keyReg[0] >> 3);
    temp[2] = ((keyReg[0] & 0x0007) << 13) | (keyReg[1] >> 3);
    temp[3] = ((keyReg[1] & 0x0007) << 13) | (keyReg[2] >> 3);
    temp[4] = ((keyReg[2] & 0x0007) << 13) | (keyReg[3] >> 3);

    for (j = 0; j < 5; j++) {
      keyReg[j] = temp[j];
    }
    pf("  Rotate: %04X %04X %04X %04X %04X\n", keyReg[0], keyReg[1], keyReg[2], \
      keyReg[3], keyReg[4]);

    // sbox
    s = S[keyReg[0] >> 12];
    keyReg[0] &= 0x0FFF;
    keyReg[0] |= (s << 12);

    pf("  Sbox:   %04X %04X %04X %04X %04X\n", keyReg[0], keyReg[1], keyReg[2], \
      keyReg[3], keyReg[4]);

    // XOR with round counter i
    pf("  Round counter: %X\n", i - 1);
    keyReg[4] ^= ((i) << 15);
    keyReg[3] ^= ((i) >> 1);

    pf("  XOR:    %04X %04X %04X %04X %04X\n\n", keyReg[0], keyReg[1], keyReg[2], \
      keyReg[3], keyReg[4]);

    K[i] = keyReg[0];

    pf("K%2d: %04X\n", i, keyReg[0]);
  }

  pf("Encryption keys: \n");
  for (i = 0; i < ROUNDS; i++) {
    pf("%8X\n", K[i]);
  }

  /*
  pf("Decryption keys: \n");
  for (i = 0; i < 33; i++) {
      pf("%8X %8X %8X %8X\n", K->Dec[i][0], K->Dec[i][1], K->Dec[i][2], \
          K->Dec[i][3]);
  }
  */
}

void encrypt(u16 K[], u16 * X) {
  u16 subkey[1];
  u8 i;

  for (i = 1; i <= ROUNDS; i++) {
    subkey[0] = K[i - 1];
    //        subkey[1] = K[i - 1][1];
    //        subkey[2] = K[i - 1][2];
    //        subkey[3] = K[i - 1][3];
    Round(subkey, X);
  }
  subkey[0] = K[i - 1];
  //    subkey[1] = K[i - 1][1];
  //    subkey[2] = K[i - 1][2];
  //    subkey[3] = K[i - 1][3];
  addRoundKey(subkey, X);

  //   for(i = 0; i < 4; i++){
  //       pf("%X\n",X[i]);
  //   }
  //   pf("done! \n");

  //pf("R%2d %8X %8X %8X %8X\n", i, B[0], B[1], B[2], B[3]);
}

void decrypt(u16 K[], u16 * X) {
  u16 subkey[1];
  s8 i;

  subkey[0] = K[ROUNDS];
  //    subkey[1] = K[31][1];
  //    subkey[2] = K[31][2];
  //    subkey[3] = K[31][3];
  addRoundKeyInv(subkey, X);
  for (i = ROUNDS; i >= 1; i--) {
    //        pf("\n",i);
    subkey[0] = K[i - 1];
    //        subkey[1] = K[i - 1][1];
    //        subkey[2] = K[i - 1][2];
    //        subkey[3] = K[i - 1][3];
    RoundInv(subkey, X);
  }

  //pf("R%2d %8X %8X %8X %8X\n", i, B[0], B[1], B[2], B[3]);
}

void Round(u16 * key, u16 * X) {
  addRoundKey(key, X);
  sBoxlayer(X);
  pLayer(X);
}

void RoundInv(u16 * key, u16 * X) {
  pLayerInv(X);
  sBoxlayerInv(X);
  addRoundKeyInv(key, X);
}

void addRoundKey(u16 * key, u16 * X) {
  u16 * temp;
  u8 i;

  //       pf("Plaintext - ");
  //       for (i = 0; i < 4; i++) {
  //           pf("%X",X[i]);
  //       }
  //       pf("\n");
  //
  //       pf("Key - %04X\n",key[0]);

  temp[0] = (key[0] & 0xF000) >> 12;
  temp[1] = (key[0] & 0x0F00) >> 8;
  temp[2] = (key[0] & 0x00F0) >> 4;
  temp[3] = (key[0] & 0x000F);

  //   pf("Ciphertext - ");
  for (i = 0; i < 4; i++) {
    X[i] ^= temp[i];
  }

  //   for(i = 0;i<4;i++){
  //      pf("%X",X[i]);
  //   }
  //   pf("\n");
}

void addRoundKeyInv(u16 * key, u16 * X) {
  u16 * temp;
  u8 i;

  //    pf("Plaintext - ");
  //    for (i = 0; i < 4; i++) {
  //        pf("%X",X[i]);
  //    }
  //    pf("\n");
  //
  //    pf("Key - %04X\n",key[0]);
  //    
  temp[0] = (key[0] & 0xF000) >> 12;
  temp[1] = (key[0] & 0x0F00) >> 8;
  temp[2] = (key[0] & 0x00F0) >> 4;
  temp[3] = (key[0] & 0x000F);

  //       pf("Ciphertext - ");
  for (i = 0; i < 4; i++) {
    X[i] ^= temp[i];
  }

  //   for(i = 0;i<4;i++){
  //      pf("%X",X[i]);
  //   }
  //   pf("\n");

}

void sBoxlayer(u16 * X) {
  u8 i;
  //       pf("After sBox - ");

  for (i = 0; i < 4; i++) {
    X[i] = S[X[i]];
    //              pf("%X",X[i]);
  }
  //       pf("\n");
}

void sBoxlayerInv(u16 * X) {
  u8 i;
  //    pf("After sBoxInv - ");

  for (i = 0; i < 4; i++) {
    X[i] = SInv[X[i]];
    //        pf("%X",X[i]);
  }
  //    pf("\n");
}

void pLayer(u16 * X) {
  u8 y[4] = {
    0
  };
  u8 i;

  y[0] = ((X[0] & 0x8));
  y[0] |= ((X[1] & 0x8) >> 1);
  y[0] |= ((X[2] & 0x8) >> 2);
  y[0] |= ((X[3] & 0x8) >> 3);
  y[1] = ((X[0] & 0x4) << 1);
  y[1] |= ((X[1] & 0x4));
  y[1] |= ((X[2] & 0x4) >> 1);
  y[1] |= ((X[3] & 0x4) >> 2);
  y[2] = ((X[0] & 0x2) << 2);
  y[2] |= ((X[1] & 0x2) << 1);
  y[2] |= ((X[2] & 0x2));
  y[2] |= ((X[3] & 0x2) >> 1);
  y[3] = ((X[0] & 0x1) << 3);
  y[3] |= ((X[1] & 0x1) << 2);
  y[3] |= ((X[2] & 0x1) << 1);
  y[3] |= ((X[3] & 0x1));

  for (i = 0; i < 4; i++) {
    X[i] = y[i];
  }

  //           pf("After pLayer - ");
  //       for (i = 0; i < 4; i++) {
  //           pf("%X",X[i]);
  //       }
  //       pf("\n");

}

void pLayerInv(u16 * X) {
  u8 y[4] = {
    0
  };
  u8 i;

  y[0] = ((X[0] & 0x8));
  y[0] |= ((X[1] & 0x8) >> 1);
  y[0] |= ((X[2] & 0x8) >> 2);
  y[0] |= ((X[3] & 0x8) >> 3);
  y[1] = ((X[0] & 0x4) << 1);
  y[1] |= ((X[1] & 0x4));
  y[1] |= ((X[2] & 0x4) >> 1);
  y[1] |= ((X[3] & 0x4) >> 2);
  y[2] = ((X[0] & 0x2) << 2);
  y[2] |= ((X[1] & 0x2) << 1);
  y[2] |= ((X[2] & 0x2));
  y[2] |= ((X[3] & 0x2) >> 1);
  y[3] = ((X[0] & 0x1) << 3);
  y[3] |= ((X[1] & 0x1) << 2);
  y[3] |= ((X[2] & 0x1) << 1);
  y[3] |= ((X[3] & 0x1));

  for (i = 0; i < 4; i++) {
    X[i] = y[i];
  }

  //        pf("After pLayerInv - ");
  //    for (i = 0; i < 4; i++) {
  //        pf("%X",y[i]);
  //    }
  //    pf("\n");

}

//u32 ROT32L(u32 a, u8 n) {
//   return (a << n) | (a >> (32 - n));
//}
//
//u32 ROT32R(u32 a, u8 n) {
//   return (a >> n) | (a << (32 - n));
//}