#ifndef PILSNG_H
#define PILSNG_H

#include <linux/types.h>
#include <linux/crypto.h>

/* Because array size can't be a const in C, the following two are macros.
   Both sizes are in bytes. */
#define PILSUNG_MAXNR 14
#define PILSUNG_BLOCK_SIZE 16
#define PILSUNG_MIN_KEY_SIZE	16
#define PILSUNG_MAX_KEY_SIZE	32
#define PILSUNG_MAX_KEYLENGTH	(15 * 16)

#ifdef  __cplusplus
extern "C" {
#endif

/* This should be a hidden type, but EVP requires that the size be known */
/*
struct aes_key_st {
    unsigned long rd_key[4 *(PILSUNG_MAXNR + 1)];
    int rounds;
};
typedef struct aes_key_st PILSUNG_KEY;
*/
//-----------------------------------------------------------------------------------
#define f1(x,y,z)	( z ^ (x & (y ^ z) ) )		/* Rounds  0-19 */
#define f2(x,y,z)	( x ^ y ^ z )			/* Rounds 20-39 */
#define f3(x,y,z)	( (x & y) + (z & (x ^ y) ) )	/* Rounds 40-59 */
#define f4(x,y,z)	( x ^ y ^ z )			/* Rounds 60-79 */

#define SHA_BLOCKBYTES	64
#define SHA_BLOCKWORDS	16

#define SHA_HASHWORDS	5
#define	MAX_KEY_BITS	512	/* max number of bits of key */
#define Nr 10  /* counts of encrypt's round. //changed by kch */ 

typedef struct SHAContext {
	unsigned long key[SHA_BLOCKWORDS];
	unsigned long iv[SHA_HASHWORDS];
	unsigned long bytesHi, bytesLo;
} SHAContext;

#define ROTL(n,X)  ( (X << n) | (X >> (32-n)) )

/* FIPS 180.1 */
#define expandx(W,i) (t = W[i&15] ^ W[(i-14)&15] ^ W[(i-8)&15] ^ W[(i-3)&15],  ROTL(1, t))
#define expand(W,i) (W[i&15] = expandx(W,i))
/* Old FIPS 180 */


#define subRound(a, b, c, d, e, f, k, data) \
	( e += ROTL(5,a) + f(b, c, d) + k + data, b = ROTL(30, b) )
#define ClearMemory(buffer, byteCount)		\
		((void)memset((void *)(buffer), '\0', (byteCount)))

static void InitSHA(void *);
static void UpdateSHA(void *, void const *, unsigned int);
static void shaByteSwap(unsigned long *, char const *, unsigned );
void TransformSHA(unsigned long *, unsigned long *);
static void const *FinalSHA(void *);
extern int  zSign(char *Srcfile,char *Destfile,char *Key,int kind);

int cfShaSign( char *src, char *sign, unsigned len,unsigned mode);
/*********** "perm.h"    */

/*-----------------------------------------------------------------------------------*/
#define MAXKC			(256/32)
#define MAXKEYSIZE 256
#define MAXCOUNT 32
#define MAXROUNDS		MAXKEYSIZE / 32 + 6
#define ENCRYPT 0
#define DECRYPT 1
/*-----------------------------------------------------------------------------------*/
typedef struct tag_ktuStr{
	unsigned char *str;
	unsigned int len;
} ktuStr;

typedef struct _PermInfor
{
	unsigned char tmp[32];
	unsigned char Key0;
	unsigned int  round;
	unsigned char VSbox[MAXROUNDS+1][16][256] ;
	unsigned char InvVSbox[MAXROUNDS+1][16][256] ;
	unsigned char VPbox[MAXROUNDS+1][MAXCOUNT] ;
	unsigned char InvVPbox[MAXROUNDS+1][MAXCOUNT] ;
	unsigned char Msk8[8];
	unsigned char PforS[8];
	unsigned char InitP8[8];
	unsigned char InitP16[16];
	unsigned char round_key[MAXROUNDS+1][4][4];	
} PILSUNG_KEY;

struct crypto_pilsung_ctx {
	PILSUNG_KEY  enckey;
	PILSUNG_KEY  deckey;
};

/*
void pilsung_decrypt_one_blk(unsigned char in[16], unsigned char out[16]);
void pilsung_encrypt_one_blk(unsigned char in[16], unsigned char out[16]);
void pilsng_set_key(const unsigned char *userKey, const int bits, const);
*/
void crypto_pilsung_decrypt(struct crypto_tfm *tfm, u8 *out, const u8 *in);
void crypto_pilsung_encrypt(struct crypto_tfm *tfm, u8 *out, const u8 *in);
int crypto_pilsung_set_key(struct crypto_tfm *tfm, const u8 *in_key, unsigned int key_len);

#ifdef  __cplusplus
}
#endif
#endif
