#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef unsigned char byte;
typedef unsigned int byte4;
typedef unsigned long long ull;

int search_for_mask(FILE* stream, ull* res, const char* mask) {

  char* t_ptr = NULL;
  byte4 mask_bin = strtoul(mask, &t_ptr, 16);
  if (t_ptr != mask + strlen(mask)) {
    return 1;
  }

  byte4 cur_mask = 0;
  byte byte_from_file;
  ull count = 0;
  while (fread(&byte_from_file, sizeof(byte), 1, stream) == 1) {
    cur_mask = cur_mask << 8;
    cur_mask = cur_mask | byte_from_file;

    if (cur_mask == mask_bin) {
      count++;
    }
  }
  *res = count;
  return 0;
}

typedef enum {
  ok,
  inv_argc,
  unknown_file,
  mask_not_ok
} st_code;

byte xor8(FILE* stream) {
  if (!stream) {
    return 0;
  }
  byte res = 0;
  int a;
  while ((a = fgetc(stream)) != EOF) {
    res = a ^ res;
  }

  return res;
}

byte4 xor32(FILE* stream) {
  if (!stream) {
    return 0;
  }

  byte4 res = 0;
  byte4 temp;
  while (fread(&temp, sizeof(byte4), 1, stream) == 1) {
    res = res ^ temp;
  }

  temp = 0;
  byte temp1;
  while (fread(&temp1, sizeof(byte), 1, stream) == 1) {
    temp = temp << 8;
    temp = temp | temp1;
  }
  res = res ^ temp;
  return res;
}



st_code find_func_and_print_result(int argc, char* argv[], FILE* stream) {

  const char* flag = argv[2];

  if (strcmp(flag, "xor8") == 0) {
    if (argc != 3) {
      return inv_argc;
    }
    printf("%d\n", xor8(stream));
  } else if (strcmp(flag, "xor32") == 0) {
    if (argc != 3) {
      return inv_argc;
    }
    printf("%d\n", xor32(stream));
  } else if (strcmp(flag, "mask") == 0) {
    if (argc != 4) {
      return inv_argc;
    }
    ull res;
    if (search_for_mask(stream, &res, argv[3]) == 1) {
      return mask_not_ok;
    }
    printf("%llu\n", res);
  }
  return ok;
}

st_code input(int argc, char* argv[]) {
  if (argc < 3 || argc > 4) {
    return inv_argc;
  }

  FILE* stream = fopen(argv[1], "rb");

  if (stream == NULL) {
    return unknown_file;
  }
  st_code res = find_func_and_print_result(argc, argv, stream);
  fclose(stream);
  return res;
}




int main(int argc, char* argv[]) {
  switch(input(argc, argv)){
    case ok:
      printf("all ok\n");
      break;
    case inv_argc:
      printf("invalid argc\n");
      break;
    case unknown_file:
      printf("unknown file\n");
      break;
    case mask_not_ok:
      printf("mask is unsuitable\n");
      break;
    default:
      printf("unknown status code\n");
  }
  return 0;
}