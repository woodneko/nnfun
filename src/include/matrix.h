#ifndef __MATRIX_H_
#define __MATRIX_H_

/*! \struct matrix_t
 *  \brief matrix data
 *
 *  Detailed description
 */
typedef struct matrix_t
{
    list_node_t node;

    float *data;
    unsigned short col;
    unsigned short row;
} matrix_t;
#endif
