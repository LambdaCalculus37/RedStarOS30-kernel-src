#ifndef __LINUX_EALD_H
#define __LINUX_EALD_H

/***********************************************************************/
/*
 * (C) Copyright May Juche94(2005) Korean Computer Center
 *	Osandok Information Center 
 *
 * Data Structure for East Asia Language Display on Virtual Console.
 * Possible Double Byte's Locale Code or UTF-8 Code Display
 * Created on May 30.
 */
/**********************************************************************/

struct eald 
{
	char*	name;
	unsigned int font_width;
	unsigned int font_height;
	unsigned char* fontdata;
	
	unsigned short (*to_unicode_from_locale_code)(unsigned short);
	unsigned short (*to_locale_code_from_unicode)(unsigned short);

	int (*identify_locale_code_character)(unsigned short);
	int (*find_font_index)(unsigned short);
};

struct korean_im
{
int	(*AsciiToKorean)(char*, char*, unsigned long*, unsigned short*, int); 
int	(*LoadCodeInfo)(void);
int	(*LoadKbdInfo)(void);
void	(*SetKoreanKeyboard)(int);
};

#endif /* __LINUX_EALD_H */
