//~~ void dump() [Payload] ~~
const void* mem = operator*();
unsigned int len = size();
unsigned int i, j;
const unsigned int columns = 16;

if (len > 160)
    len = 160;

for(i = 0; i < len + ((len % columns) ? (columns - len % columns) : 0); i++)
{
    /* print offset */
    if(i % columns == 0)
    {
        printf("0x%06x: ", i);
    }

    /* print hex data */
    if(i < len)
    {
        printf("%02x ", 0xFF & ((char*)mem)[i]);
    }
    else /* end of block, just aligning for ASCII dump */
    {
        printf("   ");
    }

    /* print ASCII dump */
    if(i % columns == (columns - 1))
    {
        for(j = i - (columns - 1); j <= i; j++)
        {
            if(j >= len) /* end of block, not really printing */
            {
                putchar(' ');
            }
            else if(isprint(((char*)mem)[j])) /* printable char */
            {
                putchar(0xFF & ((char*)mem)[j]);        
            }
            else /* other char */
            {
                putchar('.');
            }
        }
        putchar('\n');
    }
}

if (len < size())
{
    printf("... %d additional bytes ...\n",size()-len);
}

