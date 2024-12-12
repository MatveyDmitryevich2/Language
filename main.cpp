#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

#include "utils.h"
#include "lexical_analysis.h"

int main()
{
    Info_buffer info_buffer = {};
    Read_file_buffer(NAME_FILE_CTOR, &info_buffer);

    Identifiers* array_identifiers = Lexical_analysis(&info_buffer);

    free(array_identifiers);
    return EXIT_SUCCESS;
}