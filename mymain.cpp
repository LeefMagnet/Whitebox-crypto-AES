#include <string>
#include <fstream>
#include "my_wbaes.h"

#define LOGD(...) do { (void)printf(__VA_ARGS__); printf("\n"); } while(0);

static std::string string_to_hex(const std::string& s) {
  std::string res;
  char buff[3];
  for(char c : s) {
    sprintf(buff, "%02X", c);
    res += buff;
  }
  return res;
}

int main(int argc, const char * argv[]) {
  LOGD("mymain");
  MyWbAes wbaes;
  LOGD("wbaes object created");
  std::string aesInstFile = "/data/local/tmp/test_aes_wb/inst1";
  std::ifstream infile(aesInstFile.c_str(),  std::ifstream::ate | std::ios::binary);
  if(infile) {
    LOGD("AES instance size: %ld", (long)infile.tellg());
    infile.close();
    LOGD("Loading AES instance");
    bool ret = wbaes.load(aesInstFile);
    if(!ret) {
      LOGD("Failed to load AES instance");
      return -1;
    }
    LOGD("AES instance loaded!");
  }
  else {
    LOGD("Creating AES instance");
     std::string randKey = "1234567890123456";
     bool ret = wbaes.create(aesInstFile, randKey);
    if(!ret) {
      LOGD("Failed to create AES instance");
      return -1;
    }
    LOGD("AES instance created!");
  }
  LOGD("Encrypt/decrypt test!");
  std::string data = "..my plaintext..";
  LOGD("Plaintext text: %s", string_to_hex(data).c_str());
  wbaes.encrypt(data);
  LOGD("Encrypted text: %s", string_to_hex(data).c_str());
  wbaes.decrypt(data);
  LOGD("Decrypted text: %s", string_to_hex(data).c_str());
  LOGD("Encrypt/decrypt test end");
}
