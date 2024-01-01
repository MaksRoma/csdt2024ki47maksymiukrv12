#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

int main()
{
	HANDLE hComm;
	hComm = CreateFile(L"COM3",
		GENERIC_READ | GENERIC_WRITE,	// Read/Write Access
		0,										// No Sharing, ports cant be shared
		NULL,									// No Security
		OPEN_EXISTING,						// Open existing port only
		0,										// Non Overlapped I/O
		NULL);								// Null for Comm Devices

	std::cout << "========================================\n";
	std::cout << "Opening serial port: ";
	if (hComm == INVALID_HANDLE_VALUE)
	{
		std::cout << "\nError in opening serial port\n";
		return 1;
	}
	else
	{
		std::cout << "successfully!\n";
	}

	DCB dcbSerialParams = { 0 }; // Initializing DCB structure
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	std::cout << "Getting device state: ";
	if (!GetCommState(hComm, &dcbSerialParams))
	{
		std::cout << "\nError in getting device state\n";
		CloseHandle(hComm);
		return 2;
	}
	else
	{
		std::cout << "successfully!\n";
	}
	dcbSerialParams.BaudRate = CBR_115200;		// Setting BaudRate = 115200
	dcbSerialParams.ByteSize = 8;					// Setting ByteSize = 8
	dcbSerialParams.StopBits = ONE5STOPBITS;	// Setting StopBits = 1
	dcbSerialParams.Parity = NOPARITY;			// Setting Parity = None

	SetCommState(hComm, &dcbSerialParams);

	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	std::cout << "Setting timeouts: ";
	if (!SetCommTimeouts(hComm, &timeouts))
	{
		std::cout << "\nError in setting timeouts\n";
		CloseHandle(hComm);
		return 3;
	}
	else
	{
		std::cout << "successfully!\n";
	}

	// Writing data to COM Port
	std::ifstream file("test.txt", std::ios::in | std::ios::binary);

	std::cout << "Opening file: ";
	if (!file.is_open())
	{
		std::cout << "\nError in opening file\n";
		CloseHandle(hComm);
		return 4;
	}
	else
	{
		std::cout << "successfully!\n";
	}
	std::cout << "========================================\n";

	char ch;
	DWORD bytes_written = 0;
	while (file.get(ch))
	{
		WriteFile(hComm, &ch, sizeof(ch), &bytes_written, NULL);
	}

	file.close();

	// Reading data from COM Port
	char read_buffer[1024];
	memset(&read_buffer, '\0', sizeof(read_buffer));
	DWORD bytes_read = 0;
	if (!ReadFile(hComm, &read_buffer, sizeof(read_buffer) - 1, &bytes_read, NULL))
	{
		std::cout << "\nError in reading data\n";
		CloseHandle(hComm);
		return 5;
	}
	else
	{
		read_buffer[bytes_read] = '\0'; // set end of string so we can printf
		std::cout << "Received: " << read_buffer << "\n";
		std::cout << "Bytes read: " << bytes_read << "\n";
	}

	return 0;
}