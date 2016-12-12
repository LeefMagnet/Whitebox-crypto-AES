#include "my_wbaes.h"

// TODO: use secure string
#include "WBAESGenerator.h"
#include "WBAES.h"

MyWbAes::MyWbAes() : aes_inst(nullptr), generator(new WBAESGenerator),
		     coding(new _ExtEncoding){
  generator->generateExtEncoding(coding, WBAESGEN_EXTGEN_ID/*useExternal ? 0 : WBAESGEN_EXTGEN_ID*/);
}

MyWbAes::~MyWbAes() {
  if(aes_inst) {
    delete aes_inst;
    aes_inst = nullptr;
  }
  if(generator) {
    delete generator;
    generator = nullptr;
  }
  if(coding) {
    delete coding;
    coding = nullptr;
  }
}

bool MyWbAes::load(const std::string& aesTablesFile) {
  int ret = true;
  if(aes_inst) {
    delete aes_inst;
    aes_inst = nullptr;
  }
  try {
    aes_inst = new WBAES;
    int temp_ret = generator->load(aesTablesFile.c_str(), aes_inst, coding);
    if(temp_ret) {
      ret = false;
    }
  }
  catch(const std::exception& ex) {
    if(aes_inst) {
      delete aes_inst;
      aes_inst = nullptr;
    }
    ret = false;
  }
  return ret;
}

bool MyWbAes::create(const std::string& aesTablesFile, const std::string& keyToUse) {
  bool ret = true;
  if(aes_inst) {
    delete aes_inst;
    aes_inst = nullptr;
  }
  try {
    aes_inst = new WBAES;
    generator->generateTables((unsigned char*)keyToUse.data(), KEY_SIZE_16, aes_inst, coding, true);
    generator->generateTables((unsigned char*)keyToUse.data(), KEY_SIZE_16, aes_inst, coding, false);
    int temp_ret = generator->save(aesTablesFile.c_str(), aes_inst, coding);
    if(temp_ret) {
      ret = false;
    }
  }
  catch(const std::exception& ex) {
    if(aes_inst) {
      delete aes_inst;
      aes_inst = nullptr;
    }
    ret = false;
  }
  return ret;
}
void MyWbAes::encrypt(std::string& data) {
  enc_dec(data, true);
}
void MyWbAes::decrypt(std::string& data) {
  enc_dec(data, false);
}


void MyWbAes::enc_dec(std::string& data, bool encrypt) {
  if(data.length() != 16) {
    return;
  }
  W128b state;
  arr_to_W128b(data.data(), 0, state);
  if(encrypt) {
    aes_inst->encrypt(state);
  }
  else {
    aes_inst->decrypt(state);
  }
  W128b_to_str(data, 0, state);
}
