//
// Created by Roman on 10-Jun-22.
//

#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "../include/encoder.h"
#include "../include/codebook.h"
#include "../include/buffers.h"
#include "../include/freqbook.h"

struct encoder encoder_create(struct freqbook *freqbook, struct codebook *codebook, FILE *src_file, FILE *output_file_name) {
    return (struct encoder) {
        .freqbook = freqbook,
        .codebook = codebook,
        .src_file = src_file,
        .output_file = output_file_name
    };
}

void encoder_destroy(struct encoder *encoder) {
    encoder->freqbook = NULL;
    encoder->codebook = NULL;
    encoder->src_file = NULL;
    encoder->output_file = NULL;
}

static void serialize_code_count(struct encoder *encoder, int code_count) {
    fwrite(&code_count, sizeof(int), 1, encoder->output_file);
}

static void serialize_amount_of_frequencies(struct encoder *encoder) {
    int amount_of_frequencies = freqbook_get_amount_of_frequencies(encoder->freqbook);
    fwrite(&amount_of_frequencies, sizeof(int), 1, encoder->output_file);
}

void serialize_freqbook(struct encoder *encoder) {
    for (int i = 0; i < FREQBOOK_SIZE; ++i) {
        int freq = freqbook_get_freq(encoder->freqbook, (char) i);
        if (freq != 0) {
            fwrite(&i, sizeof(char), 1, encoder->output_file);
            fwrite(&freq, sizeof(int), 1, encoder->output_file);
        }
    }
}

void encoder_encode(struct encoder *encoder, char* output_filename) {
    int code_count = 0;
    serialize_code_count(encoder, code_count);

    serialize_amount_of_frequencies(encoder);
    serialize_freqbook(encoder);

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
            code_count++;
        }

        int bytes_to_write = bits_written / 8 + (bits_written % 8 == 0 ? 0 : 1);
        char *output_byte_buffer = calloc(bytes_to_write, sizeof(char));

        for (int i = 0; i < bits_written; i += 8) {
            int byte_end = (int) fmin(i + 8, bits_written + 1);
            char temp = output_bits_buffer[byte_end];
            output_bits_buffer[byte_end] = '\0';
            char encoded_byte = (char) strtol(output_bits_buffer + i, 0, 2);

            if (i + 8 > bits_written) {
                int last_byte_extra_shift = 8 - (i + 8 - bits_written);
                encoded_byte <<= last_byte_extra_shift;
            }

            output_bits_buffer[byte_end] = temp;

            output_byte_buffer[i / 8] = encoded_byte;
        }

        fwrite(output_byte_buffer, sizeof(char), bytes_to_write, encoder->output_file);
        free(output_bits_buffer);
        free(output_byte_buffer);
    }

    // FUCK THIS CODE!!!!!!!
    fclose(encoder->output_file);
    freopen(output_filename, "rb+", encoder->output_file);

    // Overwrite 1st byte
    serialize_code_count(encoder, code_count);

    free(input_buffer);
}

// sorry for govnocode and comments. had no sleep for 25 hrs by now
