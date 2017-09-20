#ifndef FUNCTIONS_H
#define FUNCTIONS_H

bool Init();
void Close();
void SetRenderDrawColour( int colour );

void Swap( int &a, int &b )
{
	int aux = a;
	a = b;
	b = a;
}

#endif

