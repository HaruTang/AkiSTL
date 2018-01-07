#include"Alloc.h"

namespace AkiSTL {
	Alloc::obj* Alloc::free_list[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	char *Alloc::free_start = 0;
	char *Alloc::free_end = 0;
	size_t Alloc::heap_size = 0;
	void *Alloc::allocate(size_t bytes)
	{
		if (bytes > MAXBYTES)
		{
			return malloc(bytes);
		}
		obj** my_free_list = free_list + LIST_INDEX(bytes);
		if (*my_free_list)
		{
			obj* list = *my_free_list;
			*my_free_list = list->next;
			return list;
		}
		else
		{
			return refill(Alloc::ROUND_UP(bytes));
		}
	}
	void Alloc::deallocate(void *ptr, size_t bytes)
	{
		if (bytes > MAXBYTES)
			return free(ptr);
		obj**my_free_list = free_list + LIST_INDEX(bytes);
		(*my_free_list)->next = (*my_free_list);
		*my_free_list = (obj*)ptr;
	}
	void *Alloc::reallocate(void *ptr, size_t oldsize, size_t newsize)
	{
		deallocate(ptr, oldsize);
		ptr = allocate(newsize);
		return ptr;//ø…∑Ò÷±Ω”return;
	}
	void *Alloc::refill(size_t bytes)
	{
		return 0;

	}
}