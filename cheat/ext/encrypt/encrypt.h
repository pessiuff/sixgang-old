#include "b64.h"
#include "vigenere.h"

namespace encrypt {
	inline std::string encrypt(std::string& msg, std::string& key) {
		std::string b64_str = encrypt_b64::base64_encode(msg);
		std::string vigenere_msg = encrypt_vigenere::encrypt_vigenere(b64_str, key);
		// std::cout << vigenere_msg << std::endl;
		return vigenere_msg;
	}


	inline std::string decrypt(std::string& encrypted_msg, std::string& key) {
		std::string newKey = encrypt_vigenere::extend_key(encrypted_msg, key);
		std::string b64_encoded_str = encrypt_vigenere::decrypt_vigenere(encrypted_msg, newKey);
		std::string b64_decode_str = encrypt_b64::base64_decode(b64_encoded_str);
		return b64_decode_str;
	}
}
