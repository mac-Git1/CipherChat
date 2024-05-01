#include "ppmUtil.h"
#include "assert.h"

int main(int argc, char** argv)
{
    FILE* output = fopen(argv[2], "w");
    assert(output != NULL);
    FILE* input = fopen(argv[1], "r");
    assert(input!=NULL);

    header_t header; 
    pixel_t *pix;

    /*Call read then write*/

    pix = read(input, &header);
    write(output, header, pix);

    /*Clean up*/
    freeMemory(pix);
    fclose(output);
    fclose(input);
    
    return 0; 

}

