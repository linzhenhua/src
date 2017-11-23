/* d3des.h - 
 * 
 *  Headers and defines for d3des.c 
 *  Graven Imagery, 1992. 
 * 
 * Copyright (c) 1988,1989,1990,1991,1992 by Richard Outerbridge 
 *  (GEnie : OUTER; CIS : [71755,204]) 
 */  
  
#define D2_DES      /* include double-length support */  
#define D3_DES      /* include triple-length support */  
  
#ifdef D3_DES  
#ifndef D2_DES  
#define D2_DES      /* D2_DES is needed for D3_DES */  
#endif  
#endif  
  
#define EN0 0   /* MODE == encrypt */  
#define DE1 1   /* MODE == decrypt */  
  
/* A useful alias on 68000-ish machines, but NOT USED HERE. */  
  
typedef union {  
    unsigned long blok[2];  
    unsigned short word[4];  
    unsigned char byte[8];  
    } M68K;  
  
extern void deskey(unsigned char *, short);  
/*            hexkey[8]     MODE 
 * Sets the internal key register according to the hexadecimal 
 * key contained in the 8 bytes of hexkey, according to the DES, 
 * for encryption or decryption according to MODE. 
 */
/*
* Sets the internal key register according to the hexadecimal 
根据十六进制设置内部密钥寄存器
 * key contained in the 8 bytes of hexkey, according to the DES, 
根据DES的数据，密钥包含在8个字节的密钥中，
 * for encryption or decryption according to MODE.
按照模式进行加密或解密。
*/ 
  
extern void usekey(unsigned long *);  
/*          cookedkey[32] 
 * Loads the internal key register with the data in cookedkey. 
 */  
/*
Loads the internal key register with the data in cookedkey.
加载内部密钥寄存器，并在关键字中使用数据。
*/ 
  
extern void cpkey(unsigned long *);  
/*         cookedkey[32] 
 * Copies the contents of the internal key register into the storage 
 * located at &cookedkey[0]. 
 */  
/*
* Copies the contents of the internal key register into the storage 
将内部密钥寄存器的内容复制到存储器中
 * located at &cookedkey[0].
*位于&cookedkey[0]。
*/ 
  
extern void des(unsigned char *, unsigned char *);  
/*          from[8]       to[8] 
 * Encrypts/Decrypts (according to the key currently loaded in the 
 * internal key register) one block of eight bytes at address 'from' 
 * into the block at address 'to'.  They can be the same. 
 */  
/*
* Encrypts/Decrypts (according to the key currently loaded in the 
加密/解密(根据当前载入的密钥
 * internal key register) one block of eight bytes at address 'from' 
内部密钥寄存器)一个8个字节的地址“来自”
 * into the block at address 'to'.
在地址'to'的block中。
*/ 
 
#ifdef D2_DES  
  
#define desDkey(a,b)    des2key((a),(b))  
extern void des2key(unsigned char *, short);  
/*            hexkey[16]     MODE 
 * Sets the internal key registerS according to the hexadecimal 
 * keyS contained in the 16 bytes of hexkey, according to the DES, 
 * for DOUBLE encryption or decryption according to MODE. 
 * NOTE: this clobbers all three key registers! 
 */  
 /*
 * Sets the internal key registerS according to the hexadecimal 
根据十六进制设置内部密钥寄存器
 * keyS contained in the 16 bytes of hexkey, according to the DES, 
根据DES的数据，键包含在16个字节的十六进制中，
 * for DOUBLE encryption or decryption according to MODE. 
按模式进行双加密或解密。
 */ 
  
extern void Ddes(unsigned char *, unsigned char *);  
/*          from[8]       to[8] 
 * Encrypts/Decrypts (according to the keyS currently loaded in the 
 * internal key registerS) one block of eight bytes at address 'from' 
 * into the block at address 'to'.  They can be the same. 
 */  
/*
* Encrypts/Decrypts (according to the keyS currently loaded in the 
加密/解密(根据当前载入的密钥
 * internal key registerS) one block of eight bytes at address 'from' 
内部密钥寄存器)一个8字节的地址“来自”
 * into the block at address 'to'.
在地址'to'的block中。
*/ 

extern void D2des(unsigned char *, unsigned char *);  
/*          from[16]          to[16] 
 * Encrypts/Decrypts (according to the keyS currently loaded in the 
 * internal key registerS) one block of SIXTEEN bytes at address 'from' 
 * into the block at address 'to'.  They can be the same. 
 */  
/*
* Encrypts/Decrypts (according to the keyS currently loaded in the 
加密/解密(根据当前载入的密钥
 * internal key registerS) one block of SIXTEEN bytes at address 'from' 
内部密钥寄存器)在地址'从'中一个16字节的块
 * into the block at address 'to'.
在地址'to'的block中。
 They can be the same.
它们可以是一样的。
*/ 
 
extern void makekey(char *, unsigned char *);  
/*      *password,  single-length key[8] 
 * With a double-length default key, this routine hashes a NULL-terminated 
 * string into an eight-byte random-looking key, suitable for use with the 
 * deskey() routine. 
 */  
/*
* With a double-length default key, this routine hashes a NULL-terminated 
使用一个双长度的默认密钥，这个例程将一个null终止
 * string into an eight-byte random-looking key, suitable for use with the 
将字符串串成一个8字节的随机字符，适合于使用
 * deskey() routine.
* deskey()例程。
*/ 
 
#define makeDkey(a,b)   make2key((a),(b))  
extern void make2key(char *, unsigned char *);  
/*      *password,  double-length key[16] 
 * With a double-length default key, this routine hashes a NULL-terminated 
 * string into a sixteen-byte random-looking key, suitable for use with the 
 * des2key() routine. 
 */  
/*
* With a double-length default key, this routine hashes a NULL-terminated 
使用一个双长度的默认密钥，这个例程将一个null终止
 * string into a sixteen-byte random-looking key, suitable for use with the 
将一个16字节的随机字符串成字符串，适合于使用
 * des2key() routine.
* des2key()例程。
*/ 
 
#ifndef D3_DES  /* D2_DES only */  
  
#define useDkey(a)  use2key((a))  
#define cpDkey(a)   cp2key((a))  
  
extern void use2key(unsigned long *);  
/*          cookedkey[64] 
 * Loads the internal key registerS with the data in cookedkey. 
 * NOTE: this clobbers all three key registers! 
 */  
 /*
 * Loads the internal key registerS with the data in cookedkey. 
在关键字中加载内部键寄存器。
 * NOTE: this clobbers all three key registers!
注意:这破坏了所有三个关键寄存器！
 */ 
  
extern void cp2key(unsigned long *);  
/*         cookedkey[64] 
 * Copies the contents of the internal key registerS into the storage 
 * located at &cookedkey[0]. 
 */  
 /*
 * Copies the contents of the internal key registerS into the storage 
将内部密钥寄存器的内容复制到存储器中
 * located at &cookedkey[0].
*位于&cookedkey[0]。
 */ 
  
#else   /* D3_DES too */  
  
#define useDkey(a)  use3key((a))  
#define cpDkey(a)   cp3key((a))  
  
extern void des3key(unsigned char *, short);  
/*            hexkey[24]     MODE 
 * Sets the internal key registerS according to the hexadecimal 
 * keyS contained in the 24 bytes of hexkey, according to the DES, 
 * for DOUBLE encryption or decryption according to MODE. 
 */  
 /*
 * Sets the internal key registerS according to the hexadecimal 
根据十六进制设置内部密钥寄存器
 * keyS contained in the 24 bytes of hexkey, according to the DES, 
根据DES的数据，密钥包含在24字节的密钥中，
 * for DOUBLE encryption or decryption according to MODE.
按模式进行双加密或解密。
 */ 
  
extern void use3key(unsigned long *);  
/*          cookedkey[96] 
 * Loads the 3 internal key registerS with the data in cookedkey. 
 */  
/*
* Loads the 3 internal key registerS with the data in cookedkey.
加载三个内部密钥寄存器，其中的数据是在库克密钥中进行的。
*/  

extern void cp3key(unsigned long *);  
/*         cookedkey[96] 
 * Copies the contents of the 3 internal key registerS into the storage 
 * located at &cookedkey[0]. 
 */  
/*
* Copies the contents of the 3 internal key registerS into the storage 
将3个内部密钥寄存器的内容复制到存储器中
 * located at &cookedkey[0].
*位于&cookedkey[0]。
*/ 
 
extern void make3key(char *, unsigned char *);  
/*      *password,  triple-length key[24] 
 * With a triple-length default key, this routine hashes a NULL-terminated 
 * string into a twenty-four-byte random-looking key, suitable for use with 
 * the des3key() routine. 
 */  
/*
* With a triple-length default key, this routine hashes a NULL-terminated 
使用一个三倍的默认密钥，这个例程将一个null终止
 * string into a twenty-four-byte random-looking key, suitable for use with 
将字符串转换成一个24字节的随机键，适合于使用
 * the des3key() routine.
* des3key()例程。
*/ 
#endif  /* D3_DES */  
#endif  /* D2_DES */  
  
/* d3des.h V5.09 rwo 9208.04 15:06 Graven Imagery 
 ********************************************************************/ 
