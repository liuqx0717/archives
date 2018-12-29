# Archives
Some course projects and hobby projects to be archived.

## labyrinth pathfinding
![screenshot](/labyrinth-pathfinding/screenshot.gif)  
Displayed the process of DFS algorithm step by step, using VB .NET for GUI and C++ for algorithm.

## online survey website
![screenshot](/online-survey-website/screenshot1.png)  
![screenshot](/online-survey-website/screenshot2.png)  
![screenshot](/online-survey-website/screenshot3.png)  
![screenshot](/online-survey-website/screenshot4.png)  
Implemented it using HTML/CSS/JavaScript, C#, ASP .NET MVC, SQL Server, which can show
questions and psychology test games one by one with rich animation effects and a modern appearance.  
Deployed on a public server, collected 522 questionnaires for my Summer Social Practice.  

## self-balancing robot
Programmed an STM32F407 board using C++ and PID algorithm with hardware affairs handled by other two teammates.  
Designed a modular and layered structure with driver layer, API layer and user layer, which features anevent-driven model with a message loop. Wrote 4500 lines of C++ code.  
Implemented a Bluetooth client on Windows using C# and WinForms, to control and get/set the parameters of the robot.  

## microcontroller project
A course project for *Microcomputer Lab*.  
Implemented a calculator and many other functions with all the peripherals onboard involved.
Designed an extensible framework for microcontroller C8051F310, which features amodular, layered structure and a non-blocking delay system.  
2000 lines of assembly code in total, including 800 lines of code from another teammate.  

## digital voice changer
![screenshot](/digital-voice-changer/screenshot.png)  
A course project for *Signals and Linear System*.  
Implemented a voice changer with GUI using Matlab, which can convert male voice into female voice.  

## lqxstd
Some useful functions I wrote. For example, an interprocess communication class using shared memory and a locking mechanism whereby multiple readers can access the memory if no writer locked it, and only a single writer can lock the memory. This class also offers a functionality of sending messages asynchronously to multiple listeners.  

## test scores manager
![screenshot](/test-scores-manager/screenshot1.png)  
![screenshot](/test-scores-manager/screenshot2.png)  
A course project for *Software Project*.  
Implemented a GUI program using C# and WinForms, which can display, edit, analyze and store the students’ scores of multiple courses.  

## binEditor
![screenshot](/binEditor/screenshot1.png)  
![screenshot](/binEditor/screenshot2.png)  
A handy tool to manage the patches in executable files.  

## tanchishe
![screenshot](/tanchishe/screenshot.png)  
A simple Snake game.  

## lqxHotkeys
A global hotkeys handler for Windows.  
```
USAGE: lqxHotkeys [command]

command can be any one of the following commands:
/start    starts the application quietly.
/stop     stops the application.
/stop-q   stops the application quietly.

The commands are case-insensitive.
The application will return 1 if an error occurs.",
```

## hookapi
Hook Windows APIs using Detours library.  
ha:    the dll to be injected to other processes.  
ha_c:  the controller.  

## lqxih
Hook Windows APIs using IAT hook.  
