# QuantumWeave: A 2D Quantum Puzzle-Strategy Game

## Overview
QuantumWeave is an innovative 2D puzzle-strategy game built in C++ using the SFML library. Players manipulate a quantum lattice by placing and rotating energy links to connect nodes while maintaining grid stability. Incorrect moves risk destabilizing the lattice, adding a strategic layer to the puzzle-solving experience. This game offers a unique blend of quantum-inspired mechanics and strategic planning, distinct from traditional puzzle or strategy games.

This open-source project is designed for developers, gamers, and educators interested in C++ game development, puzzle mechanics, and innovative gameplay. By sponsoring QuantumWeave via GitHub Sponsors, you support new features, level designs, and educational resources for the community.

## Features
- **Quantum Lattice Mechanics**: Place and rotate energy links to connect nodes while avoiding grid instability.
- **Dynamic Stability System**: Balance energy flow to prevent lattice collapse.
- **Minimalist Visuals**: Clean 2D graphics with glowing effects for an immersive experience.
- **Cross-Platform**: Runs on Windows, macOS, and Linux via SFML.
- **Modular Codebase**: Well-structured C++ code for easy extension and learning.

## Getting Started

### Prerequisites
- **C++ Compiler**: GCC, Clang, or MSVC with C++17 support.
- **SFML Library**: Version 2.5.1 or later (install via [SFML's official site](https://www.sfml-dev.org/) or package manager).
- **CMake**: Version 3.10 or later for building.

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/quantumweave.git
   cd quantumweave
   ```
2. Create a build directory:
   ```bash
   mkdir build && cd build
   ```
3. Configure with CMake:
   ```bash
   cmake ..
   ```
4. Build the project:
   ```bash
   cmake --build .
   ```
5. Run the game:
   ```bash
   ./QuantumWeave
   ```

## Gameplay
- **Objective**: Connect all energy nodes on the lattice by placing and rotating links without destabilizing the grid.
- **Controls**:
  - **Arrow Keys**: Move the cursor on the grid.
  - **Space**: Place an energy link.
  - **R**: Rotate the selected link.
  - **Enter**: Activate the lattice to test connections.
  - **Esc**: Pause or exit.
  - **Ctrl+R**: Reset the level.
- **Mechanics**: Each link directs energy flow. Misaligned links or overloaded nodes increase instability. Keep stability below the threshold to win.

## Project Structure
- `src/main.cpp`: Game entry point and main loop.
- `src/Entity.hpp`: Base class for game entities (nodes, links).
- `src/Game.hpp`: Core game logic, lattice management, and rendering.
- `assets/`: Placeholder for textures/fonts (add your own or use SFML defaults).

## Contributing
Contributions are welcome! Fork the repo, create a feature branch, and submit a pull request. For major changes, open an issue to discuss your ideas.

## Sponsorship
Support QuantumWeave’s development through [GitHub Sponsors](https://github.com/sponsors/yourusername)! Your contributions fund:
- New puzzle levels and lattice patterns.
- Advanced quantum mechanics simulations.
- Tutorials for C++ and game development.
- Optimizations for broader platform support.

## License
Licensed under the MIT License. See [LICENSE](LICENSE) for details.

## Acknowledgments
- Built with [SFML](https://www.sfml-dev.org/) for graphics and input.
- Inspired by quantum computing concepts and grid-based puzzles.
- Thanks to the open-source community for feedback and inspiration.

---

**Sponsor QuantumWeave to weave the future of puzzle gaming!**