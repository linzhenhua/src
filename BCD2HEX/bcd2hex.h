#ifndef EBC2HEX_H
#define EBC2HEX_H

unsigned char asccharebc( char codeA );

char ebccharasc( unsigned char codeE );

void AscToEbc(char *pszData, int nLen);

void EbcToAsc(char *pszEbc, char *pszAsc, int nLen);

#endif
