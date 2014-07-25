//
//	�R�E�r���h�p�p���T[������5��]��EDstudio�phtml�ɕϊ�����
//	Borland C++ 5.5�p
//
//	�g����
//		CobuildConv DataDir [-w]
//		-w ... WordBank
//
//	��
//		CobuildConv "C:\Program Files\Collins COBUILD\Cobuild Dictionary 2006\data" 
//		CobuildConv "C:\Program Files\Collins COBUILD\Cobuild Dictionary 2006\data" -w
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char	buff1[2048];
char	buff2[2048];
char	htmtxt[2048];
char	title[256];	// ���o��
char	variation[256];	// �ω��`
char	phonetic[256];	// �����L��
char	syntax[512];	// �\��
char	hyphen[256];	// ����
char	note[256];	// ����
char	subtitle[512];	// �����o��
char	subno[512];	// �����o���ԍ�
char	hinshi[512];	// �i��
char	explain[256];	// �����o���̐���
char	alternative[256];	// ���L����
char	work[1024];

int	DataNum;
int	DummyInt;
int	IndexBaseNum;

int		Base[4800];	// �C���f�b�N�X�E�x�[�X�E�e�[�u��
unsigned short	Offset[40000];	// �C���f�b�N�X�E�I�t�Z�b�g�E�e�[�u��
int		OffsetNum;	// �x�[�X������̃I�t�Z�b�g�̐�


class cHead{
public:
	char	Copyright[64];
	char	Dumy1[16];
	int	DataNum;
	int	Dumy2;
	int	IndexBaseNum;
	int	IndexOffsetNum;
	int	Dumy3;
	int	IndexPos;
	int	DataPos;
	int	Dumy4;
	char	Dumy[16];
};

class cTable{
public:
	int		Code;
	const char	*Plain;
};

cHead	Head;
cTable 	CTable[] = {
	// �p������
	1, "a",	2, "b",	3, "c", 4, "d",	5, "e", 6, "f", 7, "g", 8, "h", 9, "i",
	10, "j", 11, "k", 12, "l", 13, "m", 14, "n",
	15, "o", 16, "p", 17, "q", 18, "r", 19, "s", 
	20, "t", 21, "u", 22, "v", 23, "w", 24, "x",
	25, "y", 26, "z",
	// �L��
	32, " ", 33, ".", 34, "<", 35, ">",
	36, ",", 37, ";", 38, "-",
	0, "NORMAL"
};

// *** �L�� ***
cTable	SyTable[] = {
	4, "&sect;",
	9, "'",
	10, "\"",
	11, "\"",
	12, "�",
	13, "-",
	14, "--",
	15, "&trade;",
	18, "&cent;",
	19, "&pound;",
	24, "&copy;",
	28, "&reg;",
	29, "&deg;",
	30, "�}",
	31, "&sup2;",
	32, "&sup3;",
	35, "�E" ,
	36, "&sup1;",
	40, "&frac12;",
	43, "&times;",
	44, "&divide;",
	0, "SYMBOL"
};

// *** ����L�� ***
cTable	SpTable[] = {
	1, "!",
	2, "\"",
	3, "#",
	4, "$",
	5, "%",
	6, "&amp;",
	7, "'",
	8, "(",
	9, ")",
	10, "*",
	11, "+",
	15, "/",
	16, "0", 17, "1", 18, "2", 19, "3", 20, "4", 21, "5", 22, "6", 23, "7", 24, "8", 25, "9",
	26, ":", 27, ";",
	28, "&lt;",
	29, "=",
	30, "&gt",
	31, "?",
	32, "@",
	33, "[",
	34, "\\",
	35, "]",
	36, "^",
	37, "_",
	38, "`",
	39, "{",
	40, "|",
	41, "}",
	42, "~",
	43, "��",		// ��
	0, "SPECIAL"
};

cTable	GrTable[] = {
	1, "&agrave;",
	5, "&egrave;",
	9, "&igrave;",
	32, "&Agrave;",
	36, "&Egrave;",
	40, "&Igrave;",
	0, "GRAVE"
};

cTable	AcTable[] = {
	1, "&aacute;",
	5, "&eacute;",
	9, "&iacute;",
	15, "&oacute;",
	22, "&uacute;",
	32, "&Aacute;",
	36, "&Eacute;",
	40, "&Iacute;",
	46, "&Oacute;",
	52, "&Uacute;",
	0, "ACUTE"
};

cTable	CiTable[] = {
	1, "&acirc;",
	2, "",
	5, "&ecirc;",
	9, "&icirc;",
	15, "&ocirc;",
	21, "&ucirc;",
	25, "&ycirc;",
	32, "&Acirc;",
	36, "&Ecirc;",
	52, "&Ucirc;",
	0, "CIRC"
};

// *** tilde ***
cTable	TiTable[] = {
	1, "&atilde;",
	14, "&ntilde",
	15, "&otilde",
	32, "&Atilde;",
	45, "&Ntilde",
	46, "&Otilde",
	0, "TILDE"
};

// *** umlaut ***
cTable	UmTable[] = {
	1, "&auml;",
	9, "&iuml;",
	15, "&ouml;",
	21, "&uuml;",
	32, "&Auml;",
	40, "&Iuml;",
	46, "&Ouml;",
	52, "&Uuml;",
	0, "UML"
};

cTable	LaTable[] = {
	1, "&aring;",
	5, "&ecaron;",
	15, "&ouml;",
	32, "&Aring;",
	36, "&Ecaron;",
	0, "LATIN"
};

cTable	La2Table[] = {
	50, " S",
	0, "LATIN2"
};

cTable	CeTable[] = {
	3, "&ccedil;",
	34, "&CCEDIL;",
	0, "CEDIL"
};

cTable	SlTable[] = {
	15, "&oslash;",
	46, "&Oslash;",
	0, "SLASH"
};

cTable	ElTable[] = {
	1, "&aelig;",
	15, "&oelig;",
	32, "&Aelig;",
	46, "&Oelig;",
	0, "ELIG"
};

cTable	GkTable[] = {
	13, "��",
	16, "��",
	22, "��",
	53, "��",
	0, "GREEK"
};

// *** UNICODE ***
cTable	UnTable[] = {
	0x0259, "&#x0259;",	// schwa
	0x2070, "<sup>0</sup>",
	0x2074, "<sup>4</sup>",
	0x2075, "<sup>5</sup>",
	0x2079, "<sup>9</sup>",
	0x2153, "&xFrac13;",
	0x2192, "��",
	0x2283, "��",		// ��
	0x25a0, "��",
	0x25a1, "��",
	0x25b2, "��",
	0x25ba, "&#x25BA",
	0x2605, "��",
	0x260e, "��", 		// ��
	0x2660, "&spades;",
	0x2663, "&clubs;",
	0x2665, "&hearts;",
	0x2666, "&diams;",
	0x266D, "��",
	0x266F, "��",
	0x2726,	"&#x2726",
	0x3003, "�V",
	0, "UNICODE"
};

// *** �����L�� ***
cTable	PhTable[] = {
	' ', " ", '/', "/", '-', "-", '<', "<",
	'>', ">", ';', ";", 
	'~', "",		// ???
	'%', ",",
	'a', "a", 'b', "b", 'd', "d", 'e', "e",
	'f', "f", 'g', "g", 'h', "h", 'i', "i",
	'j', "j", 'k', "k", 'l', "l", 'm', "m",
	'n', "n", 'o', "o", 'p', "p", 'r', "r",
	's', "s", 't', "t", 'u', "u", 'v', "v",
	'w', "w", 'x', "x", 'z', "z",
	':', "&#x02D0;",	// Triangular Colon
	'{', "&aelig;",		// ae
	'@', "&#x0259;",	// Schwa
	'A', "&#x0251;",	// Alpha
	'D', "&eth;",		// Eth
	'I', "&#x026A;",	// Capital I
	'N', "&#x014B;",	// Eng
	'O', "&#x0254;",	// Open O
	'Q', "&#x0252;",	// Turned Alpha
	'S', "&#x0283;",	// Esh
	'T', "&#x03b8;",	// Theta
	'U', "&#x028A;",	// Upsilon
	'V', "&#x028C;",	// Turned V
	'Z', "&#x0292;",	// Ezh
	'3', "&#x025c;",	// Open E
	0, "PHONETIC"
};

// �P������������
char *
DecodeChar( int c, char *p, cTable *Table ){
	int	i;
	const char	*s;

	i = 0;
	while( Table[i].Code != 0 ){
		if ( Table[i].Code == c ){
			s = Table[i].Plain;
			while( *s ){
				*p++ = *s++;
			}
			goto L0;
		}
		i++;
	}
L0:
	return p;
}

//
//	����
//
int
decode( FILE *fp )
{
	unsigned char	c1, c2, c3, c4;
	unsigned char	d;
	char 		*p, *q, *r;
	const char	*s;
	unsigned int	ucode;
	int		i, n;
	int		accent;

	
	/* 6bit���ɕ����� */
	p = buff1;
	for(;;){
		c1 = fgetc( fp );
		d = ( c1 >> 2 ) & 0x3f;
		*p++ = d;
		if ( d == 0 ) break;
	
		c2 = fgetc( fp );
		d = (( c1 << 4 ) & 0x30) | (( c2 >> 4 ) & 0x0f);
		*p++ = d;
		if ( d == 0 ) break;
		
		c3 = fgetc( fp );
		d = (( c2 << 2 ) & 0x3c) | (( c3 >> 6 ) & 0x03);
		*p++ = d;
		if ( d == 0 ) break;
	
		d= c3 & 0x3f;
		*p++ = d;
		if ( d == 0 ) break;
	}
	*p = 0;
	
	/* �����ɕϊ����� */
	p = buff1;
	q = buff2;
	while( *p ){
		if ( *p < 40 ){
			/* �p�������E�ʏ�L�� */
			q = DecodeChar( *p, q, CTable );
		} else if ( *p == 40 ){
			/* grave */
			p++;
			q = DecodeChar( *p, q, GrTable );
		} else if ( *p == 41 ){
			/* acute */
			p++;
			q = DecodeChar( *p, q, AcTable );
		} else if ( *p == 42 ){
			/* circ */
			p++;
			q = DecodeChar( *p, q, CiTable );
		} else if ( *p == 43 ){
			/* tilde */
			p++;
			q = DecodeChar( *p, q, TiTable );
		} else if ( *p == 44 ){
			/* umlaut */
			p++;
			q = DecodeChar( *p, q, UmTable );
		} else if ( *p == 47 ){
			/* Latin */
			p++;
			q = DecodeChar( *p, q, LaTable );
		} else if ( *p == 49 ){
			/* Cedil */
			p++;
			q = DecodeChar( *p, q, CeTable );
		} else if ( *p == 50 ){
			/* Slash */
			p++;
			q = DecodeChar( *p, q, SlTable );
		} else if ( *p == 51 ){
			/* elig */
			p++;
			q = DecodeChar( *p, q, ElTable );
		} else if ( *p == 52 ){
			/* �M���V������ */
			p++;
			q = DecodeChar( *p, q, GkTable );
		} else if ( *p == 58 ){
			/* Latin2 */
			p++;
			q = DecodeChar( *p, q, La2Table );
		} else if ( *p == 59 ){
			/* �L�� */
			p++;
			q = DecodeChar( *p, q, SyTable );
		} else if ( *p == 61 ){
			/* �p�啶�� */
			p++;
			*q++ = 'A' + *p - 32;
		} else if ( *p == 62 ){
			/* ����L�� */
			p++;
			q = DecodeChar( *p, q, SpTable );
		} else if ( *p == 63 ){
			/* UNICODE */
			ucode = ((*(p+1)-1) << 12) + ((*(p+2)-1) << 8) + ((*(p+3)-1) << 4) + (*(p+4)-1);
			p += 4;
			q = DecodeChar( ucode, q, UnTable );
		} 

		p++;
	}
	*q = 0;
	
	/* �^�O��html�`���ɕϊ�����(���̂P) */
	/* ����q�̊O�� */
	p = buff2;
	q = buff1;
	while( *p ){
		if ( *p == '<' ){
			if ( *(p+1) == 'c' ){
				/* ���� */
				n = 0;
				p += 3;
				while( n != 0 || *p != '>' ){
					if ( *p == '<' ) n++;
					if ( *p == '>' ) n--;
					*q++ = *p++;
				}
				p++;
				continue;
			} else
			if ( *(p+1) == 'f' ){
				/* ���H */
				n = 0;
				p += 3;
				while( n != 0 || *p != '>' ){
					if ( *p == '<' ) n++;
					if ( *p == '>' ) n--;
					*q++ = *p++;
				}
				p++;
				continue;
			}
		}	
		*q++ = *p++;
	}
	*q = 0;

	/* �^�O��html�`���ɕϊ�����(���̂Q) */
	/* ����q�̓��� */	
	p = buff1;
	q = buff2;
	while( *p ){
		if ( *p != '<' ){
			*q++ = *p++;
			continue;
		}
		switch( *(p+1) ){
		case 'b':
			/* ���� */
			*q = 0;
			strcat( q, "<b>" );
			q += 3;
			p += 3;
			while( *p != '>' ){
				*q++ = *p++;
			}
			*q = 0;
			strcat( q, "</b>" );
			q += 4;
			p++;
			break;
		case 'e':
			/* ���� */
			*q = 0;
			strcat( q, "<b>" );
			q += 3;
			p += 3;
			while( *p != '>' ){
				*q++ = *p++;
			}
			*q = 0;
			strcat( q, "</b>" );
			q += 4;
			p++;
			break;
		case 'i':
			/* �Α� */
			*q = 0;
			strcat( q, "<i>" );
			q += 3;
			p += 3;
			while( *p != '>' ){
				*q++ = *p++;
			}
			*q = 0;
			strcat( q, "</i>" );
			q += 4;
			p++;
			break;
		case 'g':
			/* ���@�v�f */
			p += 3;
			while( *p != '>' ){
				*q++ = *p++;
			}
			p++;
			break;
		case 'h':
			/* ���ԕ��� */
			*q++ = '�';
			p += 3;
			break;
		case 'm':
			/* �H�H�H */
			p += 3;
			while( *p != '>' ){
				p++;
			}
			p++;
			break;
		case 'n':
			/* AM/STRONG */
			p += 3;
			while( *p != '>' ){
				*q++ = *p++;
			}
			p++;
			break;
		case 'u':
			/* �A���_�[���C�� */
			*q++ = '\'';
			p += 3;
			while( *p != '>' ){
				*q++ = *p++;
			}
			p++;
			break;
		case 'v':
			/* �H�H�H */
			p += 3;
			while( *p != '>' ){
				*q++ = *p++;
			}
			p++;
			break;
		case 'w':
			/* STRONG/WEAK */
			p += 3;
			while( *p != '>' ){
				p++;
			}
			p++;
			break;
		case 'x':
			/* ���ݎQ�� */
			*q = 0;
			strcat( q, "<b>" );
			q += 3;
			p += 3;
			while( *p != '>' ){
				*q++ = *p++;
			}
			*q = 0;
			strcat( q, "</b>" );
			q += 4;
			p++;
			break;
		case 'A':
		case 'B':
			/* �����A�C�R�� */
			p += 3;
			while( *p != '>' ){
				p++;
			}
			p++;
			break;
		case 'E':
			/* ����(�����L��) */
			*q = 0;
			strcat( q, "<sup>" );
			q += 5;
			p += 3;
			while( *p != '>' ){
				*q++ = *p++;
			}
			*q = 0;
			strcat( q, "</sup>" );
			q += 6;
			p++;
			break;
		case 'F':
			/* ��t��(�����L��) */
			*q = 0;
			strcat( q, "<sup>" );
			q += 5;
			p += 3;
			while( *p != '>' ){
				*q++ = *p++;
			}
			*q = 0;
			strcat( q, "</sup>" );
			q += 6;
			p++;
			break;
		case 'S':
			/* �L�� */
			p += 3;
			if ( strncmp( p, "TCdiam", 6 ) == 0 ){
				/* �g�p�p�x�̃_�C�� */
				*q = 0;
				strcat( q, "&#xE000;" );
				q += 8;
			}
			while( *p != '>' ){
				p++;
			}
			p++;
			break;
		case 'q':
			/* �ω��`�H */
		case 'r':
			/* ���o��? */
			p += 3;
			break;
		default:
			*q++ = *p++;
		}
	}
	*q = 0;

	/* �����L����ϊ����� */
	p = buff2;
	q = htmtxt;
	accent = 0;
	while( *p ){
		if ( *p == '<' && *(p+1) == 'p' ){
			n = 0;
			p += 3;
			while( n != 0 || *p != '>' ){
				if ( *p == '<' ) n++;
				else if ( *p == '>' ) n--;
				
				if ( *p == '\'' ){
					// �A�N�Z���g
					p++;
					if ( accent == 0 ){
						*q++ = '\'';
						accent = 2;
					}
					continue;
				} else {
					q = DecodeChar( *p, q, PhTable );
					p++;
				};
				if ( accent ) accent--;
			}
			p++;		// '>'��ǂݔ�΂�
			continue;
		}
		*q++ = *p++;	
	}
	*q = 0;
	
	return 0;
}

//
//	�ω��`�����H����
//
void
EditVariation()
{
	char	*p, *q;
	
	p = variation;
	
	/* �擪�̌��o�������菜�� */
	if ( strncmp( variation, title, strlen( title ) ) == 0 ){
		p += strlen( title );
	}
	
	/* �� */
	while ( *p == ' ' ) p++;
	
	/* �O�ɋl�߂� */
	q = variation;
	while ( *p ){
		if ( *p == ' ' && *(p-1) == ' ' ){
			/* �󔒂��������Ƃ��͂P�ɂ��� */
			p++;
			continue;
		}
		*q++ = *p++;
	}
	*q = 0;
	
	/* �����܂��̋� */
	q--;
	while ( *q == ' ' ) *(q--) = 0;
}

//
//	HTML�ɕϊ�����
//
int
ConvHtml( FILE *fp, FILE *OutFp, int wbk )
{
	int	i, j;
	unsigned char	HonbunNum;
	char	Flg1;
	char	Flg2;
	char	Count;
	char	Dummy1, Dummy2, Dummy3, Dummy4;
	
	int c = fgetc( fp );
	if ( c == EOF ){
		return 0;
	}
	/* �{�����ڐ� */
	HonbunNum = c;
	
	/* ���o�����ڃt���O */
	Flg1 = fgetc( fp );

	/* ������ */
	*variation = 0;
	*phonetic = 0;
	*syntax = 0;
	*hyphen = 0;
	*note = 0;
	if ( Flg1 & 0x01 ){
		/* ���o�� */
		Flg2 = fgetc( fp );
		if ( Flg2 & 0x01 ){
			/* ���o���� */
			decode( fp );
			strcpy( title, htmtxt );
		}
		if ( Flg2 & 0x02 ){
			/* �ٌ` */
			decode( fp );
			strcpy( syntax, htmtxt );
		}
		if ( Flg2 & 0x08 ){
			/* �i�� */
			decode( fp );
		}
		if ( Flg2 & 0x10 ){
			/* �ω��` */
			decode( fp );
			strcpy( variation, htmtxt );
			EditVariation();
		}
		if ( Flg2 & 0x20 ){
			/* �p�@ */
			decode( fp );
		}
		if ( Flg2 & 0x80 ){
			/* ���� */
			decode( fp );
			strcpy( phonetic, htmtxt );
		}
	}
	if ( Flg1 & 0x02 ){
		/* �ǉ��f�[�^ */
		Flg2 = fgetc( fp );
		if ( Flg2 & 0x01 ){
			/* �ʌ��o���ɂ������R */
			decode( fp );
			if ( *syntax ){
				strcat( syntax, "<br>" );
				strcat( syntax, htmtxt );
			} else {
				strcpy( syntax, htmtxt );
			}
		}
		if ( Flg2 & 0x02 ){
			/* �\�� */
			decode( fp );
			if ( *syntax ){
				strcat( syntax, "<br>" );
				strcat( syntax, htmtxt );
			} else {
				strcpy( syntax, htmtxt );
			}
		}
		if ( Flg2 & 0x04 ){
			/* ���� */
			decode( fp );
			strcpy( hyphen, htmtxt );
		}
		if ( Flg2 & 0x08 ){
			/* ���� */
			decode( fp );
			strcpy( note, htmtxt );
		}
		if ( Flg2 & 0x10 ){
			/* �͐ߔԍ� */
			decode( fp );
		}
		if ( Flg2 & 0x20 ){
			/* �p�x */
			Dummy1 = fgetc( fp );
		}
		
	}
	if ( Flg1 & 0x80 ){
		/* �����f�[�^ */
		for(;;){
			Flg2 = fgetc( fp );
			if ( Flg2 == 0 ) break;
			Dummy1 = fgetc( fp );
			Dummy2 = fgetc( fp );
			Dummy3 = fgetc( fp );
		}
	}
	
	/* ���[�h�o���N�łȂ��Ƃ� */
	if ( !wbk ){
		/* ���o�� */
		if ( *hyphen ){
			strcpy( work, hyphen );
		} else {
			strcpy( work, title );
		}
		
		/* �����L�� */
		if ( *phonetic ){
			strcat( work, " " );
			strcat( work, phonetic );
		}

		/* �ω��` */
		if ( *variation ){
			strcat( work, " (" );
			strcat( work, variation );
			strcat( work, ")" );
		}
		
		/* ���� */
		if ( *note ){
			strcat( work, " <sub>" );
			strcat( work, note );
			strcat( work, "</sub>" );
		}
		
		/* ���o�������� */
		fprintf( OutFp, "<dt title=\"%s\">%s</dt>\n", title, work );
		
		/* �����L�[ */
		fprintf( OutFp, "<key type=\"�\�L\">%s</key>\n", title );
		fprintf( OutFp, "<key type=\"�N���X\">%s</key>\n", title );
		
		/* �{���n�� */
		fprintf( OutFp, "<dd>\n" );
		
		/* �\�� */
		if ( *syntax ){
			fprintf( OutFp, "<p>%s</p>\n", syntax );
		}
	}
	
	/* �{�� */
	for ( i = 0; i < HonbunNum; i++ ){
		/* ���� */
		*subtitle = 0;
		*hinshi = 0;
		*subno = 0;
		*explain = 0;
		*alternative = 0;
		/* �{���t���O */
		Flg1 = fgetc( fp );
	
		/* �����o�� */
		if ( Flg1 & 0x01 ){
			subtitle[0] = 0;
			
			Flg2 = fgetc( fp );
			if ( Flg2 & 0x01 ){
				/* ���o�� */
				decode( fp );
				/* �����o���͒�`��Ƃ��� */
				sprintf( subtitle, "<dfn>%s</dfn>", htmtxt );
			}
			if ( Flg2 & 0x02 ){
				/* �ʌ��o�� */
				decode( fp );
				if ( *subtitle ){
					strcat( subtitle, " " );
					strcat( subtitle, htmtxt );
				} else {
					strcpy( subtitle, htmtxt );
				}
			}
			if ( Flg2 & 0x08 ){
				/* �i�� */
				decode( fp );
				sprintf( hinshi, "[%s]", htmtxt );
			}
			if ( Flg2 & 0x10 ){
				/* �ω��` */
				decode( fp );
			}
			if ( Flg2 & 0x20 ){
				/* ���o���S�̂̐��� */
				decode( fp );
				strcpy( explain, htmtxt );
			}
		}
		/* �p�@ */
		if ( Flg1 & 0x02 ){
			Flg2 = fgetc( fp );
			if ( Flg2 & 0x01 ){
				/* ���L���� */
				decode( fp );
				strcpy( alternative, htmtxt );
			}
			if ( Flg2 & 0x02 ){
				/* �ٌ` */
				decode( fp );
			}
			if ( Flg2 & 0x04 ){
				/* ���� */
				decode( fp );
			}
			if ( Flg2 & 0x08 ){
				/* ���� */
				decode( fp );
			}
			if ( Flg2 & 0x10 ){
				/* �p�@ */
				decode( fp );
			}
			if ( Flg2 & 0x20 ){
				/* �H�H */
				Dummy1 = fgetc( fp );
			}
			if ( Flg2 & 0x80 ){
				/* �ԍ��܂��͋L�� */
				decode( fp );
				strcpy( subno, htmtxt );
				if ( strcmp( subno, "@" ) == 0 ){
					strcpy( subno, "�E" );
				}
			}
		}

		/* ���L���������� */
		if ( *alternative ){
			fprintf( OutFp, "<p>%s</p>\n", alternative );
		}
		
		/* �����o�������� */
		if ( *subno ){
			strcpy( work, subno );
		} else {
			*work = 0;
		}
		if ( *subtitle ){
			if ( *work ){
				strcat( work, " " );
			}
			strcat( work, subtitle );
		}
		if ( *hinshi ){
			if ( *work ){
				strcat( work, " " );
			}
			strcat( work, hinshi );
		}
		if ( *explain ){
			if ( *work ){
				strcat( work, " " );
			}
			strcat( work, explain );
		}
		if ( !wbk ){
			fprintf( OutFp, "<p>%s</p>\n", work );
		}
		
		/* 0x04 */
		if ( Flg1 & 0x04 ){
			Flg2 = fgetc( fp );
			decode( fp );
		}
		/* �{�� */
		if ( Flg1 & 0x10 ){
			Flg2 = fgetc( fp );
			if ( Flg2 & 0x01 ){
				/* �Ӗ� */
				decode( fp );
				fprintf( OutFp, "<p>  %s</p>\n", htmtxt );
			}
			if ( Flg2 & 0x02 ){
				/* �ᕶ */
				Count = fgetc( fp );
				for ( j = 0; j < Count; j++ ){
					decode( fp );
					if ( wbk ){
						fprintf( OutFp, "<dt>%s</dt>\n", title );
						fprintf( OutFp, "<dd><p>%s</p></dd>\n", htmtxt );
					} else {
						fprintf( OutFp, "<p>  <i>%s</i></p>\n", htmtxt );
					}
				}
			}
			if ( Flg2 & 0x04 ){
				/* �\ */
			}
			if ( Flg2 & 0x08 ){
				/* �Q�� */
				Count = fgetc( fp );
				for ( j = 0; j < Count; j++ ){
					decode( fp );
				}
			}
			if ( Flg2 & 0x10 ){
				/* �H�H */
				Count = fgetc( fp );
				for ( j = 0; j < Count; j++ ){
					decode( fp );
					fprintf( OutFp, "<p>  <i>%s</i></p>\n", htmtxt );
				}
			}
			if ( Flg2 & 0x40 ){
				/* �Q�� */
				decode( fp );
				fprintf( OutFp, "<p>  %s</p>\n", htmtxt );
			}
		}
		/* �֘A�� */
		if ( Flg1 & 0x40 ){
			Flg2 = fgetc( fp );
			if ( Flg2 & 0x01 ){
				/* ���`�� */
				decode( fp );
				fprintf( OutFp, "<key type=\"����\">%s</key>\n", htmtxt );
				fprintf( OutFp, "<p>  ��%s</p>\n", htmtxt );
			}
			if ( Flg2 & 0x02 ){
				/* ���`�� */
				decode( fp );
				fprintf( OutFp, "<key type=\"����\">%s</key>\n", htmtxt );
				fprintf( OutFp, "<p>  ��%s</p>\n", htmtxt );
			}
		}
		/* �摜 */
		if ( Flg1 & 0x80 ){
			Flg2 = fgetc( fp );
			Dummy1 = fgetc( fp );
			Dummy2 = fgetc( fp );
			Dummy3 = fgetc( fp );
			Dummy4 = fgetc( fp );
		}
	}
	if ( !wbk ){
		fprintf( OutFp, "</dd>\n" );
	}
	
	return 0;
}

int
main( int argc, char *argv[] )
{
	FILE	*fp;
	FILE	*OutFp;
	char	infile[1024];
	char	outfile[16];
	int	wbk;
	int	st;
	int	i, j;

	/* ���� */
	if ( argc > 2 && strcmp( argv[2], "-w" ) == 0 ){
		/* ���[�h�o���N */
		wbk = 1;
		OffsetNum = 4;
	} else {
		/* ���� */
		wbk = 0;
		OffsetNum = 256;
	}
	
	/* ���̓t�@�C�� */
	if ( wbk )
		sprintf( infile, "%s\\hcp_en-wbk.trd", argv[1] );
	else
		sprintf( infile, "%s\\hcp_en-cc5.trd", argv[1] );
	fp = fopen( infile, "rb" );
	if ( fp ==0 ){
		printf( "���̓t�@�C�����I�[�v���ł��Ȃ�\n" );
		return 1;
	}

	/* �o�̓t�@�C�� */
	if ( wbk )
		sprintf( outfile, "wordbank.html" );
	else
		sprintf( outfile, "cobuild.html" );	
	OutFp = fopen( outfile, "w" );
	if ( OutFp ==0 ){
		printf( "�o�̓t�@�C�����I�[�v���ł��Ȃ�\n" );
		return 1;
	}

	/* �w�b�_��ǂ� */
	fread( &Head, sizeof( cHead ), 1, fp );
	
	/* �C���f�b�N�X���փV�[�N */
	fseek( fp, Head.IndexPos, SEEK_SET );
	
	/* �x�[�X�e�[�u����ǂ� */
	for ( i = 0;i < Head.IndexBaseNum; i++ ){
		fread( &Base[i], 4, 1, fp );
	}

	/* �I�t�Z�b�g�e�[�u����ǂ� */
	for ( i = 0;i < Head.IndexBaseNum; i++ ){
		for ( j = 0; j < OffsetNum; j++ ){
			fread( &Offset[i * OffsetNum + j], 2, 1, fp );
		}
	}

	/* �ϊ� */
	fprintf( OutFp, "<html>\n" );
	fprintf( OutFp, "<head>\n" );
	fprintf( OutFp, "<title> Cobuild </title>\n" );
	fprintf( OutFp, "</head>\n" );
	fprintf( OutFp, "<body>\n" );
	fprintf( OutFp, "<dl>\n" );
	for ( i = 0; i < Head.IndexBaseNum; i++ ){
		for ( j = 0; j < OffsetNum; j++ ){
			/* �����܂�? */
			if ( Head.IndexOffsetNum - 1 <= i * OffsetNum + j ) break;
			
			/* �f�[�^���փV�[�N */
			st = fseek( fp, Head.DataPos + Base[i] + Offset[i * OffsetNum + j] * 4, SEEK_SET );
			if ( st ){
				printf( "SEEK ERROR: i=%d j=%d\n", i, j );
			}
			st = ConvHtml( fp, OutFp, wbk );
			if ( st ){
				printf( "CONV ERROR: i=%d j=%d\n", i, j );
			}
		}
	}
	fprintf( OutFp, "</dl>\n" );
	fprintf( OutFp, "</body>\n" );
	fprintf( OutFp, "</html>\n" );
	
	/* ��n�� */
	fclose( fp );
	fclose( OutFp );
}
