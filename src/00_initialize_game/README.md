# 01_validate_file

## Purpose
Validates the `.cub` file path and ensures it can be opened for reading.

## Functions

### `validate_file(const char *file_path)`
Main validation function that checks:
1. File name has `.cub` extension
2. File is not a directory
3. File can be opened for reading

**Returns:** 0 on success, -1 on failure

### `validate_filename(const char *file_path)`
Extracts the basename from the path using `ft_strrchr()` and verifies the `.cub` extension.

### `validate_file_access(const char *file_path)`
Checks file accessibility:
- First checks if path is a directory (O_DIRECTORY flag)
- Then verifies read permissions (O_RDONLY)

### `check_extension(const char *filename)`
Case-sensitive check for `.cub` extension using `ft_strncmp()`.

## Flow
```
validate_file()
├── validate_filename()
│   ├── ft_strrchr() - extract basename
│   └── check_extension() - verify .cub
└── validate_file_access()
    ├── open(O_DIRECTORY) - check if directory
    └── open(O_RDONLY) - check read access
```

## Error Messages
- "Error: Invalid file name"
- "Error: Path is a directory"
- "Error: Cannot open file"
