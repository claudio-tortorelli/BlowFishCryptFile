#include "stdafx.h"
#include ".\blowfishfilecrypt.h"
#include "BlowFish.h"

////////////////////////////////////////////////////////
#define CRYPT_KEY_NUM	2 // numero chiavi
#define CRYPT_KEY_LEN	16 // multiplo 8

static char matrixKey[CRYPT_KEY_NUM][CRYPT_KEY_LEN];


/** 
 * Init the keys that are used (once at the start)
 */
static void InitKeys()
{
	// keys
	matrixKey[0][0] = 'w';
	matrixKey[0][1] = ',';
	matrixKey[0][2] = 'f';
	matrixKey[0][3] = 'z';
	matrixKey[0][4] = '*';
	matrixKey[0][5] = '3';
	matrixKey[0][6] = 'z';
	matrixKey[0][7] = '?';
	matrixKey[0][8] = 'w';
	matrixKey[0][9] = 'f';
	matrixKey[0][10] = 'j';
	matrixKey[0][11] = 'é';
	matrixKey[0][12] = '§';
	matrixKey[0][13] = '2';
	matrixKey[0][14] = '-';
	matrixKey[0][15] = '\0';// terminatore

	// keys
	matrixKey[1][0] = 'e';
	matrixKey[1][1] = 'f';
	matrixKey[1][2] = ' ';
	matrixKey[1][3] = 'f';
	matrixKey[1][4] = '7';
	matrixKey[1][5] = '3';
	matrixKey[1][6] = '°';
	matrixKey[1][7] = '?';
	matrixKey[1][8] = '^';
	matrixKey[1][9] = 'f';
	matrixKey[1][10] = 'a';
	matrixKey[1][11] = 'x';
	matrixKey[1][12] = 'x';
	matrixKey[1][13] = '6';
	matrixKey[1][14] = '>';
	matrixKey[1][15] = '\0';// terminatore
}
///////////////////////////////////////////////////////////

CBlowFishFileCrypt::CBlowFishFileCrypt(char* FilePath, int keyNum)
{
	InitKeys(); // init keys

	m_FilePath = FilePath;
	m_keyNum = keyNum;	
}

CBlowFishFileCrypt::~CBlowFishFileCrypt(void)
{
}

/**
 * Execute crypting on the file. It use the key that was
 * specified by index. If bOverWrite is TRUE then the result
 * of the crypting process overwrite the original file
 */
BOOL CBlowFishFileCrypt::DoCrypt(BOOL bOverWrite)
{
	if (m_keyNum < 0 || m_keyNum > CRYPT_KEY_NUM)
		return FALSE;

	if (strlen(m_FilePath) == 0)
		return FALSE;

	char cypher[CRYPT_KEY_LEN];
	ZeroMemory(cypher, CRYPT_KEY_LEN*sizeof(char));
	for (int i = 0; i < CRYPT_KEY_LEN; i++)
		cypher[i] = matrixKey[m_keyNum][i];
	
	char fileCPath[4096];
	
	if (!BlowFishCrypt(m_FilePath, cypher, fileCPath))
		return FALSE;

	if (bOverWrite)
	{
		DeleteFile(m_FilePath);
		rename(fileCPath, m_FilePath);
	}
	return TRUE;
}

/**
 * Sfrutta l'algoritmo di criptazione Blowfish per criptare il contenuto di un file
 * in base ad una certa password. Se tale password non viene fornita per il decrypt
 * il file non può essere letto correttamente
 * ---
 * It use Blowfish to crypt a file with current cypher
 */
BOOL CBlowFishFileCrypt::BlowFishCrypt(char* fileName, char* cypher, char* fileEncrypted)
{
	try
	{
		FILE* readFile = fopen(fileName, "rb");
		if (readFile == 0) 
			return FALSE;

		const size_t bufferSize = 1024;
		int barSize = 0;

		// reaching the end of the file and getting position = getting file size (bytes).
		fseek(readFile, 0, SEEK_END);
		barSize = ftell(readFile);
		fseek(readFile, 0, SEEK_SET);
		if (barSize == -1) 
			return FALSE;
		barSize = barSize / bufferSize;

		char outfile[MAX_PATH];

		char ext[8];
		char drive[8];
		char path[4096];
		char fname[4096];
		_splitpath(fileName, drive, path, fname, ext);
		
		// evita sovrascritture
		strcat(fname, "_enc");
		_makepath(outfile, drive, path, fname, ext);
	
		CFileFind ff;
		BOOL bFound = ff.FindFile(outfile);
		int count = 1;
		while (bFound)
		{
			char nextFname[4096];
			sprintf(nextFname, "%s%d", fname, count);
			_makepath(outfile, drive, path, nextFname, ext);
			bFound = ff.FindFile(outfile);
			count++;
		}
		ff.Close();

		fileEncrypted = outfile;

		FILE* writeFile = fopen(outfile, "wb");
		if (writeFile == 0) 
			return FALSE;

		char readBuffer[bufferSize];
		char writeBuffer[bufferSize];
		size_t readRet = 0;

		BlowFishEnc encryption(cypher);

		AfxGetApp()->BeginWaitCursor();

		bool abort = false;
		int encRet;
		while (!feof(readFile))
		{
			readRet = fread(readBuffer, sizeof(char), bufferSize, readFile);

			encRet = encryption.encryptStream(readBuffer, (DWORD)readRet, writeBuffer);

			fwrite(writeBuffer, sizeof(char), encRet, writeFile);
		}

		fflush(writeFile);

		fclose(writeFile);
		fclose(readFile);

		AfxGetApp()->EndWaitCursor();

		ZeroMemory(writeBuffer, bufferSize);
		ZeroMemory(readBuffer, bufferSize);
		
		return TRUE;
	}
	catch (CException* pEx)
	{
		pEx->Delete();
		return FALSE;
	}
}

/**
 * Execute Decrypting on the file. It use the key that was
 * specified by index. If bOverWrite is TRUE then the result
 * of the crypting process overwrite the original file
 */
BOOL CBlowFishFileCrypt::DoDecrypt(BOOL bOverWrite)
{
	char cypher[CRYPT_KEY_LEN];
	ZeroMemory(cypher, CRYPT_KEY_LEN*sizeof(char));
	for (int i = 0; i < CRYPT_KEY_LEN; i++)
		cypher[i] = matrixKey[m_keyNum][i];

	char fileDPath[4096];
	if (!BlowFishDecrypt(m_FilePath, cypher, fileDPath))
		return FALSE;

	if (bOverWrite)
	{
		DeleteFile(m_FilePath);
		rename(fileDPath, m_FilePath);
	}

	return TRUE;
}

BOOL CBlowFishFileCrypt::BlowFishDecrypt(char* fileName, char* cypher, char* fileDecrypted)
{
	try
	{
		FILE* readFile = fopen(fileName, "rb");
		if (readFile == 0) 
			return FALSE;

		const size_t bufferSize = 1024;
		int barSize = 0;

		// reaching the end of the file and getting position = getting file size (bytes).
		fseek(readFile, 0, SEEK_END);
		barSize = ftell(readFile);
		fseek(readFile, 0, SEEK_SET);
		if (barSize == -1) 
			return FALSE;
		barSize = barSize / bufferSize;

		char outfile[MAX_PATH];

		char ext[8];
		char drive[8];
		char path[4096];
		char fname[4096];
		_splitpath(fileName, drive, path, fname, ext);
		strcat(fname, "_dec");
		_makepath(outfile, drive, path, fname, ext);
	
		CFileFind ff;
		BOOL bFound = ff.FindFile(outfile);
		int count = 1;
		while (bFound)
		{
			char nextFname[4096];
			sprintf(nextFname, "%s%d", fname, count);
			_makepath(outfile, drive, path, nextFname, ext);
			bFound = ff.FindFile(outfile);
			count++;
		}
		ff.Close();
		fileDecrypted = outfile;

		FILE* writeFile = fopen(outfile, "wb");
		if (writeFile == 0) 
			return FALSE;

		char readBuffer[bufferSize];
		char writeBuffer[bufferSize];
		size_t readRet = 0;

		BlowFishEnc encryption(cypher);

		AfxGetApp()->BeginWaitCursor();

		bool abort = false;
		int encRet;
		while (!feof(readFile))
		{
			readRet = fread(readBuffer, sizeof(char), bufferSize, readFile);

			encRet = encryption.decryptStream(readBuffer, (DWORD)readRet, writeBuffer);
			if (feof(readFile))
			{
				int pos = 0;
				// removing trailing zeros - encrypted file must be x8 bytes.
				while ((pos < 8) && ((writeBuffer + encRet - pos)[0] == 0)) pos++;
				// if found trailing zeros - decreasing the writing buffer marker (not writing them).
				if (pos) encRet -= (pos - 1);
			}
			fwrite(writeBuffer, sizeof(char), encRet, writeFile);
		}

		fflush(writeFile);

		fclose(writeFile);
		fclose(readFile);

		AfxGetApp()->EndWaitCursor();

		ZeroMemory(writeBuffer, bufferSize);
		ZeroMemory(readBuffer, bufferSize);

		return TRUE;
	}
	catch (CException* pEx)
	{
		pEx->Delete();
		return FALSE;
	}
}
