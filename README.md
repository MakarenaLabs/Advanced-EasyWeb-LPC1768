# Advanced EasyWeb for LPC1768, MVC architecture with HTTP URL string interpretation

This is an expansion of EasyWeb example for LPC1768 example project, in order to manage user request, with simple example of authentication and HTML5/CSS3 control page. You can use and compile this project using LPCXpresso.

## HowTo Configure your project
LPCXpresso:
- import project (.cproject and other directory are already created)

LPC1768 Functionality:
- check your pinout and modify "src/lpc1768.c" and "src/main.c" for the right pinout
- "src/lpc1768.c": set function body as your board pinout
- "src/main.c": set LED_NUM macro, led_mask[] variable, line [69, 70] as your board pinout
- "src/tcpip.c": check or set MYIP_1, MYIP_2, MYIP_3, MYIP_4 for lpc1768 IP Address

Example Functionality:
- "src/main.c": set PW as your preferred password
- "src/webside.h": check or modify HTML pages

Test Demo:
- connect your PC via ETH cable and configure your local network in order to comunicate to 192.168.1.123

## HowTo works
The core of this project implements a simple char-by-char interpreter of HTTP GET string passing by browser or other. When a complete message is sent to LPC1768, the "if (SocketStatus & SOCK_DATA_AVAILABLE)" is checked and the message was processed with internal software logic of interpreter ("manage_request()" function). The views is stored in RAM in a char[][] described in "src/Webside.h".

## HowTo use this
You can modify the interpreter simply modifying "manage_request()" body function, and view modifying "src/Webside.h" function.

## Credits
This project belongs to MakarenaLabs and source code was written by Enrico Giordano, distributed as CC BY license.

