#ifndef ENTITY_H
# define ENTITY_H

#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <mlx.h>
#include "libft.h"

# define MAX_HEAP 16

typedef struct s_entity	t_entity;

typedef struct s_vtable
{
	void				(*init)(t_entity *self, void *params);
	void				(*update)(t_entity *self);
	void				(*render)(t_entity *self);
}						t_vtable;

typedef enum e_heap_type
{
	HEAP_ENTITY,    // t_entity, recursive delete
	HEAP_MLX_IMAGE, // MLX image, use mlx_destroy_image
	HEAP_MLX_WIN,   // MLX window, use mlx_destroy_window
	HEAP_RAW        // Standard free
}						t_heap_type;

typedef struct s_heap_entry
{
	void *ptr;        // Heap-allocated pointer
	t_heap_type type; // Type for cleanup
}						t_heap_entry;

typedef struct s_heap_list
{
	t_heap_entry		entries[MAX_HEAP];
	int					count;
}						t_heap_list;

typedef struct s_entity
{
	const t_vtable		*vtable;
	t_heap_list			heap;
}						t_entity;

t_entity				*entity_new(size_t size, const t_vtable *vtable,
							void *params);
void					entity_delete(t_entity *entity);
void					entity_add_heap(t_entity *entity, void *ptr,
							t_heap_type type);

#endif