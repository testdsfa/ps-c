#include "clesson.h"
#include <assert.h>
#include <stdlib.h>

enum token_type {
    NUMBER,
    SPACE
};


char parse_one(char prev_val, int *out_val, int *out_type) {
    char tmp_buf[100];
    int cnt=0;
    //enum token_type result_type;
    // skip space
    int prev_was_space = 0;
    int prev_was_char = 0;
    char _prev_val = prev_val;
    if (_prev_val != '\0') {
      if (_prev_val == ' ') { 
	      prev_was_space = 1;
      } else {
	      prev_was_char = 1;
	      tmp_buf[cnt++] = prev_val;
      }
    }

    // body
    char ch;
    do {
        ch = cl_getc();
	if (ch == ' ' && prev_was_space) {
	} else if (ch != EOF && ch != ' ' && prev_was_space) {
          *out_val = ' ';
          *out_type = SPACE;
          return ch;
	} else if (ch != EOF && ch != ' ') {
          tmp_buf[cnt++] = ch;
	} else {
          *out_val = atoi(tmp_buf);
	  *out_type = NUMBER;
          return ch;
	}
    } while (ch != EOF);
}

/*
cc cl_getc.c int_parser_getc.c
*/

void test_parse_one_123() {
    char *input = "123";
    int expected = 123;
    cl_getc_set_src(input);
    char ch;
    int out_val;
    int out_type;
    ch = parse_one('\0', &out_val, &out_type);
    assert(ch == EOF);
    assert(out_type == NUMBER);
    assert(out_val == 123);
    //printf("test_parse_one_123 succeeded!\n");
    //fflush(stdout);
}


void test_parse_one_123_456() {
    char *input = "123 456";
    cl_getc_set_src(input);

    char ch;
    int out_val;
    int out_type;

    ch = parse_one('\0', &out_val, &out_type);
    assert(ch == ' ');
    assert(out_type == NUMBER);
    assert(out_val == 123);

    ch = parse_one(ch, &out_val, &out_type);
    assert(ch == '4');
    assert(out_type == SPACE);
    assert(out_val == ' ');

    ch = parse_one(ch, &out_val, &out_type);
    assert(ch == EOF);
    assert(out_type == NUMBER);
    assert(out_val == 456);
}


int main() {
    int answer1 = 0;
    int answer2 = 0;

    // write something here.
    
    //print_input();
    test_parse_one_123();
    //cl_getc_set_src("123 456");
    //print_input();
    test_parse_one_123_456();
    cl_getc_set_src("123 456");
    char tmp_ch = EOF;
    int tmp_val;
    int tmp_type;
    tmp_ch= parse_one('\0', &answer1, &tmp_type);
    tmp_ch= parse_one(tmp_ch, &tmp_val, &tmp_type);
    tmp_ch= parse_one(tmp_ch, &answer2, &tmp_type);

    // sample for cl_getc() usage.
    /*
    int c;

    while((c = cl_getc()) != EOF) {
        printf("%c\n",c );
    }
    */

    // verity result.
    assert(answer1 == 123);
    assert(answer2 == 456);

    return 0;


}
