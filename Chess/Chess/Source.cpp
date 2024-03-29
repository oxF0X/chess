/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project,
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include <iostream>
#include <thread>
#include "Board.h"
#include <chrono>


using std::cout;
using std::endl;
using std::string;


void main()
{
	system("Start chessGraphics.exe");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::string map = "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR0";

	Pipe p;
	Board board = Board::getBoard(map);
	bool isConnect = p.connect();
	string ans;
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else
		{
			p.close();
			return;
		}
	}


	char msgToGraphics[1024];

	strcpy_s(msgToGraphics, map.c_str()); // just example...

	p.sendMessageToGraphics(msgToGraphics);   // send the board string

	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();
	std::string code = "";
	while (msgFromGraphics != "quit")
	{

		code = (char)(board.move(msgFromGraphics)) + ZERO_ASCII_CODE;
		strcpy_s(msgToGraphics, code.c_str()); // msgToGraphics should contain the result of the operation
		std::cout << "Code from board: " << code << std::endl;

		// return result to graphics		
		p.sendMessageToGraphics(msgToGraphics);


		// get message from graphics
		msgFromGraphics = p.getMessageFromGraphics();
	}

	p.close();
}