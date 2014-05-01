#include <netinet/in.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "var_int.h"
#include "var_str.h"

#define VECTOR (std::tr1::shared_ptr<std::vector<uint8_t> >::operator*())