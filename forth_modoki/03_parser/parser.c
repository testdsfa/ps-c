#include "clesson.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

enum LexicalType {
    NUMBER,
    SPACE,
    EXECUTABLE_NAME,
    LITERAL_NAME,
    OPEN_CURLY,
    CLOSE_CURLY, 
    END_OF_FILE,
    UNKNOWN
};



struct Token {
    enum LexicalType ltype;
    union {
        int number;
        char onechar;
        char *name;
    } u;
};

#define NAME_SIZE 256

int chk_type_of_(char ch) {
    if (ch == ' ') return SPACE;
    else if (ch == '{') return OPEN_CURLY;
    else if (ch == '}') return CLOSE_CURLY;
    else if (ch == '/') return LITERAL_NAME;
    else if (isalpha(ch) != 0) return EXECUTABLE_NAME;
    else if (isdigit(ch) != 0) return NUMBER;
    else if (ch == EOF) return END_OF_FILE;
    else return UNKNOWN;
}

int parse_one(int prev_ch, struct Token *out_token) {
    /****
     * 
     * TODO: Implement here!
     * 
    ****/
    char tmp_buf[100];
    memset(tmp_buf, 0, 100);
    int cnt=0;
    //int first_type = -1;
    int first_type = -99;
    int skip = 0;

    if (prev_ch != EOF) {
        first_type = chk_type_of_(prev_ch);
	if (first_type != SPACE) tmp_buf[cnt++] = prev_ch;
    }

    char ch;
    do {
        ch = cl_getc();
	int cur_type = chk_type_of_(ch);
	//if (first_type == -1) first_type = cur_type;
	if (first_type == -99) first_type = cur_type;
	//if (cur_type != first_type || (first_type == LITERAL_NAME && cur_type != EXECUTABLE_NAME) ) {
	if (cur_type == first_type || (first_type == LITERAL_NAME && (cur_type == LITERAL_NAME || cur_type == EXECUTABLE_NAME)) ) {
            if (first_type == LITERAL_NAME && cnt == 0 && skip == 0) {
		skip = 1;
	    } else {
	        tmp_buf[cnt++] = ch;
	    }
	} else if (cur_type != first_type) {
	    //break;
	    tmp_buf[cnt++] = '\0';
	    out_token->ltype = first_type;
	    if (out_token->ltype == NUMBER) out_token->u.number = atoi(tmp_buf);
	    else if (out_token->ltype == EXECUTABLE_NAME || out_token->ltype == LITERAL_NAME) out_token->u.name = tmp_buf;
	    else if (out_token->ltype == OPEN_CURLY || out_token->ltype == CLOSE_CURLY) out_token->u.onechar = tmp_buf[0];
	    else {
	    }
	    return ch;
	} 
	/*
	else {
            tmp_buf[cnt++] = ch;
	}
	*/
    } while (ch != EOF);
    //out_token->ltype = UNKNOWN;
    out_token->ltype = END_OF_FILE;
    return EOF;


    /*
    int prev_was_space = 0;
    //int prev_was_char = 0;
    int prev_was_open_curly = 0;
    int prev_was_close_curly = 0;
    int prev_was_name = 0;
    int prev_was_number= 0;
    char _prev_val = prev_ch;
    if (_prev_val != EOF) {
      if (_prev_val == ' ') { 
	      prev_was_space = 1;
      } else if (0 != isdigit(_prev_val)){
	      prev_was_number = 1;
	      tmp_buf[cnt++] = prev_ch;
      } else if (_prev_val == '{'){
	      prev_was_open_curly = 1;
	      tmp_buf[cnt++] = prev_ch;
      } else if (_prev_val == '}'){
	      prev_was_close_curly = 1;
	      tmp_buf[cnt++] = prev_ch;
      } else {
	      prev_was_name = 1;
	      tmp_buf[cnt++] = prev_ch;
      }
    }
    */

    /*
    // body
    int prev_type=-1;
    char ch;
    do {
        ch = cl_getc();
	if (ch == EOF) {
          //if (out_token->ltype == UNKNOWN) {
	  if (prev_was_space == 1) {
            //out_token->ltype = END_OF_FILE;
            out_token->ltype = SPACE;
	  } else if (prev_was_open_curly) {
	    out_token->ltype = OPEN_CURLY;
	    out_token->u.onechar = '{';
	  } else if (prev_was_close_curly) {
	    out_token->ltype = CLOSE_CURLY;
	    out_token->u.onechar = '}';
	  } else if (prev_was_name) {
	    out_token->ltype = EXECUTABLE_NAME;
            out_token->u.name = tmp_buf;
	  } else if (out_token->ltype == NUMBER) {
            out_token->u.number = atoi(tmp_buf);
	  } else if (out_token->ltype == EXECUTABLE_NAME) {
            tmp_buf[cnt++] = '\0';
            out_token->u.name = tmp_buf;
	  } else if (out_token->ltype == LITERAL_NAME) {
            tmp_buf[cnt++] = '\0';
            out_token->u.name = tmp_buf;
	  } else if (out_token->ltype == OPEN_CURLY) {
            tmp_buf[cnt++] = '\0';
            out_token->u.onechar = '{';
	  } else if (out_token->ltype == CLOSE_CURLY) {
            tmp_buf[cnt++] = '\0';
            out_token->u.onechar = '}';
	  //} else if (prev_was_space == 1) {
	  } else if (out_token->ltype == UNKNOWN) {
            //out_token->ltype = SPACE;
            out_token->ltype = END_OF_FILE;
	  }
	  return EOF;
	} else {
	  if (ch == ' ' && prev_was_space) {
	  } else if (ch != ' ' && prev_was_space) {
            out_token->ltype = SPACE;
	  //} else if (ch != ' ') {
	  } else if (0 != isdigit(ch)) {
            tmp_buf[cnt++] = ch;
	    out_token->ltype = NUMBER;
	  } else if (ch == '/' || out_token->ltype == LITERAL_NAME) {
            if (ch != '/') tmp_buf[cnt++] = ch;
            out_token->ltype = LITERAL_NAME;
	  } else if (ch == '{') {
            tmp_buf[cnt++] = ch;
            out_token->ltype = OPEN_CURLY;
	  } else if (ch == '}') {
            tmp_buf[cnt++] = ch;
            out_token->ltype = CLOSE_CURLY;
	  } else {
            tmp_buf[cnt++] = ch;
	    out_token->ltype = EXECUTABLE_NAME;
	  }

	  if (prev_type == -1 ) {
            prev_type = out_token->ltype;
	  } else if (out_token->ltype != prev_type) {
            out_token->ltype = prev_type; 
	    if (out_token->ltype == NUMBER) out_token->u.number = atoi(tmp_buf);
	    return ch;
	  }
          prev_type = out_token->ltype;
	}

    } while (ch != EOF);
    */
    //out_token->ltype = UNKNOWN;
    //return EOF;
}


void parser_print_all() {
    int ch = EOF;
    struct Token token = {
        UNKNOWN,
        {0}
    };

    do {
        ch = parse_one(ch, &token);
        if(token.ltype != UNKNOWN) {
            switch(token.ltype) {
                case NUMBER:
                    printf("num: %d\n", token.u.number);
                    break;
                case SPACE:
                    printf("space!\n");
                    break;
                case OPEN_CURLY:
                    printf("Open curly brace '%c'\n", token.u.onechar);
                    break;
                case CLOSE_CURLY:
                    printf("Close curly brace '%c'\n", token.u.onechar);
                    break;
                case EXECUTABLE_NAME:
                    printf("EXECUTABLE_NAME: %s\n", token.u.name);
                    break;
                case LITERAL_NAME:
                    printf("LITERAL_NAME: %s\n", token.u.name);
                    break;

                default:
                    printf("Unknown type %d\n", token.ltype);
                    break;
            }
        }
    }while(ch != EOF);
}


static void test_parse_one_number() {
    char *input = "123";
    int expect = 123;

    struct Token token = {UNKNOWN, {0}};
    int ch;

    cl_getc_set_src(input);

    ch = parse_one(EOF, &token);

    assert(ch == EOF);
    printf("token.u.number: %d\n", token.u.number);
    printf("token.ltype: %d\n", token.ltype);
    assert(token.ltype == NUMBER);
    assert(expect == token.u.number);
}

static void test_parse_one_empty_should_return_END_OF_FILE() {
    char *input = "";
    int expect = END_OF_FILE;

    struct Token token = {UNKNOWN, {0}};
    int ch;

    cl_getc_set_src(input);
    ch = parse_one(EOF, &token);

    assert(ch == EOF);
    assert(token.ltype == expect);
}

static void test_parse_one_executable_name() {
    char *input = "add";
    char *expect = "add";
    int expect_type = EXECUTABLE_NAME;

    struct Token token = {UNKNOWN, {0}};
    int ch;

    cl_getc_set_src(input);
    ch = parse_one(EOF, &token);

    assert(ch == EOF);
    assert(token.ltype == expect_type);
    printf("token.u.name: %s\n", token.u.name);
    //assert(expect == token.u.name);
    assert(strcmp(expect, token.u.name) == 0);
}

static void test_parse_one_literal_name() {
    char *input = "/add";
    char *expect = "add";
    int expect_type = LITERAL_NAME;

    struct Token token = {UNKNOWN, {0}};
    int ch;

    cl_getc_set_src(input);
    ch = parse_one(EOF, &token);

    printf("%c\n", ch);
    assert(ch == EOF);
    assert(token.ltype == expect_type);
    printf("token.u.name: %s\n", token.u.name);
    assert(strcmp(expect, token.u.name) == 0);
}


static void test_parse_open_curly() {
    char *input = "{";
    char expect = '{';
    int expect_type = OPEN_CURLY;

    struct Token token = {UNKNOWN, {0}};
    int ch;

    cl_getc_set_src(input);
    ch = parse_one(EOF, &token);

    assert(ch == EOF);
    assert(token.ltype == expect_type);
    assert(token.u.onechar == expect);
}


static void test_parse_close_curly() {
    char *input = "}";
    char expect = '}';
    int expect_type = CLOSE_CURLY;

    struct Token token = {UNKNOWN, {0}};
    int ch;

    cl_getc_set_src(input);
    ch = parse_one(EOF, &token);

    assert(ch == EOF);
    assert(token.ltype == expect_type);
    assert(token.u.onechar == expect);
}

void test_parse_one_123_456() {
    char *input = "123 456";
    //char *input = "123 ";
    cl_getc_set_src(input);

    char ch;
    struct Token token = {UNKNOWN, {0}};

    //ch = parse_one('\0', &out_val, &out_type);
    ch = parse_one(EOF, &token);
    assert(ch == ' ');
    assert(token.ltype == NUMBER);
    printf("token.u.number: %d\n", token.u.number);
    assert(token.u.number == 123);

    printf("check1\n");
    ch = parse_one(ch, &token);
    assert(ch == '4');
    assert(token.ltype == SPACE);

    printf("check2\n");
    ch = parse_one(ch, &token);
    assert(ch == EOF);
    assert(token.ltype == NUMBER);
    printf("token.u.number: %d\n", token.u.number);
    assert(token.u.number == 456);
}



static void unit_tests() {
    test_parse_one_number();
    test_parse_one_empty_should_return_END_OF_FILE();
    test_parse_one_executable_name();
    test_parse_one_literal_name();
    test_parse_open_curly();
    test_parse_close_curly();
    /*
    */
/*
*/
    test_parse_one_123_456();
}

int main() {
    unit_tests();

    cl_getc_set_src("123 45 add /some { 2 3 add } def");
    parser_print_all();
    return 0;
}
