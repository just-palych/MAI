#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  long index;
  long line;
} char_info;

typedef enum {
  find_ok,
  find_str_inv,
  find_eof,
  find_not_ok,
  find_cnt_inv,
  find_stream_null,
  find_bad_alloc
} find_substr_st;

bool is_equal_s(const char* s1, const char* s2) {
  while (*s1 != '\0' && *s2 != '\0') {
    if (*s1 != *s2) {
      return false;
    }
    s1++;
    s2++;
  }
  if (*s1 != '\0' || *s2 != '\0') {
    return false;
  }
  return true;
}

find_substr_st find_substr_in_file(char_info* info, const char* str, FILE* stream, char_info* ptr_pos) {
  size_t len = strlen(str);
  char* strbuf = (char*) malloc(sizeof(char) * (len + 1));
  if (strbuf == NULL) {
    return find_not_ok;
  }
  strbuf[len] = '\0';
  while (fread(strbuf, sizeof(char), len, stream) == len) {
    fseek(stream, 1 - len, SEEK_CUR);
    ptr_pos->index++;
    if (is_equal_s(str, strbuf)) {
      info->index = ptr_pos->index;
      info->line = ptr_pos->line;
      if (*strbuf == '\n') {
        ptr_pos->line++;
        ptr_pos->index = -1;
      }
      return find_ok;
    }
    if (*strbuf == '\n') {
      ptr_pos->line++;
      ptr_pos->index = -1;
    }
  }
  return find_eof;
}


find_substr_st find_all_substr(const char* str, const char* filename, char_info** substr_indexes) {
  FILE* stream = fopen(filename, "r");
  if (stream == NULL) {
    return find_stream_null;
  }
  *substr_indexes = (char_info*) malloc(sizeof(char_info));
  if (*substr_indexes == NULL) {
    return find_bad_alloc;
  }

  size_t size = 1;
  char_info res_index, cur_index = {.index = -1, .line = 1};
  int rv;
  while ((rv = find_substr_in_file(&res_index, str, stream, &cur_index)) == find_ok) {
    char_info* temp;
    (*substr_indexes)[size - 1] = res_index;
    temp = (char_info*) realloc(*substr_indexes, (++size) * sizeof(char_info));
    if (temp == NULL) {
      free(*substr_indexes);
      substr_indexes = NULL;
      return find_bad_alloc;
    }
    *substr_indexes = temp;
  }
  if (rv == find_not_ok) {
    free(*substr_indexes);
    *substr_indexes = NULL;
    return find_bad_alloc;
  }
  (*substr_indexes)[size - 1].line = -1;
  fclose(stream);
  return find_ok;
}




void erase(char_info** info, size_t cnt) {
  char_info** ptr = info;
  for (int i = 0; i < cnt; i++) {
    free(*ptr);
    ptr++;
  }
  free(info);
}


find_substr_st find_all_substr_in_multiple_files(char_info*** indexes_arr, int count, const char* substr, ...) {
  if(substr[0] == 0) {
    return find_str_inv;
  }
  va_list a;
  if (count == 0) {
    return find_cnt_inv;
  }
  *indexes_arr = (char_info**) malloc(sizeof(char_info*) * count);

  va_start(a, substr);
  for (int i = 0; i < count; i++) {
    char* filename = va_arg(a, char*);
    char_info* indexes;
    int rv = find_all_substr(substr, filename, &indexes);
    if (rv == find_ok) {
      (*indexes_arr)[i] = indexes;
    } else{
      (*indexes_arr)[i] = NULL;
    }
  }
  va_end(a);
  return 0;
}


void print(char_info* const* info, size_t cnt) {
  char_info* const* info_p = info;
  for (int i = 0; i < cnt; i++) {
    char_info const* ptr = *info_p;
    if (ptr == NULL) {
      continue;
    }

    while (ptr->line != -1) {
      printf("substr on %ld line, %ld index\n", ptr->line, ptr->index);
      ptr++;
    }
    info_p++;
    putchar('\n');
  }
}

void print_erase(char_info** info, size_t cnt) {
  print(info, cnt);
  erase(info, cnt);
}

int main() {
  char_info** indexes_arr;
  if (find_all_substr_in_multiple_files(&indexes_arr, 3, "sv", "test.txt", "../test.txt", "test2.txt") == find_ok) {
    print_erase(indexes_arr, 3);
    indexes_arr = NULL;
  } else {
    printf("something went wrong\n");
  }
  return 0;
}