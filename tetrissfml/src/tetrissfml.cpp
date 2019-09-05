#include <iostream>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include<string>



using namespace std;



wstring tetromino[7];
int nFieldWidth = 10;
int nFieldHeight = 21;


int nWindowWidth = 600;
int nWindowHeight = 600;
float nRectSize = 25.0f;

unsigned char* pField = nullptr;

int nScreenWidth = 25;
int nScreenHeight = 30;

int Rotate(int px, int py, int r) {
	switch (r % 4) {
	case 0: return py * 4 + px;
	case 1: return 12 + py - (px * 4);
	case 2: return 15 - (py * 4) - px;
	case 3: return 3 - py + (px * 4);
	}
	return 0;
}

void DrawRectangle(sf::RenderWindow& window, sf::RectangleShape& rectangle, float x, float y, sf::Color color, float nRectSize) {

	rectangle.setSize(sf::Vector2f(nRectSize, nRectSize));
	rectangle.setPosition(x, y);
	rectangle.setFillColor(color);
	window.draw(rectangle);
}


void DrawScene(sf::RenderWindow& window, wchar_t screen[], float nRectSize, sf::RectangleShape& rectangle) {
	for (int px = 0; px < nScreenWidth; px++)
		for (int py = 0; py < nScreenHeight; py++)
			switch (screen[py * nScreenWidth + px])
			{
			case L'#': DrawRectangle(window, rectangle, px * nRectSize - 1, py * nRectSize - 1, sf::Color(40, 80, 156), nRectSize + 1); break;
			case L'A': DrawRectangle(window, rectangle, (px * nRectSize), (py * nRectSize), sf::Color(94, 255, 214), nRectSize - 1); break;
			case L'B': DrawRectangle(window, rectangle, px * nRectSize, py * nRectSize, sf::Color(38, 123, 235), nRectSize - 1); break;
			case L'C': DrawRectangle(window, rectangle, px * nRectSize, py * nRectSize, sf::Color(245, 185, 37), nRectSize - 1); break;
			case L'D': DrawRectangle(window, rectangle, px * nRectSize, py * nRectSize, sf::Color(95, 23, 212), nRectSize - 1); break;
			case L'E': DrawRectangle(window, rectangle, px * nRectSize, py * nRectSize, sf::Color(246, 27, 161), nRectSize - 1); break;
			case L'F': DrawRectangle(window, rectangle, px * nRectSize, py * nRectSize, sf::Color(222, 51, 9), nRectSize - 1); break;
			case L'G': DrawRectangle(window, rectangle, px * nRectSize, py * nRectSize, sf::Color(245, 235, 88), nRectSize - 1); break;
			case L'=': DrawRectangle(window, rectangle, px * nRectSize, py * nRectSize, sf::Color(39, 0, 101), nRectSize - 1); break;
			case L' ': DrawRectangle(window, rectangle, px * nRectSize, py * nRectSize, sf::Color::White, nRectSize - 1); break;
			}
}


bool DoesPieceFit(int nTetromino, int nRotation, int nPosX, int nPosY) {
	for (int px = 0; px < 4; px++)
		for (int py = 0; py < 4; py++)
		{
			int pi = Rotate(px, py, nRotation);
			int fi = (nPosY + py) * nFieldWidth + (nPosX + px);
			if (nPosX + px >= 0 && nPosX + px < nFieldHeight) {
				if (nPosY + py >= 0 && nPosY + py < nFieldHeight) {
					if (tetromino[nTetromino][pi] == L'X' && pField[fi] != 0)
						return false;
				}
			}
		}
	return true;
}


int main()
{
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");

	tetromino[1].append(L"..X.");
	tetromino[1].append(L".XX.");
	tetromino[1].append(L".X..");
	tetromino[1].append(L"....");

	tetromino[2].append(L".X..");
	tetromino[2].append(L".XX.");
	tetromino[2].append(L"..X.");
	tetromino[2].append(L"....");

	tetromino[3].append(L"....");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L"....");

	tetromino[4].append(L"..X.");
	tetromino[4].append(L".XX.");
	tetromino[4].append(L"..X.");
	tetromino[4].append(L"....");

	tetromino[5].append(L"....");
	tetromino[5].append(L".XX.");
	tetromino[5].append(L"..X.");
	tetromino[5].append(L"..X.");

	tetromino[6].append(L"....");
	tetromino[6].append(L".XX.");
	tetromino[6].append(L".X..");
	tetromino[6].append(L".X..");

	// Text
	sf::Font font;
	sf::Text text;
	font.loadFromFile("LexendDeca-Regular.ttf");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setFillColor(sf::Color(40, 80, 160));
	text.setPosition(350, 155);


	sf::Text text1;
	text1.setFont(font);
	text1.setCharacterSize(100);
	text1.setFillColor(sf::Color(40, 80, 160));
	text1.setPosition(130, 200);
	text1.setString("Paused");

	sf::Text text2;
	text2.setFont(font);
	text2.setCharacterSize(70);
	text2.setFillColor(sf::Color(40, 80, 160));
	text2.setPosition(100, 100);
	text2.setString("Game over");

	sf::Text text3;
	text3.setFont(font);
	text3.setCharacterSize(40);
	text3.setFillColor(sf::Color(40, 80, 160));
	text3.setPosition(100, 200);



	//text.setStyle(sf::Text::Bold);
	int nLines = 0;
	int nScore = 0;
	int nLevel = 0;
	int nLinesTemp = 0;






	
	pField = new unsigned char[nFieldWidth * nFieldHeight];
	for (int x = 0; x < nFieldWidth; x++) {
		for (int y = 0; y < nFieldHeight; y++) {
			pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;
		}
	}
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';



	sf::RenderWindow window(sf::VideoMode(nWindowWidth, nWindowHeight), "Tetris", sf::Style::Titlebar | sf::Style::Close);
	sf::RectangleShape rectangle(sf::Vector2f(nRectSize - 1, nRectSize - 1));

	

	int nCurrentPiece = 1;
	int nCurrentRotation = 0;
	int nCurrentX = (nFieldWidth / 2) - 2;
	int nCurrentY = 0;
	//Here




	// random

	srand((unsigned)time(0));
	int i;
	i = (rand() % 7);


	int nNextPiece = i;

	bool bKey[4];
	bool bRotateHold = false;
	bool bYHold = false;
	bool bXLeftHold = false;
	bool bXRightHold = false;


	int nSpeed = 25;
	int nSpeedCounter = 0;
	bool bForseDown = false;
	vector<int> vLines;

	bool bIsPause = false;
	bool bIsGameOver = false;

	string sLines;

	int nMoveSpeed = 9;
	int nMoveCounterR = 0;
	int nMoveCounterL = 0;
	int nMoveCounterD = 0;

	bool bIsRestart = 0;

	while (window.isOpen())
	{
		
		// Random

		srand((unsigned)time(0));
		i = (rand() % 7);

		text.setString("Lines: " + to_string(nLines) + "\nScore: " + to_string(nScore) + "\nLevel: " + to_string(nLevel));
		window.draw(text);



		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					bIsPause = !bIsPause;
				}
				if (event.key.code == sf::Keyboard::R)
				{
					bIsGameOver = 1;
					bIsRestart = 1;
				}
			}
		}

		while (bIsPause) {
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						bIsPause = !bIsPause;
					}				
				}
				if (event.type == sf::Event::Closed)
					window.close();
			}
			window.clear(sf::Color::White);

			window.draw(text1);

			window.display();

		}

		while (bIsGameOver) {
			while (window.pollEvent(event) || bIsRestart) {
				if (event.type == sf::Event::KeyPressed || bIsRestart)
				{
					if (event.key.code == sf::Keyboard::F || bIsRestart)
					{
						nCurrentPiece = 1;
						nCurrentRotation = 0;
						nCurrentX = (nFieldWidth / 2) - 2;
						nCurrentY = 0;
						nNextPiece = i;
						nLines = 0;
						nScore = 0;
						nSpeed = 25;
						nLevel = 0;

						
						// here
						for (int x = 0; x < nFieldWidth; x++) {
							for (int y = 0; y < nFieldHeight; y++) {
								pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;
							}
						}
						for (int i = 0; i < nScreenWidth * nScreenHeight; i++) screen[i] = L' ';

						bIsGameOver = 0;
						if (bIsRestart) break;
					}
				}
				if (event.type == sf::Event::Closed)
					window.close();
			}
			
			if (!bIsRestart) {
				window.clear(sf::Color::White);

				window.draw(text2);
				window.draw(text3);

				window.display();
			}
			bIsRestart = 0;
		}


		// GAME TIMING
		sf::sleep(sf::milliseconds(10));
		nSpeedCounter++;
		bForseDown = (nSpeedCounter == nSpeed);




		for (int k = 0; k < 4; k++)
			bKey[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;





		//bool bYHold = false;
		//bool bXLeftHold = false;
		//bool bXRightHold = false;




		


		if (bKey[1])
		{
			if ((nMoveCounterL == nMoveSpeed) || !bXLeftHold)
			{
				nCurrentX -= (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX - 1, nCurrentY));
				nMoveCounterL = 0;
				bXLeftHold = true;
			}
			else
			{
				nMoveCounterL++;
			}
		}
		else bXLeftHold = false;


		if (bKey[0])
		{
			if ((nMoveCounterR == nMoveSpeed) || !bXRightHold)
			{
				nCurrentX += (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX + 1, nCurrentY));
				nMoveCounterR = 0;
				bXRightHold = true;
			}
			else
			{
				nMoveCounterR++;
			}
		}
		else bXRightHold = false;

		if (bKey[3])
		{
			nCurrentRotation += (!bRotateHold && DoesPieceFit(nCurrentPiece, nCurrentRotation + 1, nCurrentX, nCurrentY));
			bRotateHold = true;

		}
		else bRotateHold = false;

		// Forse down


		if (!bKey[2]) {
			bYHold = false;
		}


		if (bForseDown || (bKey[2]))
		{
			nSpeedCounter = 0;
			if (DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY + 1))
			{
				if (bKey[2])
				{
					if ((nMoveCounterD == 10 - nLevel) || !bYHold) 
					{
						nCurrentY++;
						nMoveCounterD = 0;
						bYHold = true;
					}
					else nMoveCounterD++;
				}
				else {
					nCurrentY++; 
					bYHold = false;
				}
			}	
			else
			{
				
				// Lock the current piece in the field
				for (int px = 0; px < 4; px++)
					for (int py = 0; py < 4; py++)
						if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
							pField[(nCurrentY + py) * nFieldWidth + (nCurrentX + px)] = nCurrentPiece + 1;
				// Check have we got any lines
				for (int py = 0; py < 4; py++)
					if (nCurrentY + py < nFieldHeight - 1)
					{
						bool bLine = true;
						for (int px = 1; px < nFieldWidth - 1; px++)
							bLine &= (pField[(nCurrentY + py) * nFieldWidth + px]) != 0;

						if (bLine)
						{
							for (int px = 1; px < nFieldWidth - 1; px++)
								pField[(nCurrentY + py) * nFieldWidth + px] = 8;
							vLines.push_back(nCurrentY + py);
						}
					}
				// Choose next piece
				nCurrentX = (nFieldWidth / 2) - 2;
				nCurrentY = 0;
				nCurrentRotation = 0;
				nCurrentPiece = nNextPiece;

				nNextPiece = i;

				// Draw next piece

				for (int px = 0; px < 4; px++)
					for (int py = 0; py < 4; py++)
						screen[(py + 2) * nScreenWidth + (px + 13)] = ' ';

				// If piece does not fit
				bIsGameOver = !DoesPieceFit(nCurrentPiece, nCurrentRotation, nCurrentX, nCurrentY);
				if (bIsGameOver)
					text3.setString("Lines: " + to_string(nLines) + "\nScore: " + to_string(nScore) + "\nLevel: " + to_string(nLevel) + "\nPress F to continue");

			}
			
		}
		 



		// RENDER OUTPUT




		// Draw Field
		for (int x = 0; x < nFieldWidth; x++) {
			for (int y = 0; y < nFieldHeight; y++) {
				screen[(y + 2) * nScreenWidth + (x + 2)] = L" ABCDEFG=#"[pField[y * nFieldWidth + x]];
			}
		}

		// Draw Current Piece
		for (int px = 0; px < 4; px++)
			for (int py = 0; py < 4; py++)
				if (tetromino[nCurrentPiece][Rotate(px, py, nCurrentRotation)] == L'X')
					screen[(nCurrentY + py + 2) * nScreenWidth + (nCurrentX + px + 2)] = nCurrentPiece + 65;

		// Draw Next Piece
		for (int px = 0; px < 4; px++)
			for (int py = 0; py < 4; py++)
				if (tetromino[nNextPiece][Rotate(px, py, 0)] == L'X')
					screen[(py + 2) * nScreenWidth + (px + 13)] = nNextPiece + 65;

		if (!vLines.empty())
		{
			//here

			window.clear(sf::Color(255, 255, 255));
			DrawScene(window, screen, nRectSize, rectangle);
			window.draw(text);
			window.display();
			sf::sleep(sf::milliseconds(400));


			for (auto& v : vLines) {
				for (int px = 1; px < nFieldWidth - 1; px++) {
					for (int py = v; py > 0; py--)
						pField[py * nFieldWidth + px] = pField[(py - 1) * nFieldWidth + px];
					pField[px] = 0;
				}
				nLines++;
				nLinesTemp++;
			}
			switch (nLinesTemp) {
			case 1: nScore += 100; break;
			case 2: nScore += 300; break;
			case 3: nScore += 700; break;
			case 4: nScore += 1500; break;
			}
			switch (nLines / 10) {
			case 0: nLevel = 1; nSpeed = 23; break;
			case 1: nLevel = 2; nSpeed = 20; break;
			case 2: nLevel = 3;	nSpeed = 15; break;
			case 3: nLevel = 4; nSpeed = 10; break;
			case 4: nLevel = 5; nSpeed = 5; break;
			case 5: nLevel = 6; bIsGameOver = 1; text2.setString("You won!"); 
				text3.setString("Lines: " + to_string(nLines) + "\nScore: " + to_string(nScore) + "\nLevel: " + to_string(nLevel) + "\nPress F to continue");
				break;

			}
			nLinesTemp = 0;
			vLines.clear();


		}



		// Display Frame
		window.clear(sf::Color(255, 255, 255));
		DrawScene(window, screen, nRectSize, rectangle);
		window.draw(text);

		window.display();
	}
	return 0;
}