<!-- markdownlint-disable MD024 -->
# Fractals Changelog

## Overview

This log is meant to track the development of my assignment 1.10
Versioning is marked when there is a notable change

## Versions

- [0.0.1](#ver-001)
- [0.0.2](#ver-002)
- [0.0.5](#ver-005)
- [0.1.0](#ver-010)
- [0.2.0](#ver-020)
- [0.2.5](#ver-025)
- [0.5.0](#ver-050)
- [1.0.0](#ver-100)

## Versions and Details

### Ver 0.0.1

#### Brief

- Project initialised with addition of main files
- Temporary UI is created and implemented

#### Added

### Ver 0.0.2

#### Brief

- Code for the Mandelbrot set and Julia set formulae have been implemented
- Code for generating ppm files for the 2 mentioned sets

### Ver 0.0.5

#### Brief

- Minor change to UI
- Attempting to create script to convert ppm to png using python

### Ver 0.1.0

#### Brief

- Initial Julia set and Mandelbrot set can be rendered into a ppm format
- minor change of file name

### Ver 0.2.0

#### Brief

- Changed output file to bitmap format
- Julia set functions expanded for z^2, z^4 and z^8
- created buffer for better performance
- Escape radius being tampered with

#### Bug

- Julia z^4 and z^8 not printing proper images

### Ver 0.2.5

#### Brief

- Julia z^4 now generates image
- MAX_ITER adjusted
- RGB get_colour adjusted
- increased image options
- added more fractal equations
- Pausing work on video generation

### Ver 0.5.0

#### Brief

- Adding Julia Frame generation then conversion to video
- Marking initial phase as complete and will not be adding more features until polishing is done
- Beginning polish phase

### Ver 1.0.0

#### Brief

- Code works now for Julia set (z^2 and z^4), Mandelbrot
- video generation is complete for Julia sets

### Ver 1.3.0

#### Major change

- Frames folder now gets deleted after video is generated
- Julia Sets options now generate frames and videos from a single choice

#### Minor change

- FPS lowered
- Frames generated lowered
- Added `time_taken()` function to main.cpp for debugging
