#include "../../framework.h"

//Just print to console.
void GameFramework::PrintNewLineToConsole(int newLineCount) {
	for (int lineIterator = 0; lineIterator < newLineCount; lineIterator++) m_PrintInterface ("\n");
}