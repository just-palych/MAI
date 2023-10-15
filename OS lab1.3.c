#include <stdio.h>

typedef enum {
  fsc_ok,
  fsc_invalid_num_arg,
  fsc_error_input,
  fsc_error_output
} function_status_code;

int copy(FILE* proto, FILE* post) {
  char buff[BUFSIZ];
  size_t ch = fread(buff, sizeof(char), BUFSIZ, proto);
  while (ch > 0) {
    fwrite(buff, sizeof(char), ch, post);
    ch = fread(buff, sizeof(char), 1, proto);
  }
  return 0;
}

function_status_code input(int argc, char* argv[]) {
  if (argc != 3) {
    return fsc_invalid_num_arg;
  }
  FILE* input_f = fopen(argv[1], "rb");
  if (input_f == NULL) {
    return fsc_error_input;
  }
  FILE* output_f = fopen(argv[2], "wb");
  if (output_f == NULL) {
    return fsc_error_output;
  }

  copy(input_f, output_f);
  fclose(input_f);
  fclose(output_f);
  return fsc_ok;
}



int main(int argc, char* argv[]) {
  switch (input(argc, argv)) {
    case fsc_ok:
      printf("All is ok\n");
      break;
    case fsc_invalid_num_arg:
      printf("Invalid number of arg\n");
      break;
    case fsc_error_input:
      printf("Error input file\n");
      break;
    case fsc_error_output:
      printf("Error output file\n");
      break;
  }

  return 0;
}