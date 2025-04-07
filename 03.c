// Usage: in_file out_file [bsort|bsort_mt|qsort]
// Takes the in_file, sorts lines in alphabetic order
// and puts non-empty ones in out_file

// Adapted from:
// https://github.com/pk399/ded-huawei-course-2023/
// 2. Eugene Onegin/text5.cpp

#include <stdlib.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "bsort.h"
#include "bsort_mt.h"

struct text {
    char* chars;
    size_t nchars;
    char** lines;
    size_t nlines;
};


int _file_size(size_t* sz, const char* path)
{
    struct stat stats_buf = {};

    if (stat(path, &stats_buf))
        return -1;

    *sz = stats_buf.st_size;

    return 0;
}


void _find_lines(struct text* txt)
{
    txt->lines[0] = txt->chars;

    size_t nline = 1;
    for (size_t i = 0; i < txt->nchars; i++)
        if (txt->chars[i] == '\n')
        {
            txt->chars[i] = '\0';
            txt->lines[nline++] = txt->chars + i + 1;
        }

    txt->nlines = nline;
}


int text_ctor(struct text* txt, const char* path)
{
    size_t sz = 0;
    if (_file_size(&sz, path)) return -1;

    sz++;
    txt->nchars = sz;
    txt->chars = (char*) calloc(sz, sizeof(char));
    if (!txt->chars) return -1;


    FILE* file = fopen(path, "rb");
    if (!file) return -1;
    size_t sz_read = fread(txt->chars, sizeof(char), sz, file);
    fclose(file);

    size_t max_lines = sz; // Just to be sure
    txt->lines = (char**) calloc(max_lines, sizeof(char*));
    if (!txt->lines) return -1;
    _find_lines(txt);

    return 0;
}


bool has_printable(const char* str)
{
    for (size_t i = 0; str[i]; i++)
        if (!isspace(str[i]))
            return true;

    return false;
}

void text_dtor(struct text* txt)
{
    free(txt->chars);
    txt->chars = 0;
    txt->nchars = 0;

    free(txt->lines);
    txt->lines = 0;
    txt->nlines = 0;
}

int text_write(const struct text* txt, const char* path)
{
    FILE* file = fopen(path, "wt");

    if ( file == NULL ) return -1;

    for (int i = 0; i < txt->nlines; i++)
    {
        char* ptr = txt->lines[i];
        if ( has_printable(ptr) )
        {
            fwrite(ptr, sizeof(char), strlen(ptr), file);
            fputc('\n', file);
        }
    }

    fclose(file);

    return 0;
}

int line_cmp(const void* a_void, const void* b_void)
{
    char* a = *((char**) a_void);
    char* b = *((char**) b_void);

    size_t i = 0, j = 0;
    for (; a[i] && b[j]; i++, j++)
    {
        while ( isspace(a[i]) && a[i] ) i++;
        while ( isspace(b[j]) && b[j] ) j++;

        if ( tolower(a[i]) > tolower(b[j]) )
            return 1;
        else if ( tolower(a[i]) < tolower(b[j]) )
            return -1;
    }

    return a[i] == b[j] ? 0 : ( a[i] == 0 ? 1 : -1 );
}

int main(int argc, char** argv)
{
    if (argc != 4 ||
            (
            strcmp(argv[3], "bsort")    &&
            strcmp(argv[3], "bsort_mt") &&
            strcmp(argv[3], "qsort")
            )
       )
    {
        printf("Usage: in_file out_file [bsort|bsort_mt|qsort]\n");
        return 1;
    }

    struct text txt = {};
    if ( text_ctor(&txt, argv[1]) )
    {
        printf("Failed to read in_file\n");
        return 1;
    }

    if ( !strcmp(argv[3], "bsort") )
    {
        bsort(txt.lines, txt.nlines, sizeof(char**), &line_cmp);
    }
    else if ( !strcmp(argv[3], "bsort_mt") )
    {
        bsort_mt(txt.lines, txt.nlines, sizeof(char**), &line_cmp);
    }
    else
    {
        qsort(txt.lines, txt.nlines, sizeof(char**), &line_cmp);
    }

    text_write(&txt, argv[2]);

    text_dtor(&txt);
}
