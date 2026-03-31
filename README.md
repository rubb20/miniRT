*This project has been created as part of the 42 curriculum by ralba-ji, isastre-.*

# miniRT

## Description

miniRT is a small ray tracer developed as part of the 42 curriculum.  
The goal of the project is to introduce the fundamentals of computer graphics by implementing a basic rendering engine from scratch in C.

The program reads a scene description from a `.rt` file and renders a 3D image using ray tracing techniques. It supports simple geometric objects such as spheres, planes, and cylinders, as well as lighting, camera configuration, and colors.

This project focuses on:
- Understanding 3D mathematics (vectors, normalization, intersections)
- Parsing structured input files
- Implementing a basic rendering pipeline
- Managing memory and data structures in C

## Instructions

### Compilation

Clone the repository and run:

```bash
make
```

### Execution

Run the program with a .rt scene file:
```bash
./miniRT <scene>.rt
```

## Resources

### Documentation & References
- Ray Tracing fundamentals:
	- [Ray Tracing in One Weekend — Peter Shirley](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
	- [Phong ilumination model](https://learnopengl.com/Advanced-Lighting/Advanced-Lighting)
	- [Rotation matrix](https://es.wikipedia.org/wiki/Matriz_de_rotaci%C3%B3n)

### AI Usage

ChatGPT and Gemini were used during the development of this project for:

- Understanding floating-point precision issues
- Designing parsing strategies and edge-case handling
- Generating test cases for parser validation
- Debugging and improving Makefile configuration
- Understanding the mathemathics of cylinder intersection
