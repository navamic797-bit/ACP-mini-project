# 2D Graphics Editor (C Program)

A command-line terminal-based 2D graphics editor written in C. It allows you to draw and manage geometric shapes (Lines, Rectangles, Circles, and Triangles) on an 80x24 canvas using standard ASCII characters (`*` for pixels and `_` for empty space).

## Features

- **Geometry Drawing Algorithms**:
  - **Line**: Uses *Bresenham's Line Algorithm* for clean integer-only line rendering.
  - **Rectangle**: Draws a box structure using four lines from top-left to bottom-right coordinates.
  - **Circle**: Uses the *Midpoint Circle Algorithm* (Bresenham's circle) to render circles using 8-way symmetry.
  - **Triangle**: Connects three arbitrary coordinate points using three lines.
- **Object Management**:
  - **Add Object**: Choose a shape, enter its parameters, and store it.
  - **Delete Object**: Remove an object from the canvas using its index.
  - **Modify Object**: Re-define parameters for an existing shape index.
  - **List Objects**: Show a list of all active/deleted shapes and their current parameters.
  - **Display Picture**: Clears the screen and draws all active objects to output the updated canvas.

---

## Files

- [main.c](file:///C:/Users/SHRAVAN%20S%20N/.gemini/antigravity/scratch/graphics-editor/main.c): Main source code containing the logic, shape drawing algorithms, menus, and object storage array.

---

## Canvas Layout

- **Width**: 80 columns (x-axis: 0 to 79)
- **Height**: 24 rows (y-axis: 0 to 23)
- **Pixel character**: `*`
- **Empty canvas character**: `_`

---

## How to Build and Run

### 1. Compile the program
Use any standard C compiler (like GCC or Clang) to compile the code.

On Linux / macOS / WSL (Windows Subsystem for Linux):
```bash
gcc -o graphics_editor main.c -lm
```
*(Note: `-lm` links the math library which might be required for some systems)*

On Windows (using MinGW/GCC in PowerShell or Command Prompt):
```cmd
gcc -o graphics_editor.exe main.c
```

### 2. Run the executable
On Linux / macOS / WSL:
```bash
./graphics_editor
```

On Windows:
```cmd
graphics_editor.exe
```

---

## Menu Options

When you run the program, you will interact with the following menu:

1. **Add object**: Allows you to create a new shape:
   - Line: Enter `x1 y1 x2 y2`
   - Rectangle: Enter top-left `x y` and bottom-right `x y`
   - Circle: Enter center `x y` and `radius`
   - Triangle: Enter three points `x1 y1 x2 y2 x3 y3`
2. **Delete object**: Prompts you for the index of the shape you want to delete.
3. **Modify object**: Allows you to update the dimensions of an existing shape by entering its index and typing new coordinates.
4. **Display picture**: Renders the complete canvas with all active objects printed.
5. **List objects**: Displays a history list of all created shapes, including active parameters and deleted indicators.
0. **Exit**: Exits the graphics editor.
1. 
