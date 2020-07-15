# NEW_Genome_1.0
space to work on new genome class for MABE
afdssa

### To compile:
cd code  <br />
bash build.sh  <br />
./test

### Adding Tests:
create test header under Tests folder

### Adding Genomes:
create genome .cpp and .h in Genomes Folder <br />
if you're adding a folder, add "include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Genomes/< foldername >)" under # include source in code/CMakeLists.txt.

### Changing Tests:
include the testing header file name, and add the function calls in main.cpp 
