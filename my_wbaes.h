#ifndef MY_WBAES_H_
#define MY_WBAES_H_

// Custom interface to Whitebox Crypto AES (doesn't require Boost or NTL
// which are used internally).

#include <string>

class WBAES;
class WBAESGenerator;
struct _ExtEncoding;

class MyWbAes {
private:
  WBAES* aes_inst;
  WBAESGenerator* generator;
  _ExtEncoding* coding;
  void enc_dec(std::string& data, bool encrypt);
public:
  MyWbAes();
  ~MyWbAes();
  bool load(const std::string& aesTablesFile);
  bool create(const std::string& aesTablesFile, const std::string& keyToUse);
  void encrypt(std::string& data);
  void decrypt(std::string& data);
};



#endif // MY_WBAES_H_
