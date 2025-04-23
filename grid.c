#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

// Creates an example grid with predefined values
Grid* create_example_grid() {
    Grid* grid = (Grid*)malloc(sizeof(Grid));
    if (!grid) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Initialize grid metadata
    grid->x_min = 0.0;
    grid->x_max = 10.0;
    grid->y_min = 0.0;
    grid->y_max = 10.0;
    grid->x_size = 11;
    grid->y_size = 11;
    grid->x_step = (grid->x_max - grid->x_min) / (grid->x_size - 1);
    grid->y_step = (grid->y_max - grid->y_min) / (grid->y_size - 1);
    grid->z_min = 0.0;
    grid->z_max = 1.0;
    grid->blank_value = GRID_DEFAULT_BLANK_VALUE;

    // Allocate memory for the data array
    grid->data = (double*)malloc(grid->x_size * grid->y_size * sizeof(double));
    if (!grid->data) {
        fprintf(stderr, "Memory allocation for data array failed\n");
        free(grid);
        return NULL;
    }

    // Initialize the data array with sequential values
    for (int i = 0; i < grid->x_size * grid->y_size; i++) {
        grid->data[i] = i;
    }

    // Calculate Z min and max values
    calculate_z_min_max(grid);

    return grid;
}

// Frees all memory associated with the grid
void free_grid(Grid* grid) {
    if (grid) {
        free(grid->data);
        free(grid);
    }
}

// Retrieves the value at a specific (x, y) position
double get_xy_value(Grid* grid, int x, int y) {
    if (!grid) {
        fprintf(stderr, "Grid is NULL\n");
        return GRID_DEFAULT_BLANK_VALUE;
    }
    if (x < 0 || x >= grid->x_size || y < 0 || y >= grid->y_size) {
        fprintf(stderr, "Index out of bounds\n");
        return grid->blank_value;
    }
    return grid->data[y * grid->x_size + x];
}

// Sets the value at a specific (x, y) position
void set_xy_value(Grid* grid, int x, int y, double value) {
    if (!grid) {
        fprintf(stderr, "Grid is NULL\n");
        return;
    }
    if (x < 0 || x >= grid->x_size || y < 0 || y >= grid->y_size) {
        fprintf(stderr, "Index out of bounds\n");
        return;
    }
    grid->data[y * grid->x_size + x] = value;
}

// Updates the minimum X-coordinate and recalculates the step size
void set_grid_x_min(Grid* grid, double x_min) {
    if (!grid) {
        fprintf(stderr, "Grid is NULL\n");
        return;
    }
    grid->x_min = x_min;
    grid->x_step = (grid->x_max - grid->x_min) / (grid->x_size - 1);
}

// Updates the maximum X-coordinate and recalculates the step size
void set_grid_x_max(Grid* grid, double x_max) {
    if (!grid) {
        fprintf(stderr, "Grid is NULL\n");
        return;
    }
    grid->x_max = x_max;
    grid->x_step = (grid->x_max - grid->x_min) / (grid->x_size - 1);
}

// Updates the minimum Y-coordinate and recalculates the step size
void set_grid_y_min(Grid* grid, double y_min) {
    if (!grid) {
        fprintf(stderr, "Grid is NULL\n");
        return;
    }
    grid->y_min = y_min;
    grid->y_step = (grid->y_max - grid->y_min) / (grid->y_size - 1);
}

// Updates the maximum Y-coordinate and recalculates the step size
void set_grid_y_max(Grid* grid, double y_max) {
    if (!grid) {
        fprintf(stderr, "Grid is NULL\n");
        return;
    }
    grid->y_max = y_max;
    grid->y_step = (grid->y_max - grid->y_min) / (grid->y_size - 1);
}

// Calculates and updates the minimum and maximum Z-values
void calculate_z_min_max(Grid* grid) {
    grid->z_min = GRID_DEFAULT_Z_MIN;
    grid->z_max = GRID_DEFAULT_Z_MAX;
    for (int i = 0; i < grid->x_size * grid->y_size; i++) {
        if (grid->data[i] != grid->blank_value) {
            if (grid->data[i] < grid->z_min) {
                grid->z_min = grid->data[i];
            }
            if (grid->data[i] > grid->z_max) {
                grid->z_max = grid->data[i];
            }
        }
    }

    // Handle the case where all values are blank_value
    if (grid->z_min == __DBL_MAX__ || grid->z_max == -__DBL_MAX__) {
        grid->z_min = grid->blank_value;
        grid->z_max = grid->blank_value;
    }
}

// Prints metadata information about the grid
void print_grid_info(Grid* grid) {
    if (!grid) {
        fprintf(stderr, "Grid is NULL\n");
        return;
    }
    printf("Grid Information:\n");
    printf("X Min: %f, X Max: %f\n", grid->x_min, grid->x_max);
    printf("Y Min: %f, Y Max: %f\n", grid->y_min, grid->y_max);
    printf("X Size: %d, Y Size: %d\n", grid->x_size, grid->y_size);
    printf("X Step: %f, Y Step: %f\n", grid->x_step, grid->y_step);
    printf("Z Min: %f, Z Max: %f\n", grid->z_min, grid->z_max);
    printf("Blank Value: %f\n", grid->blank_value);
}

// Prints the grid data in a human-readable format
void print_grid_data(Grid* grid) {
    if (!grid) {
        fprintf(stderr, "Grid is NULL\n");
        return;
    }
    printf("Grid Data:\n");
    for (int y = 0; y < grid->y_size; y++) {
        for (int x = 0; x < grid->x_size; x++) {
            printf("%6.2f ", grid->data[y * grid->x_size + x]);
        }
        printf("\n");
    }
}

// Reads a grid from a Surfer 6 binary file
Grid* read_surfer_grid_6bin(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return NULL;
    }

    Grid* grid = (Grid*)malloc(sizeof(Grid));
    if (!grid) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }
    grid->blank_value = GRID_DEFAULT_BLANK_VALUE;
    fseek(file, 4, SEEK_CUR); // Skip 4 bytes
    short temp_sh;
    fread(&temp_sh, sizeof(short), 1, file); // Read n_x
    grid->x_size = temp_sh;
    fread(&temp_sh, sizeof(short), 1, file); // Read n_y
    grid->y_size = temp_sh;

    fread(&grid->x_min, sizeof(double), 1, file);
    fread(&grid->x_max, sizeof(double), 1, file);
    fread(&grid->y_min, sizeof(double), 1, file);
    fread(&grid->y_max, sizeof(double), 1, file);
    fread(&grid->z_min, sizeof(double), 1, file);
    fread(&grid->z_max, sizeof(double), 1, file);

    grid->x_step = (grid->x_max - grid->x_min) / (grid->x_size - 1);
    grid->y_step = (grid->y_max - grid->y_min) / (grid->y_size - 1);

    grid->data = (double*)malloc(grid->x_size * grid->y_size * sizeof(double));
    if (!grid->data) {
        fprintf(stderr, "Memory allocation for data array failed\n");
        free(grid);
        fclose(file);
        return NULL;
    }

    float temp_fl;
    for (int i = 0; i < grid->x_size * grid->y_size; ++i) {
        fread(&temp_fl, sizeof(float), 1, file);
        grid->data[i] = temp_fl;
    }

    fclose(file);
    return grid;
}

// Writes a grid to a Surfer 6 binary file
void write_surfer_grid_6bin(const char* filename, Grid* grid) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filename);
        return;
    }
    
    fwrite("DSBB", sizeof(char), 4, file);
    short n_x = grid->x_size;
    short n_y = grid->y_size;

    fwrite(&n_x, sizeof(short), 1, file);
    fwrite(&n_y, sizeof(short), 1, file);
    fwrite(&grid->x_min, sizeof(double), 1, file);
    fwrite(&grid->x_max, sizeof(double), 1, file);
    fwrite(&grid->y_min, sizeof(double), 1, file);
    fwrite(&grid->y_max, sizeof(double), 1, file);
    fwrite(&grid->z_min, sizeof(double), 1, file);
    fwrite(&grid->z_max, sizeof(double), 1, file);

    for (int i = 0; i < grid->x_size * grid->y_size; ++i) {
        float temp_fl = (float)grid->data[i];
        fwrite(&temp_fl, sizeof(float), 1, file);
    }

    fclose(file);
}