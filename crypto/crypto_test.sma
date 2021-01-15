#include <amxmodx>
#include <crypto>

public plugin_init() {
	register_clcmd("say /crypto", "cmdCrypto");
	register_srvcmd("crypto", "cmdCrypto2");
}

public cmdCrypto(id) {
	new iHash[256];
	new iSuccess = crypto_hash("base64", "Test", iHash);
	
	if(iSuccess == 0)
		client_print(id, print_chat, "Success: %s", iHash);
	else
		client_print(id, print_chat, "No Success: %d", iSuccess);
}

public cmdCrypto2(id) {
	new iHash[256];
	new iSuccess = crypto_hash("base64", "Test", iHash);
	
	if(iSuccess == 0)
		server_print("Success: %s", iHash);
	else
		server_print("No Success: %d", iSuccess);
}