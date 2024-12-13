#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "utils.h"
#include "RLE.h"
#include "lexical_analysis.h"
#include "dump.h"

int main()
{
    Write_html_mode(Dump_html_BEGIN);
    Info_buffer info_buffer = {};
    Read_file_buffer(NAME_FILE_CTOR, &info_buffer);

    Identifiers* array_identifiers = Lexical_analysis(&info_buffer);

    Node* node = GetG(array_identifiers);
    Dump_grapviz(node);

    free(array_identifiers);
    Write_html_mode(Dump_html_END);
    return EXIT_SUCCESS;
}