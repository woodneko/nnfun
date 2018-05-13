#include <stdio.h>
#include <string.h>
#include "cfg.h"
#include "list.h"
#include "matrix.h"
#include "network.h"

#if (NN_MEMORY_TYPE == NN_MEMORY_DYNAMIC)
#include <stdlib.h>

static layer_t *layer = NULL; 
static neural_node_t *nodes = NULL; 

#else
static layer_t layer_hd = {0}; 
static layer_t layer[NN_LAYER_TOTAL_NUM] = {0}; 
static neural_node_t nodes[NN_NODES_TOTAL_NUM] = {0}; 
static matrix_t wmatrix[NN_LAYER1_ONE_NODES_WEIGHT_MATRIX_NUM] = {0};
static float weight_data[NN_LAYER_TOTAL_NUM*NN_NODES_TOTAL_NUM*NN_LAYER1_ONE_NODES_WEIGHT_MATRIX_NUM*WEIGHT_MATRIX_COL*WEIGHT_MATRIX_ROW] = {0};
#endif

void test_setlayer()
{
    int i;

    for(i = 0; i < sizeof(weight_data)/sizeof(float); i++)
    {
        weight_data[i] = i;
    }
}

void print_matrix(matrix_t *m)
{
    int col = 0;
    int row = 0;

    if ( NULL == m ) 
    {
        return ;
    }
    
    for(row = 0; row < m->row; row++)
    {
        for(col = 0; col < m->col; col++)
        {
            printf("%f ", m->data[row+col]);
        }
        
        printf("\r\n");
    }

}

void print_weight_matrix(neural_node_t *nd)
{
    int i;
    matrix_t *mtmp = NULL;

    if ( NULL == nd ) 
    {
        return ;
    }

    mtmp = &nd->wm_hd;
    for(i = 0; i < nd->w_num ; i++)
    {
        mtmp = (matrix_t *)mtmp->node.next;
        print_matrix(mtmp);
    }
}

void print_nodes(layer_t *ly)
{
    int i;
    neural_node_t *ntmp = NULL;

    if ( NULL == ly ) 
    {
        return ;
    }

    ntmp = &ly->nd_lh;
    for(i = 0; i < ly->nodes_cnt; i++)
    {
        ntmp = (neural_node_t *)ntmp->node.next;
        print_weight_matrix(ntmp);
    }
}

void print_layer(unsigned short layer_index)
{
    int i;
    layer_t *ltmp = &layer_hd; 

    if ( layer_index >= NN_LAYER_TOTAL_NUM ) 
    {
        return ;
    }

    for(i = 0; i < layer_index ; i++)
    {
        ltmp = (layer_t *)ltmp->node.next;
    }

    print_nodes(ltmp);
}

void print_network()
{
    int i;

    for(i = 0; i < NN_LAYER_TOTAL_NUM; i++)
    {
        print_layer(i);
    }
}

int set_network_data(unsigned short layer_index, unsigned short nodes_index, unsigned short mindex, matrix_t const *matrix, matrix_type_e type)
{
    int i;
    layer_t *ltmp = &layer_hd;
    neural_node_t *ntmp = NULL;
    matrix_t *mtmp = NULL;

    if ( layer_index >= NN_LAYER_TOTAL_NUM ) 
    {
        return -1;
    }

    for(i = 0; i < layer_index; i++)
    {
        ltmp = (layer_t *)ltmp->node.next;
    }

    if ( nodes_index > ltmp->nodes_cnt ) 
    {
        return -1;
    }

    ntmp = &ltmp->nd_lh;

    for(i = 0; i < nodes_index; i++)
    {
        ntmp = (neural_node_t *)ntmp->node.next;
    }
    
    switch (type) 
    {
        case MATRIX_TYPE_WEIGHT:
            if ( mindex > ntmp->w_num ) 
            {
                return -1;
            }

            mtmp = &ntmp->wm_hd;
            for(i = 0; i < mindex; i++)
            {
                mtmp = (matrix_t *)mtmp->node.next;
            }

            if ( mtmp->col == matrix->col 
                    && mtmp->row == matrix->row ) 
            {
                memcpy(mtmp->data, matrix->data, sizeof(float)*matrix->col*matrix->row);
            }
            else 
            {
                return -1;
            }
            
            break;
        default:
            return -1;
    }

    return 0;
}

matrix_t *get_network_data(unsigned short layer_index, unsigned short nodes_index, unsigned short mindex, matrix_type_e type)
{
    int i;
    layer_t *ltmp = &layer_hd;
    neural_node_t *ntmp = NULL;
    matrix_t *mtmp = NULL;

    if ( layer_index >= NN_LAYER_TOTAL_NUM) 
    {
        return NULL;
    }

    for(i = 0; i < layer_index; i++)
    {
        ltmp = (layer_t *)ltmp->node.next;
    }

    if ( nodes_index > ltmp->nodes_cnt ) 
    {
        return NULL;
    }

    ntmp = &ltmp->nd_lh;

    for(i = 0; i < nodes_index; i++)
    {
        ntmp = (neural_node_t *)ntmp->node.next;
    }
    
    switch (type) 
    {
        case MATRIX_TYPE_WEIGHT:
            if ( mindex > ntmp->w_num ) 
            {
                return NULL;
            }

            mtmp = &ntmp->wm_hd;
            for(i = 0; i < mindex; i++)
            {
                mtmp = (matrix_t *)mtmp->node.next;
            }

            return mtmp;
            
        default:
            return NULL;
    }

    return NULL;
}

void network_layer1_init()
{
    int i,j;

    list_init(&layer[NN_LAYER1].node);
    list_init(&layer[NN_LAYER1].nd_lh.node);
    list_insert_before(&layer_hd.node, &layer[NN_LAYER1].node);
    for(i = NN_LAYER1_NODES_START; i < NN_NODES_TOTAL_NUM; i++)
    {
        list_init(&nodes[i].node);
        for(j = NN_LAYER1_NODES_WEIGHT_START; j < NN_LAYER1_ONE_NODES_WEIGHT_MATRIX_NUM; j++)
        {
            wmatrix[j].col = WEIGHT_MATRIX_COL;
            wmatrix[j].row = WEIGHT_MATRIX_ROW;
            wmatrix[j].data = &weight_data[i*j*WEIGHT_MATRIX_COL*WEIGHT_MATRIX_ROW];
            nodes[i].w_num ++;
            list_insert_before(&nodes[i].wm_hd.node, &wmatrix[j].node);
        }

        list_insert_before(&layer[NN_LAYER1].nd_lh.node, &nodes[i].node);
        layer[NN_LAYER1].nodes_cnt ++;
    }
}

int init_global_network_data()
{
#if (NN_MEMORY_TYPE == NN_MEMORY_DYNAMIC)

#else
    list_init(&layer_hd.node);
    network_layer1_init();
    test_setlayer();
    print_network();

#endif
    return 0;
}
