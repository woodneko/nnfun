#ifndef __CFG_H_
#define __CFG_H_

#define NN_MEMORY_STATIC     (0)
#define NN_MEMORY_DYNAMIC    (1)

#define NN_MEMORY_TYPE      NN_MEMORY_STATIC

/*! \enum foo
 *
 *  Detailed description
 */
typedef enum 
{
    NN_LAYER1=0,
    NN_LAYER_TOTAL_NUM 
} layer_size_e;

#define NN_LAYER1_NODES_START   (0) /** use static memory method */
#define NN_LAYER1_NODES_NUM     (4)
#define NN_NODES_TOTAL_NUM      (NN_LAYER1_NODES_NUM) 

#define NN_LAYER1_NODES_WEIGHT_START    (0)
#define NN_LAYER1_ONE_NODES_WEIGHT_MATRIX_NUM      (1)
#define NN_NODES_MATRIX_TOTAL_NUM           (NN_LAYER1_ONE_NODES_WEIGHT_MATRIX_NUM)

#define WEIGHT_MATRIX_COL   (1)
#define WEIGHT_MATRIX_ROW   (2)

#endif
