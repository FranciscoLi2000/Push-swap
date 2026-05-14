# Push Swap

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![Language: C](https://img.shields.io/badge/language-C-blue.svg)

## Table of Contents
- [Project Introduction](#project-introduction)
- [Tech Stack](#tech-stack)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing Guide](#contributing-guide)
- [License](#license)

## Project Introduction
Push Swap is a C program that sorts a list of integers using two stacks and a restricted set of operations, outputting an efficient instruction sequence.

Key capabilities:
- Generates sorting instructions for the `push_swap` evaluator
- Provides a bonus `checker` tool to validate instruction sequences
- Handles input validation (invalid integers, duplicates, out-of-range values)

## Tech Stack
- C (C standard library)
- Make (build system)
- libft (local utility library)

## Installation
Prerequisites:
- A C compiler (e.g., `cc` or `clang`)
- `make`

Steps:
```bash
# Clone the repository
git clone https://github.com/FranciscoLi2000/Push-swap.git

# Or clone your fork if contributing
git clone https://github.com/<your-username>/Push-swap.git
cd Push-swap

# Build push_swap
make

# Build checker (bonus)
make bonus
```

Build outputs:
- `push_swap`
- `checker`

## Usage
Generate sorting instructions:
```bash
./push_swap 3 2 5 1 4
```

Validate instructions with the bonus checker:
```bash
ARG="3 2 5 1 4"
./push_swap $ARG | ./checker $ARG
# Expected output: OK
```

## Contributing Guide
Contributions are welcome.

1. Fork the repository.
2. Create a feature branch: `git checkout -b feature/your-change`.
3. Commit your changes: `git commit -m "Add your change"`.
4. Push to your fork and open a pull request.

Please keep changes focused and include a clear description of the motivation and scope.

## License
This project is licensed under the [MIT License](LICENSE).
