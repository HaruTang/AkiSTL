#ifndef _ALLOC_H
#define _ALLOC_H

#include<cstdlib>

namespace AkiSTL {
	class Alloc {

	public:
		enum EALIGNS
		{
			ALIGN = 8
		};
		enum EMAXBYTES
		{
			MAXBYTES = 128
		};
		enum ENOBJS
		{
			NOBJS = 20
		};
		union obj
		{
			obj*next;
			char client[1];
		};
		static size_t LIST_INDEX(size_t bytes)
		{
			return (bytes - 1) / ALIGN;
		}
		static obj* free_list[16];
		static void *allocate(size_t bytes);
		static void deallocate(void *ptr, size_t oldsize);
		static void *reallocate(void *ptr, size_t oldsize, size_t newsize);
	private:
		static char *free_start;
		static char *free_end;
		static size_t heap_size;

		static size_t ROUND_UP(size_t bytes)
		{
			return (bytes + EALIGNS::ALIGN - 1)&(~(EALIGNS::ALIGN - 1));
		}
		static void *refill(size_t bytes);
		static char *chunk_alloc(size_t bytes, int &nobjs);
		
	};
}

#endif