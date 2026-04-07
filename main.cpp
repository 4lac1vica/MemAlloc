#include <ranges>
#include <stdio.h>
#include <stdint.h>

///Memory Allocator prototype

typedef struct {
    char* memory; ///buffer
    size_t size; ///dimensiunea totala a bufferului
    size_t offset; ///cat s-a folosit din capacitatea totala
}BumpAllocator;

size_t allign8(size_t size) {
    return (size + 7) & ~((size_t)7); /// facem alinierea la 8 bytes, are rolul de a face rotunjirea la urmatorul multiplu de 8
}

void bump_init(BumpAllocator* allocator, size_t size) {
    allocator -> memory = (char*)malloc(size);
    if (allocator -> memory == NULL) {
        printf("Nu a putut fi alocata memorie. Cod eroare 1.");
        exit(1);
    }
    allocator -> size = size;
    allocator -> offset = 0;
}

void bump_destroy(BumpAllocator* allocator) {
    free(allocator -> memory);
    allocator -> memory = NULL;
    allocator -> size = 0;
    allocator -> offset = 0;
}

void* bump_alloc(BumpAllocator* allocator, size_t size) {
    size = allign8(size);

    if (allocator -> offset + size > allocator -> size) {
        return NULL;
    }

    void* ptr = allocator -> memory + allocator -> offset;
    allocator -> offset += size;
    return ptr;
}

void bump_reset(BumpAllocator* allocator) {
    allocator -> offset = 0;
}

int main() {

    BumpAllocator allocator;
    bump_init(&allocator, 1024);

    auto* x = (int*)bump_alloc(&allocator, sizeof(int));
    auto* y = (double*)bump_alloc(&allocator, sizeof(double));

    *x = 10;
    *y = 3.14;

    printf("%d\n", *x);
    printf("%.2f\n", *y);

    bump_reset(&allocator);
    bump_destroy(&allocator);

    return 0;
}
