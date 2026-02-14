# 00_validate_mapfile

## Purpose
Validates the `.cub` map file path and ensures it can be opened for reading before parsing.

## File
- `00_validate_mapfile.c`

## Functions

### `int validate_mapfile(const char *file_path)`
Main validation function that checks:
1. File name is valid and has `.cub` extension
2. File is not a directory
3. File can be opened for reading

**Parameters:**
- `file_path`: Path to the `.cub` file

**Returns:** 
- `0` on success
- `1` on failure (with error message printed)

---

### `static int validate_filename(const char *path)` 
Validates the filename structure:
- Checks for NULL pointer (`ERR_NULL_FILENAME`)
- Checks for empty string (`ERR_EMPTY_STRING`)
- Extracts basename using `ft_strrchr(path, '/')`
- Validates minimum length (5 chars: `x.cub`) (`ERR_TOO_SHORT`)
- Checks it doesn't start with `.` (`ERR_ONLY_EXTENSION`)
- Calls `check_extension()` for extension validation

**Returns:** Error code or `0` on success

---

### `static int check_extension(const char *path, int len)`
Performs case-sensitive `.cub` extension check:
- Compares last 4 characters with `.cub` using `ft_strncmp()`
- If case mismatch, checks if lowercase version matches (`ERR_CASE_SENSITIVE`)
- Returns `ERR_WRONG_EXTENSION` if extension doesn't match

**Returns:** Error code or `0` on success

---

### `static int validate_file_access(const char *path)`
Checks file accessibility:
1. Attempts to open as directory with `O_DIRECTORY` flag
   - If succeeds → returns `ERR_IS_DIRECTORY`
2. Attempts to open with `O_RDONLY` flag
   - If fails → returns `ERR_OPEN_FAILED`

**Returns:** Error code or `0` on success

---

## Error Codes (from error.h)
- `ERR_NULL_FILENAME` - NULL file path provided
- `ERR_EMPTY_STRING` - Empty string provided
- `ERR_TOO_SHORT` - Filename shorter than 5 characters
- `ERR_WRONG_EXTENSION` - Extension is not `.cub`
- `ERR_ONLY_EXTENSION` - Filename starts with `.`
- `ERR_CASE_SENSITIVE` - Extension case mismatch (e.g., `.CUB`)
- `ERR_IS_DIRECTORY` - Path points to a directory
- `ERR_OPEN_FAILED` - Cannot open file for reading

## Flow
```
validate_mapfile()
├── validate_filename()
│   ├── NULL check
│   ├── Empty string check
│   ├── ft_strrchr('/') - extract basename
│   ├── Length validation (>= 5)
│   ├── Check first char != '.'
│   └── check_extension()
│       ├── ft_strncmp() - exact match
│       └── Case-insensitive check
└── validate_file_access()
    ├── open(O_DIRECTORY) - check if directory
    └── open(O_RDONLY) - check read access
```

## Usage Example
```c
if (validate_mapfile("maps/level1.cub") != 0)
    return (1);  // Error printed by function
// Proceed with parsing...
```
