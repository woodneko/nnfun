#include <stdio.h>
#include <string.h>
#include "data.h"

#if ( NN_MEMORY_TYPE == NN_MEMORY_DYNAMIC)
#include <stdlib.h>
#endif

int main(int argc, char *argv[])
{
    if ( -1 == init_global_network_data() ) 
    {
        printf("init settinf failed");
        return -1;
    }
    
    /** do training process */

    /** write result to file */
    
    return 0;
}
