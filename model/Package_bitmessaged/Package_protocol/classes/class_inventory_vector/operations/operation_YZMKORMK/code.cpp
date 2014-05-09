//~~ bool operator<(const inventory_vector& other) [inventory_vector] ~~
return (memcmp ( data, other.data, sizeof(data) ) < 0);