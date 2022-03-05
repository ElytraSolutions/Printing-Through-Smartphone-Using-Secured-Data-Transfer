#include <iostream>
#include <Windows.h>

#define rSize 57
#define MODE 2
#define Size rSize*rSize

void DisplayFormattedBits(uint16_t c) {

	std::string Temp = "";

	for (int Index = 10; Index >= 0; Index--) {
	
		Temp += (c & (0b1 << Index)) ? '1' : '0';
	
	}

	std::cout << Temp;

}

std::string FormattedBitsString(size_t c) {

	std::string Temp = "";

	for (int Index = 10; Index >= 0; Index--) {

		Temp += (c & (0b1 << Index)) ? '1' : '0';

	}

	return Temp;

}

unsigned char GetAlphaNumericValue(unsigned char Data) {
	if (Data > 96 && Data < 123) {

		Data -= 32;

	}

	switch (Data) {
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	case 'A': return 10;
	case 'B': return 11;
	case 'C': return 12;
	case 'D': return 13;
	case 'E': return 14;
	case 'F': return 15;
	case 'G': return 16;
	case 'H': return 17;
	case 'I': return 18;
	case 'J': return 19;
	case 'K': return 20;
	case 'L': return 21;
	case 'M': return 22;
	case 'N': return 23;
	case 'O': return 24;
	case 'P': return 25;
	case 'Q': return 26;
	case 'R': return 27;
	case 'S': return 28;
	case 'T': return 29;
	case 'U': return 30;
	case 'V': return 31;
	case 'W': return 32;
	case 'X': return 33;
	case 'Y': return 34;
	case 'Z': return 35;
	case ' ': return 36;
	case '$': return 37;
	case '%': return 38;
	case '*': return 39;
	case '+': return 40;
	case '-': return 41;
	case '.': return 42;
	case '/': return 43;
	case ':': return 44;
	default:
		return 0;
	}

}


//std::string FormatMsgEncode(unsigned char* Msg, size_t Length) {
//
//	std::string Output = "";
//
//	size_t FormattedLength = Length;
//
//	if (Length & 1) {
//
//		FormattedLength++;
//
//	}
//
//	size_t* FormattedMsg = (size_t*)malloc(FormattedLength / 2);
//
//	if (FormattedMsg == NULL) {
//
//		::exit(-1);
//
//	}
//
//	memset(FormattedMsg, 0, FormattedLength);
//
//	size_t Temp = Length;
//
//	if (Length & 1) {
//
//		Length--;
//
//	}
//
//	for (size_t Index = 0; Index < Length; Index++) {
//
//		if (Index & 1) {
//
//			FormattedMsg[static_cast<size_t>(floor((float)Index / 2))] = (FormattedMsg[Index / 2] + GetAlphaNumericValue(Msg[Index])) & 0b11111111111; //Converting Into 11-bit 
//
//		}
//		else {
//
//			FormattedMsg[Index / 2] = (GetAlphaNumericValue(Msg[Index]) * 45);
//
//		}
//
//	}
//
//	Length ^= Temp;
//	Temp ^= Length;
//	Length ^= Temp;
//	
//	for (size_t Index = 0; Index < Temp / 2; Index++) {
//
//		Output += FormattedBitsString(FormattedMsg[Index]);
//
//	}
//
//	return Output;
//
//}


std::string FormatMsgEncode(unsigned char* Msg, size_t MsgLength) {

	std::string FormattedMsg = "";

	bool OddMsgLength = false;

	if (MsgLength & 1) {

		OddMsgLength = true;

	}

	unsigned int Temp = UINT32_MAX;

	for (size_t Index = 0; Index < MsgLength; Index++) {

		if (Index & 1) {


			Temp += GetAlphaNumericValue(Msg[Index]);

		}
		else {

			if (Temp != UINT32_MAX) {

				FormattedMsg += FormattedBitsString(Temp & 0x7ff);

			}

			Temp = GetAlphaNumericValue(Msg[Index]) * 45;

		}

	}

	if (OddMsgLength) {

		std::string TempMsg = "";

		char TempChar = GetAlphaNumericValue(Msg[MsgLength - 1]);

		for (char Index = 0; Index < 6; Index++) {

			TempMsg += (TempChar & 0b1 << (5 - Index) ? "1" : "0");

		}

		FormattedMsg += TempMsg;

	}

	MsgLength = FormattedMsg.length();

	while(MsgLength & 7) {

		FormattedMsg += "0";

		MsgLength = FormattedMsg.length();

	}

	MsgLength = FormattedMsg.length();

	std::string AppendByte[2] = { "11101100", "00010001" };

	if ((MsgLength / 8) > 38) { // 38 for Quartile and 49 for Low Error Correction

		//Maximum Data Capacity Reached
		::exit(-38);

	}

	size_t NumOfAppendByte = 38 - (MsgLength / 8); // 38 for Quartile and 49 for Low Error Correction

	for (size_t Index = 0; Index < NumOfAppendByte; Index++) {

		if (Index & 1) {

			FormattedMsg += AppendByte[1];

		}
		else {

			FormattedMsg += AppendByte[0];

		}

	}

	return FormattedMsg;

}

BYTE* PeekByte(BYTE* ByteArray, size_t IndexX, size_t IndexY) {

	return &ByteArray[IndexY * rSize + IndexX];

}


void GeneratePositionBlock(BYTE* ByteArray) {

	for (size_t i = 0; i < 7; i++) {
		*(ByteArray + rSize * 0 + i) = (0b1111111 >> i) & 0b1;
		*(ByteArray + rSize * 1 + i) = (0b1000001 >> i) & 0b1;
		*(ByteArray + rSize * 2 + i) = (0b1011101 >> i) & 0b1;
		*(ByteArray + rSize * 3 + i) = (0b1011101 >> i) & 0b1;
		*(ByteArray + rSize * 4 + i) = (0b1011101 >> i) & 0b1;
		*(ByteArray + rSize * 5 + i) = (0b1000001 >> i) & 0b1;
		*(ByteArray + rSize * 6 + i) = (0b1111111 >> i) & 0b1;
	}

}


void GenerateAlignmentBlock(BYTE* ByteArray) {

	for (size_t i = 0; i < 5; i++) {

		*(ByteArray + rSize * 0 + i) |= (0b1);
		*(ByteArray + rSize * 1 + i) = (0b10001 >> i) & 0b1;
		*(ByteArray + rSize * 2 + i) = (0b10101 >> i) & 0b1;
		*(ByteArray + rSize * 3 + i) = (0b10001 >> i) & 0b1;
		*(ByteArray + rSize * 4 + i) |= (0b1);

	}

}


void GenerateHorizontalTiming(BYTE* ByteArray) {

	for (size_t j = 0; j < rSize; j++) {

		*(ByteArray + rSize * j + 6) |= !(j & 0b1);

	}

}


void GenerateVerticalTiming(BYTE* ByteArray) {

	for (size_t j = 0; j < rSize; j++) {

		*(ByteArray + rSize * 6 + j) |= !(j & 0b1);

	}

}


void FormatQR(BYTE* ByteArray) {

	GenerateHorizontalTiming(ByteArray);
	GenerateVerticalTiming(ByteArray);

	GeneratePositionBlock(ByteArray);

}

void FillEncodedMsg(BYTE* ByteArray, std::string EncodedMsg) {



}

int main() {

	BYTE* ByteArray = (BYTE*)malloc(Size);

	if (ByteArray == NULL) {

		::exit(-1);

	}

	memset(ByteArray, 2, Size);

	unsigned char* Msg = (unsigned char*)"HELLO WORLD";

	size_t CharCount = 11;

	std::string EncodedMsg = FormatMsgEncode(Msg, CharCount);

	FormatQR(ByteArray);

	FillEncodedMsg(ByteArray, EncodedMsg);

	return 0;

}