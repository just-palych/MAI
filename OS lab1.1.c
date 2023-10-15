#include <stdio.h>
#include <stdlib.h>


typedef enum {
  fsc_ok,
  fsc_invalid_num_arg,
  fsc_error_output
} function_status_code;


int print_all_file(FILE* stream) {
  printf("Empty:  _ptr: %p, _base: %p, _bufsiz: %d, _charbuf: %d, _cnt: %d, _file: %d, _flag: %d\n", stream->_ptr,
         stream->_base,
         stream->_bufsiz, stream->_charbuf,
         stream->_cnt, stream->_file, stream->_flag);
  char buff[1];
  do {
    fread(buff, sizeof(char), 1, stream);
    printf("%d: _ptr: %p, _base: %p, _bufsiz: %d, _charbuf: %d, _cnt: %d, _file: %d, _flag: %d\n", buff[0],
           stream->_ptr,
           stream->_base,
           stream->_bufsiz, stream->_charbuf,
           stream->_cnt, stream->_file, stream->_flag);
  } while (!feof(stream));
  return 0;
}

int print_n_bytes_from_file(FILE* stream, int n) {
  char* buff = (char*) malloc(sizeof(char) * (n));
  if (buff == NULL) {
    return -1;
  }
  fread(buff, sizeof(char), n, stream);
  buff[n] = 0;
  printf("%d bytes ", n);
  for(int i = 0; i < n; i++){
    printf("%d ", buff[i]);
  }
  return 0;
}

function_status_code execute(char* filename) {
  FILE* stream = fopen(filename, "wb");
  if (stream == NULL) {
    return fsc_error_output;
  }
  char buff[11] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
  fwrite(buff, sizeof(char), 11, stream);
  fclose(stream);

  stream = fopen(filename, "rb");
  if (stream == NULL) {
    return fsc_error_output;
  }
  print_all_file(stream);
  fclose(stream);

  stream = fopen(filename, "rb");
  if (stream == NULL) {
    return fsc_error_output;
  }
  fseek(stream, 3, SEEK_SET);
  print_n_bytes_from_file(stream, 4);
  fclose(stream);
  return fsc_ok;
}

function_status_code input(int argc, char* argv[]) {
  if (argc != 2) {
    return fsc_invalid_num_arg;
  }
  return execute(argv[1]);
}

int main(int argc, char* argv[]) {
  switch (input(argc, argv)) {
    case fsc_ok:
      printf("All is ok");
      break;
    case fsc_invalid_num_arg:
      printf("invalid argc\n");
      break;
    case fsc_error_output:
      printf("couldn't open file\n");
      break;
    default:
      printf("stc unknown\n");
  }
  return 0;
}