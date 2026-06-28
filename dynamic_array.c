#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>


#define DARRAY_INIT_SIZE 10

typedef struct {
    size_t max_size;
    size_t size;
    int *data;
} DynamicArray;


bool darray_init(DynamicArray *arr);

bool darray_get(const DynamicArray *arr, size_t index, int *out);

bool darray_set(DynamicArray *arr, size_t index, int value);

bool darray_append(DynamicArray *arr, int val);

bool darray_remove(DynamicArray *arr, size_t index, int *out);

void darray_free(DynamicArray *arr);

void print_darray(const DynamicArray *arr);


int main(void) {
    printf("Hello, World\n");

    DynamicArray dap;
    if (!darray_init(&dap)) {
        return -1;
    }

    for (size_t i = 0; i < 10; i++) {
        darray_append(&dap, i);
    }
    darray_append(&dap, 10);

    print_darray(&dap);

    int second, last, secondToLast;

    darray_get(&dap, 1, &second);
    darray_get(&dap, dap.size - 1, &last);
    darray_get(&dap, dap.size - 2, &secondToLast);

    printf("Second element: %d\n", second);
    printf("Last element: %d\n", last);
    printf("Second to last element: %d\n", secondToLast);

    assert(!darray_get(&dap, 11, NULL));
    assert(!darray_get(&dap, -12, NULL));

    printf("Setting first element to 99...\n");
    darray_set(&dap, 0, 99);
    print_darray(&dap);

    printf("Removing first element...\n");
    darray_remove(&dap, 0, NULL);
    print_darray(&dap);

    printf("Removing second to last element...\n");
    darray_remove(&dap, dap.size - 2, NULL);
    print_darray(&dap);

    darray_free(&dap);
    return 0;
}

bool darray_init(DynamicArray *arr) {
    arr->max_size = DARRAY_INIT_SIZE;
    arr->size = 0;
    arr->data = malloc(DARRAY_INIT_SIZE * sizeof(int));

    if (arr->data == NULL) {
        return false;
    }

    return true;
}

bool darray_get(const DynamicArray *arr, size_t index, int *out) {
    if (index >= arr->size) {
        return false;
    }
    *out = arr->data[index];
    return true;
}

bool darray_set(DynamicArray *arr, size_t index, int value) {
    if (index >= arr->size) {
        return false;
    }
    arr->data[index] = value;
    return true;
}

bool darray_append(DynamicArray *arr, int val) {
    if (arr->size == arr->max_size) {
        int *temp = (int *)reallocarray(arr->data, arr->max_size * 2, sizeof(int));
        if (temp == NULL) {
            return false;
        }
        arr->data = temp;
        arr->max_size *= 2;
    }
    arr->data[arr->size++] = val;
    return true;
}

bool darray_remove(DynamicArray *arr, size_t index, int *out) {
    if (index >= arr->size) {
        return false;
    }

    int removed = arr->data[index];
    for (size_t i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;

    if (out != NULL) {
        *out = removed;
    }
    return true;
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

