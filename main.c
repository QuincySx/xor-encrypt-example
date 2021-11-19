#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "hexstring.c"


void encryptKey(const char *content, int contentSize, const char *key, uint8_t *out) {
    const char *obfuscator = key;

    for (int i = 0; i < contentSize; i++) {
        out[i] = *(content + i) ^ obfuscator[i % strlen(obfuscator)];
    }

    out[contentSize] = 0x0;
}

int main(int argc, char *argv[]) {
    int ch;
    char *key;
    char *secret;

    while ((ch = getopt(argc, argv, "k:s:")) != -1) {
        switch (ch) {
            case 'k':
                printf("k:%s\n", optarg);
                key = optarg;
                break;
            case 's':
                printf("s:%s\n", optarg);
                secret = optarg;
                break;
        }
    }

    int secretBytesSize = strlen(secret) / 2;
    char *secretBytes = malloc(secretBytesSize);
    strToHex(secretBytes, secret, secretBytesSize);

    int keySize = strlen(key) + 1;
    uint8_t *output = malloc(keySize);
    encryptKey(key, keySize, secretBytes, output);
    printf("result:\n");
    printf("{");
    for (int i = 0; i < keySize; ++i) {
        printf(" 0x%x", *(output + i) & 0xFF);
        if (i != keySize - 1) {
            printf(",");
        }
    }
    printf("}\n");
    return 0;
}
