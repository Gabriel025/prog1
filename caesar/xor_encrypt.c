#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void xor_encrypt(char *key, char *buffer, int buffer_size);


#ifndef XOR_ENCRYPT_NO_MAIN

#define MAX_KEY_LEN 20
#define BUFFER_SIZE 256

int main(int argc, char **argv)
{
    char key[MAX_KEY_LEN], buffer[BUFFER_SIZE];
    
    if(argc > 1) strncpy(key, argv[1], MAX_KEY_LEN);
    else
    {
        printf("Encryption key: ");
        fgets(key, MAX_KEY_LEN, stdin);
    }

    int n_bytes;
    while(n_bytes=read(0, buffer, BUFFER_SIZE))
    {
        xor_encrypt(key, buffer, n_bytes);
        write(1, buffer, n_bytes);
        //for(int i = 0; i < n; i++)
        //    printf("%0x2X ", (unsigned char)buffer[i]);
    }
    

    return 0;
}

#endif //XOR_ENCRYPT_NO_MAIN


void xor_encrypt(char *key, char *buffer, int buffer_size)
{
    int keysize = strlen(key);

    for(int i = 0; i < buffer_size; i++)
        buffer[i] ^= key[i % keysize];
}
