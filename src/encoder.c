//
// Created by Roman on 10-Jun-22.
//

#include <malloc.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "../include/encoder.h"
#include "../include/codebook.h"

struct encoder encoder_create(struct codebook *codebook, FILE *src_file, FILE *output_file_name) {
    return (struct encoder) {
        .codebook = codebook,
        .src_file = src_file,
        .output_file = output_file_name
    };
}

void encoder_destroy(struct encoder *encoder) {
    encoder->codebook = NULL;
    encoder->src_file = NULL;
    encoder->output_file = NULL;
}

static int int_to_binary_string(char ch, char *buffer, int buf_size) {
    int char_count =
            ch == '\0' ?
            8 // saying 00000000 has no leading zeros
                       :
            (int) log2((unsigned char) ch) + 1;

    buffer += (buf_size - 1);

    for (int i = 7; i >= 0; i--) {
        *buffer-- = (ch & 1) + '0';
        ch >>= 1;
    }

    return (int) char_count;
}

void encoder_encode(struct encoder *encoder) {
    char *input_buffer = calloc(WRITE_BUFFER_SIZE + 1, sizeof(char));
    input_buffer[WRITE_BUFFER_SIZE] = '\0'; // debug)

    int longest_code_len = codebook_get_longest_code_length(encoder->codebook);

    while (true) {
        int chars_read = (int) fread(input_buffer, sizeof(char), WRITE_BUFFER_SIZE, encoder->src_file);
        if (chars_read == 0) {
            break;
        }

        char *output_bits_buffer = calloc(chars_read * longest_code_len + 1, sizeof(char));
        char *output_bits_buf_ptr = output_bits_buffer;
        int bits_written = 0;

        for (int i = 0; i < chars_read; ++i) {
            char src = input_buffer[i];
            char *encoded = codebook_get_code(encoder->codebook, src);

            sprintf(output_bits_buf_ptr, "%s", encoded);
            size_t len = strlen(encoded);
            output_bits_buf_ptr += len;
            bits_written += (int) len;
        }

        int bytes_to_write = bits_written / 8 + (bits_written % 8 == 0 ? 0 : 1);
        char *output_byte_buffer = calloc(bytes_to_write, sizeof(char));

        for (int i = 0; i < bits_written; i += 8) {
            int byte_end = (int) fmin(i + 8, bits_written + 1);
            char temp = output_bits_buffer[byte_end];
            output_bits_buffer[byte_end] = '\0';
            char encoded_byte = (char) strtol(output_bits_buffer + i, 0, 2);
            output_bits_buffer[byte_end] = temp;

            sprintf(output_byte_buffer, "%c", encoded_byte);
        }

        fwrite(output_byte_buffer, sizeof(char), bytes_to_write, encoder->output_file);
        free(output_bits_buffer);
        free(output_byte_buffer);
    }

    free(input_buffer);
}