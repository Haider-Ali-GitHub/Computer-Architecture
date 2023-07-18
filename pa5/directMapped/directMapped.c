#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// Rutgers University 2021 Spring CS 211 Computer Architecture
// Assignment based on CS:APP Cache Lab

// 64-bit memory address
typedef unsigned long long int mem_addr_t;

// cache properties
unsigned char s = 4; // set index bits
unsigned short S = 1<<4; // set count

unsigned char b = 4; // block offset bits
// unsigned short B = 1<<4; // block size in bytes

// direct mapped cache set/line
typedef struct cache_set_line {
    bool valid;
    mem_addr_t tag;
} cache_set_line_t;

typedef cache_set_line_t* cache_t;

// accessData - Access data at memory address addr.
void accessData (
    mem_addr_t addr,
    cache_t cache,
    unsigned int* hit_count, // If it is already in cache, increase hit_count
    unsigned int* miss_count, // If it is not in cache, bring it in cache, increase miss_count
    unsigned int* eviction_count // Also increase eviction_count if a line is evicted
) {

    // Cache indices for this address
    mem_addr_t set_index = (addr >> b) & (S - 1);
    mem_addr_t tag = addr >> (b + s);
    cache_set_line_t *line = &cache[set_index];

    if (line->valid && line->tag == tag) {
        // Cache hit
        (*hit_count)++;
    } else {
         // If cache set line already in use as indicated by the valid variable, then evict the existing cache set line
        if (line->valid) {
            (*eviction_count)++;
        }
        line->valid = true;
        line->tag = tag;
         // Otherwise, cache miss
        (*miss_count)++;
    }
}

int main(int argc, char* argv[]) {

    // path to memory trace
    if ( argc!= 2 ) {
        printf( "Usage: ./directMapped <mem_trace_file>" );
    }
    char* mem_trace_file = argv[1];
    FILE *fp = fopen(mem_trace_file, "r");
    if (!fp) {
        fprintf(stderr, "Error opening file '%s'\n", mem_trace_file);
        exit( EXIT_FAILURE );
    }

    // Allocate memory, write 0's for valid and tag and LRU
    cache_t cache = (cache_set_line_t*) calloc( S, sizeof(cache_set_line_t) );

    unsigned int hit_count = 0;
    unsigned int miss_count = 0;
    unsigned int eviction_count = 0;
    char buf[256];
    while (fgets(buf, sizeof(buf), fp)) {
        char access_type;
        mem_addr_t addr;
        unsigned int size;
        if (sscanf(buf, " %c %llx,%u", &access_type, &addr, &size) == 3) {
            if (access_type == 'I'){
                 continue;
            }
            
            accessData(addr, cache, &hit_count, &miss_count, &eviction_count);
        
            if (access_type == 'M') {
                accessData(addr, cache, &hit_count, &miss_count, &eviction_count);
            }
        }
    }
    fclose(fp);

    printf("hits:%u misses:%u evictions:%u\n", hit_count, miss_count, eviction_count);

    free(cache);
}
