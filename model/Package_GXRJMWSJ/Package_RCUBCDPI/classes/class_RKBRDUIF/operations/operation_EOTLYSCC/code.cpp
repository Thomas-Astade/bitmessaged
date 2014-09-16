uint64_t h;
char* i = (char*)&value;
char* o = (char*)&h;

o[0] = i[7];
o[1] = i[6];
o[2] = i[5];
o[3] = i[4];
o[4] = i[3];
o[5] = i[2];
o[6] = i[1];
o[7] = i[0];

return h;
