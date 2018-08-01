# OS image
FROM gmedders/cpp_scientific_libraries:v0.2.0

MAINTAINER gmedders "https://github.com/gmedders"

WORKDIR /app
ADD . /app

# Build the packaged
RUN mkdir build && cd build && cmake .. && make

# When the image is run, go directly to the executables
WORKDIR /app/build

# Define default command.
CMD ["bash"]
