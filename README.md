<a name="readme-top"></a>

<!-- PROJECT SHIELDS -->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

# <center>Introduction to Programming II Mini Project 3</center>

<div align="center">

  <p align="center">
    project_description
    <br />
    <a href="https://github.com/Lewis-Tsai/Introduction-to-Programming-II-Mini_Project_3"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/Lewis-Tsai/Introduction-to-Programming-II-Mini_Project_3">View Demo</a>
    ·
    <a href="https://github.com/Lewis-Tsai/Introduction-to-Programming-II-Mini_Project_3/issues">Report Bug</a>
    ·
    <a href="https://github.com/Lewis-Tsai/Introduction-to-Programming-II-Mini_Project_3/issues">Request Feature</a>
  </p>
</div>


## Semester and class
2021 Spring NTHU CS 135602

<!-- ABOUT THE PROJECT -->
## About The Project

This is an Othello AI. This program will play against these baselines and try to defeat them.

## Built With

* ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
* ![Windows Terminal](https://img.shields.io/badge/Windows%20Terminal-%234D4D4D.svg?style=for-the-badge&logo=windows-terminal&logoColor=white)


<!-- GETTING STARTED -->
## Getting Started

### Othello Rules

* Use black and white discs and an 8 x 8 board, black plays first
* Starts with initial board (the board on the previous page)
* Player can place disc if the new disc and another same color disc are on a line (horizontal, vertical, diagonal), with one or more contiguous opposite color discs between the two discs of the player
* The opposite color discs between player discs will be flipped
* Player passes if no valid move can be performed
* The game ends when neither player can move
* The one with more discs wins


### How To Compile Your Code
* To compile all programs <br>
  Type `make` when your working directory is ‘src’
* To compile <program_name>.cpp <br>
  Type `make <program_name>` when your working directory is ‘src’
* To clean the executables <br>
  Type `make clean` when your working directory is ‘src’
* Also make sure your program can be compiled by the command below with no error before proceeding <br>
  `g++ -O2 -std=c++14 -Wall -Wextra <student_id>_project3.cpp`

### Output files
* This program will output the next move to the `action` file
* All steps of the two players will be recorded in `gamelog` file



<!-- USAGE EXAMPLES -->
## How To Test Your Code

* If you use Windows, type the command below in cmd <br>
  `main.exe <AI1>.exe <AI2>.exe`
* If you use Linux / Max, type the command below in terminal <br>
  `./main ./<AI1> ./<AI2>`


## Contact

[![gmail][gmail]][gmail-url]


<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/Lewis-Tsai/Introduction-to-Programming-II-Mini_Project_3.svg?style=for-the-badge
[contributors-url]: https://github.com/Lewis-Tsai/Introduction-to-Programming-II-Mini_Project_3/contributors
[forks-shield]: https://img.shields.io/github/forks/Lewis-Tsai/Introduction-to-Programming-II-Mini_Project_3.svg?style=for-the-badge
[forks-url]: https://github.com/Lewis-Tsai/Introduction-to-Programming-II-Mini_Project_3/network/members
[stars-shield]: https://img.shields.io/github/stars/Lewis-Tsai/Introduction-to-Programming-II-Mini_Project_3.svg?style=for-the-badge
[stars-url]: https://github.com/Lewis-Tsai/Introduction-to-Programming-II-Mini_Project_3/stargazers
[issues-shield]: https://img.shields.io/github/issues/Lewis-Tsai/Introduction-to-Programming-II-Mini_Project_3.svg?style=for-the-badge
[issues-url]: https://github.com/Lewis-Tsai/Introduction-to-Programming-II-Mini_Project_3/issues
[license-shield]: https://img.shields.io/github/license/Lewis-Tsai/Introduction-to-Programming-II-Mini_Project_3.svg?style=for-the-badge
[license-url]: https://github.com/Lewis-Tsai/Introduction-to-Programming-II-Mini_Project_3/blob/master/license
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/lewis-tsai-7b570421a
[product-screenshot]: images/screenshot.png

[gmail]: https://img.shields.io/badge/Gmail-D14836?style=for-the-badge&logo=gmail&logoColor=white
[gmail-url]: mailto:A38050787@gmail.com
