# Ray Tracing Journey
## A repository to explore ray tracing and path tracers
## Initially focusing on the Ray Tracing series

## For BasicRayTracing branch:
### [Ray Tracing in One Weekend — The Book Series](https://raytracing.github.io/books/RayTracingInOneWeekend.html)

## Goal of this repository is to create a collection of ray tracing and path tracing techniques, ranging from basic to sophisticated implementations
## Each branch will contain a different project of a ray tracer

![Sphere intersection with normals](image.ppm)



# To use meson build follow
## [mesonbuild installation instructions](https://mesonbuild.com/SimpleStart.html)
## [quickstart guide](https://mesonbuild.com/Quick-guide.html)

# Build and Run
## CLI Commands

## initialize meson build system  (under directory)

```bash
meson build
```

## build target -> project name inside meson.build file (raytracing in this case)

```bash
ninja -C build raytracing
```

## output build to an image.ppm

```bash
./build/raytracing > image.ppm
```
