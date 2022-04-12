#pragma once
#include "GameServerMessage.h"
#include "ContentsEnum.h"
#include "ContentsStruct.h"

class SignInResultMessage : public GameServerMessage                    
{                                                               
public:                                                         
	ESignInResultType m_SignInResultType;
	int m_UserIdx;
                                                                
public:                                                         
    SignInResultMessage()                                               
        : GameServerMessage(EMessageType::SignInResult)                    
        , m_SignInResultType()
        , m_UserIdx()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~SignInResultMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(m_SignInResultType) + DataSizeCheck(m_UserIdx);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer<<static_cast<int>(m_SignInResultType);
        _Serializer << m_UserIdx;

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        int temp ;		
        _Serializer>>temp;
        m_SignInResultType = static_cast<ESignInResultType>(temp); 
        _Serializer >> m_UserIdx;

    }                                                           
};                                                              

class ServerDestroyMessage : public GameServerMessage                    
{                                                               
public:                                                         
                                                                
public:                                                         
    ServerDestroyMessage()                                               
        : GameServerMessage(EMessageType::ServerDestroy)                    
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~ServerDestroyMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return 0;    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            

    }                                                           
};                                                              

class SignUpResultMessage : public GameServerMessage                    
{                                                               
public:                                                         
	ESignUpResultType m_SignUpResultType;
                                                                
public:                                                         
    SignUpResultMessage()                                               
        : GameServerMessage(EMessageType::SignUpResult)                    
        , m_SignUpResultType()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~SignUpResultMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(m_SignUpResultType);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer<<static_cast<int>(m_SignUpResultType);

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        int temp ;		
        _Serializer>>temp;
        m_SignUpResultType = static_cast<ESignUpResultType>(temp); 

    }                                                           
};                                                              

class ReplyCharacterInfoMessage : public GameServerMessage                    
{                                                               
public:                                                         
	std::vector<FCharacterInfo> m_CharacterInfoList;
                                                                
public:                                                         
    ReplyCharacterInfoMessage()                                               
        : GameServerMessage(EMessageType::ReplyCharacterInfo)                    
        , m_CharacterInfoList()
    {                                                           
                                                                
    }                                                           
                                                                
    virtual ~ReplyCharacterInfoMessage() {}                                   
                                                                
    virtual int SizeCheck()                                     
    {                                                           
		return DataSizeCheck(m_CharacterInfoList);
    }                                                           
                                                                
    void Serialize(GameServerSerializer& _Serializer)           
    {                                                           
        GameServerMessage::Serialize(_Serializer);              
        _Serializer.WriteVector( m_CharacterInfoList);

    }                                                           
                                                                
    void DeSerialize(GameServerSerializer& _Serializer)         
    {                                                           
        GameServerMessage::DeSerialize(_Serializer);            
        _Serializer.ReadVector( m_CharacterInfoList);

    }                                                           
};                                                              

