#pragma once

/**
 * Claudiosoft 2005 - by Claudio Tortorelli
 */

class CBlowFishFileCrypt
{
public:
	CBlowFishFileCrypt(char* FilePath, int keyNum);
	virtual ~CBlowFishFileCrypt(void);

/////// attributes
protected:
	char*		m_FilePath; // file that is the subject of the process
	int			m_keyNum; // index of the key that the process use

/////// methods
public:
	BOOL	DoCrypt(BOOL bOverWrite = FALSE); 
	BOOL	DoDecrypt(BOOL bOverWrite = FALSE);

	void	SetKey(int key){m_keyNum = key;}
	void	SetFilePath(char* path){m_FilePath = path;}

	int		GetKey(){return m_keyNum;}
	char*	GetFilePath(){return m_FilePath;}

private:
	// these methods recall the BlowFish Algorithm
	BOOL	BlowFishCrypt(char* fileName, char* cypher, char* fileEncrypted);
	BOOL	BlowFishDecrypt(char* fileName, char* cypher, char* fileDecrypted);
};
