#include "mbedtls/aes.h"


void encrypt(char* plainText, char * key, unsigned char * outputBuffer) {
  mbedtls_aes_context aes;

  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_enc(&aes,(const unsigned char*)key,strlen(key)*8);
  mbedtls_aes_crypt_ecb(&aes,MBEDTLS_AES_ENCRYPT, (const unsigned char*)plainText,outputBuffer);
  mbedtls_aes_free(&aes);
}

void decrypt(unsigned char* cipherText, char * key, unsigned char * outputBuffer) {
  mbedtls_aes_context aes;

  mbedtls_aes_init(&aes);
  mbedtls_aes_setkey_dec(&aes,(const unsigned char*)key,strlen(key)*8);
  mbedtls_aes_crypt_ecb(&aes,MBEDTLS_AES_DECRYPT, (const unsigned char*)cipherText,outputBuffer);
  mbedtls_aes_free(&aes);
}


void setup(){
  Serial.begin(115200);
  unsigned char cipheredTextOutput[16];
  unsigned char decipheredTextOutput[16];
  char *texto= "Texto a encriptar";
  char *key="sistemaembebido1";

  encrypt(texto,key,cipheredTextOutput);
  decrypt(cipheredTextOutput,key,decipheredTextOutput);


  Serial.println("Texto cifrado: "  );
  for(int i=0; i<16;i++){
   Serial.print(cipheredTextOutput[i]);
  }
  Serial.println();
  Serial.println("Texto decifrado: "  );
  for(int i=0; i<16;i++){
   Serial.print((char)decipheredTextOutput[i]);
  }
  
}
void loop () {
  
}
