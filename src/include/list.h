#ifndef _LIST_NODE_H_
#define _LIST_NODE_H_

/*! \struct list_node_t
 *  \brief Brief struct description
 *
 *  Detailed description
 */
typedef struct list_node_t
{
    struct list_node_t *prev;
    struct list_node_t *next;
} list_node_t;


/**
 * @brief initialize a list
 *
 * @param l list to be initialized
 */
inline void list_init(list_node_t *l)
{
    l->next = l->prev = l;
}

/**
 * @brief insert a node after a list
 *
 * @param l list to insert it
 * @param n new node to be inserted
 */
inline void list_insert_after(list_node_t *l, list_node_t *n)
{
    l->next->prev = n;
    n->next = l->next;

    l->next = n;
    n->prev = l;
}

/**
 * @brief insert a node before a list
 *
 * @param n new node to be inserted
 * @param l list to insert it
 */
inline void list_insert_before(list_node_t *l, list_node_t *n)
{
    l->prev->next = n;
    n->prev = l->prev;

    l->prev = n;
    n->next = l;
}

/**
 * @brief remove node from list.
 * @param n the node to remove from the list.
 */
inline void list_remove(list_node_t *n)
{
    n->next->prev = n->prev;
    n->prev->next = n->next;

    n->next = n->prev = n;
}

/**
 * @brief tests whether a list is empty
 * @param l the list to test.
 */
inline int list_isempty(const list_node_t *l)
{
    return l->next == l;
}

extern inline void list_init(list_node_t *l);
extern inline void list_insert_after(list_node_t *l, list_node_t *n);
extern inline void list_insert_before(list_node_t *l, list_node_t *n);
extern inline void list_remove(list_node_t *n);
extern inline int list_isempty(const list_node_t *l);

#endif
