#include<iostream>
#include <iomanip>
#include "Constants.h"

using std::cin;
using std::cout;
using std::endl;

void fillInstructionArr(int instructionArr[]);
bool validWord(int instruction);
bool executeInstruction(int instructionArr[], int numArr[], int instruction, int& accumulator, int& operationCode, int& location);
void instructionArrDump(int Arr[], int accumulator, int instructionCounter, int instructionRegister, int operationCode, int location);
void numArrDump(int Arr[]);
void print(const char* name, int num, int value, bool sign);
int readCommand(int num);
int readLocation(int num);

int main() {

	int instructionArr[INSTRUCTION_SIZE] = { 0 };
	int  numArr[NUMARR_SIZE] = { 0 };

	int accumulator = 0;
	int instructionRegister = 0;
	int instructionCounter = 0;

	int operationCode = 0;
	int location = 0;

	fillInstructionArr(instructionArr);

	for (instructionCounter = 0; instructionCounter < INSTRUCTION_SIZE; instructionCounter++, operationCode, location) {

	    instructionRegister = instructionArr[instructionCounter];
		
		if (!executeInstruction(instructionArr, numArr, instructionRegister, accumulator, operationCode, location)) {

			cout << "\n*** END SIMPLETRON EXECUTION  ***\n";
			break;
		}
	}

	instructionArrDump(instructionArr, accumulator, instructionCounter, instructionRegister, operationCode, location);
	numArrDump(numArr);

	return 0;
}

void fillInstructionArr(int instructionArr[]) {

	cout << "***   Welcome to Simpletron!  *** \n\n"
		<< "*** Please enter your program one instruction *** \n "
		<< "*** (or data word) at a time. I will type the *** \n "
		<< "*** location number and a question mark (?).  ***  \n "
		<< "*** You then type the word for that location. *** \n "
		<< "*** Type the sentinel -99999 to stop entering *** \n "
		<< "*** your program. *** \n\n"
		<< "00 ? ";

	int instruction;
	cin >> instruction;

	int i = 0;
	while (instruction != SENTINEL) {

		if (!validWord(instruction)) {

			cout << "Invalid instruction. Please enter a valid one : ";
		}
		else {
			instructionArr[i] = instruction;
			i++;
		}
		cout << std::setw(2) << std::setfill('0') << i << " ? ";
		cin >> instruction;

	}

	cout << "*** Program loading completed *** \n"
		 << "*** Program execution begins *** \n\n ";

}

bool validWord(int instruction) {

	return instruction >= MIN_WORD && instruction <= MAX_WORD;
}

bool executeInstruction(int instructionArr[], int numArr[], int instruction, int& accumulator, int& operationCode, int& location) {

    operationCode = readCommand(instruction);

	location = readLocation(instruction);

	bool fatal = false;
	int isValid;
	int number;  // used in case : EXPONENTIATION , SUM , AVERAGE
	int sum;  // used in case : SUM , AVERAGE
	int howManyNumbers; 
	int numbers[100];  // used in case : LARGEST_NUMBER
	int max; // used in case : LARGEST_NUMBER

	switch (operationCode) {

	case READ:

		cout << "Enter a number: ";
		cin >> numArr[location];

		while (!validWord(numArr[location])) {

			cout << "Invalid number. Please enter again: ";
			cin >> numArr[location];
		}
		break;


	case WRITE:

		cout << "Content of " << std::setw(2) << std::setfill('0') << location << ": " << numArr[location] << endl;
		break;


	case LOAD:

		accumulator = numArr[location];
		break;


	case STORE:

		numArr[location] = accumulator;
		break;


	case ADD:

		isValid = accumulator + numArr[location];
		if (!validWord(isValid)) {

			cout << "*** FATAL ERROR: Accumulator overflow! *** \n";
			fatal = true;
		}
		else {
			accumulator = isValid;
		}
		break;


	case SUBTRACT:

		isValid = accumulator - numArr[location];
		if (!validWord(isValid)) {

			cout << "*** FATAL ERROR: Accumulator overflow! *** \n";
			fatal = true;
		}
		else {
			accumulator = isValid;
		}
		break;


	case DIVIDE:

		if (numArr[location] == 0) {

			cout << "*** FATAL ERROR: Attempt to divide by zero. *** \n ";
			fatal = true;
		}
		else {
			accumulator = accumulator / numArr[location];
		}
		break;


	case MULTIPLY:

		isValid = accumulator * numArr[location];
		if (!validWord(isValid)) {

			cout << "*** FATAL ERROR: Accumulator overflow! *** \n";
			fatal = true;
		}
		else {
			accumulator = isValid;
		}
		break;


	case SUM:

		sum = 0;
		cout << "How many numbers you want to sum: " ;

		cin >> howManyNumbers;

		for (int i = 0; i < howManyNumbers; i++) {

			cout << "number: ";
			cin >> number;
			if (number < 0) {
				return 1;
			}
			sum += number;
		}
		numArr[location] = sum;
		break;


	case AVERAGE:

		sum = 0;
		cout << "Enter your 7 numbers: \n";

		for (int i = 0; i < 7; i++) {

			cout << "number: ";
			cin >> number;
			sum += number;
		}

		numArr[location] = sum / 7;
		break;


	case LARGEST_NUMBER:

		cout << "Among how meny numbers you want to see the largest one: \n";
		cin >> howManyNumbers;

		for (int i = 0; i < howManyNumbers; i++) {

			cout << "number: ";
			cin >> numbers[i];
		}

		max = numbers[0];
		for (int i = 0; i < howManyNumbers; i++) {

			if (max < numbers[i]) {

				max = numbers[i];
			}

		}
		numArr[location] = max;
		break;


	case MODUL:

		if (accumulator < 0) {

			accumulator = accumulator * -1;
		}
		break;


	case EXPONENTIATION:

		number = 1;
		for (int i = 0; i < numArr[location]; i++) {

			number = number * accumulator;
		}
		accumulator = number;
		break;


	case BRANCH:

		return executeInstruction(instructionArr, numArr, instructionArr[location], accumulator, operationCode, location);


	case BRANCHNEG:

		if (accumulator < 0) {

			return executeInstruction(instructionArr, numArr, instructionArr[location], accumulator, operationCode, location);
		}
		break;


	case BRANCHZERO:

		if (accumulator == 0) {

			return executeInstruction(instructionArr, numArr, instructionArr[location], accumulator, operationCode, location);
		}
		break;


	case HALT:

		cout << "*** Simpletron execution terminated ***\n";
		return false;


	default:
		cout << " *** FATAL ERROR: Invalid operation code detected! *** \n";
		return false;
	}


	if (fatal == true) {

		return false;
	}
	else {
		return true;
	}
}

void instructionArrDump(int Arr[], int accumulator, int instructionCounter, int instructionRegister, int operationCode, int location) {

	cout << " \n REGISTERS: \n";
	print("accumulator", 5, accumulator, true);
	print("instructionCounter", 2, instructionCounter, false);
	print("instructionRegister", 5, instructionRegister, true);
	print("operationCode", 2, operationCode, false);
	print("operand", 2, location, false);

	cout << " \n INSTRUCTION MEMORY : \n";
	cout << std::setfill(' ') << std::setw(3) << ' ';
	
	for (int i = 0; i <= 9; i++) {

		cout << std::setw(5) << i << ' ';
	}

	for (int i = 0; i < INSTRUCTION_SIZE; i++) {

		if (i % 10 == 0) {
			cout << '\n' << std::setw(3) << std::setfill('0') << i << ' ';
		}

		cout << std::setiosflags(std::ios::internal | std::ios::showpos)
			<< std::setw(5) << std::setfill('0') << Arr[i] << ' '
			<< std::resetiosflags(std::ios::internal | std::ios::showpos);
	}
	cout << std::endl;
}

void numArrDump(int Arr[]) {

	cout << " \n  MEMORY : \n";
	cout << std::setfill(' ') << std::setw(3) << ' ';

	for (int i = 0; i <= 9; i++) {

		cout << std::setw(5) << i << ' ';
	}

	for (int i = 0; i < INSTRUCTION_SIZE; i++) {

		if (i % 10 == 0) {
			cout << '\n' << std::setw(3) << std::setfill('0') << i << ' ';
		}

		cout << std::setiosflags(std::ios::internal | std::ios::showpos)
			<< std::setw(5) << std::setfill('0') << Arr[i] << ' '
			<< std::resetiosflags(std::ios::internal | std::ios::showpos);
	}
	cout << std::endl;

}

void print(const char* name, int num, int value, bool sign) {

	cout << std::setfill(' ') << std::setiosflags(std::ios::left) << std::setw(20) << name << ' ';

	if (sign) {
		cout << std::setiosflags(std::ios::showpos | std::ios::internal);
	}

	cout << std::setfill('0') << std::internal;

	if (num == 5) {
		cout << std::setw(num) << value << std::endl;
	}
	else {
		cout << std::setfill(' ') << std::setw(3) << ' ' << std::setw(num) << std::setfill('0') << value << std::endl;
	}

	if (sign) {
		cout << std::resetiosflags(std::ios::showpos | std::ios::internal);
	}

}

int readCommand(int num) {  // get first two digits

	return num / 100;
}

int readLocation(int num) {  //get last two digits

	return num % 100;
}

