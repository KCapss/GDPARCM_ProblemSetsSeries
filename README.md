# GDPARCM_ProblemSetsSeries
A compilation of deliverable in Problem Sets for GDPARCM class

## Problem Set 1
**By Capalar, K.C.**

### Instruction
- Entry File
  - Main.cpp
- Setup:
  - Project Folder Name: ""
  - Req. Package
    - Opencv.package (v4.90)
  - Build Depedencies
    - opencv_world490d.dll (for debug)
    - opencv_world490.dll (for release)
 
**Important:**
- It is adivisable to run the program on release (for improved speed on multithreading) 
- When compiling the program both (release/debug)
  - make sure to enable _**/FORCE:MULTIPLE**_ or _**Force File Multiple**_ (Proj.properties->Linker->General)
  - (For Release) Disable Function Locking **/Gy~**
- After the program finished or encountered an error make sure to end the program then wait for couple a seconds before running another instance of the program.
- In any case you unable to compile and run the program via the compiler, you can open both the png and zip of the test cases which contain the release exec version.
  - To access. (projectDir)->OutputFile/

### Commit History Reference
1. Initial Commit - [[62477a7](https://github.com/KCapss/GDPARCM_ProblemSetsSeries/commit/62477a735b8bb38a5ed5e57f79abef870032889d)]
2. Test Case 1 Commit - [[748b5e2](https://github.com/KCapss/GDPARCM_ProblemSetsSeries/commit/748b5e24c29c20b199e44ba670601ae0db6e861f)]
3. Test Case 2 Commit - [[8682f92](https://github.com/KCapss/GDPARCM_ProblemSetsSeries/commit/8682f9252fe88f00f36e6e48ecdf0c1553034856)]
4. Test Case 3 Commit  - [[8d8aa36](https://github.com/KCapss/GDPARCM_ProblemSetsSeries/commit/8d8aa3663b72526039acd24e8362f079c2584f49)]

## Problem Set 2
  An interactive loading heavily inspired from honkai star rail

  Project Dir = P2  = Capalar_P2_Interactive_Loading_Screen;
  
### Instruction
- Entry File
  - (ProjectDir)->Main.cpp
- Setup:
  - Project Folder Name: "Capalar_P2_Interactive_Loading_Screen"
  - Assets Folder Name: "Media"
    - File Size
       - Stream = 169mb
       - Loading = 13mb
  - Req. Package
    - SFML Stable Ver (For Working)
      - Use the vcpkg from the [website (https://vcpkg.io/)] and install the latest stable version to the project dir.    
  - Build Depedencies
    - OpenAl32.dll: Audio Integration (both)
    

**Important:**
- It is adivisable to run the program on release (for improved speed on multithreading)
- - In any case you unable to compile and run the program via the compiler, you can open contain the release exec version.
  - To access. (projectDir)->OutputFile/
 
### Commit History Reference
1. Initial Commit -  - [[a5f413f](https://github.com/KCapss/GDPARCM_ProblemSetsSeries/commit/a5f413f8be4045000cb16807afa49ad60a1c491d)]
2. Final Commit -  [[487ef3d](https://github.com/KCapss/GDPARCM_ProblemSetsSeries/commit/487ef3dffa637f15a51bc1932dfa7566bd212126)]
