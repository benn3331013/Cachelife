/*
 *  Filename: cachelife.h
 *  Author: Benn3331013
 *  Description: The is the header file for the C implementation of Cachelife. See the README for details of the implementation.
 */

#ifndef CACHELIFE_H
#define CACHELIFE_H
#include <stdlib.h>
#include <stdio.h>
//  uint8,  uint32, ...
#include <stdint.h>
//  size_t
#include <stddef.h>
//  Library handling the big ints. The iterations counter for example.
#include <gmp.h>

//  Since the QuadTreeNode is at least 21 bytes large, and unless you have 20*4.3*10**9 bytes ~ 80 Gb, it will be enough
//  Increasing to u64 will increase the QuadTreeNode size to 41 bytes large. 
typedef uint8_t u8;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int64_t i64;
typedef uint_fast8_t ufast8;



//  uncomment this to replace the alignment optimization by a memory optimization
//  when uncommented, the QuadNodeTree struct will be of size 21, instead of 24. This can impact performance by misaligning the elements in the cache.
#define PACKING

//  This typedef allows to simply change the maximum number of layers. 
//  This shouldn't be a concern, unless you want a particularly big simulation which is massively sparse. In that case : u8 -> u16 (or even u32)
typedef u8 uint_layer;

//  This typedef allows to simply change the size of the index. 
//  As stated above, this should not be a concern, unless you have way more than 80 Gb of RAM.
//  If you do, you can change this from u32 to u64. 
//  Doing so will reduce the maximum number of nodes you can store by doubling their size, but might avoid overflowing if you have too many nodes.
typedef u32 uint_index;

//  An object representing a node of the quadtree
struct quadtree_node {
    uint_layer layer;//  The layer of the node, for a node of size 2**N x 2**N, the layer is N
    uint_index NorthWest_index;// The index, in the cache, of the North-West element of the node  cache[node.layer - 1][NorthWest_index]
    uint_index NorthEast_index;// The index, in the cache, of the North-East element of the node  cache[node.layer - 1][NorthEast_index]
    uint_index SouthWest_index;// The index, in the cache, of the South-West element of the node  cache[node.layer - 1][SouthWest_index]
    uint_index SouthEast_index;// The index, in the cache, of the South-East element of the node  cache[node.layer - 1][NothEast_index]
    uint_index future_index;//    The index, in the cache, of the node corresponding to the next iteration  cache[node.layer + 1][future_index]
} 
#ifdef PACKING 
__attribute__((packed))
#endif
;
typedef struct quadtree_node QuadTreeNode;



//dimensions_cache[i] is the number of nodes of layer i stored in the cache.
extern uint_index* dimensions_cache;
//  The maximum layer contained in the cache, ie : the size of cache[i]
extern uint_layer size_cache;
//  Nodes of layer i are stored in cache[i].
//  cache[i][0] always corresponds to the empty node of layer i.
extern QuadTreeNode** cache;

extern uint_layer root_layer;
extern uint_index root_index;

extern mpz_t iteration_counter;

extern i64 x_minimum;
extern i64 y_minimum;


/*
    \brief Initializes Cachelife. This allocates memory for the cache and creates a few starter nodes.
    \return 0 if the initialization went accordingly. -1 if any error occured.
*/
int InitCachelife(void);
/*
    \brief De-initializes Cachelife. This frees the memory used for the cache.
*/
void QuitCachelife(void);

/*
    \brief Create the zero-nodes up to the layer specified, and store them in the cache.
    \param lay the objective layer. The zero-nodes will be created up to that layer, starting from the current maximum layer of the cache.
*/
void CreateZeros(const uint_layer lay);
/*
    \brief Tell if a node is present in the cache
    \param nod the node to be searched in the cache.
    \return the position of the node if its in the cache, -1 otherwise.
*/
uint_index VerifyCache(QuadTreeNode nod);

/*
    \brief Insert a living cell in the given node, at the given position. This function is used by the "set" functions.
*/
QuadTreeNode InsertLivingCell(QuadTreeNode nod, i64 x, i64 y, uint_layer lay, size_t pow_2);
/*
    \brief Set the initial position for the simulation, from a file.
    \param n_living_cells The number of cells that are alive in the initial configuration. It's also the size of the two next arguments. 
    \param x_positions The x positions of the living cells. 
    \param y_positions The y positions of the living cells.
    \param output_layer the layer of the returned node 
    \return the position, in the cache, of the root node
*/
void CachelifeSet_array(const size_t n_living_cells, i64* x_positions, i64* y_positions);
/*
    \brief Set the initial position for the simulation, from a file.
    \param filename The name of the file containing the initial position. 
    \param returned_layer the layer of the returned node
    \return the position, in the cache, of the root node
*/
void CachelifeSet_file(char* filename);


/*
    \brief Convert a cached node to arrays of x and y coordinates.
    \param nod the index of the node in the cache
    \param lay the layer of the node
    \param x_positions the returned x positions
    \param y_positions the returned y positions
    \return the length of x_positions and y_positions
*/
size_t ArrayFromNode(const uint_layer lay, const uint_index nod, i64** x_positions, i64** y_positions, const i64 x_min, const i64 y_min);


/*
    \brief Join 4 nodes of the same layer to create a node of the next layer.
    \param layer the common layer of all the nodes
    \param a the node to put on the NorthWest of the resulting node.
    \param b the node to put on the NorthEast of the resulting node.
    \param c the node to put on the SouthWest of the resulting node.
    \param d the node to put on the SouthEast of the resulting node.
    \return the index of the node, in the cache.
*/
uint_index Join(const uint_layer lay, const uint_index a, const uint_index b, const uint_index c, const uint_index d);

/*
    \brief Create a new node by surrounding the given node with empty nodes of the same size. 
    \param root the node to surround with empty nodes.
    \return the position, in the cache, of the created node. The layer of the created node is root.layer+1.
*/
uint_index Surround(QuadTreeNode root);

/*
    \brief Try to remove excedent empty nodes and find the smallest non-empty node. 
    \param nod the node you want to reduce the size of.
    \param the layer of the inputted node. Will contain the layer of the outputted node.
    \return the position, in the cache, of the smallest non-empty node. 
    The layer of the returned node is smaller than the one of nod.
*/
uint_index Crop( const QuadTreeNode nod, uint_layer* layer );

/*
    \brief Computes the successor of a 4x4 (layer 2) node.
    The successor is a 2x2 (layer 1) node, corresponding to the 4x4 node, 1 iteration later.
    \param nod The input node.
    \return The position, in the cache of the 
*/
uint_index Next_4x4( const QuadTreeNode nod );

/*
    \brief Computes the successor of a node.
    the successor if a node of layer (input.layer - 1).
    \param lay the layer of the input node.
    \param ind the index, in the cache of the input node.
    \return The index, in the cache, of the node (2**(layer-2)) iterations deep.
*/
uint_index Next( const uint_layer lay, const uint_index ind);

/*
    \brief Runs the hashlife algorithm on the root, with the current cache.
    \param n_iterations_obj The number of iterations. This is a string, as the number of iterations can be bigger than a 128 bits int.
    It's internally converted to a mpz_t.
*/
void Cachelife(char* n_iterations_obj);

/*
    \brief Exports the configuration to a file.
    \param filename The name of the file.
*/
void Export_file(char* filename);
#endif // CACHELIFE