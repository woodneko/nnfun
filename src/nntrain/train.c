#include <stdio.h>
#include <string.h>
#include "data.h"

#define  NNTRAIN_DATA_COL   2
#define  NNTRAIN_DATA_ROW   200

#if ( NN_MEMORY_TYPE == NN_MEMORY_DYNAMIC)
#include <stdlib.h>
#endif

data_set_t input = {0};

void load_input_data()
{
    input.data.col  = NNTRAIN_DATA_COL;  
    input.data.row  = NNTRAIN_DATA_ROW;  
#if ( NN_MEMORY_TYPE == NN_MEMORY_DYNAMIC)
    input.data.data = (float *)malloc(sizeof(float)*input.data.col*input.data.row);
#else
    input.data.data = input_train_data;
#endif

    /** set data, generate from python scripts*/
    set_training_data(&input);

}

void build_layer(layer_t *l)
{
    neural_node_t *ntmp = NULL;

    if ( NULL == l ) 
    {
        return ;
    }

    ntmp = (neural_node_t *)l->nd_lh.next;

}

void build_layer()
{
    int i, j;
    layer_t *ltmp = NULL;

    for(i = 0; i < NN_LAYER_TOTAL_NUM; i++)
    {
        ltmp = get_layer(i);
        if ( NULL == ltmp ) 
        {
            printf("get layer%d error\r\n", i)
            return ;
        }

        build_nodes(ltmp);
    }
}

int main(int argc, char *argv[])
{
    /** set up input data */
    load_input_data();

    if ( -1 == init_global_network_data() ) 
    {
        printf("init settinf failed");
        return -1;
    }
    
    /** do training process */

    /** write result to file */
    
    return 0;
}
