#ifndef UTILITY_H
#define UTILITY_H

/*
 * 函数说明：3DES加密
 * 参数1：明文(就是891位的RSA私钥)
 * 参数2：密文保存的绝对路径(保存16进制数)
 * 返回值: 0:成功 -1:失败
 */
int D3DesEncrypt(unsigned char *pszIn, const char *pszPath);

/*
 * 函数说明：3DES解密
 * 参数1：密文保存的绝对路径
 * 参数2：明文
 * 返回值: 0:成功 -1:失败
 */
int D3DesDecrypt(const char *pszPath, unsigned char *pszOut);

#endif
