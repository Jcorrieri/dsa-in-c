#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#define DARRAY_INIT_SIZE 10

typedef struct {
    size_t max_size;
    size_t size;
    int *data;
} DynamicArray;


int darray_init(DynamicArray *arr);

int darray_get(const DynamicArray *arr, size_t index, int *out);

int darray_set(DynamicArray *arr, size_t index, int value);

int darray_append(DynamicArray *arr, int val);

int darray_remove(DynamicArray *arr, size_t index, int *out);

void darray_free(DynamicArray *arr);

void print_darray(const DynamicArray *arr);


int main(void) {
    DynamicArray darray;
    if (darray_init(&darray) == -1) {
        return -1;
    }

    for (size_t i = 0; i < 10; i++) {
        darray_append(&darray, i);
    }
    darray_append(&darray, 10);

    print_darray(&darray);

    int second, last, secondToLast;

    darray_get(&darray, 1, &second);
    darray_get(&darray, darray.size - 1, &last);
    darray_get(&darray, darray.size - 2, &secondToLast);

    printf("Second element: %d\n", second);
    printf("Last element: %d\n", last);
    printf("Second to last element: %d\n", secondToLast);

    assert(darray_get(&darray, 11, NULL) == -1);
    assert(darray_get(&darray, -12, NULL) == -1);

    printf("Setting first element to 99...\n");
    darray_set(&darray, 0, 99);
    print_darray(&darray);

    printf("Removing first element...\n");
    darray_remove(&darray, 0, NULL);
    print_darray(&darray);

    printf("Removing second to last element...\n");
    darray_remove(&darray, darray.size - 2, NULL);
    print_darray(&darray);

    darray_free(&darray);
    return 0;
}

int darray_init(DynamicArray *arr) {
    arr->max_size = DARRAY_INIT_SIZE;
    arr->size = 0;
    arr->data = malloc(DARRAY_INIT_SIZE * sizeof(int));

    if (arr->data == NULL) {
        return -1;
    }

    return 0;
}

int darray_get(const DynamicArray *arr, size_t index, int *out) {
    if (index >= arr->size) {
        return -1;
    }
    *out = arr->data[index];
    return 0;
}

int darray_set(DynamicArray *arr, size_t index, int value) {
    if (index >= arr->size) {
        return -1;
    }
    arr->data[index] = value;
    return 0;
}

int darray_append(DynamicArray *arr, int val) {
    if (arr->size >= arr->max_size) {
        int *temp = (int *)reallocarray(arr->data, arr->max_size * 2, sizeof(int));
        if (temp == NULL) {
            return -1;
        }
        arr->data = temp;
        arr->max_size *= 2;
    }
    arr->data[arr->size++] = val;
    return 0;
}

int darray_remove(DynamicArray *arr, size_t index, int *out) {
    if (index >= arr->size) {
        return -1;
    }

    int removed = arr->data[index];
    for (size_t i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;

    if (out != NULL) {
        *out = removed;
    }
    return 0;
}

void darray_free(DynamicArray *arr) {
    free(arr->data);
    arr->data = NULL;
}

void print_darray(const DynamicArray *arr) {
    printf("[");
    for (size_t i = 0; i < arr->size; i++) {
        printf("%d", arr->data[i]);
        if (i != arr->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

