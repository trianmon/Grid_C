#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

int main() {
    // Example 1: Read a grid from a Surfer 6 binary file
    const char* input_file = "examples/example_input.grd";
    Grid* file_grid = read_surfer_grid_6bin(input_file);
    if (!file_grid) {
        fprintf(stderr, "Failed to read grid from file: %s\n", input_file);
    } else {
        printf("Grid read from file:\n");
        print_grid_info(file_grid);
        printf("\nGrid Data from file:\n");
        print_grid_data(file_grid);

        // Modify a specific value in the file grid
        set_xy_value(file_grid, 3, 3, 42.0);
        printf("\nUpdated Grid Value at (3, 3): %6.2f\n", get_xy_value(file_grid, 3, 3));

        // Write the modified grid to a new file
        const char* output_file = "examples/example_output.grd";
        write_surfer_grid_6bin(output_file, file_grid);
        printf("\nModified grid written to file: %s\n", output_file);

        // Free the file grid
        free_grid(file_grid);
    }

    // Example 2: Create an example grid programmatically
    Grid* example_grid = create_example_grid();
    if (!example_grid) {
        fprintf(stderr, "Failed to create example grid\n");
        return 1; // Exit if grid creation failed
    }

    printf("\nExample Grid Information:\n");
    print_grid_info(example_grid);

    printf("\nExample Grid Data:\n");
    print_grid_data(example_grid);

    // Modify a specific value in the example grid
    set_xy_value(example_grid, 5, 5, 99.0);
    printf("\nUpdated Example Grid Value at (5, 5): %6.2f\n", get_xy_value(example_grid, 5, 5));

    // Free the example grid
    free_grid(example_grid);

    return 0;
}