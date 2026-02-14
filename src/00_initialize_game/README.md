# 01_read_map_grid

## Purpose
Reads the map grid from `.cub` file and stores it in `t_map->grid` array. This module **only reads** - does not validate or normalize the map.

## Files
- **00_read_map_grid.c** - Main map reading logic
- **01_read_map_grid_utils.c** - Helper functions for line processing

---

## Functions Overview

### **00_read_map_grid.c**

#### `int is_empty_line(char *line)`
Checks if a line is empty (only spaces/tabs or newline).

**Returns:**
- `1` if line is empty
- `0` if line has content

**Examples:**
```c
"    \n"     → 1 (empty)
"\n"         → 1 (empty)
"1111"       → 0 (not empty)
```

---

#### `int is_texture_or_color_line(char *line)`
Checks if a line is a texture or color definition.

**Recognizes:**
- `NO ` - North texture
- `SO ` - South texture  
- `WE ` - West texture
- `EA ` - East texture
- `F ` - Floor color
- `C ` - Ceiling color

**Returns:**
- `1` if texture/color line
- `0` otherwise

**Note:** Handles leading whitespace

---

#### `static void skip_to_map_section(int fd)`
Skips all texture/color lines and empty lines until first map line is reached.

**Process:**
1. Read line
2. If texture/color/empty → free and continue
3. If map line → free and break (file pointer now at map start)

---

#### `static int calculate_map_height(const char *file_path)`
Counts the number of map lines (for malloc sizing).

**Process:**
1. Open file
2. Skip to map section
3. Count lines until empty line
4. Close file

**Returns:**
- Number of map lines
- `-1` on error

---

#### `int read_map_grid(const char *file_path, t_map *map)`
**Main function** - orchestrates the entire map reading process.

**Parameters:**
- `file_path`: Path to `.cub` file
- `map`: Map structure to fill

**Process:**
```
1. Calculate map height (file opened and closed)
2. Allocate memory for map->grid
3. Open file again  
4. Skip to map section
5. Read all map lines (process_lines_loop)
6. Close file
```

**Returns:**
- `0` on success
- `1` on error

---

### **01_read_map_grid_utils.c**

#### `char *parse_map_line(char *line)`
Cleans a map line by removing newline characters.

**Process:**
1. Get line length
2. Remove trailing `\n` and `\r`
3. Allocate new string
4. Copy all characters **including leading spaces**

**Important:** Preserves leading spaces!

**Example:**
```c
"   111\n"  → "   111"  (spaces preserved)
"100N01\r\n" → "100N01"
```

---

#### `static int process_single_map_line(char *line, t_map *map, int i)`
Processes one map line and updates width tracking.

**Process:**
1. Parse the line (remove newlines)
2. Store in `map->grid[i]`
3. Update `map->width` if this line is longer

**Returns:**
- `0` on success
- `1` on malloc failure

---

#### `int process_lines_loop(int fd, t_map *map)`
Reads all map lines from current file pointer position.

**Assumption:** File pointer already at first map line (skip_to_map_section was called)

**Process:**
```
i = 0
while (line)
{
    if empty_line → STOP (map ended)
    process_single_map_line()
    i++
}
```

**Returns:**
- `0` on success
- `1` on error

---

## Flow Diagram

```
read_map_grid(file_path, map)
│
├─► calculate_map_height(file_path)
│   ├── open(file)
│   ├── skip_to_map_section(fd)
│   ├── count lines until empty
│   └── close(file)
│   └── return count
│
├─► map->height = count
├─► malloc(map->grid)
│
├─► open(file)  [NEW FD, pointer at start]
├─► skip_to_map_section(fd)
│   └── Skip NO/SO/WE/EA/F/C/empty lines
│
├─► process_lines_loop(fd, map)
│   │
│   └─► for each line:
│       ├── if empty → STOP
│       └── process_single_map_line()
│           ├── parse_map_line()
│           ├── store in grid[i]
│           └── update max width
│
└─► close(file)
```

---

## Example

**Input File:**
```
NO assets/textures/north_wall.xpm
SO assets/textures/south_wall.xpm
F 220,100,0
C 135,206,235

   111
  11011
 1100N011
  11011
   111

```

**After read_map_grid:**
```c
map->height = 5
map->width = 9  // longest line

map->grid[0] = "   111"      // 6 chars (spaces preserved!)
map->grid[1] = "  11011"     // 7 chars
map->grid[2] = " 1100N011"   // 9 chars (max)
map->grid[3] = "  11011"     // 7 chars
map->grid[4] = "   111"      // 6 chars
map->grid[5] = NULL
```

**Note:** 
- ✅ Lines are **different lengths** (irregular)
- ✅ **Leading spaces preserved**
- ❌ NOT normalized yet (happens in validate_map)
- ❌ NOT validated yet

---

## Important Notes

### Why File Opened Twice?
1. **First open:** Count lines (need size for malloc)
2. **Second open:** Read actual data

**Alternative:** Use dynamic arrays, but this is simpler.

### Why Preserve Spaces?
Irregular maps need spaces to maintain structure:
```
   111      ← These spaces are meaningful!
  11011
 1100N011
```

Later, `normalize_to_rectangle()` will:
1. Extend short lines with spaces
2. Convert all spaces to '1' (walls)

### File Pointer Position
After `skip_to_map_section(fd)`, file pointer is positioned **right before first map line**.

`process_lines_loop()` starts reading from current position - no texture/color skipping needed!

---

## Separation of Concerns

| Module | Responsibility |
|--------|----------------|
| `read_map_grid` | **Read** raw map data |
| `validate_map` | **Validate** and normalize |
| `parse_textures` | **Parse** texture/color info |

Each module does **one thing** well!
