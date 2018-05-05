//
// Created by Peter Zheng on 2018/05/05.
//

#include "HashTookit.h"

void myAlgorithm::HashTookit::MD5::MD5_Init(myAlgorithm::HashTookit::MD5::MD5_Core *ctx) {
    ctx->count[0] = 0;
    ctx->count[1] = 0;
    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xEFCDAB89;
    ctx->state[2] = 0x98BADCFE;
    ctx->state[3] = 0x10325476;
}

void myAlgorithm::HashTookit::MD5::MD5_Update(myAlgorithm::HashTookit::MD5::MD5_Core *ctx, unsigned char *input,
                                              unsigned int len) {
    unsigned int i = 0;
    unsigned int index = 0;
    unsigned int partlen = 0;

    index = (ctx->count[0] >> 3) & 0x3F;
    partlen = 64 - index;
    ctx->count[0] += len << 3;

    if (ctx->count[0] < (len << 3)) { ctx->count[1]++; }
    ctx->count[1] += len >> 29;

    if (len >= partlen) {
        memcpy(&ctx->buffer[index], input, partlen);
        MD5_Transform(ctx->state, ctx->buffer);
        for (i = partlen; i + 64 <= len; i += 64)
            MD5_Transform(ctx->state, &input[i]);
        index = 0;
    } else { i = 0; }
    memcpy(&ctx->buffer[index], &input[i], len - i);
}

void myAlgorithm::HashTookit::MD5::MD5_Final(myAlgorithm::HashTookit::MD5::MD5_Core *ctx, unsigned char *digest) {
    unsigned int index = 0, padlen = 0;
    unsigned char bits[8];

    index = (ctx->count[0] >> 3) & 0x3F;
    padlen = (index < 56) ? (56 - index) : (120 - index);
    MD5_Encode(bits, ctx->count, 8);
    MD5_Update(ctx, PADDING, padlen);
    MD5_Update(ctx, bits, 8);
    MD5_Encode(digest, ctx->state, 16);
}

void myAlgorithm::HashTookit::MD5::MD5_Transform(unsigned int *state, unsigned char *block) {
    unsigned int a = state[0];
    unsigned int b = state[1];
    unsigned int c = state[2];
    unsigned int d = state[3];
    unsigned int x[64];

    MD5_Decode(x, block, 64);

    FF(a, b, c, d, x[0], 7, 0xd76aa478); // 1
    FF(d, a, b, c, x[1], 12, 0xe8c7b756); // 2
    FF(c, d, a, b, x[2], 17, 0x242070db); // 3
    FF(b, c, d, a, x[3], 22, 0xc1bdceee); // 4
    FF(a, b, c, d, x[4], 7, 0xf57c0faf); // 5
    FF(d, a, b, c, x[5], 12, 0x4787c62a); // 6
    FF(c, d, a, b, x[6], 17, 0xa8304613); // 7
    FF(b, c, d, a, x[7], 22, 0xfd469501); // 8
    FF(a, b, c, d, x[8], 7, 0x698098d8); // 9
    FF(d, a, b, c, x[9], 12, 0x8b44f7af); // 10
    FF(c, d, a, b, x[10], 17, 0xffff5bb1); // 11
    FF(b, c, d, a, x[11], 22, 0x895cd7be); // 12
    FF(a, b, c, d, x[12], 7, 0x6b901122); // 13
    FF(d, a, b, c, x[13], 12, 0xfd987193); // 14
    FF(c, d, a, b, x[14], 17, 0xa679438e); // 15
    FF(b, c, d, a, x[15], 22, 0x49b40821); // 16
    // Round 2
    GG(a, b, c, d, x[1], 5, 0xf61e2562); // 17
    GG(d, a, b, c, x[6], 9, 0xc040b340); // 18
    GG(c, d, a, b, x[11], 14, 0x265e5a51); // 19
    GG(b, c, d, a, x[0], 20, 0xe9b6c7aa); // 20
    GG(a, b, c, d, x[5], 5, 0xd62f105d); // 21
    GG(d, a, b, c, x[10], 9, 0x2441453);  // 22
    GG(c, d, a, b, x[15], 14, 0xd8a1e681); // 23
    GG(b, c, d, a, x[4], 20, 0xe7d3fbc8); // 24
    GG(a, b, c, d, x[9], 5, 0x21e1cde6); // 25
    GG(d, a, b, c, x[14], 9, 0xc33707d6); // 26
    GG(c, d, a, b, x[3], 14, 0xf4d50d87); // 27
    GG(b, c, d, a, x[8], 20, 0x455a14ed); // 28
    GG(a, b, c, d, x[13], 5, 0xa9e3e905); // 29
    GG(d, a, b, c, x[2], 9, 0xfcefa3f8); // 30
    GG(c, d, a, b, x[7], 14, 0x676f02d9); // 31
    GG(b, c, d, a, x[12], 20, 0x8d2a4c8a); // 32
    // Round 3
    HH(a, b, c, d, x[5], 4, 0xfffa3942); // 33
    HH(d, a, b, c, x[8], 11, 0x8771f681); // 34
    HH(c, d, a, b, x[11], 16, 0x6d9d6122); // 35
    HH(b, c, d, a, x[14], 23, 0xfde5380c); // 36
    HH(a, b, c, d, x[1], 4, 0xa4beea44); // 37
    HH(d, a, b, c, x[4], 11, 0x4bdecfa9); // 38
    HH(c, d, a, b, x[7], 16, 0xf6bb4b60); // 39
    HH(b, c, d, a, x[10], 23, 0xbebfbc70); // 40
    HH(a, b, c, d, x[13], 4, 0x289b7ec6); // 41
    HH(d, a, b, c, x[0], 11, 0xeaa127fa); // 42
    HH(c, d, a, b, x[3], 16, 0xd4ef3085); // 43
    HH(b, c, d, a, x[6], 23, 0x4881d05);  // 44
    HH(a, b, c, d, x[9], 4, 0xd9d4d039); // 45
    HH(d, a, b, c, x[12], 11, 0xe6db99e5); // 46
    HH(c, d, a, b, x[15], 16, 0x1fa27cf8); // 47
    HH(b, c, d, a, x[2], 23, 0xc4ac5665); // 48
    // Round 4
    II(a, b, c, d, x[0], 6, 0xf4292244); // 49
    II(d, a, b, c, x[7], 10, 0x432aff97); // 50
    II(c, d, a, b, x[14], 15, 0xab9423a7); // 51
    II(b, c, d, a, x[5], 21, 0xfc93a039); // 52
    II(a, b, c, d, x[12], 6, 0x655b59c3); // 53
    II(d, a, b, c, x[3], 10, 0x8f0ccc92); // 54
    II(c, d, a, b, x[10], 15, 0xffeff47d); // 55
    II(b, c, d, a, x[1], 21, 0x85845dd1); // 56
    II(a, b, c, d, x[8], 6, 0x6fa87e4f); // 57
    II(d, a, b, c, x[15], 10, 0xfe2ce6e0); // 58
    II(c, d, a, b, x[6], 15, 0xa3014314); // 59
    II(b, c, d, a, x[13], 21, 0x4e0811a1); // 60
    II(a, b, c, d, x[4], 6, 0xf7537e82); // 61
    II(d, a, b, c, x[11], 10, 0xbd3af235); // 62
    II(c, d, a, b, x[2], 15, 0x2ad7d2bb); // 63
    II(b, c, d, a, x[9], 21, 0xeb86d391); // 64
    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
}

void myAlgorithm::HashTookit::MD5::MD5_Encode(unsigned char *output, unsigned int *input, unsigned int len) {
    unsigned int i = 0;
    unsigned int j = 0;

    while (j < len) {
        output[j] = input[i] & 0xFF;
        output[j + 1] = (input[i] >> 8) & 0xFF;
        output[j + 2] = (input[i] >> 16) & 0xFF;
        output[j + 3] = (input[i] >> 24) & 0xFF;
        i++;
        j += 4;
    }
}

void myAlgorithm::HashTookit::MD5::MD5_Decode(unsigned int *output, unsigned char *input, unsigned int len) {
    unsigned int i = 0;
    unsigned int j = 0;

    while (j < len) {
        output[i] = (input[j]) |
                    (input[j + 1] << 8) |
                    (input[j + 2] << 16) |
                    (input[j + 3] << 24);
        i++;
        j += 4;
    }
}

void myAlgorithm::HashTookit::SHA1::SHA1_Transform(myAlgorithm::HashTookit::SHA1::SHA_Core *ctx) {
    int t;
    unsigned int A = ctx->state[0];
    unsigned int B = ctx->state[1];
    unsigned int C = ctx->state[2];
    unsigned int D = ctx->state[3];
    unsigned int E = ctx->state[4];
    unsigned int TEMP;

    const unsigned int k1 = 0x5a827999;
    const unsigned int k2 = 0x6ed9eba1;
    const unsigned int k3 = 0x8f1bbcdc;
    const unsigned int k4 = 0xca62c1d6;

    for (t = 16; t <= 79; t++)
        ctx->buffer[t] = SHA_ROTATE(ctx->buffer[t - 3] ^ ctx->buffer[t - 8] ^ ctx->buffer[t - 14] ^ ctx->buffer[t - 16],
                                    1);

    for (t = 0; t <= 19; t++) {
        TEMP = SHA_ROTATE(A, 5) + (((C ^ D) & B) ^ D) + E + ctx->buffer[t] + k1;
        E = D;
        D = C;
        C = SHA_ROTATE(B, 30);
        B = A;
        A = TEMP;
    }
    for (t = 20; t <= 39; t++) {
        TEMP = SHA_ROTATE(A, 5) + (B ^ C ^ D) + E + ctx->buffer[t] + k2;
        E = D;
        D = C;
        C = SHA_ROTATE(B, 30);
        B = A;
        A = TEMP;
    }
    for (t = 40; t <= 59; t++) {
        TEMP = SHA_ROTATE(A, 5) + ((B & C) | (D & (B | C))) + E + ctx->buffer[t] + k3;
        E = D;
        D = C;
        C = SHA_ROTATE(B, 30);
        B = A;
        A = TEMP;
    }
    for (t = 60; t <= 79; t++) {
        TEMP = SHA_ROTATE(A, 5) + (B ^ C ^ D) + E + ctx->buffer[t] + k4;
        E = D;
        D = C;
        C = SHA_ROTATE(B, 30);
        B = A;
        A = TEMP;
    }

    ctx->state[0] += A;
    ctx->state[1] += B;
    ctx->state[2] += C;
    ctx->state[3] += D;
    ctx->state[4] += E;
}

void myAlgorithm::HashTookit::SHA1::SHA1_Init(myAlgorithm::HashTookit::SHA1::SHA_Core *ctx) {

    int i;
    ctx->lenBuf = 0;
    ctx->count[0] = ctx->count[1] = 0;
    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xefcdab89;
    ctx->state[2] = 0x98badcfe;
    ctx->state[3] = 0x10325476;
    ctx->state[4] = 0xc3d2e1f0;
    for (i = 0; i < 80; i++) { ctx->buffer[i] = 0; }
}

void myAlgorithm::HashTookit::SHA1::SHA1_Update(myAlgorithm::HashTookit::SHA1::SHA_Core *ctx, void *data, int len) {
    unsigned char *dataIn = (unsigned char *) data;
    int i;

    for (i = 0; i < len; i++) {
        ctx->buffer[ctx->lenBuf / 4] <<= 8;
        ctx->buffer[ctx->lenBuf / 4] |= (unsigned int) dataIn[i];
        if ((++ctx->lenBuf) % 64 == 0) {
            SHA1_Transform(ctx);
            ctx->lenBuf = 0;
        }
        ctx->count[1] += 8;
        ctx->count[0] += (ctx->count[1] < 8);
    }
}

void myAlgorithm::HashTookit::SHA1::SHA1_Final(unsigned char *digest, myAlgorithm::HashTookit::SHA1::SHA_Core *ctx) {
    unsigned char pad0x80 = 0x80;
    unsigned char pad0x00 = 0x00;
    unsigned char padlen[8];
    int i;

    padlen[0] = (unsigned char) ((ctx->count[0] >> 24) & 255);
    padlen[1] = (unsigned char) ((ctx->count[0] >> 16) & 255);
    padlen[2] = (unsigned char) ((ctx->count[0] >> 8) & 255);
    padlen[3] = (unsigned char) ((ctx->count[0] >> 0) & 255);
    padlen[4] = (unsigned char) ((ctx->count[1] >> 24) & 255);
    padlen[5] = (unsigned char) ((ctx->count[1] >> 16) & 255);
    padlen[6] = (unsigned char) ((ctx->count[1] >> 8) & 255);
    padlen[7] = (unsigned char) ((ctx->count[1] >> 0) & 255);

    SHA1_Update(ctx, &pad0x80, 1);
    while (ctx->lenBuf != 56) { SHA1_Update(ctx, &pad0x00, 1); }
    SHA1_Update(ctx, padlen, 8);
    for (i = 0; i < 20; i++) {
        digest[i] = (unsigned char) (ctx->state[i / 4] >> 24);
        ctx->state[i / 4] <<= 8;
    }
    SHA1_Init(ctx);
}
