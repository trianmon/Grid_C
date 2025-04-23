/**
 * @file grid.h
 * @brief Header file for the Grid structure and related operations.
 * 
 * This file defines the Grid structure and provides functions for creating,
 * manipulating, and managing grid data. It also includes functionality for
 * reading and writing grid data in Surfer 6 binary format.
 */

#ifndef GRID_H
#define GRID_H

/**
 * @def GRID_DEFAULT_BLANK_VALUE
 * @brief Default value for uninitialized cells in the grid.
 */
#define GRID_DEFAULT_BLANK_VALUE 170141000918782798866653488190622531584.000000

/**
 * @def GRID_DEFAULT_Z_MIN
 * @brief Default minimum Z-value for the grid, initialized to the maximum double value.
 */
#define GRID_DEFAULT_Z_MIN __DBL_MAX__

/**
 * @def GRID_DEFAULT_Z_MAX
 * @brief Default maximum Z-value for the grid, initialized to the negative maximum double value.
 */
#define GRID_DEFAULT_Z_MAX -__DBL_MAX__

/**
 * @struct Grid
 * @brief Represents a 2D grid with associated metadata and data storage.
 * 
 * The Grid structure contains information about the grid's bounding box,
 * dimensions, step sizes, Z-value range, blank value, and the actual grid data.
 */
typedef struct Grid
{
    double x_min, x_max, y_min, y_max; /**< Bounding box coordinates. */
    int x_size, y_size;               /**< Grid dimensions (number of cells in X and Y directions). */
    double x_step, y_step;            /**< Step sizes in X and Y directions. */
    double z_min, z_max;              /**< Range of Z-values in the grid. */
    double blank_value;               /**< Value used for uninitialized cells. */
    double* data;                     /**< Pointer to the grid data array. */
} Grid;

/**
 * @brief Creates an example grid with predefined values.
 * 
 * @return Pointer to the newly created Grid structure.
 */
Grid* create_example_grid();

/**
 * @brief Frees the memory allocated for a Grid structure.
 * 
 * @param grid Pointer to the Grid structure to be freed.
 */
void free_grid(Grid* grid);

/**
 * @brief Retrieves the value at a specific (x, y) position in the grid.
 * 
 * @param grid Pointer to the Grid structure.
 * @param x X-coordinate of the cell.
 * @param y Y-coordinate of the cell.
 * @return The value at the specified (x, y) position.
 */
double get_xy_value(Grid* grid, int x, int y);

/**
 * @brief Sets the value at a specific (x, y) position in the grid.
 * 
 * @param grid Pointer to the Grid structure.
 * @param x X-coordinate of the cell.
 * @param y Y-coordinate of the cell.
 * @param value The value to set at the specified (x, y) position.
 */
void set_xy_value(Grid* grid, int x, int y, double value);

/**
 * @brief Sets the minimum X-coordinate of the grid's bounding box.
 * 
 * @param grid Pointer to the Grid structure.
 * @param x_min The minimum X-coordinate to set.
 */
void set_grid_x_min(Grid* grid, double x_min);

/**
 * @brief Sets the maximum X-coordinate of the grid's bounding box.
 * 
 * @param grid Pointer to the Grid structure.
 * @param x_max The maximum X-coordinate to set.
 */
void set_grid_x_max(Grid* grid, double x_max);

/**
 * @brief Sets the minimum Y-coordinate of the grid's bounding box.
 * 
 * @param grid Pointer to the Grid structure.
 * @param y_min The minimum Y-coordinate to set.
 */
void set_grid_y_min(Grid* grid, double y_min);

/**
 * @brief Sets the maximum Y-coordinate of the grid's bounding box.
 * 
 * @param grid Pointer to the Grid structure.
 * @param y_max The maximum Y-coordinate to set.
 */
void set_grid_y_max(Grid* grid, double y_max);

/**
 * @brief Calculates and updates the minimum and maximum Z-values in the grid.
 * 
 * @param grid Pointer to the Grid structure.
 */
void calculate_z_min_max(Grid* grid);

/**
 * @brief Prints metadata information about the grid.
 * 
 * @param grid Pointer to the Grid structure.
 */
void print_grid_info(Grid* grid);

/**
 * @brief Prints the grid data in a human-readable format.
 * 
 * @param grid Pointer to the Grid structure.
 */
void print_grid_data(Grid* grid);

/**
 * @brief Reads a grid from a Surfer 6 binary file.
 * 
 * @param filename Path to the Surfer 6 binary file.
 * @return Pointer to the newly created Grid structure containing the data.
 */
Grid* read_surfer_grid_6bin(const char* filename);

/**
 * @brief Writes a grid to a Surfer 6 binary file.
 * 
 * @param filename Path to the Surfer 6 binary file.
 * @param grid Pointer to the Grid structure to be written.
 */
void write_surfer_grid_6bin(const char* filename, Grid* grid);

#endif