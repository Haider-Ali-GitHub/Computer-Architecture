#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Markers used to bound trace regions of interest */
volatile char MARKER_START, MARKER_END;




int main(int argc, char* argv[])
{
    const size_t BLOCK_SIZE = 16;

    const size_t TILE_SIZE = 4;
    /* Record marker addresses */
    FILE* marker_fp = fopen(".marker","w");
    assert(marker_fp);
    fprintf(marker_fp, "%llx\n%llx",
        (unsigned long long int) &MARKER_START,
        (unsigned long long int) &MARKER_END );
    fclose(marker_fp);

    if (argc!=3) {
        printf("Usage: ./cacheBlocking <matrix_a_file> <matrix_b_file>\n");
        exit(EXIT_FAILURE);
    }

    FILE* matrix_a_fp = fopen(argv[1], "r");
    if (!matrix_a_fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    size_t n;
    int ret = fscanf(matrix_a_fp, "%ld\n", &n);
    assert (ret==1);
    int* a = calloc( n*n, sizeof(int) );
    for ( size_t i=0; i<n; i++ ) {
        for ( size_t k=0; k<n; k++ ) {
            ret = fscanf(matrix_a_fp, "%d ", &a[i*n+k]);
            assert (ret==1);
        }
        ret = fscanf(matrix_a_fp, "\n");
    }
    fclose(matrix_a_fp);

    FILE* matrix_b_fp = fopen(argv[2], "r");
    if (!matrix_b_fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    size_t m;
    ret = fscanf(matrix_b_fp, "%ld\n", &m);
    assert (ret==1);
    assert( n==m );
    int* b = calloc( n*n, sizeof(int) );
    for ( size_t k=0; k<n; k++ ) {
        for ( size_t j=0; j<n; j++ ) {
            ret = fscanf(matrix_b_fp, "%d ", &b[k*n+j]);
            assert (ret==1);
        }
        ret = fscanf(matrix_b_fp, "\n");
    }
    fclose(matrix_b_fp);

    int* c = calloc( n*n, sizeof(int) );
    MARKER_START = 211;

    // kij
    // for ( size_t k=0; k<n; k++ ) {
    //     for ( size_t i=0; i<n; i++ ) {
    //         int r = a[i*n+k];
    //         for ( size_t j=0; j<n; j++ ) {
    //             c[i*n+j] += r * b[k*n+j];
    //         }
    //     }
    // }


    for (size_t i = 0; i < n; i += BLOCK_SIZE) {
        for (size_t j = 0; j < n; j += BLOCK_SIZE) {
            for (size_t k = 0; k < n; k += BLOCK_SIZE) {
                for (size_t i_tile = i; i_tile < i + BLOCK_SIZE && i_tile < n; i_tile += TILE_SIZE) {
                    for (size_t j_tile = j; j_tile < j + BLOCK_SIZE && j_tile < n; j_tile += TILE_SIZE) {
                        for (size_t k_tile = k; k_tile < k + BLOCK_SIZE && k_tile < n; k_tile += TILE_SIZE) {
                            for (size_t ii = i_tile; ii < i_tile + TILE_SIZE && ii < n; ii++) {
                                for (size_t kk = k_tile; kk < k_tile + TILE_SIZE && kk < n; kk++) {
                                    int r = a[ii * n + kk];
                                    for (size_t jj = j_tile; jj < j_tile + TILE_SIZE && jj < n; jj++) {
                                        c[ii * n + jj] += r * b[kk * n + jj];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // ijk
    // for ( size_t i=0; i<n; i++ ) {
    //     for ( size_t j=0; j<n; j++ ) {
    //         int sum = c[i*n+j];
    //         for ( size_t k=0; k<n; k++ ) {
    //             sum += a[i*n+k] * b[k*n+j];
    //         }
    //         c[i*n+j] = sum;
    //     }
    // }

    // jki
    // for ( size_t j=0; j<n; j++ ) {
    //     for ( size_t k=0; k<n; k++ ) {
    //         int r = b[k*n+j];
    //         for ( size_t i=0; i<n; i++ ) {
    //             c[i*n+j] += a[i*n+k] * r;
    //         }
    //     }
    // }
    
    MARKER_END = 211;

    for ( size_t i=0; i<n; i++ ) {
        for ( size_t j=0; j<n; j++ ) {
            printf( "%d ", c[i*n+j] );
        }
        printf( "\n" );
    }

    free(c);
    free(b);
    free(a);
    exit(EXIT_SUCCESS);

}
