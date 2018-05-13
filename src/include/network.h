#ifndef __NETWORK_H_
#define __NETWORK_H_

/*! \enum foo
 *
 *  Detailed description
 */
typedef enum 
{
    MATRIX_TYPE_WEIGHT /*!< Description */
} matrix_type_e;
/*! \struct neural_node_t
 *  \brief neural network base data structure
 *
 *  Detailed description
 */
typedef struct neural_node_t
{
    list_node_t node;

    matrix_t wm_hd;
    unsigned short w_num;
} neural_node_t;

/*! \struct layer_t
 *  \brief Brief struct description
 *
 *  Detailed description
 */
typedef struct layer_t
{
    list_node_t node;

    neural_node_t nd_lh;
    unsigned short nodes_cnt;
} layer_t;

#endif
