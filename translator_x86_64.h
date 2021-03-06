#include <string.h>
#include <time.h>
#include "linker.h"
#include "My_Headers/txt_files.h"
#include "My_Headers/elf_maker.h"

enum MODES {TEXT = 's', BINARY = 0};

/**
 *Contains binary and text representation for single x86_64 intstruction.
 **/
class Command_x86_64
{
private:
    char*     _body;
    size_t    _size;
    MODES     _mode;

    void make_label(int pc, char* label);
    void get_args(char* operand, int* buff, int nargs);
    void match_reg(int code, char* reg);
    int translate_text(char* src, int pc);
    int translate_bin(char* src, int pc);

public:
    const static int STDIN_POS  = 0;
    const static int STDOUT_POS = 1;

    Command_x86_64(MODES mode);
    int translate_cmd(char* src, int pc, size_t offsets[]);
    char* get_body();
    size_t get_size();
    void dump(FILE* log_fp);
    ~Command_x86_64();
};

int check_source(char* buffer);

size_t make_prologue(char* dst, MODES mode, size_t offsets[]);

void make_epilogue(char* dst, MODES mode);

char* translate(const char* bin_file, MODES mode, size_t* res_size);

void patch_on_byte(char* src, int pc, char* dst, size_t offsets[], size_t instr_sz, int byte_pos);

void patch(char* src, int pc, size_t src_size, char* dst, size_t offsets[]);

void plain_print(const char* filename, const char* text);

void make_elf(const char* filename, const char* body);
