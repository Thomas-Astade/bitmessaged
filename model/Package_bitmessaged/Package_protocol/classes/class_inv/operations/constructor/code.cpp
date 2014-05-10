//~~ inv(const Payload& data, unsigned int& index) [inv] ~~
var_int count(data,index);
uint64_t vectorcount = count.getValue();

if (vectorcount > 50000) // an inv  with mrte than 50000 objects is invalid
    return;

while (vectorcount--)
{
    inventory_vector aVector(data,index);
    if (find(aVector) == end())
        insert(aVector);
    else
        duplicateCount++;
}