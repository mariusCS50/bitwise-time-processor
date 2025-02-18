<!-- Improved compatibility of back to top link -->
<a id="readme-top"></a>

<!-- PROJECT LOGO -->
<div align="center">
  <h1>Time Processing & Bit Manipulation Resource Library</h1>
  <p>
	A comprehensive suite for efficient time handling, precise bit operations, and robust memory management in C.
	Leverage cutting-edge techniques for time format conversions, bit-level optimizations, and dynamic resource control.
  </p>
  <p>
	<a href="#usage">Usage Examples</a> ·
	<a href="#installation">Installation Guide</a> ·
	<a href="#features">Project Features</a>
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
	<li><a href="#about-the-project">About The Project</a></li>
	<li><a href="#features">Features</a></li>
	<li>
	  <a href="#getting-started">Getting Started</a>
	  <ul>
		<li><a href="#prerequisites">Prerequisites</a></li>
		<li><a href="#installation">Installation</a></li>
	  </ul>
	</li>
	<li><a href="#usage">Usage</a></li>
	<li><a href="#implementation-details">Implementation Details</a></li>
	<li><a href="#testing">Testing</a></li>
  </ol>
</details>

## About The Project

This project implements a comprehensive library for time processing, bit operations and memory management in C. It handles complex time format conversions, binary operations, and efficient memory allocation techniques. The system processes time in various formats, performs time zone calculations, and manages calendar operations through bit manipulation.

### Features

* Time Processing:
  - 12/24 hour format conversions
  - Time zone handling
  - Calendar operations
  - Date validation
  - Time arithmetic

* Bit Operations:
  - Basic binary operations
  - Advanced bit manipulation
  - Bit packing and unpacking
  - Bitwise optimizations

* Memory Management:
  - Dynamic allocation
  - Memory leak prevention
  - Resource cleanup
  - Efficient memory usage

### Built With

* C
* GCC Compiler
* Make build system
* CPPLint & Clang-tidy

## Getting Started

### Prerequisites

* GCC compiler
* Make build system
* Linux/Unix environment

### Installation

1. Clone the repository
2. Install linting tools:
   ```bash
   ./install-linters.sh
   ```
3. Build the project:
   ```bash
   make -f Makefile.checker
   ```

## Usage

The project contains multiple executables for different tasks:

1. Bit Operations (Tasks 1-6):
   ```bash
   ./check16 [task-number] < input_file
   ```
2. Bit Packing (Tasks 7-8):
   ```bash
   ./bitpacking < input_file
   ```
3. Memory Management (Task 9):
   ```bash
   ./planner < input_file
   ```

## Implementation Details

### Core Components

1. **Bit Operations**
   - Basic binary manipulations
   - Bit shifting and masking
   - Logical operations
   - Pattern matching

2. **Memory Management**
   - Dynamic allocation strategies
   - Memory cleanup procedures
   - Resource tracking
   - Leak prevention

3. **Time Handling**
   - Time format conversions
   - Efficient bit packing
   - Date/time manipulations

### Project Structure

- `check16.c` - Main bit operations implementation
- `bitpacking.c` - Bit packing operations
- `planner.c` - Memory management implementation
- `timelib.c/h` - Time manipulation utilities
- `tests/` - Test cases and verification

## Testing

Run all tests using:

```bash
./check.sh
```

Test suite includes:
- Unit tests for each operation
- Memory leak checks with Valgrind
- Input/output verification
- Edge case testing

<p align="right">(<a href="#readme-top">back to top</a>)</p>
