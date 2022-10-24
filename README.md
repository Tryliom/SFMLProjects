#SFML Projects

A set of projects that use SFML.

# Requirement

You need to install [vcpkg](https://vcpkg.io/en/getting-started.html)
* Run this command `vcpkg integrate install`
* Install SFML `vcpkg install sfml`
* Install SFML x64 `vcpkg install sfml:x64-windows`
* Install Box2d `vcpkg install box2d`
* Install Box2d x64 `vcpkg install box2d:x64-windows`

Install and open cmake
* Add the path to the project in the first field
* Create a folder named `build` in the project folder
* Select the build folder in the third field
* Click on `Configure` button
* Click on `Specify toolchain file for cross-compiling` and select `[path to vcpkg]/scripts/buildsystems/vcpkg.cmake` file
* Delete the whole build folder
* Delete files inside out folder
* Close and reopen project

# Open the project

You need to right click on the folder and click on `Open Folder in Visual Studio Code`