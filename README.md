# Grid Manipulation Library

This project provides a library for creating, manipulating, and managing 2D grids. It includes functionality for reading and writing grid data in Surfer 6 binary format, as well as creating example grids programmatically.

## Features
- Create example grids programmatically.
- Read grids from Surfer 6 binary files.
- Modify grid values.
- Write grids to Surfer 6 binary files.
- Print grid metadata and data.

## Requirements
- GCC or any C compiler.
- Linux or any POSIX-compliant operating system.

## Build Instructions
To compile the project, use the following command:

```bash
gcc [main.c](http://_vscodecontentref_/4) [grid.c](http://_vscodecontentref_/5) -o grid_program
```

## Usage
1. Run the program:
   ```bash
   ./grid_program
   ```
2. The program demonstrates:
   - Reading a grid from a file (`example_input.grd`).
   - Creating an example grid programmatically.
   - Modifying grid values.
   - Writing the modified grid to a file (`example_output.grd`).

## File Structure
- `main.c`: Example usage of the library.
- `grid.h`: Header file defining the `Grid` structure and functions.
- `grid.c`: Implementation of the `Grid` library.

## Example Input and Output
### Input
The program expects a Surfer 6 binary grid file as input (e.g., `example_input.grd`).

### Output
The program generates a modified grid file (e.g., `example_output.grd`) and prints the following to the console:
- Grid metadata (e.g., dimensions, bounding box, step sizes).
- Grid data in a human-readable format.

## Plans
Here are some planned improvements and features for the Grid Manipulation Library:

- [ ] Add unit tests for all functions in the library.
- [ ] Implement support for additional grid file formats (e.g., ASCII grids, Surfer 7 binary).
- [ ] Add error handling for invalid or corrupted input files.
- [ ] Create a Python wrapper for easier integration with Python projects.
- [ ] Add a graphical visualization tool for grid data.

## License
This project is licensed under the MIT License. See `LICENSE` for details.