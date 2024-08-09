# Develop an Azure C++ App using vcpkg and CMake

## Perquisite 
1. Any Text Editor 
2. A terminal
3. A C++ compiler
4. git

## Steps 
### Install CMake
- Go to the [CMake Downloads page](https://cmake.org/download/) where you can either download the latest version of the CMake source or an installer for your OS. I'd recommend using the installer for simplicity. When asked select the option to add CMake to your PATH. 
- Once you've downloaded and run through the installer program run the following command to verify CMake has been installed properly:
```bash
cmake --version
```
- You should get an output denoting the currently install version of CMake. Like this: 
```bash
cmake version 3.30.2
```

### Install vcpkg
- To install vcpkg you'll first need to clone the vcpkg repo. I recommend cloning vcpkg to a central location on your development environment and not in your C++ Project directory. In this example I'll clone vcpkg to my home dir. 
```bash
cd ~
git clone https://github.com/microsoft/vcpkg.git ~
```
- Once the vcpkg repo is cloned traverse into the new directory and run the bootstrap-vcpkg script. 
  - If you're on Windows run: 
  ```bash
  cd .\vcpkg\
  .\bootstrap-vcpkg.bat
  ```
  - If you're on MacOS or Linux, run: 
  ```bash
  cd vcpkg
  ./bootstrap-vcpkg.sh
  ```
- After bootstrapping vcpkg, add it to your path so you can access the vcpkg executable from your project directory. 
  - On Windows Powershell, enter: 
  ```bash
  $env:Path += 'C:\path\to\vcpkg'
  ```
  - On MacOS or Linux systems, enter: 
  ```bash
  PATH=$PATH:/path/to/vcpkg
  ```
- Traverse back to your project directory and run the following to verify the vcpkg directory was added to your path: 
```bash
vcpkg --version
```
- You should get an output resembling the following (The hash at the end of the line does not need to match exactly):
```bash
vcpkg package management program version 2024-08-01-fd884a0d390d12783076341bd43d77c3a6a15658
```

### Project Setup
- Let's start by creating our main C++ file. 
  - On Windows Powershell, enter: 
  ```bash
  echo main > main.cpp
  ```
  - On MacOS and Linux, enter:
  ```bash
  touch main.cpp
  ```
- Now lets create our CMakeLists.txt to use with CMake. 
  - On Windows Powershell, enter: 
  ```bash
  echo cmake > CMakeLists.txt
  ```
  - On MacOS and Linux systems, enter: 
  ```bash
  touch CMakeLists.txt
  ```
- We'll also create a `build` directory to store all out build related artifacts.
  - On Windows Powershell, MacOs and Linux systems, enter: 
  ```bash
  mkdir build
  ```
### Setup CMakeLists.txt file
- Now open the `CMakeLists.txt` file in your text editor and delete any contents inside it.
- To set up a extremely basic CMake project add the following to your `CMakeLists.txt` file: 
```cmake
cmake_minimum_required(VERSION 3.30.0)
project(azure_sample VERSION 0.1.0 LANGUAGES C CXX)

add_executable(azure_sample main.cpp)
```
- To test our project setup so far lets also open our `main.cpp` file and add the following hello world code: 
```cpp
#include <iostream>

int main() {
    std::cout << "Hello World!";
    return 0;
}
```
- Now, in the terminal lets move inside our build directory and run the command to configure our CMake build. 
```bash
cd build
cmake ..
```
- You should see the build directory populate with some directories and files. 
- Now lets try building the project with: 
```bash
cmake --build .
```
- The output of the build should contain a line stating where the executable that was built was placed. By default it should be in your `build` directory under a new `Debug` directory with the name `azure_sample.exe` if your on Windows or `azure_sample` if your on MacOS or Linux.
- Lets try running our new executable. 
  - If your on Windows Powershell, enter: 
  ```bash
  .\Debug\azure_sample.exe
  ```
  - If your on MacOS or Linux, enter: 
  ```bash
  ./Debug/azure_sample
  ```
- You should get the following out put: 
```bash
Hello World!
```

### Install packages with vcpkg
- In this example we'll be using vcpkg in what's known as manifest mode.
- First we'll start by moving back to the root directory of our project, and creating a new vcpkg application with the following command: 
```bash
cd ../
vcpkg new --application
```
- You should now have a `vcpkg.json` and `vcpkg-configuration.json` file in your project directory with the following contents: 
  - `vcpkg.json`
  ```json
  {}
  ```
  - `vcpkg-configuration.json` *It's okay if the hash on the `baseline` property doesn't match exactly.*
  ```json
  {
    "default-registry": {
      "kind": "git",
      "baseline": "6af584dd59aa5bdba75dae6781ec74614e03e5b9",
      "repository": "https://github.com/microsoft/vcpkg"
    },
    "registries": [
      {
        "kind": "artifact",
        "location": "https://github.com/microsoft/vcpkg-ce-catalog/archive/refs/heads/main.zip",
        "name": "microsoft"
      }
    ]
  }
  ```
- Now we can add the Azure Key Vault and Identity libraries from the Azure SDK for C++ to our project, by entering the following command:
```bash
vcpkg add port azure-identity-cpp azure-security-keyvault-secrets-cpp
```
- Your `vcpkg.json` file should now look like this: 
```json
{
  "dependencies": [
    "azure-identity-cpp",
    "azure-security-keyvault-secrets-cpp"
  ]
}
```
# azure-cpp-sample
