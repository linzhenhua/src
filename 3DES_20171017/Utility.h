#ifndef UTILITY_H
#define UTILITY_H

/* 
 * 函数说明：3DES加密
 * 参数1：明文
 * 参数2：密文保存的绝对路径 
 * 返回值: 0:成功 -1:失败 
 */  
int DesEncrypt(unsigned char *pszSrc, const char *pszPath);

/* 
 * 函数说明：3DES解密
 * 参数1：密文保存的绝对路径
 * 参数2：明文 
 * 返回值: 0:成功 -1:失败 
 */  
int DesDecrypt(const char *pszPath, unsigned char *pszDest);

#endif
