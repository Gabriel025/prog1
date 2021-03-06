#define XOR_ENCRYPT_NO_MAIN
#include "xor_encrypt.c"
#include <strings.h>

typedef int (*heuristic_func)(char *buffer, int n);

void first_key(char *allowed_ch, int min_len, char *result);
int next_key(char *allowed_ch, int max_len, char *key);
int check_common_words_hu(char *buffer, int n);

int main(int argc, char **argv)
{
    char allowed_chars[] = "0123456789abcdef";
    int min_key_size = 2;
    int max_key_size = 6;

    int sample_size = 128, sample_offset = 0;
    heuristic_func heuristic = check_common_words_hu;
    
    
    char key[max_key_size + 1], buffer[sample_size + 1];
    
    for(int i = 0; i < sample_offset; i++) read(0, buffer, 1);
    int n_bytes = read(0, buffer, sample_size);
    buffer[n_bytes] = '\0';

    first_key(allowed_chars, min_key_size, key);
    do
    {
        xor_encrypt(key, buffer, n_bytes);
        
        if(heuristic(buffer, n_bytes))
        {
            printf("%s\n\n", buffer);
        }

        xor_encrypt(key, buffer, n_bytes);
    } while(next_key(allowed_chars, max_key_size, key) > 0);

    return 0;
}

void first_key(char *allowed_ch, int min_len, char *result)
{
    for(int i = 0; i < min_len; i++) result[i] = allowed_ch[0];
    result[min_len] = '\0';
}

int next_key(char *allowed_ch, int max_len, char *key)
{
    //printf("allowed_ch@%X: \"%s\"; key@%X: \"%s\"\n", allowed_ch, allowed_ch, key, key);
    int carry = 1, allowed_ch_len = strlen(allowed_ch), key_len = strlen(key);

    while(carry)
    {
        if(*key == '\0')
        { 
            if(key_len == max_len) return 0;
            else
            {
                key[0] = allowed_ch[0];
                key[1] = '\0';
            }
        }

        int pos;
        for(pos = 0; pos < allowed_ch_len; pos++)
            if(allowed_ch[pos] == *key) break;
        
        if(pos == allowed_ch_len) return -1;
        pos = (pos + 1) % allowed_ch_len;
        
        *key = allowed_ch[pos];
        if(pos != 0) carry = 0;
        key++; 
    }

    return 1;
}

int check_common_words_hu(char *buffer, int n)
{
    return n == strlen(buffer) && strcasestr(buffer, "az") && strcasestr(buffer, "egy") && strcasestr(buffer, "hogy");
}