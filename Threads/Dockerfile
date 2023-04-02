# building it:  sudo docker build -t myproject .
# compiling and running each code: sudo docker run -v "$(pwd)":/app myproject g++ -pthread -o l1.out l1.cpp && ./l1.out

# Use the official GCC image as the base
FROM gcc:latest

# Install any additional dependencies needed for the project
# RUN apt-get update && apt-get install -y <dependency>

# Create a new directory for the project
RUN mkdir /app
WORKDIR /app

# Copy the C++ files into the Docker image
COPY l1.cpp /app
COPY l2.cpp /app
COPY l3.cpp /app
COPY l4.cpp /app
COPY l5.cpp /app
COPY l6.cpp /app


# Add a script to compile and run a specific file
COPY run.sh /app
RUN chmod +x run.sh
CMD ["/bin/bash"]

# docker run: This command is used to run a Docker container.
# -v "$(pwd)":/app: This option mounts the current working directory ($(pwd)) to the /app directory inside the Docker container. This allows the container to access the files in the current directory.
# myproject: This is the name of the Docker image to use. In this case, it refers to the image that you created earlier using the docker build command.
# g++: This is the command to compile C++ code using the GNU Compiler Collection.
# -pthread: This option is used to link the pthread library, which is required for multi-threading in C++.
# -o l1.out: This option specifies the name of the output file to be generated. In this case, it will generate an executable file named l1.out.
# l1.cpp: This is the name of the C++ source code file to be compiled.
# &&: This operator is used to run the next command only if the previous command succeeds.
# ./l1.out: This command runs the compiled executable file generated in the previous command.
