// Copyright (C) FlatGlobus(wtlbuilder@gmail.com) All rights reserved.
//
// This file is a part of the WTLBuilder.
// The use and distribution terms for this software are covered by the
// Microsoft Public License (http://opensource.org/licenses/MS-PL)
// which can be found in the file MS-PL.txt at the root folder.

#ifndef __MAPFILE_H
#define __MAPFILE_H
//////////////////////////////////////////////////////////////////////////
enum openMode{omRead,omWrite,omCreate,omTemp};
class MapFile
{
public:
    MapFile(DWORD delta=0x0FFFL);
    MapFile(const CString &,DWORD delta=0x0FFFL);
    virtual ~MapFile(void);
    void CopyTo(MapFile & );
    CString FileName(void);
    void Open(const CString &,openMode om,DWORD size=0xFFFFL);
    void Close(void);
    DWORD Length(void);
    void Seek(DWORD offset = 0,short fromWhere = 0);
    DWORD Tell(void);
    int  Eof(void);
    int  Exists(void);
    BOOL IsValid(void);

    void InsertArea(DWORD,PVOID Buf=NULL);
    void RemoveArea(DWORD);
    BYTE  &operator [](DWORD idx);
    CHAR  *Char(DWORD idx);
    short *Short(DWORD idx);
    int   *Int(DWORD idx);
    long  *Long(DWORD idx);
    float *Float(DWORD idx);
    double*Double(DWORD idx);

    MapFile & operator >>(BYTE &ch);
    MapFile & operator >>(signed short &ch);
    MapFile & operator >>(unsigned short &ch);
    MapFile & operator >>(signed int &ch);
    MapFile & operator >>(unsigned int &ch);
    MapFile & operator >>(signed long &ch);
    MapFile & operator >>(unsigned long &ch);
    MapFile & operator >>(float &ch);
    MapFile & operator >>(double &ch);
    MapFile & operator <<(BYTE ch);
    MapFile & operator <<(signed short &ch);
    MapFile & operator <<(unsigned short &ch);
    MapFile & operator <<(signed int ch);
    MapFile & operator <<(unsigned int ch);
    MapFile & operator <<(signed long ch);
    MapFile & operator <<(unsigned long ch);
    MapFile & operator <<(float ch);
    MapFile & operator <<(double ch);
    MapFile & operator <<(LPTSTR ch);
    MapFile & operator >>(LPTSTR&ch);

    BYTE GetByte(void);
    void PutByte(BYTE ch);
    void PutWord(short ch);
    short GetWord(void);
    void GetBuffer(void *,DWORD);
    void PutBuffer(void *,DWORD);
    PVOID buff(void){return Buffer;}
protected:
    HANDLE    OpenFile(LPTSTR,openMode,DWORD);
    PVOID     MapViewOfFile(HANDLE,openMode,DWORD);
    HANDLE    CreateFileMapping(HANDLE,openMode,DWORD &);
    HANDLE    CreateFile(LPCTSTR,openMode);

    void      reSize(DWORD);
    void      reSizeWithCopy(DWORD);
    void      reSizeNoCopy(DWORD);

    openMode  OpenMode;
    HANDLE    hFile,hFileMap;
    CString   path;
    PVOID     Buffer;
    DWORD      CP;
    DWORD      Delta;
    DWORD      Size;
    DWORD      Limit;
    BOOL      kakDela;
};
//////////////////////////////////////////////////////////////////////////
inline BYTE &MapFile::operator [](DWORD idx)
{
    return *((BYTE*)Buffer+idx);
}
inline CHAR * MapFile::Char(DWORD idx)
{
    return ((CHAR *)Buffer+idx);
}
inline short * MapFile::Short(DWORD idx)
{
    return (short *)((CHAR *)Buffer+idx);
}
inline int *MapFile::Int(DWORD idx)
{
    return (int *)((CHAR *)Buffer+idx);
}
inline long *MapFile::Long(DWORD idx)
{
    return (long *)((CHAR *)Buffer+idx);
}
inline float *MapFile::Float(DWORD idx)
{
    return (float *)((CHAR *)Buffer+idx);
}
inline double *MapFile::Double(DWORD idx)
{
    return (double *)((CHAR *)Buffer+idx);
}
inline BYTE MapFile::GetByte(void)
{
    BYTE ch=*Char(CP);
    CP+=sizeof(BYTE);
    return ch;
}
inline void MapFile::PutByte(BYTE ch)
{
    PutBuffer((void *)&ch,1);
}
inline void MapFile::PutWord(short ch)
{
    PutBuffer((void *)&ch,2);
}
inline short MapFile::GetWord(void)
{
    short ch=*Short(CP);
    CP+=sizeof(short);
    return ch;
}
inline MapFile & MapFile::operator >>(BYTE &ch)
{
    ch=(BYTE)GetByte();
    return *this;
}
inline MapFile & MapFile::operator >>(signed short &ch)
{
    ch=(signed short)GetWord();
    return *this;
}
inline MapFile & MapFile::operator >>(unsigned short &ch)
{
    ch=(unsigned short)GetWord();
    return *this;
}
inline MapFile & MapFile::operator >>(signed int &ch)
{
    ch=*Int(CP);
    CP+=sizeof(int);
    return *this;
}
inline MapFile & MapFile::operator >>(unsigned int &ch)
{
    ch=*Int(CP);
    CP+=sizeof(int);
    return *this;
}
inline MapFile & MapFile::operator >>(signed long &ch)
{
    ch=*Long(CP);
    CP+=sizeof(long);
    return *this;
}
inline MapFile & MapFile::operator >>(unsigned long &ch)
{
    ch=*Long(CP);
    CP+=sizeof(long);
    return *this;
}
inline MapFile & MapFile::operator >>(float &ch)
{
    ch=*Float(CP);
    CP+=sizeof(float);
    return *this;
}
inline MapFile & MapFile::operator >>(double &ch)
{
    ch=*Double(CP);
    CP+=sizeof(double);
    return *this;
}
inline MapFile & MapFile::operator <<(BYTE ch)
{
    PutByte(ch);
    return *this;
}
inline MapFile & MapFile::operator <<(signed short &ch)
{
    PutWord(ch);
    return *this;
}
inline MapFile & MapFile::operator <<(unsigned short &ch)
{
    PutWord(ch);
    return *this;
}
inline MapFile & MapFile::operator <<(signed int ch)
{
    PutBuffer((void *)&ch,sizeof(signed int));
    return *this;
}
inline MapFile & MapFile::operator <<(unsigned int ch)
{
    PutBuffer((void *)&ch,sizeof(unsigned int));
    return *this;
}
inline MapFile & MapFile::operator <<(signed long ch)
{
    PutBuffer((void *)&ch,sizeof(long));
    return *this;
}
inline MapFile & MapFile::operator <<(unsigned long ch)
{
    PutBuffer((void *)&ch,sizeof(long));
    return *this;
}
inline MapFile & MapFile::operator <<(float ch)
{
    PutBuffer((void *)&ch,sizeof(float));
    return *this;
}
inline MapFile & MapFile::operator <<(double ch)
{
    PutBuffer((void *)&ch,sizeof(double));
    return *this;
}
inline void MapFile::InsertArea(DWORD sizeArea,PVOID item)
{
    if(!kakDela)
        return;
    if(Size+sizeArea > Limit)
        reSize(Limit-(CP+sizeArea));

    MoveMemory((LPTSTR)Buffer+CP+sizeArea,(LPTSTR)Buffer+CP,Size-CP);
    Size+=sizeArea;

    if(item)
        MoveMemory((LPTSTR)Buffer+CP,(LPTSTR)item,sizeArea);
}

inline void MapFile::RemoveArea(DWORD sizeArea)
{
    if(!kakDela)
        return;
    if(sizeArea < Size)
    {
        MoveMemory((LPTSTR)Buffer+CP,(LPTSTR)Buffer+CP+sizeArea,Size-CP-sizeArea);
        Size-=sizeArea;
    }
}
inline void MapFile::GetBuffer(void *Buf,DWORD Count)
{
    if(!kakDela)
        return;
    DWORD ACP=CP+Count;
    if(ACP <= Size)
    {
        MoveMemory(Buf,(LPTSTR)Buffer+CP,Count);
        CP=ACP;
    }
}
inline void MapFile::PutBuffer(void *Buf,DWORD Count)
{
    if(!kakDela)
        return;
    DWORD ACP=CP+Count;
    if(ACP > Limit)
        reSize(Count < Delta ? Delta : Count+Delta);

    if(ACP > Size)
        Size=ACP;
    MoveMemory((LPTSTR)Buffer+CP,Buf,Count);
    CP=ACP;
}


inline CString MapFile::FileName(void)
{
    return path;
}

inline BOOL MapFile::IsValid(void)
{                                 
    return kakDela==TRUE && hFile!=NULL;
}
//////////////////////////////////////////////////////////////////////////

#endif
