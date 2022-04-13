
-----------------------------------------------------
-----------------------------------------------------

/*
 // Поместить в *.h  файл

#define printf  printfM

#define puts   puts_host

#define putch  (*ff_putch[ComPortHost])

int  printfM(char *format , ...);
*/

-----------------------------------------------------
-----------------------------------------------------


 // Поместить в *.c  файл



int (*ff_putch[5])(int ch)= {ToCom1,ToCom1,ToCom2,ToCom3,ToCom4};


int ComPortHost=4;


int (*ff_putch[5])(int ch)= {ToCom1,ToCom1,ToCom2,ToCom3,ToCom4};

int puts_host(char *str)
{
int i;
 for(i=0;str[i];i++)
 putch(str[i]);
 return i;
}

//-------------------

char BufferPrintf[128];
int  printfM(char *format , ...)
{
  va_list marker;
  va_start( marker, format);
  vsprintf(BufferPrintf, format, marker);
  puts(BufferPrintf);
  return (strlen(BufferPrintf));
}
//-------------------

