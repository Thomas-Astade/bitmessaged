#include <string.h>
#include <netinet/in.h>

char comand_defines [][16] = {
    {"\xE9\xBE\xB4\xD9""version\x00\x00\x00\x00"},
    {"\xE9\xBE\xB4\xD9""verack\x00\x00\x00\x00\x00"},
    {"\xE9\xBE\xB4\xD9""addr\x00\x00\x00\x00\x00\x00\x00"},
    {"\xE9\xBE\xB4\xD9""inv\x00\x00\x00\x00\x00\x00\x00\x00"},
    {"\xE9\xBE\xB4\xD9""getdata\x00\x00\x00\x00"},
    {"\xE9\xBE\xB4\xD9""getpubkey\x00\x00"},
    {"\xE9\xBE\xB4\xD9""pubkey\x00\x00\x00\x00\x00"},
    {"\xE9\xBE\xB4\xD9""msg\x00\x00\x00\x00\x00\x00\x00\x00"},
    {"\xE9\xBE\xB4\xD9""broadcast\x00\x00"},
    {"\xE9\xBE\xB4\xD9""object\x00\x00\x00\x00\x00"},
    };
