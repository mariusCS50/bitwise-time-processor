# Bitwise Time Processor

A command-line tool for processing and manipulating time values using bitwise operations. This project includes two main components:
- A bitwise time conversion and arithmetic module.
- A planner module that schedules events based on participants' available time intervals.

## Features

- Convert time values between different formats.
- Perform arithmetic operations using bitwise operators.
- Plan events by evaluating participants' free intervals.
- Designed for low resource usage and high performance.
- Modular architecture for easy maintenance and extension.

## Building the Project

Use the provided Makefile with the following targets:
```bash
make run-bitpacking    # Build and run the bitwise processing module
make run-planner       # Build and run the planner module
make clean             # Clean build artifacts
```

## Usage

### Bitwise Processing Module
Run interactive commands for bitwise time operations:
```bash
./bitpacking
# Commands:
# t <value>  - Process a time value
# c          - Convert time formats
# q          - Exit the application
```

### Planner Module
Schedules events based on participants' availability:
```bash
./planner
# The planner reads input data, processes available intervals,
# and outputs the scheduled time if sufficient participants can join.
```

## Technical Details

- Time values are assumed to be in milliseconds.
- The core logic is decoupled from I/O operations.
- Implements bit-level operations for optimized calculations.
- Both modules are managed via the Makefile to ensure consistent builds.
