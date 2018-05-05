//
// Created by Peter Zheng on 2018/05/05.
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_HASHTOOKIT_H
#define INC_2018DATASTRUCTUREBIGWORK_HASHTOOKIT_H

#include <cstring>

#define F(x, y, z) ((x & y) | (~x & z))
#define G(x, y, z) ((x & z) | (y & ~z))
#define H(x, y, z) (x ^ y ^ z)
#define I(x, y, z) (y ^ (x | ~z))
#define MD5_ROTATE(x, n) ((x << n) | (x >> (32-n)))

#define FF(a, b, c, d, x, s, ac) { \
    a += F(b,c,d) + x + ac;  \
    a = MD5_ROTATE(a,s);     \
    a += b;                  \
}

#define GG(a, b, c, d, x, s, ac) { \
    a += G(b,c,d) + x + ac;  \
    a = MD5_ROTATE(a,s);     \
    a += b;                  \
}

#define HH(a, b, c, d, x, s, ac) { \
    a += H(b,c,d) + x + ac;  \
    a = MD5_ROTATE(a,s);     \
    a += b;                  \
}

#define II(a, b, c, d, x, s, ac) { \
    a += I(b,c,d) + x + ac;  \
    a = MD5_ROTATE(a,s);     \
    a += b;                  \
}

#define SHA_ROTATE(X, n) (((X) << (n)) | ((X) >> (32-(n))))
namespace myAlgorithm {
    class HashTookit {

        class MD5 {
        private:
            struct MD5_Core {
                unsigned int count[2];
                unsigned int state[4];
                unsigned char buffer[64];
            };
            unsigned char PADDING[] = {
                    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
            };
        public:
            void MD5_Init(MD5_Core *ctx);

            void MD5_Update(MD5_Core *ctx, unsigned char *input, unsigned int len);

            void MD5_Final(MD5_Core *ctx, unsigned char digest[16]);

            void MD5_Transform(unsigned int state[4], unsigned char block[64]);

            void MD5_Encode(unsigned char *output, unsigned int *input, unsigned int len);

            void MD5_Decode(unsigned int *output, unsigned char *input, unsigned int len);
        };

        class SHA1 {
        private:
            struct SHA_Core {
                unsigned int state[5];
                unsigned int count[2];
                unsigned int buffer[80];
                int lenBuf;
            };
        public:
            void SHA1_Transform(SHA_Core *ctx);

            void SHA1_Init(SHA_Core *ctx);

            void SHA1_Update(SHA_Core *ctx, void *data, int len);

            void SHA1_Final(unsigned char digest[20], SHA_Core *ctx);
        };

    };
}


#endif //INC_2018DATASTRUCTUREBIGWORK_HASHTOOKIT_H
